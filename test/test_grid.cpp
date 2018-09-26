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
namespace test_grid
{

HBOOST_AUTO_TEST_CASE(test_grid)
{
    float grid_P[] = {
        -0.5, 0, -0.5,
        0.5, 0, -0.5,
        -0.5, 0, 0.5,
        0.5, 0, 0.5
    };

    float grid_uv[] = {
        0, 0,
        1, 0,
        0, 1,
        1, 1
    };

    int32_t grid_vertices[] = {
        0, 1, 3, 2
    };

    int32_t grid_start[] = {
        0, 4
    };

    Bgeo bgeo("geo/grid.bgeo");

    HBOOST_CHECK_EQUAL(4, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_P[0], &grid_P[12], P.begin(), P.end());

    std::vector<float> uv;
    bgeo.getPointUV(uv);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_uv[0], &grid_uv[8], uv.begin(), uv.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive->isType<Poly>());
    HBOOST_CHECK_EQUAL(4, primitive->getVertexCount());

    const Poly* poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);

    HBOOST_CHECK_EQUAL(1, poly->getFaceCount());

    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_vertices[0], &grid_vertices[4],
                                  vertices.begin(), vertices.end());

    std::vector<int32_t> startIndices;
    poly->getStartIndices(startIndices);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_start[0], &grid_start[2],
                                  startIndices.begin(), startIndices.end());
}

HBOOST_AUTO_TEST_CASE(test_grid_16)
{
    float grid_P[] = {
        -0.5, 0, -0.5,
        0.5, 0, -0.5,
        -0.5, 0, 0.5,
        0.5, 0, 0.5
    };

    float grid_uv[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };

    int32_t grid_vertices[] = {
        0, 1, 3, 2
    };

    int32_t grid_start[] = {
        0, 4
    };

    Bgeo bgeo("geo/grid_16.bgeo");

    HBOOST_CHECK_EQUAL(4, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_P[0], &grid_P[12], P.begin(), P.end());

    std::vector<float> uv;
    bgeo.getVertexUV(uv);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_uv[0], &grid_uv[8], uv.begin(), uv.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive->isType<Poly>());
    HBOOST_CHECK_EQUAL(4, primitive->getVertexCount());

    const Poly* poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);

    HBOOST_CHECK_EQUAL(1, poly->getFaceCount());

    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_vertices[0], &grid_vertices[4],
                                  vertices.begin(), vertices.end());

    std::vector<int32_t> startIndices;
    poly->getStartIndices(startIndices);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&grid_start[0], &grid_start[2],
                                  startIndices.begin(), startIndices.end());
}

} // namespace test_grid
} // namespace bgeo
} // namespace ika
