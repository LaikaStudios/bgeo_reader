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
namespace test_grid_tetra
{

HBOOST_AUTO_TEST_CASE(test_grid_tetra)
{
    float expected_P[] = {
        -0.5, 0, -0.5,
        0.5, 0, -0.5,
        -0.5, 0, 0.5,
        0.5, 0, 0.5,
        0, -0.539999961853, 0,
        -0.942810356617, -1.87332963943, 0,
        0.471405237913, -1.87332963943, 0.81649762392,
        0.471405088902, -1.87332963943, -0.81649774313
    };

    float expected_uv[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1,
        1, 0.891826152802,
        0.136407256126, 0.323981493711,
        0.863592743874, 0.323981493711,
        1, 0.891826152802,
        0.5, 0.259368151426,
        0.136407256126, 0.323981493711,
        1, 0.891826152802,
        0.863592743874, 0.323981493711,
        0.5, 0.259368151426,
        0.5, 0.259368151426,
        0.863592743874, 0.323981493711,
        0.136407256126, 0.323981493711
    };

    int32_t expected_vertices[] = {
        0, 1, 3, 2,
        4, 7, 6,
        4, 5, 7,
        4, 6, 5,
        5, 6, 7
    };

    int32_t expected_start[] = {
        0, 4, 7, 10, 13, 16
    };

    Bgeo bgeo("geo/grid_tetra.bgeo");

    HBOOST_CHECK_EQUAL(8, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(16, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[24],
                                  P.begin(), P.end());

    std::vector<float> uv;
    bgeo.getVertexUV(uv);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_uv[0], &expected_uv[32],
                                  uv.begin(), uv.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive->isType<Poly>());
    HBOOST_CHECK_EQUAL(16, primitive->getVertexCount());

    auto poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);

    HBOOST_CHECK_EQUAL(5, poly->getFaceCount());

    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_vertices[0], &expected_vertices[16],
                                  vertices.begin(), vertices.end());

    std::vector<int32_t> startIndices;
    poly->getStartIndices(startIndices);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_start[0], &expected_start[6],
                                  startIndices.begin(), startIndices.end());
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_16)
{
    float expected_P[] = {
        -0.5, 0, -0.5,
        0.5, 0, -0.5,
        -0.5, 0, 0.5,
        0.5, 0, 0.5,
        0, -0.5, 0,
        -0.942810297, -1.83332968, 0,
        0.471405149, -1.83332968, 0.816497624,
        0.471405149, -1.83332968, -0.816497624
    };

    float expected_uv[] = {
        0.30690819, 0.193814188,
        1, 0.193814188,
        1, 0.806185842,
        0.30690819, 0.806185842,
        0.653454065, 0.5,
        0.980181158, 0,
        0.980181158, 1,
        0.653454065, 0.5,
        0, 0.5,
        0.980181158, 0,
        0.653454065, 0.5,
        0.980181158, 1,
        0, 0.5,
        0, 0.5,
        0.980181158, 1,
        0.980181158, 0,
    };

    int32_t expected_vertices[] = {
        0, 1, 3, 2,
        4, 7, 6,
        4, 5, 7,
        4, 6, 5,
        5, 6, 7
    };

    int32_t expected_start[] = {
        0, 4, 7, 10, 13, 16
    };

    Bgeo bgeo("geo/grid_tetra_16.bgeo");

    HBOOST_CHECK_EQUAL(8, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(16, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[24],
                                  P.begin(), P.end());

    std::vector<float> uv;
    bgeo.getVertexUV(uv);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_uv[0], &expected_uv[32],
                                  uv.begin(), uv.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive->isType<Poly>());
    HBOOST_CHECK_EQUAL(16, primitive->getVertexCount());

    auto poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);

    HBOOST_CHECK_EQUAL(5, poly->getFaceCount());

    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_vertices[0], &expected_vertices[16],
                                  vertices.begin(), vertices.end());

    std::vector<int32_t> startIndices;
    poly->getStartIndices(startIndices);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_start[0], &expected_start[6],
                                  startIndices.begin(), startIndices.end());
}

} // namespace test_grid_tetra
} // namespace bgeo
} // namespace ika
