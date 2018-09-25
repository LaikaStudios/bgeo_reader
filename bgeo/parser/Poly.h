/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_POLY_H
#define BGEO_PARSER_POLY_H

#include <vector>

#include "Primitive.h"
#include "VertexArrayBuilder.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class Poly : public Primitive
{
public:
    Poly(const Detail& detail);
    Poly(const Poly& poly) = default;

    /*virtual*/ Poly* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return PolyType;
    }

    /*virtual*/ RunMode getRunMode() const
    {
        return MergeRunMode;
    }

    /*virtual*/ void loadData(UT_JSONParser &parser);

    /*virtual*/ void loadVaryingData(UT_JSONParser& parser, const StringList& fields);
    /*virtual*/ void loadUniformData(UT_JSONParser& parser);

    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    VertexArrayBuilder::VertexArray vertices;
    VertexArrayBuilder::VertexArray sides;

    typedef std::vector<bool> ClosedArray;
    ClosedArray closed;

    void getVerticesMappedToPoints(VertexArrayBuilder::VertexArray& vertexPoints) const;
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_POLY_H
