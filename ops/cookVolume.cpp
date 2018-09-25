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
#include "bgeo/Volume.h"

#include "build.h"

namespace ika
{
namespace BgeoInOp
{

static FnKat::GroupAttribute buildGeometry(const bgeo::Volume& volume)
{
    FnKat::GroupBuilder gbGeometry;

    gbGeometry.set("type", FnKat::StringAttribute("rivolume"));
    gbGeometry.set("shape", FnKat::StringAttribute("box"));

    int32_t resolution[3];
    volume.getResolution(resolution);
    gbGeometry.set("voxelResolution", FnKat::IntAttribute(resolution, 3, 3));

    // geometry.arbitrary
    FnKat::GroupBuilder gbArbitrary;

    FnKat::GroupBuilder gbDensity;

    gbDensity.set("scope", FnKat::StringAttribute("point"));
    gbDensity.set("inputType", FnKat::StringAttribute("float"));

    FnKat::FloatBuilder densityBuilder;
    volume.getVoxels(densityBuilder.get());
    gbDensity.set("value", densityBuilder.build());

    gbArbitrary.set("density", gbDensity.build());

    gbGeometry.set("arbitrary", gbArbitrary.build());

    return gbGeometry.build();
}

static FnKat::GroupAttribute buildXform(const bgeo::Volume& volume)
{
    FnKat::GroupBuilder gbXform;

    double translate[3];
    volume.getTranslate(translate);
    gbXform.set("translate", FnKat::DoubleAttribute(translate, 3, 3));

    double matrix[16];
    volume.getExtraTransform(matrix);
    gbXform.set("matrix", FnKat::DoubleAttribute(matrix, 16, 16));
    return gbXform.build();
}

static FnKat::DoubleAttribute buildBound(const bgeo::Volume& volume)
{
    FnKat::DoubleBuilder boundBuilder;
    boundBuilder.get().resize(6);
    volume.getBoundingBox(boundBuilder.get().data());
    return boundBuilder.build();
}

/*static*/ void BgeoInOp::cookVolume(Foundry::Katana::GeolibCookInterface& interface,
                                     const bgeo::Volume& volume)
{
    interface.setAttr("type", FnAttribute::StringAttribute("volume"));
    interface.setAttr("geometry", buildGeometry(volume));
    interface.setAttr("xform", buildXform(volume));
    interface.setAttr("bound", buildBound(volume));
}

} // namespace BgeoInOp
} // namespace ika
