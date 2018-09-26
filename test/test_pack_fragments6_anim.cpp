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
namespace test_pack_fragments6_anim
{

class PackFragments6AnimFixture
{
public:
    PackFragments6AnimFixture()
        : bgeo("geo/pack_fragments6_anim_16.0020.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

std::vector<float> expected_P = {
    1.05895591, 0.285170734, 0.807400465,
    0.380258828, 0.249864608, 0.380244672,
    0.017419463, 0.208380997, -0.334947854,
    0.0339404829, 0.24616015, -1.13657546,
    -0.535132408, 0.34420222, 0.583373249,
    -1.40871906, 0.333948344, 1.63560438
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_pack_fragments6_anim, PackFragments6AnimFixture)

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_counts)
{
    HBOOST_CHECK_EQUAL(6, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(6, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(6, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(28, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(2, bgeo.getPrimitiveAttributeCount());
    HBOOST_CHECK_EQUAL(3, bgeo.getDetailAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_P)
{
    std::vector<float> P;
    bgeo.getP(P);

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_name)
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

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_path)
{
    auto attribute = bgeo.getPrimitiveAttributeByName("path");
    HBOOST_REQUIRE(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);

    std::vector<std::string> expected_paths = {
        "op:/obj/fracture/assemble1/pack/piece0",
        "op:/obj/fracture/assemble1/pack/piece1",
        "op:/obj/fracture/assemble1/pack/piece2",
        "op:/obj/fracture/assemble1/pack/piece3",
        "op:/obj/fracture/assemble1/pack/piece4",
        "op:/obj/fracture/assemble1/pack/piece5"
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

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_primitives_are_fragments)
{
    for (int i = 0; i < 6; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_REQUIRE(primitive);
        HBOOST_CHECK(primitive->isType<PackedFragment>());
    }
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_packed_parameters_common)
{
    for (int i = 0; i < 6; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_REQUIRE(primitive);

        auto fragment = primitive->cast<PackedFragment>();
        HBOOST_REQUIRE(fragment);

        // name attribute
        HBOOST_CHECK_EQUAL("name", fragment->getNameAttribute());
    }
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_fragment_parameters_0)
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
        -0.242365837097167969, 0.5,
        0.670282125473022461, 1.25357699394226074,
        -0.330976128578186035, 0.5
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
    HBOOST_CHECK_CLOSE(0.235550165, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.99797374, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0.150272042, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    fragment->getExtraTransform(xform);

    double expected_xform[16] = {
        -0.0518918045862753474, -0.998043174790356979, -0.0348870767074283689, 0,
        0.797668590893775731, -0.0624418255500654301, 0.599854907535661508, 0,
        -0.600859459364777249, 0.00329917713326104665, 0.799347861274998572, 0,
        0, 0, 0, 1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);

    // name
    HBOOST_CHECK_EQUAL("piece0", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_fragment_parameters_1)
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
        -0.268821775913238525, 0.5,
        0.253576993942260742, 0.813160300254821777,
        -0.204243898391723633, 0.5
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
    HBOOST_CHECK_CLOSE(0.212833121, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.503501475, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0.246036574, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    fragment->getExtraTransform(xform);

    double expected_xform[16] = {
        0.999428612448282516, -6.9286906325881756e-06, 0.0337990917395382603, 0,
        8.35459815014941818e-06, 1.00000000091885499, -4.20465176045956289e-05, 0,
        -0.0337990923843057844, 4.23048727781376782e-05, 0.999428613354261475, 0,
        0, 0, 0, 1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);

    // name
    HBOOST_CHECK_EQUAL("piece1", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_fragment_parameters_2)
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
        0.253576993942260742, 0.745403587818145752,
        -0.5, 0.141023203730583191
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
    HBOOST_CHECK_CLOSE(0.0103541994, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.461953759, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(-0.263642013, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    fragment->getExtraTransform(xform);

    double expected_xform[16] = {
        0.9803066436124932, 1.68166665777458304e-06, 0.197481550542809192, 0,
        -1.15584012746216497e-05, 1.00000000126048794, 4.88608178032138438e-05, 0,
        -0.197481551204991224,-5.01811565537572078e-05, 0.980306644182303288, 0,
        0, 0, 0, 1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);

    // name
    HBOOST_CHECK_EQUAL("piece2", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_fragment_parameters_3)
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
        0.588265895843505859, 1.25357699394226074,
        -0.5, 0.0676364079117774963
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
    HBOOST_CHECK_CLOSE(-0.039192643, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.959815145, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(-0.280727088, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    fragment->getExtraTransform(xform);

    double expected_xform[16] = {
        0.999904219062128896, -0.00235137996785824473, -0.0136395968421466861, 0,
        -0.0138033897079322763, -0.0970109708050519437, -0.99518750038440984, 0,
        0.00101687425842656213,0.995280499977191035, -0.0970340961279856778, 0,
        0, 0, 0, 1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);

    // name
    HBOOST_CHECK_EQUAL("piece3", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_fragment_parameters_4)
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
        -0.5, 0.0485223196446895599,
        0.253576993942260742, 1.05693364143371582,
        -0.367936700582504272, 0.5
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
    HBOOST_CHECK_CLOSE(-0.313334644, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.583304524, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0.15184693, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    fragment->getExtraTransform(xform);

    double expected_xform[16] = {
        0.17022728703553916, -0.0646950902099336644, 0.983278818787320708, 0,
        0.0678319475133114247, 0.996244820432252376, 0.0538049852109514989, 0,
        -0.983067458448507403, 0.057538634901671791, 0.173976479649089022, 0,
        0, 0, 0, 1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);

    // name
    HBOOST_CHECK_EQUAL("piece4", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_fragment_parameters_5)
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
        -0.5, 0.169905036687850952,
        0.688788354396820068, 1.25357699394226074,
        -0.00462805712595582008, 0.5
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
    HBOOST_CHECK_CLOSE(-0.227203056, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(1.02395141, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0.310710579, pivot[2], 0.0001);

    // extra transform
    double xform[16] = { -1 };
    fragment->getExtraTransform(xform);

    double expected_xform[16] = {
        0.392875552927262728, 0.892322469276475183, 0.222281886919948407, 0,
        -0.883014969801582894, 0.433556421756600086, -0.179758958278906339, 0,
        -0.256774713616727657, -0.125655352540829379, 0.958267906504157829, 0,
        0, 0, 0, 1
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                  &xform[0], &xform[16]);

    // name
    HBOOST_CHECK_EQUAL("piece5", fragment->getName());
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_embedded_geo)
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
    HBOOST_CHECK_EQUAL(2, embeddedGeo->getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getVertexAttributeCount());
    HBOOST_CHECK_EQUAL(2, embeddedGeo->getPrimitiveAttributeCount());
    HBOOST_CHECK_EQUAL(1, embeddedGeo->getDetailAttributeCount());

    auto embeddedPrim = embeddedGeo->getPrimitive(0);
    HBOOST_CHECK(embeddedPrim->isType<Poly>());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_pack_fragments6_anim
} // namespace bgeo
} // namespace ika
