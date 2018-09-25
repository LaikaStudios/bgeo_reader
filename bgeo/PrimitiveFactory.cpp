/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PrimitiveFactory.h"

#include <cassert>

#include "parser/PackedDisk.h"
#include "parser/PackedFragment.h"
#include "parser/PackedGeometry.h"
#include "parser/Part.h"
#include "parser/Primitive.h"
#include "parser/PolygonRun.h"
#include "parser/Poly.h"
#include "parser/PolySoup.h"
#include "parser/Sphere.h"
#include "parser/Volume.h"

#include "PackedDisk.h"
#include "PackedFragment.h"
#include "PackedGeometry.h"
#include "Part.h"
#include "Poly.h"
#include "Sphere.h"
#include "Volume.h"

namespace ika
{
namespace bgeo
{
namespace factory
{

namespace
{

std::shared_ptr<Bgeo> findOrCreateEmbedded(const parser::PackedGeometry& packed,
                                           EmbeddedGeoMap& embeddedGeoMap)
{
    auto pos = embeddedGeoMap.find(packed.getEmbeddedKey());
    if (pos != embeddedGeoMap.end())
    {
        return pos->second;
    }

    auto embedded = std::make_shared<Bgeo>(packed.getEmbeddedGeo());
    embeddedGeoMap.insert(std::make_pair(packed.getEmbeddedKey(), embedded));
    return embedded;
}

} // namespace anonymous

// FIXME: clean up the factory method by abstracting out construction of the
// parser and bgeo primitives.
Bgeo::PrimitivePtr create(const Bgeo& bgeo,
                          const parser::Primitive& parserPrimitive,
                          EmbeddedGeoMap& embeddedGeoMap,
                          size_t index)
{
    switch(parserPrimitive.getType())
    {
    case parser::Primitive::UnknownType:
        return nullptr;
    case parser::Primitive::PackedDiskType:
    {
        const parser::PackedDisk* parserDisk =
                reinterpret_cast<const parser::PackedDisk*>(&parserPrimitive);
        assert(parserDisk);
        return Bgeo::PrimitivePtr(new PackedDisk(*parserDisk));
    }
    case parser::Primitive::PackedFragmentType:
    {
        const parser::PackedFragment* parserFragment =
                reinterpret_cast<const parser::PackedFragment*>(&parserPrimitive);
        assert(parserFragment);
        auto embedded = findOrCreateEmbedded(*parserFragment, embeddedGeoMap);
        return Bgeo::PrimitivePtr(new PackedFragment(*parserFragment, embedded));
    }
    case parser::Primitive::PackedGeometryType:
    {
        const parser::PackedGeometry* parserPacked =
                reinterpret_cast<const parser::PackedGeometry*>(&parserPrimitive);
        assert(parserPacked);
        auto embedded = findOrCreateEmbedded(*parserPacked, embeddedGeoMap);
        return Bgeo::PrimitivePtr(new PackedGeometry(*parserPacked, embedded));
    }
    case parser::Primitive::PartType:
    {
        const parser::Part* parserPart =
                reinterpret_cast<const parser::Part*>(&parserPrimitive);
        assert(parserPart);
        return Bgeo::PrimitivePtr(new Part(*parserPart));
    }
    case parser::Primitive::PolyType:
    {
        const parser::Poly* parserPoly =
                reinterpret_cast<const parser::Poly*>(&parserPrimitive);
        assert(parserPoly);
        return Bgeo::PrimitivePtr(new Poly(bgeo, *parserPoly));
    }
    case parser::Primitive::PolygonRunType:
    {
        const parser::PolygonRun* parserPoly =
                reinterpret_cast<const parser::PolygonRun*>(&parserPrimitive);
        assert(parserPoly);
        auto poly = new Poly(bgeo, *parserPoly);
        return Bgeo::PrimitivePtr(poly);
    }
    case parser::Primitive::PolySoupType:
    {
        const parser::PolySoup* parserPoly =
                reinterpret_cast<const parser::PolySoup*>(&parserPrimitive);
        assert(parserPoly);
        auto poly = new Poly(bgeo, *parserPoly);
        poly->splitThisPoly(index);
        return Bgeo::PrimitivePtr(poly);
    }
    case parser::Primitive::RunType:
    {
        return nullptr;
    }
    case parser::Primitive::SphereType:
    {
        const parser::Sphere* sphereParser =
                reinterpret_cast<const parser::Sphere*>(&parserPrimitive);
        assert(sphereParser);
        return Bgeo::PrimitivePtr(new Sphere(*sphereParser));
    }
    case parser::Primitive::VolumeType:
        const parser::Volume* volumeParser =
                reinterpret_cast<const parser::Volume*>(&parserPrimitive);
        assert(volumeParser);
        return Bgeo::PrimitivePtr(new Volume(*volumeParser));
    }

    return nullptr;
}

} // namespace factory
} // namespace bgeo
} // namespace ika
