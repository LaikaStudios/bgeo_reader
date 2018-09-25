/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "BgeoInOp.h"

#include <FnAttribute/FnAttribute.h>
#include <FnAttribute/FnGroupBuilder.h>
#include <FnAttribute/FnDataBuilder.h>

#include "bgeo/Bgeo.h"
#include "bgeo/PackedGeometry.h"

namespace ika
{
namespace BgeoInOp
{

static FnKat::GroupAttribute buildXform(const bgeo::PackedGeometry& packed)
{
    FnKat::GroupBuilder xform;

    double translate[3];
    packed.getTranslate(translate);
    xform.set("translate", FnKat::DoubleAttribute(translate, 3, 3));

    double matrix[16];
    packed.getExtraTransform(matrix);
    xform.set("matrix", FnKat::DoubleAttribute(matrix, 16, 16));

    double pivot[3];
    packed.getPivot(pivot);
    pivot[0] = -pivot[0];
    pivot[1] = -pivot[1];
    pivot[2] = -pivot[2];
    xform.set("translate_pivot", FnKat::DoubleAttribute(pivot, 3, 3));

    return xform.build();
}

/*static*/ void BgeoInOp::cookPackedGeometry(FnKat::GeolibCookInterface& interface,
                                             const bgeo::Bgeo& /*bgeo*/,
                                             const bgeo::PackedGeometry& packed)
{
    if (packed.hasBoundingBox())
    {
        FnAttribute::DoubleBuilder boundBuilder;
        boundBuilder.get().resize(6);
        packed.getBoundingBox(boundBuilder.get().data());
        interface.setAttr("bound", boundBuilder.build());
    }

    interface.setAttr("xform", buildXform(packed));
}


} // namespace BgeoInOp
} // namespace ika
