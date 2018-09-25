/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Part.h"

#include "parser/Part.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(Part, Primitive)

Part::Part(const parser::Part& part)
    : m_part(part)
{
}

void Part::getPointList(std::vector<int32_t>& points) const
{
    m_part.getVerticesMappedToPoints(points);
}

void Part::getVertexList(std::vector<int32_t> &vertices) const
{
    vertices = m_part.vertices;
}

int32_t Part::getVertexCount() const
{
    return m_part.vertices.size();
}

} // namespace ika
} // namespace bgeo
