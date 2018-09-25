/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "VertexArrayBuilder.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

VertexArrayBuilder::VertexArrayBuilder(VertexArray&vertices, VertexArray& sides)
    : stack(0),
      sideCount(0),
      vertices(vertices),
      sides(sides)
{
}

/*virtual*/ bool VertexArrayBuilder::jsonInt(UT_JSONParser &parser, int64 value)
{
    sideCount++;
    vertices.push_back(value);
    return true;
}

/*virtual*/ bool VertexArrayBuilder::jsonBeginArray(UT_JSONParser &parser)
{
    sideCount = 0;
    stack++;
    return true;
}

/*virtual*/ bool VertexArrayBuilder::jsonEndArray(UT_JSONParser &parser)
{
    stack--;
    if (stack == 0)
    {
        sides.push_back(sideCount);
    }
    return true;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
