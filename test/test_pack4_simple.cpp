/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/parser/StorageTraits.h"

#include "bgeo/Bgeo.h"
#include "bgeo/PackedGeometry.h"
#include "bgeo/Sphere.h"

namespace ika
{
namespace bgeo
{
namespace test_pack4_simple
{

class Pack4SimpleFixture
{
public:
    Pack4SimpleFixture()
        : bgeo("geo/pack4_simple.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

float expected_P[] = {
    0, 0, 0,
    3, 0, 0,
    6, 0, 0,
    9, 0, 0
};

double expected_xform[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

double expected_bounds[] = {
    -1, 1,
    -1, 1,
    -1, 1
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_pack4_simple, Pack4SimpleFixture)

HBOOST_AUTO_TEST_CASE(test_pack4_simple_counts)
{
    HBOOST_CHECK_EQUAL(4, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_pack4_simple_P)
{
    std::vector<float> P;
    bgeo.getP(P);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[12], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_pack4_simple_4_packed_primitives)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_CHECK(primitive);
        HBOOST_CHECK(primitive->isType<PackedGeometry>());
    }
}

HBOOST_AUTO_TEST_CASE(test_pack4_simple_packed_parameters)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        assert(primitive);

        auto packed = primitive->cast<PackedGeometry>();
        assert(packed);

        // bounding box
        HBOOST_CHECK(packed->hasBoundingBox());

        double bounds[6] = { -1 };
        packed->getBoundingBox(bounds);
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                      &bounds[0], &bounds[6]);

        // translate
        double translate[3] = { -1 };
        packed->getTranslate(translate);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 0], translate[0], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 1], translate[1], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 2], translate[2], 0.0001);

        // pivot
        double pivot[3] = { -1 };
        packed->getPivot(pivot);
        HBOOST_CHECK_CLOSE(0, pivot[0], 0.0001);
        HBOOST_CHECK_CLOSE(0, pivot[1], 0.0001);
        HBOOST_CHECK_CLOSE(0, pivot[2], 0.0001);

        // extra transform
        double xform[16] = { -1 };
        packed->getExtraTransform(xform);
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                      &xform[0], &xform[16]);
    }
}

HBOOST_AUTO_TEST_CASE(test_pack4_simple_packed_detail)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        assert(primitive);

        auto packed = primitive->cast<PackedGeometry>();
        assert(packed);

        auto embeddedGeo = packed->getEmbeddedGeo();
        HBOOST_CHECK(embeddedGeo);

        HBOOST_CHECK_EQUAL(1, embeddedGeo->getPointCount());
        HBOOST_CHECK_EQUAL(1, embeddedGeo->getTotalVertexCount());
        HBOOST_CHECK_EQUAL(1, embeddedGeo->getPrimitiveCount());
        HBOOST_CHECK_EQUAL(1, embeddedGeo->getPointAttributeCount());
        HBOOST_CHECK_EQUAL(0, embeddedGeo->getPrimitiveAttributeCount());

        auto embeddedPrim = embeddedGeo->getPrimitive(0);
        HBOOST_CHECK(embeddedPrim->isType<Sphere>());
    }
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_pack4_simple
} // namespace bgeo
} // namespace ika
