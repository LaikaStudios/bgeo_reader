/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Primitive.h"

#include "util.h"

#include "Detail.h"
#include "PackedDisk.h"
#include "PackedFragment.h"
#include "PackedGeometry.h"
#include "Part.h"
#include "Poly.h"
#include "PolySoup.h"
#include "PolygonRun.h"
#include "Run.h"
#include "Sphere.h"
#include "Volume.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

static const char* typeStringMap[] = {
    "Unknown",
    "PackedDisk",
    "PackedFragment",
    "PackedGeometry",
    "Part",
    "Polygon_run",
    "Poly",
    "PolySoup",
    "run",
    "Sphere",
    "Volume"
};

const char* Primitive::toString(PrimType type)
{
    return typeStringMap[type];
}

Primitive::PrimType Primitive::toPrimType(const UT_String& type)
{
    for (int i = 0; i < (sizeof(typeStringMap) / sizeof(const char*)); i++)
    {
        if (type == typeStringMap[i])
        {
            return static_cast<Primitive::PrimType>(i);
        }
    }
    return Primitive::UnknownType;
}

Primitive* Primitive::create(const UT_String& type, const Detail& detail)
{
    if (type == "Poly")
    {
        return new Poly(detail);
    }
    else if (type == "Polygon_run" || type == "p_r")
    {
        return new PolygonRun(detail);
    }
    else if (type == "PolySoup")
    {
        return new PolySoup(detail);
    }
    else if (type == "run")
    {
        return new Run(detail);
    }
    else if (type == "PackedDisk")
    {
        return new PackedDisk(detail);
    }
    else if (type == "PackedFragment")
    {
        return new PackedFragment(detail);
    }
    else if (type == "PackedGeometry")
    {
        return new PackedGeometry(detail);
    }
    else if (type == "Part")
    {
        return new Part(detail);
    }
    else if (type == "Sphere")
    {
        return new Sphere(detail);
    }
    else if (type == "Volume")
    {
        return new Volume(detail);
    }

    std::cerr << "Warning: unsupported primitive type: " << type << std::endl;
    return new Primitive(detail);
}

Primitive::Primitive(const Detail& detail)
    : detail(detail)
{
}

Primitive::~Primitive()
{
}

Primitive* Primitive::clone() const
{
    return new Primitive(detail);
}

/*virtual*/ Primitive::PrimType Primitive::getType() const
{
    return UnknownType;
}

/*virtual*/ void Primitive::loadType(UT_JSONParser& parser)
{
    // unknown type - rely on Primitives to eat rest of data
}

/*virtual*/ void Primitive::loadData(UT_JSONParser& parser)
{
    // unknown type - skip data
    BGEO_CHECK(parser.skipNextObject());
}

/*virtual*/ Primitive::RunMode Primitive::getRunMode() const
{
    return NoRunMode;
}

/*virtual*/ void Primitive::loadVaryingData(UT_JSONParser& parser, const StringList& /*fields*/)
{
    // unknown type - skip data
    BGEO_CHECK(parser.skipNextObject());
}

/*virtual*/ void Primitive::loadUniformData(UT_JSONParser& parser)
{
    // unknown type - skip data
    BGEO_CHECK(parser.skipNextObject());
}

/*virtual*/ bool Primitive::loadSharedData(UT_JSONParser& parser,
                                           UT_String& dataType,
                                           UT_String& dataKey)
{
    // unknown type - don't handle it
    return false;
}

void Primitive::loadSharedData(const Primitive& source,
                               const UT_String& dataType,
                               const UT_String& dataKey)
{
}

/*virtual*/ std::ostream& Primitive::encode(std::ostream& co) const
{
    co << "type = " << Primitive::toString(getType());
    return co;
}

std::ostream& operator << (std::ostream& co, const Primitive& primitive)
{
    return primitive.encode(co);
}

} // namespace parser
} // namespace ika
} // namespace bgeo
