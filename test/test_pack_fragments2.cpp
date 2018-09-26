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
#include "bgeo/PackedFragment.h"
#include "bgeo/Poly.h"

namespace ika
{
namespace bgeo
{
namespace test_pack_fragments2
{

class PackFragmentsFixture
{
public:
    PackFragmentsFixture()
        : bgeo("geo/pack_fragments2.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

float expected_P[] = {
    0, 0, 0,
    0, 0, 0
};

double expected_xform[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

double expected_bounds[] = {
    -0.5, 0.5,
    -0.5, 0.5,
    -0.5, 0.5
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_pack_fragments2, PackFragmentsFixture)

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_counts)
{
    HBOOST_CHECK_EQUAL(2, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_P)
{
    std::vector<float> P;
    bgeo.getP(P);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[6], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_name)
{
    auto attribute = bgeo.getPointAttributeByName("name");
    HBOOST_REQUIRE(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);
    HBOOST_CHECK_EQUAL(2, strings.size());
    HBOOST_CHECK_EQUAL("piece0", strings[0]);
    HBOOST_CHECK_EQUAL("piece1", strings[1]);

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);
    HBOOST_CHECK_EQUAL(2, indices.size());
    HBOOST_CHECK_EQUAL(0, indices[0]);
    HBOOST_CHECK_EQUAL(1, indices[1]);
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_path)
{
    auto attribute = bgeo.getPrimitiveAttributeByName("path");
    HBOOST_REQUIRE(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);
    HBOOST_CHECK_EQUAL(2, strings.size());
    HBOOST_CHECK_EQUAL("op:/obj/packed/assemble2/pack/piece0", strings[0]);
    HBOOST_CHECK_EQUAL("op:/obj/packed/assemble2/pack/piece1", strings[1]);

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);
    HBOOST_CHECK_EQUAL(2, indices.size());
    HBOOST_CHECK_EQUAL(0, indices[0]);
    HBOOST_CHECK_EQUAL(1, indices[1]);
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_first_primitive_is_fragment)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);
    HBOOST_CHECK(primitive->isType<PackedFragment>());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_second_primitive_is_fragment)
{
    auto primitive = bgeo.getPrimitive(1);
    HBOOST_REQUIRE(primitive);
    HBOOST_CHECK(primitive->isType<PackedFragment>());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_packed_parameters_common)
{
    for (int i = 0; i < 2; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_REQUIRE(primitive);

        auto packed = primitive->cast<PackedFragment>();
        HBOOST_REQUIRE(packed);

        // bounding box
        HBOOST_CHECK(packed->hasBoundingBox());

        double bounds[6] = { -1 };
        packed->getBoundingBox(bounds);
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                      &bounds[0], &bounds[6]);

        // translate
        double translate[3] = { -1 };
        packed->getTranslate(translate);
        HBOOST_CHECK_CLOSE(expected_P[i * 2 + 0], translate[0], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 2 + 1], translate[1], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 2 + 2], translate[2], 0.0001);

        // pivot
        double pivot[3] = { -1 };
        packed->getPivot(pivot);

        double expected_pivot[3] = {
            0, 0, 0
        };
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_pivot[0], &expected_pivot[3],
                                      &pivot[0], &pivot[3]);
        // extra transform
        double xform[16] = { -1 };
        packed->getExtraTransform(xform);
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                      &xform[0], &xform[16]);
    }
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_fragment_parameters_1)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    HBOOST_CHECK_EQUAL("name", fragment->getNameAttribute());
    HBOOST_CHECK_EQUAL("piece0", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_fragment_parameters_2)
{
    auto primitive = bgeo.getPrimitive(1);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    HBOOST_CHECK_EQUAL("name", fragment->getNameAttribute());
    HBOOST_CHECK_EQUAL("piece1", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments2_embedded_geo)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    auto embeddedGeo = fragment->getEmbeddedGeo();
    HBOOST_CHECK(embeddedGeo);

    HBOOST_CHECK_EQUAL(20, embeddedGeo->getPointCount());
    HBOOST_CHECK_EQUAL(36, embeddedGeo->getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getVertexAttributeCount());
    HBOOST_CHECK_EQUAL(2, embeddedGeo->getPrimitiveAttributeCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getDetailAttributeCount());

    auto embeddedPrim = embeddedGeo->getPrimitive(0);
    HBOOST_CHECK(embeddedPrim->isType<Poly>());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_pack_fragments2
} // namespace bgeo
} // namespace ika
