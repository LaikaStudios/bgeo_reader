/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PackedGeometry.h"

#include "parser/PackedGeometry.h"

#include "Bgeo.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(PackedGeometry, Primitive)

PackedGeometry::PackedGeometry(const parser::PackedGeometry& packed,
                               std::shared_ptr<Bgeo> embedded)
    : m_packed(packed),
      m_embedded(embedded)
{
}

/*virtual*/ int32_t PackedGeometry::getVertexCount() const
{
    return 1;
}

bool PackedGeometry::hasBoundingBox() const
{
    return m_packed.hasBounds();
}

void PackedGeometry::getBoundingBox(double bounds[]) const
{
    m_packed.getBounds(bounds);
}

void PackedGeometry::getPivot(double pivot[]) const
{
    m_packed.getPivot(pivot);
}

void PackedGeometry::getTranslate(double translate[]) const
{
    m_packed.getTranslate(translate);
}

void PackedGeometry::getExtraTransform(double transform[]) const
{
    m_packed.getTransform(transform);
}

const std::shared_ptr<Bgeo> PackedGeometry::getEmbeddedGeo() const
{
    return m_embedded;
}

} // namespace ika
} // namespace bgeo
