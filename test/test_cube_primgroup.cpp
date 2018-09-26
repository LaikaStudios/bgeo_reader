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
namespace test_cube_primgroup
{

class TestCubeBasicsFixture
{
public:
    TestCubeBasicsFixture()
        : bgeo("geo/cube_primgroup.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

HBOOST_FIXTURE_TEST_SUITE(test_cube_primgroup, TestCubeBasicsFixture)

HBOOST_AUTO_TEST_CASE(test_counts)
{
    HBOOST_CHECK_EQUAL(8, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(24, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());
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
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Poly>());
    const Poly* poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);
}

HBOOST_AUTO_TEST_SUITE_END()

class TestCubePolyFixture : public TestCubeBasicsFixture
{
public:
    TestCubePolyFixture()
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

HBOOST_FIXTURE_TEST_SUITE(test_cube_poly, TestCubePolyFixture)

HBOOST_AUTO_TEST_CASE(test_face_count)
{
    HBOOST_CHECK_EQUAL(6, poly->getFaceCount());
}

HBOOST_AUTO_TEST_CASE(test_vertices)
{
    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    std::vector<int32_t> expected = {
        1, 5, 4, 0,
        2, 6, 5, 1,
        3, 7, 6, 2,
        0, 4, 7, 3,
        2, 1, 0, 3,
        5, 6, 7, 4
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  vertices.begin(), vertices.end());
}

HBOOST_AUTO_TEST_CASE(test_start_indices)
{
    std::vector<int32_t> start;
    poly->getStartIndices(start);

    std::vector<int32_t> expected = {
        0, 4, 8, 12, 16, 20, 24
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  start.begin(), start.end());
}

HBOOST_AUTO_TEST_SUITE_END()

class TestPrimgroupFixture : public TestCubeBasicsFixture
{
public:
    TestPrimgroupFixture()
    {
    }
};

HBOOST_FIXTURE_TEST_SUITE(test_primgroup, TestPrimgroupFixture)

HBOOST_AUTO_TEST_CASE(test_has_primgroup)
{
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveGroupCount());
}

HBOOST_AUTO_TEST_CASE(test_primgroup_0)
{
    std::string name = bgeo.getPrimitiveGroupName(0);
    std::vector<int32_t> groupIndices;

    bgeo.getPrimitiveGroup(0, groupIndices);
    HBOOST_CHECK_EQUAL("faces", name);

    std::vector<int32_t> expected_indices = {
        2, 3, 4
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_indices.begin(),
                                  expected_indices.end(),
                                  groupIndices.begin(), groupIndices.end());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_cube_primgroup
} // namespace bgeo
} // namespace ika
