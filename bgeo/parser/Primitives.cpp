/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Primitives.h"

#include <cassert>

#include "Primitive.h"
#include "Detail.h"
#include "Run.h"
#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

Primitives::Primitives(const Detail& detail)
    : detail(detail)
{
}

Primitives::~Primitives()
{
    for (auto primitive : primitives)
    {
        delete primitive;
    }
}

void Primitives::load(UT_JSONParser& parser)
{
    UT_String type;
    UT_JSONParser::iterator it;
    for (it = parser.beginArray(); !it.atEnd(); ++it)
    {
        Primitive* primitive = nullptr;

        //std::cout << "p0 " << parser.getStreamPosition() << std::endl;
        parseBeginArray(parser);
        {
            //std::cout << "p1 " << parser.getStreamPosition() << std::endl;
            parseBeginArray(parser);
            {
                //std::cout << "p2 " << parser.getStreamPosition() << std::endl;
                parseArrayValueForKey(parser, "type", type);
                //std::cout <<"type = " << type <<std::endl;

                primitive = Primitive::create(type, detail);
                assert(primitive);
                primitive->loadType(parser);

                //std::cout << "p3 " << parser.getStreamPosition() << std::endl;
            }
            if (primitive->getType() == Primitive::UnknownType)
            {
                // unknown type - eat rest of entries
                bool error = false;
                while (!parser.parseEndArray(error))
                {
                    BGEO_CHECK(!error);
                }
            }
            else
            {
                parseEndArray(parser);
            }
            //std::cout << "p4 " << parser.getStreamPosition() << std::endl;
            primitive->loadData(parser);
        }
        parseEndArray(parser);

        if (primitive->getType() == Primitive::RunType)
        {
            auto run = static_cast<Run*>(primitive);
            primitives.reserve(primitives.size() + run->primitives.size());
            primitives.insert(primitives.end(), run->primitives.begin(),
                              run->primitives.end());
            delete run;
        }
        else
        {
            primitives.push_back(primitive);
        }
    }
}

// shared data is currently only used for houdini 14 volumes. It is structured
// like this:
// ["Volume", ["geo:voxels", "voxels:0x7fd40c63a280", <voxel data> ]
//  prim type   data type     data key
//
void Primitives::loadSharedData(UT_JSONParser &parser)
{
    UT_WorkBuffer buffer;
    Primitive::PrimType type;
    UT_String dataType;
    UT_String dataKey;

    for (auto it = parser.beginArray(); !it .atEnd(); ++it)
    {
        it.getKey(buffer);
        type = Primitive::toPrimType(buffer.buffer());

        parseBeginArray(parser);
        {
            BGEO_CHECK(parser.parseString(buffer));
            dataType.harden(buffer.buffer());

            BGEO_CHECK(parser.parseString(buffer));
            dataKey.harden(buffer.buffer());

            Primitive* source = nullptr;

            for (Primitive* primitive : primitives)
            {
                assert(primitive);
                if (primitive->getType() == type)
                {
                    if (source)
                    {
                        primitive->loadSharedData(*source, dataType, dataKey);
                    }
                    else
                    {
                        if (primitive->loadSharedData(parser, dataType, dataKey))
                        {
                            source = primitive;
                        }
                    }
                }
            }

            if (!source)
            {
                std::cerr << "Warning: unhandled shared data of primitive: "
                          << Primitive::toString(type)
                          << " data type: " << dataType
                          << " key: " << dataKey << std::endl;
                BGEO_CHECK(parser.skipNextObject());
            }
        }
        parseEndArray(parser);
    }
}

const Primitive* Primitives::getPrimitive(int64 index) const
{
    assert(index < primitives.size());
    return primitives[index];
}

std::ostream& operator << (std::ostream& co, const Primitives& primitives)
{
    Primitives::PrimitiveVector::const_iterator it;
    co << "[\n";
    for (it = primitives.primitives.begin(); it != primitives.primitives.end(); ++it)
    {
        co << "    " << *(*it) << "\n\n";
    }
    co << "\n]";

    return co;
}

} // namespace parser
} // namespace ika
} // namespace bgeo

