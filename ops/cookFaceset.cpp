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

static FnKat::GroupAttribute buildGeometry(const bgeo::Bgeo& bgeo, int index)
{
    FnKat::GroupBuilder geometryBuilder;

    FnKat::IntBuilder facesBuilder;
    std::string name = bgeo.getPrimitiveGroupName(index);
    bgeo.getPrimitiveGroup(index, facesBuilder.get());

    geometryBuilder.set("faces", facesBuilder.build());
    return geometryBuilder.build();
}

/*static*/ void BgeoInOp::cookFaceset(Foundry::Katana::GeolibCookInterface& interface,
                                      const bgeo::Bgeo& bgeo)
{
    FnAttribute::IntAttribute indexAttribute = interface.getOpArg("_index");
    int index = indexAttribute.getValue();

    interface.setAttr("type", FnAttribute::StringAttribute("faceset"));
    interface.setAttr("geometry", buildGeometry(bgeo, index));
}

} // namespace BgeoInOp
} // namespace ika
