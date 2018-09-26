/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/Bgeo.h"
#include "bgeo/Poly.h"

namespace ika
{
namespace bgeo
{
namespace test_psoup_simple
{

class TestPsoupSimpleFixture
{
public:
    TestPsoupSimpleFixture()
        : bgeo("geo/psoup_simple.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

HBOOST_FIXTURE_TEST_SUITE(test_psoup_simple, TestPsoupSimpleFixture)

HBOOST_AUTO_TEST_CASE(test_counts)
{
    HBOOST_CHECK_EQUAL(8, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(8, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPointAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_P)
{
    std::vector<float> P;
    bgeo.getP(P);

    std::vector<float> expected = {
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_primitive_poly)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);
    HBOOST_REQUIRE(primitive->isType<Poly>());
    const Poly* poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);
}

HBOOST_AUTO_TEST_SUITE_END()

class TestCubePsoupFixture : public TestPsoupSimpleFixture
{
public:
    TestCubePsoupFixture()
    {
        polyif = bgeo.getPrimitive(0);
        assert(polyif->isType<Poly>());
        poly = polyif->cast<Poly>();
        assert(poly);
    }

protected:
    Bgeo::PrimitivePtr polyif;
    const Poly* poly;
};

HBOOST_FIXTURE_TEST_SUITE(test_cube_psoup, TestCubePsoupFixture)

HBOOST_AUTO_TEST_CASE(test_face_count)
{
    HBOOST_CHECK_EQUAL(7, poly->getFaceCount());
}

HBOOST_AUTO_TEST_CASE(test_vertices)
{
    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    std::vector<int32_t> expected = {
        1, 5, 4, 0,
        3, 7, 6, 2,
        0, 4, 7, 3,
        2, 1, 0, 3,
        5, 6, 7, 4,
        6, 5, 1,
        1, 2, 6
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  vertices.begin(), vertices.end());
}

HBOOST_AUTO_TEST_CASE(test_start_indices)
{
    std::vector<int32_t> start;
    poly->getStartIndices(start);

    std::vector<int32_t> expected = {
        0, 4, 8, 12, 16, 20, 23, 26
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  start.begin(), start.end());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_psoup_simple
} // namespace bgeo
} // namespace ika
