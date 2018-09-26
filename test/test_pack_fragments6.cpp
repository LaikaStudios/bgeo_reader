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
namespace test_pack_fragments6
{

class PackFragments6Fixture
{
public:
    PackFragments6Fixture()
        : bgeo("geo/pack_fragments6.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

std::vector<double> expected_xform = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

std::vector<float> expected_P = {
    0.128816411, 0.208352581, 0.0845114291,
    0.11558944, -0.22020793, 0.147876382,
    0, -0.254086345, -0.179487646,
    0, 0.167343348, -0.216182113,
    -0.225738809, -0.0983223915, 0.0660327226,
    -0.165048614, 0.217605233, 0.247685909
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_pack_fragments6, PackFragments6Fixture)

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_counts)
{
    HBOOST_CHECK_EQUAL(6, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(6, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(6, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_P)
{
    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_name)
{
    auto attribute = bgeo.getPointAttributeByName("name");
    HBOOST_REQUIRE(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);

    std::vector<std::string> expected_names = {
        "piece0",
        "piece1",
        "piece2",
        "piece3",
        "piece4",
        "piece5"
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_names.begin(), expected_names.end(),
                                  strings.begin(), strings.end());

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);

    std::vector<int32> expected_indices = {
        0, 1, 2, 3, 4, 5
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_indices.begin(),
                                  expected_indices.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_path)
{
    auto attribute = bgeo.getPrimitiveAttributeByName("path");
    HBOOST_REQUIRE(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);

    std::vector<std::string> expected_paths = {
        "op:/obj/packed/assemble1/pack/piece0",
        "op:/obj/packed/assemble1/pack/piece1",
        "op:/obj/packed/assemble1/pack/piece2",
        "op:/obj/packed/assemble1/pack/piece3",
        "op:/obj/packed/assemble1/pack/piece4",
        "op:/obj/packed/assemble1/pack/piece5"
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_paths.begin(), expected_paths.end(),
                                  strings.begin(), strings.end());

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);

    std::vector<int32> expected_indices = {
        0, 1, 2, 3, 4, 5
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_indices.begin(),
                                  expected_indices.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_primitives_are_fragments)
{
    for (int i = 0; i < 6; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_REQUIRE(primitive);
        HBOOST_CHECK(primitive->isType<PackedFragment>());
    }
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_packed_parameters_common)
{
    for (int i = 0; i < 6; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_REQUIRE(primitive);

        auto fragment = primitive->cast<PackedFragment>();
        HBOOST_REQUIRE(fragment);

        // extra transform
        double xform[16] = { -1 };
        fragment->getExtraTransform(xform);
        HBOOST_CHECK_EQUAL_COLLECTIONS(expected_xform.begin(), expected_xform.end(),
                                      &xform[0], &xform[16]);

        // name attribute
        HBOOST_CHECK_EQUAL("name", fragment->getNameAttribute());
    }
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_fragment_parameters_0)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    // bounding box
    HBOOST_CHECK(fragment->hasBoundingBox());

    double bounds[6] = { -1 };
    fragment->getBoundingBox(bounds);

    double expected_bounds[] = {
        -0.242367178201675415, 0.5,
        -0.0832948461174964905, 0.5,
        -0.330977141857147217, 0.5
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    fragment->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[0], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    fragment->getPivot(pivot);
    HBOOST_CHECK_CLOSE(expected_P[0], pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], pivot[2], 0.0001);

    // name
    HBOOST_CHECK_EQUAL("piece0", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_fragment_parameters_1)
{
    auto primitive = bgeo.getPrimitive(1);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    // bounding box
    HBOOST_CHECK(fragment->hasBoundingBox());

    double bounds[6] = { -1 };
    fragment->getBoundingBox(bounds);

    double expected_bounds[] = {
        -0.268821120262145996, 0.5,
        -0.5, 0.0595841407775878906,
        -0.204247251152992249, 0.5
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    fragment->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[3], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[4], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[5], translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    fragment->getPivot(pivot);
    HBOOST_CHECK_CLOSE(expected_P[3], pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[4], pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[5], pivot[2], 0.0001);

    // name
    HBOOST_CHECK_EQUAL("piece1", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_fragment_parameters_2)
{
    auto primitive = bgeo.getPrimitive(2);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    // bounding box
    HBOOST_CHECK(fragment->hasBoundingBox());

    double bounds[6] = { -1 };
    fragment->getBoundingBox(bounds);

    double expected_bounds[] = {
        -0.5, 0.5,
        -0.5, -0.00817271973937749863,
        -0.5, 0.14102470874786377
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    fragment->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[6], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[7], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[8], translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    fragment->getPivot(pivot);
    HBOOST_CHECK_CLOSE(expected_P[6], pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[7], pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[8], pivot[2], 0.0001);

    // name
    HBOOST_CHECK_EQUAL("piece2", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_fragment_parameters_3)
{
    auto primitive = bgeo.getPrimitive(3);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    // bounding box
    HBOOST_CHECK(fragment->hasBoundingBox());

    double bounds[6] = { -1 };
    fragment->getBoundingBox(bounds);

    double expected_bounds[] = {
        -0.5, 0.5,
        -0.165313303470611572, 0.5,
        -0.5, 0.0676357671618461609
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    fragment->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[9], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[10], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[11], translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    fragment->getPivot(pivot);
    HBOOST_CHECK_CLOSE(expected_P[9], pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[10], pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[11], pivot[2], 0.0001);

    // name
    HBOOST_CHECK_EQUAL("piece3", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_fragment_parameters_4)
{
    auto primitive = bgeo.getPrimitive(4);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    // bounding box
    HBOOST_CHECK(fragment->hasBoundingBox());

    double bounds[6] = { -1 };
    fragment->getBoundingBox(bounds);

    double expected_bounds[] = {
        -0.5, 0.0485223792493343353,
        -0.5, 0.303355216979980469,
        -0.367934554815292358, 0.5
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    fragment->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[12], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[13], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[14], translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    fragment->getPivot(pivot);
    HBOOST_CHECK_CLOSE(expected_P[12], pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[13], pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[14], pivot[2], 0.0001);

    // name
    HBOOST_CHECK_EQUAL("piece4", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_fragment_parameters_5)
{
    auto primitive = bgeo.getPrimitive(5);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    // bounding box
    HBOOST_CHECK(fragment->hasBoundingBox());

    double bounds[6] = { -1 };
    fragment->getBoundingBox(bounds);

    double expected_bounds[] = {
        -0.5, 0.169902771711349487,
        -0.0647895187139511108, 0.5,
        -0.00462818797677755356, 0.5
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);

    // translate
    double translate[3] = { -1 };
    fragment->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[15], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[16], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[17], translate[2], 0.0001);

    // pivot
    double pivot[3] = { -1 };
    fragment->getPivot(pivot);
    HBOOST_CHECK_CLOSE(expected_P[15], pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[16], pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[17], pivot[2], 0.0001);

    // name
    HBOOST_CHECK_EQUAL("piece5", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_embedded_geo)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_REQUIRE(primitive);

    auto fragment = primitive->cast<PackedFragment>();
    HBOOST_REQUIRE(fragment);

    auto embeddedGeo = fragment->getEmbeddedGeo();
    HBOOST_CHECK(embeddedGeo);

    HBOOST_CHECK_EQUAL(116, embeddedGeo->getPointCount());
    HBOOST_CHECK_EQUAL(216, embeddedGeo->getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getVertexAttributeCount());
    HBOOST_CHECK_EQUAL(2, embeddedGeo->getPrimitiveAttributeCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getDetailAttributeCount());

    auto embeddedPrim = embeddedGeo->getPrimitive(0);
    HBOOST_CHECK(embeddedPrim->isType<Poly>());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_pack_fragments6
} // namespace bgeo
} // namespace ika
