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
#include "bgeo/Sphere.h"

#include "build.h"

namespace ika
{
namespace BgeoInOp
{

static FnKat::GroupAttribute buildGeometry()
{
    FnKat::GroupBuilder geometry;
    geometry.set("radius", FnKat::DoubleAttribute(1.0));
    return geometry.build();
}

static FnKat::GroupAttribute buildXform(const bgeo::Sphere& sphere)
{
    FnKat::GroupBuilder xform;

    double translate[3];
    sphere.getTranslate(translate);
    xform.set("translate", FnKat::DoubleAttribute(translate, 3, 3));

    double matrix[16];
    sphere.getExtraTransform(matrix);
    xform.set("matrix", FnKat::DoubleAttribute(matrix, 16, 16));
    return xform.build();
}

/*static*/ void BgeoInOp::cookSphere(Foundry::Katana::GeolibCookInterface& interface,
                                     const bgeo::Sphere& sphere)
{
    interface.setAttr("type", FnAttribute::StringAttribute("sphere"));
    interface.setAttr("geometry", buildGeometry());
    interface.setAttr("xform", buildXform(sphere));
}

} // namespace BgeoInOp
} // namespace ika
