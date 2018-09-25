/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PACKED_GEOMETRY_H
#define BGEO_PACKED_GEOMETRY_H

#include <vector>
#include <cinttypes>

#include "rtti.h"
#include "Bgeo.h"
#include "Primitive.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class PackedGeometry;
}

class PackedGeometry : public Primitive
{
    RTTI_DECLARE(PackedGeometry, Primitive)

public:
    PackedGeometry(const parser::PackedGeometry& packed,
                   std::shared_ptr<Bgeo> embedded);

    /*virtual*/ int32_t getVertexCount() const;

    bool hasBoundingBox() const;
    void getBoundingBox(double bounds[6]) const;
    void getPivot(double pivot[3]) const;
    void getTranslate(double translate[3]) const;
    void getExtraTransform(double transform[16]) const;

    const std::shared_ptr<Bgeo> getEmbeddedGeo() const;

private:
    const parser::PackedGeometry& m_packed;
    std::shared_ptr<Bgeo> m_embedded;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_PACKED_GEOMETRY_H
