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

namespace ika
{
namespace bgeo
{
namespace test_points_noprim
{

HBOOST_AUTO_TEST_CASE(test_points_noprim)
{
    Bgeo bgeo("geo/points_noprim.bgeo");

    HBOOST_CHECK_EQUAL(10, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getPrimitiveCount());

    float points_P[] = {
        -1.070956707, 0.245002537966, 0.0458687506616,
        -0.0866123065352, -0.131825581193, -0.394379287958,
        -0.495128661394, -0.480341881514, 0.240714371204,
        0.0364076420665, -0.0627112537622, -0.233789160848,
        -0.203708991408, -0.220273539424, -0.61152100563,
        0.342897295952, 0.0706753358245, 0.0209402479231,
        -0.610469520092, -0.186384543777, -0.054688680917,
        -0.028063878417, 0.108390271664, 0.349550485611,
        -0.262257426977, -0.54922670126, 0.11263243109,
        0.235484302044, -0.103837713599, -0.471310973167,
    };

    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&points_P[0], &points_P[30], P.begin(), P.end());

    float points_N[] = {
        -0.601949989796, 0.732883214951, 0.317077845335,
        0.10831219703, 0.238412290812, -0.965105235577,
        -0.748496055603, -0.55580663681, 0.361708045006,
        0.404422521591, 0.368939369917, -0.836854934692,
        -0.220309466124, -0.152831375599, -0.963382720947,
        0.910714387894, 0.400190740824, 0.102209098637,
        0.465347737074, 0.847251236439, -0.256157964468,
        0, 1, 0,
        -2.83211285534e-08, -1, 9.0482245696e-07,
        0.605720460415, 0.24071238935, -0.758393168449
    };

    std::vector<float> N;
    bgeo.getPointN(N);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&points_N[0], &points_N[30], N.begin(), N.end());
}

} // namespace test_points_noprim
} // namespace bgeo
} // namespace ika
