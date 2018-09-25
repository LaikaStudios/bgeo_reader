
/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
#include <vector>

#include <UT/UT_JSONParser.h>
#include <UT/UT_IStream.h>

#include "bgeo/parser/Detail.h"
#include "bgeo/parser/ReadError.h"
#include "bgeo/parser/Primitive.h"
#include "bgeo/parser/Run.h"
#include "bgeo/parser/Volume.h"
namespace parser = ika::bgeo::parser;

int check_filename(const std::string& filename)
{
    size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos)
    {
        std::cerr << "Filename [" << filename << "] missing extension.\n";
        return 1;
    }

    std::string extension = filename.substr(pos + 1);
    if (extension != "bgeo" && extension != "geo" &&
        #if HVERSION_MAJOR >= 15
            extension != "sc" &&
        #endif // HVERSION_MAJOR > 15
            extension != "gz")
    {
        std::cerr << "Unsupported file extension [" << extension << "]\n";
        return 1;
    }

    return 0;
}

int check_geometry(const parser::Detail& detail)
{
    for (int64 i = 0; i < detail.primitives.getCount(); ++i)
    {
        auto primitive = detail.primitives.getPrimitive(i);

        // check for supported primitive type.
        if (primitive->getType() == parser::Primitive::UnknownType)
        {
            std::cerr << "Primitive " << i << ": Unsupported primitive type.\n";
            return 1;
        }

        // check for valid volume voxel count
        if (primitive->getType() == parser::Primitive::VolumeType)
        {
            auto volume = static_cast<const parser::Volume*>(primitive);

            // NOTE: prevent crashing with large voxel counts due to katana bug
            // when count is > 2^32-1 = 4294967295
            // prman has a similar limit, though based on signed 32-bit int
            // which is 2^31-1 =  2147483647
            //  REMOVE ME if both limits are corrected.

            if (volume->getNumVoxels() > 2147483647)
            {
                std::cerr << "Primitive " << i
                          << ": Voxel count [" << volume->getNumVoxels()
                          << "] too high for prman.\n";
                return 1;
            }

            // now check for valid voxel float data in the volume
            std::vector<float> voxels;
            parser::Volume::extractVoxelData(*volume, voxels);

            for (auto voxel : voxels)
            {
                if (std::isnan(voxel))
                {
                    std::cerr << "Primitive " << i
                              << ": NaN detected in voxel data.\n";
                    return 1;
                }

                if (std::isinf(voxel))
                {
                    std::cerr << "Primitive " << i
                              << ": Infinite value detected in voxel data.\n";
                    return 1;
                }

                if (voxel < 0.0f)
                {
                    std::cerr << "Primitive " << i
                              << ": Negative value detected in voxel data.\n";
                    return 1;
                }
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Must supply .bgeo file as only argument.\n";
        return 1;
    }

    parser::Detail detail;

    int result = check_filename(argv[1]);
    if (result != 0)
    {
        return result;
    }

    {
        UT_IFStream stream(argv[1], UT_ISTREAM_BINARY);
        if (stream.isError())
        {
            std::cerr << "Unable to read file: " << argv[1] << "\n";
            return 1;
        }
        UT_AutoJSONParser parserLoader(stream);
        UT_JSONParser parser = parserLoader.parser();
        try
        {
            detail.loadGeometry(parser);
        }
        catch (const parser::ReadError& e)
        {
            std::cerr << "Parse error: " << e.what() << "\n";
            return 1;
        }
    }

    return check_geometry(detail);
}
