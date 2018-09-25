/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PARTICLE_H
#define BGEO_PARSER_PARTICLE_H

#include <vector>

#include "Primitive.h"
#include "VertexArrayBuilder.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class Part : public Primitive
{
public:
    Part(const Detail& detail);

    /*virtual*/ PrimType getType() const
    {
        return PartType;
    }

    /*virtual*/ void loadData(UT_JSONParser &parser);

    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    void getVerticesMappedToPoints(VertexArrayBuilder::VertexArray& vertexPoints) const;

    VertexArrayBuilder::VertexArray vertices;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_PARTICLE_H
