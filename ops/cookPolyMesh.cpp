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
#include "bgeo/Poly.h"
#include "bgeo/PolySplitter.h"

#include "build.h"

namespace ika
{
namespace BgeoInOp
{

static FnKat::GroupAttribute buildGeometry(const bgeo::Bgeo& bgeo,
                                           const bgeo::Poly& poly,
                                           bool isSubd)
{
    FnKat::GroupBuilder gbGeometry;

    // geometry.poly
    FnKat::GroupBuilder gbPoly;

    FnKat::IntBuilder vertexListBuilder;
    poly.getVertexList(vertexListBuilder.get());
    gbPoly.set("vertexList", vertexListBuilder.build());

    FnKat::IntBuilder startIndexBuilder;
    poly.getStartIndices(startIndexBuilder.get());
    gbPoly.set("startIndex", startIndexBuilder.build());

    gbGeometry.set("poly", gbPoly.build());

    // geometry.point
    FnKat::GroupBuilder gbPoint;

    // geometry.point.P (float3)
    gbPoint.set("P", build::pointP(bgeo));

    // geometry.point.N (float3)
    auto pointN = build::pointN(bgeo);
    if (pointN.isValid())
    {
        gbPoint.set("N", pointN);
    }

    // geometry.point.uv (float2)
    auto pointUV = build::pointUV(bgeo);
    if (pointUV.isValid())
    {
        gbPoint.set("uv", pointUV);
    }

    gbGeometry.set("point", gbPoint.build());

    // geometry.vertex
    bool hasVertex = false;
    FnKat::GroupBuilder gbVertex;

    // geometry.vertex.N (float3)
    auto vertexN = build::vertexN(bgeo);
    if (vertexN.isValid())
    {
        hasVertex = true;
        gbVertex.set("N", vertexN);
    }

    // geometry.vertex.uv (float2)
    auto vertexUV = build::vertexUV(bgeo);
    if (vertexUV.isValid())
    {
        hasVertex = true;
        gbVertex.set("uv", vertexUV);
    }

    if (hasVertex)
    {
        gbGeometry.set("vertex", gbVertex.build());
    }

    // geometry.arbitrary
    auto arbitrary = build::arbitraryGroup(bgeo, {"P", "N", "uv"});
    if (arbitrary.getNumberOfChildren() > 0)
    {
        gbGeometry.set("arbitrary", arbitrary);
    }

    // subdmesh
    if (isSubd)
    {
        gbGeometry.set("interpolateBoundary", FnAttribute::IntAttribute(1));
        gbGeometry.set("facevaryingpropagatecorners", FnAttribute::IntAttribute(1));
    }

    return gbGeometry.build();
}

/*static*/ void BgeoInOp::cookPolyMesh(FnKat::GeolibCookInterface& interface,
                                       const bgeo::Bgeo& bgeo,
                                       const bgeo::Poly& poly)
{
    FnAttribute::IntAttribute createSubdAttr = interface.getOpArg("createSubd");

    bool isSubd = createSubdAttr.isValid() && createSubdAttr.getValue();
    FnAttribute::StringAttribute type = isSubd ? "subdmesh" : "polymesh";
    interface.setAttr("type", type);

    interface.setAttr("geometry", buildGeometry(bgeo, poly, isSubd));
}

static FnKat::GroupAttribute buildGeometry(const bgeo::Bgeo& bgeo,
                                           bool isSubd,
                                           const bgeo::PolySplitter& splitter)
{
    //splitter.
    FnKat::GroupBuilder gbGeometry;

    // geometry.poly
    FnKat::GroupBuilder gbPoly;

    FnKat::IntBuilder vertexListBuilder;
    splitter.getVertexList(vertexListBuilder.get());
    gbPoly.set("vertexList", vertexListBuilder.build());

    FnKat::IntBuilder startIndexBuilder;
    splitter.getStartIndices(startIndexBuilder.get());
    gbPoly.set("startIndex", startIndexBuilder.build());

    gbGeometry.set("poly", gbPoly.build());

    // geometry.point
    FnKat::GroupBuilder gbPoint;

    // geometry.point.P (float3)
    gbPoint.set("P", build::pointP(bgeo, splitter));

    // geometry.point.N (float3)
    auto pointN = build::pointN(bgeo, splitter);
    if (pointN.isValid())
    {
        gbPoint.set("N", pointN);
    }

    // geometry.point.uv (float2)
    auto pointUV = build::pointUV(bgeo, splitter);
    if (pointUV.isValid())
    {
        gbPoint.set("uv", pointUV);
    }

    gbGeometry.set("point", gbPoint.build());

    // geometry.vertex
    bool hasVertex = false;
    FnKat::GroupBuilder gbVertex;

    // geometry.vertex.N (float3)
    auto vertexN = build::vertexN(bgeo, splitter);
    if (vertexN.isValid())
    {
        hasVertex = true;
        gbVertex.set("N", vertexN);
    }

    // geometry.vertex.uv (float2)
    auto vertexUV = build::vertexUV(bgeo, splitter);
    if (vertexUV.isValid())
    {
        hasVertex = true;
        gbVertex.set("uv", vertexUV);
    }

    if (hasVertex)
    {
        gbGeometry.set("vertex", gbVertex.build());
    }

    // geometry.arbitrary
    auto arbitrary = build::arbitraryGroup(bgeo, splitter, {"P", "N", "uv"});
    if (arbitrary.getNumberOfChildren() > 0)
    {
        gbGeometry.set("arbitrary", arbitrary);
    }

    // subdmesh
    if (isSubd)
    {
        gbGeometry.set("interpolateBoundary", FnAttribute::IntAttribute(1));
        gbGeometry.set("facevaryingpropagatecorners", FnAttribute::IntAttribute(1));
    }

    return gbGeometry.build();
}

void BgeoInOp::cookPolyMesh(FnKat::GeolibCookInterface& interface,
                            const bgeo::Bgeo& bgeo,
                            const bgeo::PolySplitter& splitter)
{
    std::cout << "current split = " << splitter.getCurrentSplit() << std::endl;

    FnAttribute::IntAttribute createSubdAttr = interface.getOpArg("createSubd");

    bool isSubd = createSubdAttr.isValid() && createSubdAttr.getValue();
    FnAttribute::StringAttribute type = isSubd ? "subdmesh" : "polymesh";
    interface.setAttr("type", type);

    interface.setAttr("geometry", buildGeometry(bgeo, isSubd, splitter));
}

} // namespace BgeoInOp
} // namespace ika
