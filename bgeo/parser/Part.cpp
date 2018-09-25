/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Part.h"

#include <cassert>

#include "Detail.h"
#include "ReadError.h"
#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

Part::Part(const Detail& detail)
    : Primitive(detail)
{
}

/*virtual*/ void Part::loadData(UT_JSONParser &parser)
{
    parseBeginArray(parser);
    {
        parseArrayKey(parser, "vertex");
        VertexArrayBuilder::VertexArray sides;
        VertexArrayBuilder vertexBuilder(vertices, sides);
        assert(sides.size() == 0);
        BGEO_CHECK(parser.parseObject(vertexBuilder));

        BGEO_CHECK(parser.skipNextObject()); // "renderproperties"
        BGEO_CHECK(parser.skipNextObject());
    }
    parseEndArray(parser);
}

/*virtual*/ std::ostream& Part::encode(std::ostream& co) const
{
    co << "    ";
    Primitive::encode(co);

    co << "\n    vertices = [";
    if (vertices.size() < 20)
    {
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            co << *it << " ";
        }
    }
    else
    {
        co << "...";
    }
    co << "]" << "\n";

    return co;
}

void Part::getVerticesMappedToPoints(VertexArrayBuilder::VertexArray& vertexPoints) const
{
    detail.mapVerticesToPoints(vertices, vertexPoints);
}

} // namespace parser
} // namespace bgeo
} // namespace ika
