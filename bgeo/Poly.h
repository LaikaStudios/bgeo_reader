/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_POLY_H
#define BGEO_POLY_H

#include <vector>
#include <cinttypes>

#include "rtti.h"
#include "Bgeo.h"
#include "PolySplitter.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Poly;
}

class Poly : public Primitive
{
    RTTI_DECLARE(Poly, Primitive)

public:
    // FIXME probably ought to be shared ptr
    Poly(const Bgeo& bgeo, const parser::Poly& poly);

    void getRawVertexList(std::vector<int32_t>& vertices) const;
    void getVertexList(std::vector<int32_t>& vertices) const;
    void getStartIndices(std::vector<int32_t>& startIndices) const;
    int32_t getFaceCount() const;

    /*virtual*/ int32_t getVertexCount() const;

    void splitByPrimitiveString(const char* attributeName);
    void splitThisPoly(size_t primitiveIndex);

    PolySplitter& getSplitter();
    const PolySplitter& getSplitter() const;
    bool isSplitting() const;

private:
    const Bgeo& m_bgeo;
    const parser::Poly& m_poly;

    PolySplitter m_splitter;
    bool m_splitting;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_POLY_H
