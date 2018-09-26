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
#include "bgeo/parser/storage.h"

namespace ika
{
namespace bgeo
{
namespace test_splash_interior
{

class TestSplashFixture
{
public:
    TestSplashFixture()
        : bgeo("geo/splash_interior.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

HBOOST_FIXTURE_TEST_SUITE(test_splash, TestSplashFixture)

HBOOST_AUTO_TEST_CASE(test_counts)
{
    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());
}

HBOOST_AUTO_TEST_CASE(test_P)
{
    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL(3, P.size());
    HBOOST_CHECK_EQUAL(0, P[0]);
    HBOOST_CHECK_EQUAL(0, P[1]);
    HBOOST_CHECK_EQUAL(0, P[2]);
}

HBOOST_AUTO_TEST_CASE(test_primitive_is_volume)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<Volume>());

    const Volume* volume = primitive->cast<Volume>();
    HBOOST_CHECK(volume);
}

HBOOST_AUTO_TEST_CASE(test_primitive_has_1_vertex)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK_EQUAL(1, primitive->getVertexCount());
}

HBOOST_AUTO_TEST_CASE(test_name_attribute)
{
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());

    auto attribute = bgeo.getPrimitiveAttribute(0);
    HBOOST_CHECK_EQUAL("name", attribute->getName());

    HBOOST_CHECK_EQUAL(parser::storage::Int32, attribute->getFundamentalType());

    std::vector<int32_t> indices;
    attribute->getData(indices);

    HBOOST_CHECK_EQUAL(1, indices.size());
    HBOOST_CHECK_EQUAL(0, indices[0]);

    std::vector<std::string> strings;
    attribute->getStrings(strings);

    HBOOST_CHECK_EQUAL(1, strings.size());
    HBOOST_CHECK_EQUAL("density", strings[0]);
}

HBOOST_AUTO_TEST_SUITE_END()

class TestVolumeFixture : public TestSplashFixture
{
public:
    TestVolumeFixture()
    {
        assert(1 == bgeo.getPrimitiveCount());
        primitive = bgeo.getPrimitive(0);
        volume = primitive->cast<Volume>();
        assert(volume);
    }

protected:
    Bgeo::PrimitivePtr primitive;
    const Volume* volume;
};

HBOOST_FIXTURE_TEST_SUITE(test_volume, TestVolumeFixture)

HBOOST_AUTO_TEST_CASE(test_volume_resolution)
{
    int32_t resolution[3];
    volume->getResolution(resolution);

    HBOOST_CHECK_EQUAL(7, resolution[0]);
    HBOOST_CHECK_EQUAL(1, resolution[1]);
    HBOOST_CHECK_EQUAL(7, resolution[2]);
}

HBOOST_AUTO_TEST_CASE(test_volume_translation)
{
    double Pd[3];
    volume->getTranslate(Pd);
    HBOOST_CHECK_CLOSE(0, Pd[0], 0.0001);
    HBOOST_CHECK_CLOSE(0, Pd[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, Pd[2], 0.0001);

    double expected_xform[] = {
        7, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 7, 0,
        0, 0, 0, 1
    };

    double matrix[16];
    volume->getExtraTransform(matrix);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &matrix[0], &matrix[16]);
}

HBOOST_AUTO_TEST_CASE(test_volume_density)
{
    std::vector<float> expected_density = {
        0.555214941502, 0.64601880312, 0, 0, 0, 0,
        0.312741041183, 0, 0.099324695766, 0.0947518050671, 0, 0,
        0, 0.326379448175, 0, 0.564753472805, 0.516943514347, 0,
        0, 0, 0.306060999632, 0, 0.374862790108, 0.447583526373,
        0, 0, 0.641304790974, 0, 0,
        0.396016985178, 0.165875911713, 0, 0.509693384171, 0, 0,
        0, 0.526293575764, 1, 0, 0.409888923168, 0,
        0.134026691318, 0.807023823261, 0.644068002701,
        0.726701915264, 0.427917480469, 0.162173435092,
        0.591297626495,0.150183662772
    };

    std::vector<float> voxels;
    volume->getVoxels(voxels);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_density.begin(), expected_density.end(),
                                  voxels.begin(), voxels.end());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_splash_interior
} // namespace bgeo
} // namespace ika
