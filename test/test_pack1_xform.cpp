/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/parser/StorageTraits.h"

#include "bgeo/Bgeo.h"
#include "bgeo/PackedGeometry.h"
#include "bgeo/Sphere.h"

namespace ika
{
namespace bgeo
{
namespace test_pack1_xform
{

class Pack1XformFixture
{
public:
    Pack1XformFixture()
        : bgeo("geo/pack1_xform.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

float expected_P[] = {
    1.79999995, 0.399999976, 0
};

double expected_xform[] = {
    1.26668107509613037, 0, -0.292436361312866211, 0,
    0, 1, 0, 0,
    0.224951058626174927, 0, 0.974370062351226807, 0,
    0, 0, 0, 1
};

double expected_bounds[] = {
    -1, 1,
    -1, 1.79999995231628418,
    -1, 1
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_pack1_xform, Pack1XformFixture)

HBOOST_AUTO_TEST_CASE(test_pack1_xform_counts)
{
    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_pack1_xform_P)
{
    std::vector<float> P;
    bgeo.getP(P);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_pack1_xform_path)
{
    auto attribute = bgeo.getPrimitiveAttributeByName("path");
    HBOOST_CHECK(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);
    HBOOST_CHECK_EQUAL(1, strings.size());
    HBOOST_CHECK_EQUAL("op:/obj/packed/pack2", strings[0]);

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);
    HBOOST_CHECK_EQUAL(1, indices.size());
    HBOOST_CHECK_EQUAL(0, indices[0]);
}

HBOOST_AUTO_TEST_CASE(test_pack1_xform_one_packed_primitive)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<PackedGeometry>());
}

HBOOST_AUTO_TEST_CASE(test_pack1_xform_packed_parameters)
{
    auto primitive = bgeo.getPrimitive(0);
    assert(primitive);

    auto packed = primitive->cast<PackedGeometry>();
    assert(packed);

    // bounding box
    HBOOST_CHECK(packed->hasBoundingBox());

    double bounds[6] = { -1 };
    packed->getBoundingBox(bounds);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    packed->getTranslate(translate);
    HBOOST_CHECK_CLOSE(1.79999995, translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.399999976, translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    packed->getPivot(pivot);
    HBOOST_CHECK_CLOSE(0, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.399999976, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    packed->getExtraTransform(xform);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);
}

HBOOST_AUTO_TEST_CASE(test_pack1_xform_packed_detail)
{
    auto primitive = bgeo.getPrimitive(0);
    assert(primitive);

    auto packed = primitive->cast<PackedGeometry>();
    assert(packed);

    auto embeddedGeo = packed->getEmbeddedGeo();
    HBOOST_CHECK(embeddedGeo);

    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPointCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPointAttributeCount());
    HBOOST_CHECK_EQUAL(0, embeddedGeo->getPrimitiveAttributeCount());

    auto embeddedPrim = embeddedGeo->getPrimitive(0);
    HBOOST_CHECK(embeddedPrim->isType<Sphere>());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_pack1
} // namespace bgeo
} // namespace ika
