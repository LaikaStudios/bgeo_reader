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
#include "bgeo/Volume.h"

namespace ika
{
namespace bgeo
{
namespace test_vol
{

HBOOST_AUTO_TEST_CASE(test_vol)
{
    Bgeo bgeo("geo/vol.bgeo");

    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    float expected_P[] = {
        0, 0, 0
    };

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Volume>());
    HBOOST_CHECK_EQUAL(1, primitive->getVertexCount());

    const Volume* volume = primitive->cast<Volume>();
    HBOOST_CHECK(volume);

    int32_t expected_resolution[] = {
        4, 3, 3
    };
    int32_t resolution[3];
    volume->getResolution(resolution);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_resolution[0], &expected_resolution[3],
                                  &resolution[0], &resolution[3]);

    double Pd[3];
    volume->getTranslate(Pd);
    HBOOST_CHECK_CLOSE(expected_P[0], Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], Pd[2], 0.0001);

    // Use this for .geo vvvvvvvv
//    double expected_xform[] = {
//        1.99180066586, 0, 0, 0,
//        0, 1.49385046959, 0, 0,
//        0, 0, 1.49385046959, 0,
//        0, 0, 0, 1
//    };

    // Use this for .bgeo vvvvvvv
    double expected_xform[] = {
        1.9918006658554077, 0, 0, 0,
        0, 1.4938504695892334, 0, 0,
        0, 0, 1.4938504695892334, 0,
        0, 0, 0, 1
    };

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);

    float expected_density[] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0.729885101318,
        0.446920752525, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    };

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_density[0], &expected_density[36],
                                  voxels.begin(), voxels.end());
}

HBOOST_AUTO_TEST_CASE(test_vol_14)
{
    Bgeo bgeo("geo/vol_14.bgeo");

    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    float expected_P[] = {
        0, 0, 0
    };

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Volume>());
    HBOOST_CHECK_EQUAL(1, primitive->getVertexCount());

    const Volume* volume = primitive->cast<Volume>();
    HBOOST_CHECK(volume);

    int32_t expected_resolution[] = {
        4, 3, 3
    };
    int32_t resolution[3];
    volume->getResolution(resolution);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_resolution[0], &expected_resolution[3],
                                  &resolution[0], &resolution[3]);

    double Pd[3];
    volume->getTranslate(Pd);
    HBOOST_CHECK_CLOSE(expected_P[0], Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], Pd[2], 0.0001);

    // Use this for .geo vvvvvvvv
//    double expected_xform[] = {
//        1.99180066586, 0, 0, 0,
//        0, 1.49385046959, 0, 0,
//        0, 0, 1.49385046959, 0,
//        0, 0, 0, 1
//    };

    // Use this for .bgeo vvvvvvv
    double expected_xform[] = {
        1.9918006658554077, 0, 0, 0,
        0, 1.4938504695892334, 0, 0,
        0, 0, 1.4938504695892334, 0,
        0, 0, 0, 1
    };

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);

    float expected_density[] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0.729885101318,
        0.446920752525, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    };

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_density[0], &expected_density[36],
                                  voxels.begin(), voxels.end());
}

HBOOST_AUTO_TEST_CASE(test_vol_15)
{
    Bgeo bgeo("geo/vol_15.bgeo");

    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    float expected_P[] = {
        0, 0, 0
    };

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Volume>());
    HBOOST_CHECK_EQUAL(1, primitive->getVertexCount());

    const Volume* volume = primitive->cast<Volume>();
    HBOOST_CHECK(volume);

    int32_t expected_resolution[] = {
        4, 3, 3
    };
    int32_t resolution[3];
    volume->getResolution(resolution);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_resolution[0], &expected_resolution[3],
                                  &resolution[0], &resolution[3]);

    double Pd[3];
    volume->getTranslate(Pd);
    HBOOST_CHECK_CLOSE(expected_P[0], Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], Pd[2], 0.0001);

    // Use this for .geo vvvvvvvv
//    double expected_xform[] = {
//        1.99180066586, 0, 0, 0,
//        0, 1.49385046959, 0, 0,
//        0, 0, 1.49385046959, 0,
//        0, 0, 0, 1
//    };

    // Use this for .bgeo vvvvvvv
    double expected_xform[] = {
        1.9918006658554077, 0, 0, 0,
        0, 1.4938504695892334, 0, 0,
        0, 0, 1.4938504695892334, 0,
        0, 0, 0, 1
    };

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);

    float expected_density[] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0.729885101318,
        0.446920752525, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    };

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_density[0], &expected_density[36],
                                  voxels.begin(), voxels.end());
}

HBOOST_AUTO_TEST_CASE(test_vol_16)
{
    Bgeo bgeo("geo/vol_16.bgeo");

    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    float expected_P[] = {
        0, 0, 0
    };

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Volume>());
    HBOOST_CHECK_EQUAL(1, primitive->getVertexCount());

    const Volume* volume = primitive->cast<Volume>();
    HBOOST_CHECK(volume);

    int32_t expected_resolution[] = {
        4, 3, 3
    };
    int32_t resolution[3];
    volume->getResolution(resolution);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_resolution[0], &expected_resolution[3],
                                  &resolution[0], &resolution[3]);

    double Pd[3];
    volume->getTranslate(Pd);
    HBOOST_CHECK_CLOSE(expected_P[0], Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], Pd[2], 0.0001);

    // Use this for .geo vvvvvvvv
//    double expected_xform[] = {
//        1.99180066586, 0, 0, 0,
//        0, 1.49385046959, 0, 0,
//        0, 0, 1.49385046959, 0,
//        0, 0, 0, 1
//    };

    // Use this for .bgeo vvvvvvv
    double expected_xform[] = {
        1.9918006658554077, 0, 0, 0,
        0, 1.4938504695892334, 0, 0,
        0, 0, 1.4938504695892334, 0,
        0, 0, 0, 1
    };

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);

    float expected_density[] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0.729885101318,
        0.446920752525, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    };

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_density[0], &expected_density[36],
                                  voxels.begin(), voxels.end());
}

} // namespace test_vol
} // namespace bgeo
} // namespace ika
