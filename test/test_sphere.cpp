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
#include "bgeo/Sphere.h"

namespace ika
{
namespace bgeo
{
namespace test_sphere
{

HBOOST_AUTO_TEST_CASE(test_sphere)
{
    float expected_P[] = {
        2, 0.800000011921, 0
    };

    double expected_xform[] = {
        0, 0, -0.899999976158, 0,
        0, 1.15999996662, 0, 0,
        0.899999976158, 0, 0, 0,
        0, 0, 0, 1
    };

    Bgeo bgeo("geo/sphere.geo");

    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Sphere>());
    HBOOST_CHECK_EQUAL(1, primitive->getVertexCount());

    const Sphere* sphere = primitive->cast<Sphere>();
    HBOOST_CHECK(sphere);

    double Pd[3];
    sphere->getTranslate(Pd);
    HBOOST_CHECK_CLOSE(expected_P[0], Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], Pd[2], 0.0001);

    double matrix[16];
    sphere->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);
}

} // namespace test_sphere
} // namespace bgeo
} // namespace ika
