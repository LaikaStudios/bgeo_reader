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
#include "bgeo/Sphere.h"

namespace ika
{
namespace bgeo
{
namespace test_sphere_grid
{

HBOOST_AUTO_TEST_CASE(test_sphere_grid)
{
    Bgeo bgeo("geo/sphere_grid.geo");

    HBOOST_CHECK_EQUAL(5, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(5, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getPrimitiveCount());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Sphere>());

    const Sphere* sphere = primitive->cast<Sphere>();
    HBOOST_CHECK(sphere);

    double expected_sphere_P[] = {
        4, 0, 0
    };

    double Pd[3];
    sphere->getTranslate(Pd);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_sphere_P[0],
                                  &expected_sphere_P[3],
                                  &Pd[0], &Pd[3]);


    double expected_sphere_xform[] = {
        0.800000011921, 0, 0, 0,
        0, 0, -0.800000011921, 0,
        0, 0.800000011921, 0, 0,
        0, 0, 0, 1
    };

    double matrix[16];
    sphere->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_sphere_xform[0],
                                  &expected_sphere_xform[16],
                                  &matrix[0], &matrix[16]);

    int32_t expected_grid_vertices[] = {
        1, 2, 4, 3
    };

    int32_t expected_grid_start[] = {
        0, 4
    };

    auto gridPrimitive = bgeo.getPrimitive(1);
    HBOOST_CHECK(gridPrimitive);
    HBOOST_CHECK(gridPrimitive->isType<Poly>());

    auto grid = gridPrimitive->cast<Poly>();
    HBOOST_CHECK(grid);
    HBOOST_CHECK_EQUAL(4, grid->getVertexCount());
    HBOOST_CHECK_EQUAL(1, grid->getFaceCount());

    std::vector<int32_t> vertices;
    grid->getVertexList(vertices);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_grid_vertices[0], &expected_grid_vertices[4],
                                  vertices.begin(), vertices.end());

    std::vector<int32_t> startIndices;
    grid->getStartIndices(startIndices);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_grid_start[0], &expected_grid_start[2],
                                  startIndices.begin(), startIndices.end());

    float expected_grid_P[] = {
        4, 0, 0,
        -0.5, 0, -0.5,
        0.5, 0, -0.5,
        -0.5, 0, 0.5,
        0.5, 0, 0.5
    };

    float expected_grid_uv[] = {
        0.84905654192, 0.5,
        0, 0.1875,
        0.188679233193, 0.1875,
        0.188679233193, 0.8125,
        0, 0.8125
    };

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_grid_P[0], &expected_grid_P[15],
                                  P.begin(), P.end());

    std::vector<float> uv;
    bgeo.getVertexUV(uv);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_grid_uv[0], &expected_grid_uv[10],
                                  uv.begin(), uv.end());
}

} // namespace test_sphere_grid
} // namespace bgeo
} // namespace ika
