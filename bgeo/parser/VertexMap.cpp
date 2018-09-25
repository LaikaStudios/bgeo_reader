/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "VertexMap.h"

#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

VertexMap::VertexMap()
    : vertices(0),
      vertexCount(0)
{
}

VertexMap::~VertexMap()
{
    delete[] vertices;
}

void VertexMap::load(UT_JSONParser &parser, int64 vertexCount_)
{
    vertexCount = vertexCount_;
    vertices = new int32[vertexCount];

    parseBeginArray(parser);
    {
        parseArrayKey(parser, "pointref");
        parseBeginArray(parser);
        {
            parseArrayValueForKey(parser, "indices", vertices, vertexCount);
        }
        parseEndArray(parser);
    }
    parseEndArray(parser);
}

std::ostream& operator << (std::ostream& co, const VertexMap& map)
{
    co << "[";
    if (map.vertexCount < 20)
    {
        for (int64 i = 0; i < map.vertexCount; i++)
        {
            co << map.vertices[i] << " ";
        }
    }
    else
    {
        co << "...";
    }
    co << "]";

    return co;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
