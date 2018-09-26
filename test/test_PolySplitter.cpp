/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <iostream>

#include <hboost/test/unit_test.hpp>

#include "bgeo/Bgeo.h"
#include "bgeo/Poly.h"
#include "bgeo/PolySplitter.h"

namespace ika
{
namespace bgeo
{
namespace test_PolySplitter
{

HBOOST_AUTO_TEST_CASE(test_poly_splitter_split_missing_attribute_returns_0)
{
    Bgeo bgeo("geo/cube_even_odd.bgeo");
    auto primitive(bgeo.getPrimitive(0));
    HBOOST_REQUIRE(primitive);

    auto poly = primitive->cast<Poly>();
    HBOOST_REQUIRE(poly);

    PolySplitter splitter;

    // suppress error output when splitting missing attribute.
    auto previousStream = std::cerr.rdbuf(nullptr);
    HBOOST_CHECK_EQUAL(0, splitter.splitByPrimitiveString(bgeo, *poly, "HELLO!"));
    std::cerr.rdbuf(previousStream);

    HBOOST_CHECK_EQUAL(0, splitter.getSplitCount());
}


class CubeEvenOddFixture
{
public:
    CubeEvenOddFixture()
        : bgeo("geo/cube_even_odd.bgeo"),
          poly(*bgeo.getPrimitive(0)->cast<Poly>())
    {
        HBOOST_CHECK_EQUAL(2, splitter.splitByPrimitiveString(bgeo, poly, "even_odd"));
    }

protected:
    Bgeo bgeo;
    const Poly& poly;
    PolySplitter splitter;
};

HBOOST_FIXTURE_TEST_SUITE(test_poly_splitter_even_odd, CubeEvenOddFixture)

HBOOST_AUTO_TEST_CASE(split_results_in_2_splits)
{
    HBOOST_CHECK_EQUAL(2, splitter.getSplitCount());
}

// cube_even_odd.geo info:
//
// topology indices (map vertices to points)
// 1,5,4,0,
// 2,6,5,1,
// 3,7,6,2,
// 0,4,7,3,
// 2,1,0,3,
// 5,6,7,4
//
// face -> vertex map (name attribute value)
//    [0,1,2,3]      (0)
//    [4,5,6,7]      (1)
//    [8,9,10,11]    (0)
//    [12,13,14,15]  (1)
//    [16,17,18,19]  (0)
//    [[20,21,22,23] (1)
//
// original P
//    -0.5, -0.5, -0.5,
//    0.5, -0.5, -0.5,
//    0.5, -0.5, 0.5,
//    -0.5, -0.5, 0.5,
//    -0.5, 0.5, -0.5,
//    0.5, 0.5, -0.5,
//    0.5, 0.5, 0.5,
//    -0.5, 0.5, 0.5
//
// original uv
// [1,0,0],[1,0,1],[0,0,1],[0,0,0],
// [1,1,0],[1,1,1],[1,0,1],[1,0,0],
// [0,1,0],[0,1,1],[1,1,1],[1,1,0],
// [0,0,0],[0,0,1],[0,1,1],[0,1,0],
// [1,1,0],[1,0,0],[0,0,0],[0,1,0],
// [1,0,1],[1,1,1],[0,1,1],[0,0,1]

HBOOST_AUTO_TEST_CASE(split_0_vertices)
{
    std::vector<int32_t> vertices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getVertexList(vertices);

    // original vertex -> original point -> split point
    // 0 -> 1 -> 0
    // 1 -> 5 -> 1
    // 2 -> 4 -> 2
    // 3 -> 0 -> 3
    // 8 -> 3 -> 4
    // 9 -> 7 -> 5
    // 10 -> 6 -> 6
    // 11 -> 2 -> 7
    // 16 -> 2 -> 7
    // 17 -> 1 -> 0
    // 18 -> 0 -> 3
    // 19 -> 3 -> 4

    std::vector<int32_t> expected = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        7, 0, 3, 4
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  vertices.begin(), vertices.end());
}

HBOOST_AUTO_TEST_CASE(split_0_original_vertex_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getOriginalVertexIndices(indices);

    std::vector<int32_t> expected = {
        0, 1, 2, 3,
        8, 9, 10, 11,
        16, 17, 18, 19
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(split_0_original_point_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getOriginalPointIndices(indices);

    std::vector<int32_t> expected = {
        1, 5, 4, 0,
        3, 7, 6, 2
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(split_0_original_primitive_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getOriginalPrimitiveIndices(indices);

    std::vector<int32_t> expected = {
        0, 2, 4
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(split_0_start_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getStartIndices(indices);

    std::vector<int32_t> expected = {
        0, 4, 8, 12
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(test_split_0_P)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getOriginalPointIndices(indices);

    auto attribute = bgeo.getPointAttributeByName("P");
    HBOOST_REQUIRE(attribute);

    std::vector<float> P;
    attribute->getDataForIndices(P, indices);

    std::vector<float> expected_P = {
        0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, -0.5, 0.5
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_split_0_uv)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getOriginalVertexIndices(indices);

    auto attribute = bgeo.getVertexAttributeByName("uv");
    HBOOST_REQUIRE(attribute);

    std::vector<float> uv;
    attribute->getDataForIndices(uv, indices);

    std::vector<float> expected_uv = {
         1,0,0, 1,0,1, 0,0,1, 0,0,0,
         0,1,0, 0,1,1, 1,1,1, 1,1,0,
         1,1,0, 1,0,0, 0,0,0, 0,1,0
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_uv.begin(), expected_uv.end(),
                                  uv.begin(), uv.end());
}

HBOOST_AUTO_TEST_CASE(test_split_0_even_odd)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 1);
    splitter.setCurrentSplit(0);
    splitter.getOriginalPrimitiveIndices(indices);

    auto attribute = bgeo.getPrimitiveAttributeByName("even_odd");
    HBOOST_REQUIRE(attribute);

    std::vector<int32_t> even_odd;
    attribute->getDataForIndices(even_odd, indices);

    std::vector<float> expected = {
        0, 0, 0
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  even_odd.begin(), even_odd.end());
}

HBOOST_AUTO_TEST_CASE(split_1_vertices)
{
    std::vector<int32_t> vertices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getVertexList(vertices);

    // original vertex -> original point -> split point
    // 4 -> 2 -> 0
    // 5 -> 6 -> 1
    // 6 -> 5 -> 2
    // 7 -> 1 -> 3
    // 12 -> 0 -> 4
    // 13 -> 4 -> 5
    // 14 -> 7 -> 6
    // 15 -> 3 -> 7
    // 20 -> 5 -> 2
    // 21 -> 6 -> 1
    // 22 -> 7 -> 6
    // 23 -> 4 -> 5

    std::vector<int32_t> expected = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        2, 1, 6, 5
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  vertices.begin(), vertices.end());
}

HBOOST_AUTO_TEST_CASE(split_1_start_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getStartIndices(indices);

    std::vector<int32_t> expected = {
        0, 4, 8, 12
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(split_1_original_vertex_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getOriginalVertexIndices(indices);

    std::vector<int32_t> expected = {
        4, 5, 6, 7,
        12, 13, 14, 15,
        20, 21, 22, 23
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(split_1_original_point_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getOriginalPointIndices(indices);

    std::vector<int32_t> expected = {
        2, 6, 5, 1,
        0, 4, 7, 3,
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(split_1_original_primitive_indices)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getOriginalPrimitiveIndices(indices);

    std::vector<int32_t> expected = {
        1, 3, 5
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(test_split_1_P)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getOriginalPointIndices(indices);

    auto attribute = bgeo.getPointAttributeByName("P");
    HBOOST_REQUIRE(attribute);

    std::vector<float> P;
    attribute->getDataForIndices(P, indices);

    std::vector<float> expected_P = {
        0.5, -0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,
        -0.5, -0.5, 0.5
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_split_1_uv)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getOriginalVertexIndices(indices);

    auto attribute = bgeo.getVertexAttributeByName("uv");
    HBOOST_REQUIRE(attribute);

    std::vector<float> uv;
    attribute->getDataForIndices(uv, indices);

    std::vector<float> expected_uv = {
         1,1,0, 1,1,1, 1,0,1, 1,0,0,
         0,0,0, 0,0,1, 0,1,1, 0,1,0,
         1,0,1, 1,1,1, 0,1,1, 0,0,1
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_uv.begin(), expected_uv.end(),
                                  uv.begin(), uv.end());
}

HBOOST_AUTO_TEST_CASE(test_split_1_even_odd)
{
    std::vector<int32_t> indices;

    HBOOST_REQUIRE_GE(splitter.getSplitCount(), 2);
    splitter.setCurrentSplit(1);
    splitter.getOriginalPrimitiveIndices(indices);

    auto attribute = bgeo.getPrimitiveAttributeByName("even_odd");
    HBOOST_REQUIRE(attribute);

    std::vector<int32_t> even_odd;
    attribute->getDataForIndices(even_odd, indices);

    std::vector<float> expected = {
        1, 1, 1
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  even_odd.begin(), even_odd.end());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_Attribute
} // namespace bgeo
} // namespace ika
