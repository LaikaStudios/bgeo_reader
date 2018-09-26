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
#include "bgeo/Part.h"

namespace ika
{
namespace bgeo
{
namespace test_points_partsys
{

HBOOST_AUTO_TEST_CASE(test_points_partsys)
{
    Bgeo bgeo("geo/points_partsys_15.bgeo");

    HBOOST_CHECK_EQUAL(10, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(10, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    // P ///////////////

    {
        auto attribute = bgeo.getPointAttribute(0);
        HBOOST_CHECK_EQUAL("P", attribute->getName());
        HBOOST_CHECK_EQUAL("point", attribute->getSubType());
        HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
        HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                          attribute->getFundamentalType());

        float points_P[] = {
            -1.07095671,0.245002538,0.0458687507,
            -0.0866123065,-0.131825581,-0.394379288,
            -0.495128661,-0.480341882,0.240714371,
            0.0364076421,-0.0627111569,-0.233789161,
            -0.203708991,-0.220273584,-0.611521006,
            0.342897117,0.0706753358,0.0209402479,
            -0.61046946,-0.186384633,-0.0546886809,
            -0.0280638784,0.108390272,0.349550486,
            -0.262257427,-0.549226701,0.112632774,
            0.235484302,-0.103837714,-0.471310914
        };

        std::vector<float> P;
        bgeo.getP(P);

        HBOOST_CHECK_EQUAL_COLLECTIONS(&points_P[0], &points_P[30], P.begin(), P.end());
    }

    // N ///////////////

    {
        auto attribute = bgeo.getPointAttribute(1);
        HBOOST_CHECK_EQUAL("N", attribute->getName());
        HBOOST_CHECK_EQUAL("normal", attribute->getSubType());
        HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
        HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                          attribute->getFundamentalType());

        float points_N[] = {
            -0.60194993,0.732883334,0.317077965,
            0.108312637,0.238411933,-0.965105236,
            0,-1,1.50774852e-07,
            0.40442276,0.368939161,-0.836854935,
            -0.220309302,-0.152831182,-0.96338284,
            0.910714388,0.40019092,0.102208957,
            0.465347618,0.847251475,-0.256157309,
            0,1,0,
            0,-1,5.57950237e-08,
            0.60572046,0.240712076,-0.758393347
        };

        std::vector<float> N;
        bgeo.getPointN(N);

        HBOOST_CHECK_EQUAL_COLLECTIONS(&points_N[0], &points_N[30], N.begin(), N.end());
    }

    // primitives /////////
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);
    auto part = primitive->cast<bgeo::Part>();
    HBOOST_REQUIRE(part);

    HBOOST_CHECK_EQUAL(10, part->getVertexCount());

    int32_t vertices[] = {
        0,1,2,3,4,5,6,7,8,9
    };
    std::vector<int32_t> v;
    part->getVertexList(v);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&vertices[0], &vertices[10], v.begin(), v.end());

    std::vector<int32_t> p;
    part->getPointList(p);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&vertices[0], &vertices[10], p.begin(), p.end());
}

} // namespace test_points_partsys
} // namespace bgeo
} // namespace ika
