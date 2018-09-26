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
#include "bgeo/Primitive.h"

namespace ika
{
namespace bgeo
{
namespace test_simple_partanim
{

HBOOST_AUTO_TEST_CASE(test_simple_partanim)
{
    Bgeo bgeo("geo/simple_partanim.0017.bgeo");

    HBOOST_CHECK_EQUAL(10, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getPrimitiveCount());

    std::vector<float> expected_P = {
        7.52561378479, 1.34114897251, 4.4661989212,
        18.6682453156, 11.7645292282, 14.9641275406,
        3.30707645416, -0.675694525242, 6.2386507988,
        18.1324710846, 11.2287540436, 14.4283533096,
        7.79181003571, 1.74453234673, 6.45593690872,
        -12.0477552414, 6.93027925491, -8.97026157379,
        5.73230075836, -1.02348589897, 2.74033617973,
        3.3771777153, -0.605593442917, 6.30875205994,
        6.08369874954, 1.34579455853, 1.57943093777,
        5.95316314697, 1.21525859833, 1.44889509678,
    };
    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(),
                                  expected_P.end(),
                                  P.begin(), P.end());

    HBOOST_CHECK_EQUAL(13, bgeo.getPointAttributeCount());

    // P ///////////////

    auto attribute = bgeo.getPointAttribute(0);
    HBOOST_CHECK_EQUAL("P", attribute->getName());
    HBOOST_CHECK_EQUAL("hpoint", attribute->getSubType());
    HBOOST_CHECK_EQUAL(4, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    // age ///////////////

    attribute = bgeo.getPointAttribute(1);
    HBOOST_CHECK_EQUAL("age", attribute->getName());
    HBOOST_CHECK_EQUAL(1, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> age;
    attribute->getData(age);

    std::vector<float> expected_age = {
        0.67465698719,
        0.698820769787,
        0.672470152378,
        0.672229111195,
        0.69934630394,
        0.700282931328,
        0.675255954266,
        0.701218724251,
        0.695114254951,
        0.670331060886
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_age.begin(),
                                  expected_age.end(),
                                  age.begin(), age.end());

    // dead ///////////////

    attribute = bgeo.getPointAttribute(2);
    HBOOST_CHECK_EQUAL("dead", attribute->getName());
    HBOOST_CHECK_EQUAL(1, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Int32,
                      attribute->getFundamentalType());

    std::vector<int32_t> dead;
    attribute->getData(dead);

    std::vector<int32_t> expected_dead(10, 0);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_dead.begin(), expected_dead.end(),
                                  dead.begin(), dead.end());

    // force ///////////////

    attribute = bgeo.getPointAttribute(3);
    HBOOST_CHECK_EQUAL("force", attribute->getName());
    HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> force;
    attribute->getData(force);

    std::vector<float> expected_force(30, 0);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_force.begin(), expected_force.end(),
                                  force.begin(), force.end());

    // has_pprevious ///////////////

    attribute = bgeo.getPointAttribute(4);
    HBOOST_CHECK_EQUAL("has_pprevious", attribute->getName());
    HBOOST_CHECK_EQUAL(1, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Int32,
                      attribute->getFundamentalType());

    std::vector<int32_t> has_pprevious;
    attribute->getData(has_pprevious);

    std::vector<int32_t> expected_has_pprevious(10, 1);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_has_pprevious.begin(),
                                  expected_has_pprevious.end(),
                                  has_pprevious.begin(), has_pprevious.end());

    // id ///////////////

    attribute = bgeo.getPointAttribute(5);
    HBOOST_CHECK_EQUAL("id", attribute->getName());
    HBOOST_CHECK_EQUAL(1, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Int32,
                      attribute->getFundamentalType());

    std::vector<int32_t> id;
    attribute->getData(id);

    std::vector<int32_t> expected_id = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_id.begin(),
                                  expected_id.end(),
                                  id.begin(), id.end());
    // life ///////////////

    attribute = bgeo.getPointAttribute(6);
    HBOOST_CHECK_EQUAL("life", attribute->getName());
    HBOOST_CHECK_EQUAL(1, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> life;
    attribute->getData(life);

    std::vector<float> expected_life(10, 100);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_life.begin(),
                                  expected_life.end(),
                                  life.begin(), life.end());

    // N ///////////////

    attribute = bgeo.getPointAttribute(7);
    HBOOST_CHECK_EQUAL("N", attribute->getName());
    HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> N;
    attribute->getData(N);

    std::vector<float> expected_N = {
        1, -1.58454618315e-08, -7.92273091577e-09,
        1, -1.58454618315e-08, -7.92273091577e-09,
        0.500000059605, -0.162460118532, 0.850650727749,
        1, -1.58454618315e-08, -7.92273091577e-09,
        0.809017121792, 0.262865424156, 0.525730907917,
        -1, 2.11272812578e-08, -7.92273091577e-09,
        1, -1.58454618315e-08, -7.92273091577e-09,
        0.500000059605, -0.162460118532, 0.850650727749,
        0.809017121792, -0.262865424156, -0.525730967522,
        0.809017121792, -0.262865424156, -0.525730967522
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_N.begin(), expected_N.end(),
                                  N.begin(), N.end());

    // pprevious ///////////////

    attribute = bgeo.getPointAttribute(8);
    HBOOST_CHECK_EQUAL("pprevious", attribute->getName());
    HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> pprevious;
    attribute->getData(pprevious);

    std::vector<float> expected_pprevious = {
        7.29978227615, 1.38772463799, 4.24036741257,
        17.8287353516, 11.1974277496, 14.1246185303,
        3.20547556877, -0.504888415337, 6.13705015182,
        17.2929611206, 10.661652565, 13.5888442993,
        7.54991817474, 1.77504718304,6.21404504776,
        -11.4976358414, 6.65256690979, -8.42014217377,
        5.65257930756, -0.830800175667, 2.66061496735,
        3.27557682991, -0.434787303209, 6.20715141296,
        5.86423540115, 1.39873790741, 1.35996735096,
        5.73369979858, 1.26820194721, 1.22943150997
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_pprevious.begin(),
                                  expected_pprevious.end(),
                                  pprevious.begin(), pprevious.end());
    // rest ///////////////

    attribute = bgeo.getPointAttribute(9);
    HBOOST_CHECK_EQUAL("rest", attribute->getName());
    HBOOST_CHECK_EQUAL("point", attribute->getSubType());
    HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> rest;
    attribute->getData(rest);

    std::vector<float> expected_rest = {
        3.86900305748, 0, 0.809591114521,
        4.58825111389, 0, 0.884136080742,
        1.66731119156, 0, 4.59888935089,
        4.58825111389, 0, 0.884136080742,
        3.73182153702, 0, 2.39594745636,
        -2.80201530457, 0, 0.275477290154,
        4.44032430649, 0, 1.44836306572,
        1.66731119156, 0, 4.59888935089,
        2.42244720459, 0, -2.08182287216,
        2.42244720459, 0, -2.08182287216
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_rest.begin(),
                                  expected_rest.end(),
                                  rest.begin(), rest.end());

    // sourceptnum ///////////////

    attribute = bgeo.getPointAttribute(10);
    HBOOST_CHECK_EQUAL("sourceptnum", attribute->getName());
    HBOOST_CHECK_EQUAL(1, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Int32,
                      attribute->getFundamentalType());

    std::vector<int32_t> sourceptnum;
    attribute->getData(sourceptnum);

    std::vector<int32_t> expected_sourceptnum = {
        9,0,6,0,5,8,4,6,1,1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_sourceptnum.begin(),
                                  expected_sourceptnum.end(),
                                  sourceptnum.begin(), sourceptnum.end());

    // uv ///////////////

    attribute = bgeo.getPointAttribute(11);
    HBOOST_CHECK_EQUAL("uv", attribute->getName());
    HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> uv;
    attribute->getData(uv);

    std::vector<float> expected_uv = {
        0.902676343918, 0.46931374073, 0,
        1, 0.479753702879, 0,
        0.604758501053, 1, 0,
        1, 0.479753702879, 0,
        0.884113848209, 0.691480875015, 0,
        0, 0.394511818886, 0,
        0.979983568192, 0.558772921562, 0,
        0.604758501053, 1, 0,
        0.706938326359, 0.0643749907613, 0,
        0.706938326359, 0.0643749907613, 0
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_uv.begin(),
                                  expected_uv.end(),
                                  uv.begin(), uv.end());

    // v ///////////////

    attribute = bgeo.getPointAttribute(12);
    HBOOST_CHECK_EQUAL("v", attribute->getName());
    HBOOST_CHECK_EQUAL("vector", attribute->getSubType());
    HBOOST_CHECK_EQUAL(3, attribute->getTupleSize());
    HBOOST_CHECK_EQUAL(parser::storage::Fpreal32,
                      attribute->getFundamentalType());

    std::vector<float> v;
    attribute->getData(v);

    std::vector<float> expected_v = {
        5.4199514389, -1.11781489849, 5.4199514389,
        20.1482181549, 13.6104431152, 20.1482181549,
        2.4384200573, -4.09934663773, 2.4384200573,
        20.1482181549, 13.6104431152, 20.1482181549,
        5.80540895462, -0.732357263565, 5.80540895462,
        -13.2028608322, 6.66509532928, -13.2028608322,
        1.91330909729, -4.62445735931, 1.91330909729,
        2.4384200573, -4.09934663773, 2.4384200573,
        5.2671251297, -1.2706413269, 5.2671251297,
        5.2671251297, -1.2706413269, 5.2671251297
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_v.begin(),
                                  expected_v.end(),
                                  v.begin(), v.end());
}

} // namespace test_simple_partanim
} // namespace bgeo
} // namespace ika
