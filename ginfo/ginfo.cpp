
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
#include <memory>

#include <vector>

#include <hboost/timer.hpp>

#include <UT/UT_JSONParser.h>
#include <UT/UT_IStream.h>

#include "bgeo/parser/Detail.h"
#include "bgeo/parser/compression.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Must supply .bgeo file as only argument" << std::endl;
        return 1;
    }

    ika::bgeo::parser::Detail detail;
    double elapsed = 0;

    // NOTE: this is split into to to mimic what the SGG does.
    {
        UT_IFStream stream(argv[1], UT_ISTREAM_BINARY);
        if (stream.isError())
        {
            std::cerr << "Unable to read file: " << argv[1] << std::endl;
            return 1;
        }

        auto decompStream = ika::bgeo::parser::getDecompressionStream(argv[1], stream);
        UT_IStream* thestream = decompStream ? decompStream.get() : &stream;

        UT_AutoJSONParser parserLoader(*thestream);
        UT_JSONParser parser = parserLoader.parser();
        detail.loadHeaderAndInfo(parser);
    }
    {
        hboost::timer t;
        UT_IFStream stream(argv[1], UT_ISTREAM_BINARY);
        if (stream.isError())
        {
            std::cerr << "Unable to read file: " << argv[1] << std::endl;
            return 1;
        }

        auto decompStream = ika::bgeo::parser::getDecompressionStream(argv[1], stream);
        UT_IStream* thestream = decompStream ? decompStream.get() : &stream;

        UT_AutoJSONParser parserLoader(*thestream);
        UT_JSONParser parser = parserLoader.parser();
        detail.loadGeometry(parser);
        elapsed = t.elapsed();
    }

    std::cout << detail << std::endl;

    std::cerr << "file loaded in " << elapsed << "s" << std::endl;

    return 0;
}
