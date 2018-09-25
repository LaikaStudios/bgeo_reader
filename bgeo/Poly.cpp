/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Poly.h"

#include "parser/Poly.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(Poly, Primitive)

Poly::Poly(const Bgeo& bgeo, const parser::Poly& poly)
    : m_bgeo(bgeo),
      m_poly(poly),
      m_splitting(false)
{
}

void Poly::getRawVertexList(std::vector<int32_t>& vertices) const
{
    vertices = m_poly.vertices;
}

void Poly::getVertexList(std::vector<int32_t>& vertices) const
{
    m_poly.getVerticesMappedToPoints(vertices);
}

void Poly::getStartIndices(std::vector<int32_t>& startIndices) const
{
    startIndices.resize(m_poly.sides.size() + 1);
    startIndices[0] = 0;

    int64 current = 0;
    for (int i = 0; i < m_poly.sides.size(); ++i)
    {
        current += m_poly.sides[i];
        startIndices[i + 1] = current;
    }
}

int32_t Poly::getFaceCount() const
{
    return m_poly.sides.size();
}

int32_t Poly::getVertexCount() const
{
    return m_poly.vertices.size();
}

void Poly::splitByPrimitiveString(const char *attributeName)
{
    m_splitter.splitByPrimitiveString(m_bgeo, *this, attributeName);
    m_splitting = true;
}

void Poly::splitThisPoly(size_t primitiveIndex)
{
    m_splitter.splitThisPoly(m_bgeo, *this, primitiveIndex);
    m_splitting = true;
}

PolySplitter& Poly::getSplitter()
{
    return m_splitter;
}

const PolySplitter& Poly::getSplitter() const
{
    return m_splitter;
}

bool Poly::isSplitting() const
{
    return m_splitting;
}

} // namespace ika
} // namespace bgeo
