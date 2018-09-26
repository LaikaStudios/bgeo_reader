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

#include <iomanip>

namespace ika
{
namespace bgeo
{
namespace test_vol2_shared
{

class Vol2SharedFixture
{
public:
    Vol2SharedFixture()
        : bgeo("geo/vol2_shared.bgeo")
    {
        bgeo.getP(P);
    }

protected:
    Bgeo bgeo;
    std::vector<float> P;
};

static float expected_P[] =
{
    0, 0, 0,
    2.9000001, 0, 0
};

static double expected_xform[] = {
    1.9918006658554077, 0, 0, 0,
    0, 1.4938504695892334, 0, 0,
    0, 0, 1.4938504695892334, 0,
    0, 0, 0, 1
};

static float expected_density[] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0.729885101,
    0.446920753, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

HBOOST_FIXTURE_TEST_SUITE(test_vol2_shared, Vol2SharedFixture)

HBOOST_AUTO_TEST_CASE(test_counts)
{
    HBOOST_CHECK_EQUAL(2, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getPrimitiveCount());
}

HBOOST_AUTO_TEST_CASE(test_P)
{
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[6], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_volume_0)
{
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

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_density[0], &expected_density[36],
                                  voxels.begin(), voxels.end());

}

HBOOST_AUTO_TEST_CASE(test_volume_1)
{
    auto primitive = bgeo.getPrimitive(1);
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
    HBOOST_CHECK_CLOSE(expected_P[3], Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[4], Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[5], Pd[2], 0.0001);

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_density[0], &expected_density[36],
                                  voxels.begin(), voxels.end());

}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_vol2_noshared
} // namespace bgeo
} // namespace ika
