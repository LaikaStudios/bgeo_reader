/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_VERTEX_ARRAY_BUILDER_H
#define BGEO_PARSER_VERTEX_ARRAY_BUILDER_H

#include <UT/UT_JSONHandle.h>

#include <vector>

namespace ika
{
namespace bgeo
{
namespace parser
{

class VertexArrayBuilder : public UT_JSONHandleError
{
public:
    typedef std::vector<int32> VertexArray;
    VertexArrayBuilder(VertexArray& vertices, VertexArray& sides);

    /*virtual*/ bool jsonInt(UT_JSONParser& parser, int64 value);
    /*virtual*/ bool jsonBeginArray(UT_JSONParser& parser);
    /*virtual*/ bool jsonEndArray(UT_JSONParser& parser);

private:
    int stack;
    int64 sideCount;
    VertexArray& vertices;
    VertexArray& sides;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_VERTEX_ARRAY_BUILDER_H
