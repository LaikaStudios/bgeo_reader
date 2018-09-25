/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_VERTEX_MAP_H
#define BGEO_PARSER_VERTEX_MAP_H

#include <UT/UT_JSONParser.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class VertexMap
{
public:
    VertexMap();
    ~VertexMap();

    void load(UT_JSONParser& parser, int64 vertexCount);

    int32* vertices;
    int64 vertexCount;

    friend std::ostream& operator << (std::ostream& co, const VertexMap& map);
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_VERTEX_MAP_H
