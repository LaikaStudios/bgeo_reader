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

#include "build.h"

namespace ika
{
namespace BgeoInOp
{

static FnAttribute::GroupAttribute buildGeometry(const bgeo::Bgeo& bgeo)
{
    FnKat::GroupBuilder gbGeometry;

    FnKat::GroupBuilder gbPoint;

    // geometry.point.P
    gbPoint.set("P", build::pointP(bgeo));

    // geometry.point.N
    auto N = build::pointN(bgeo);
    if (N.isValid())
    {
        gbPoint.set("N", N);
    }

    // geometry.point.uv
    auto uv = build::pointUV(bgeo);
    if (uv.isValid())
    {
        gbPoint.set("uv", uv);
    }

    // geometry.point.width
    auto width = build::pointAttribute(bgeo, "width");
    if (width.isValid())
    {
        gbPoint.set("width", width);
    }

    // geometry.point.constantwidth
    // auto constantwidth = build::constantAttribute("constantwidth");

    gbGeometry.set("point", gbPoint.build());

    // geometry.arbitrary
    auto arbitrary = build::arbitraryPointGroup(bgeo,
            {"P", "N", "uv", "width", "constantwidth"});

    if (arbitrary.isValid())
    {
        gbGeometry.set("arbitrary", arbitrary);
    }

    return gbGeometry.build();
}

/*static*/ void BgeoInOp::cookPointCloud(FnKat::GeolibCookInterface& interface,
                                         const bgeo::Bgeo& bgeo)
{
    interface.setAttr("type", FnAttribute::StringAttribute("pointcloud"));
    interface.setAttr("geometry", buildGeometry(bgeo));
}

void BgeoInOp::cookParticleSystem(Foundry::Katana::GeolibCookInterface &interface,
                                  const bgeo::Bgeo& bgeo,
                                  const bgeo::Part& /*part*/)
{
    interface.setAttr("type", FnAttribute::StringAttribute("pointcloud"));
    interface.setAttr("geometry", buildGeometry(bgeo));
}

} // namespace BgeoInOp
} // namespace ika
