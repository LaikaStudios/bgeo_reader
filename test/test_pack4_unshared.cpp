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
namespace test_pack4_unshared
{

class Pack4UnsharedFixture
{
public:
    Pack4UnsharedFixture()
        : bgeo("geo/pack4_unshared.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

float expected_P[] = {
    1, 0.399999976, 0,
    5, 0.399999976, 0,
    9, 0.399999976, 0,
    13, 0.399999976, 0
};

double expected_transform[16] = {
    1, 0, 0, 0,
    0, 0, -1, 0,
    0, 1.399999976158142, 0, 0,
    0, 0, 0, 1
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_pack4_unshared, Pack4UnsharedFixture)

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_counts)
{
    HBOOST_CHECK_EQUAL(4, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_P)
{
    std::vector<float> P;
    bgeo.getP(P);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[12], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_4_packed_primitives)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_CHECK(primitive);
        HBOOST_CHECK(primitive->isType<PackedGeometry>());
    }
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_common_packed_parameters)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        assert(primitive);

        auto packed = primitive->cast<PackedGeometry>();
        assert(packed);

        // translate
        double translate[3] = { -1 };
        packed->getTranslate(translate);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 0], translate[0], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 1], translate[1], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 2], translate[2], 0.0001);

        // extra transform
        double expected_xform[] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        double xform[16] = { -1 };
        packed->getExtraTransform(xform);
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                      &xform[0], &xform[16]);
    }
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_bounds_pivot_0)
{
    auto primitive = bgeo.getPrimitive(0);
    assert(primitive);

    auto packed = primitive->cast<PackedGeometry>();
    assert(packed);

    // pivot
    double pivot[3] = { -1 };
    packed->getPivot(pivot);
    HBOOST_CHECK_CLOSE(1, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.399999976, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, pivot[2], 0.0001);

    // bounding box
    HBOOST_CHECK(packed->hasBoundingBox());

    double expected_bounds[] = {
        0, 2,
        -1, 1.79999995231628418,
        -1, 1
    };

    double bounds[6] = { -1 };
    packed->getBoundingBox(bounds);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_bounds_pivot_1)
{
    auto primitive = bgeo.getPrimitive(1);
    assert(primitive);

    auto packed = primitive->cast<PackedGeometry>();
    assert(packed);

    // pivot
    double pivot[3] = { -1 };
    packed->getPivot(pivot);
    HBOOST_CHECK_CLOSE(2, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.399999976, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, pivot[2], 0.0001);

    // bounding box
    double expected_bounds[] = {
        1, 3,
        -1, 1.79999995231628418,
        -1, 1
    };

    double bounds[6] = { -1 };
    packed->getBoundingBox(bounds);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_bounds_pivot_2)
{
    auto primitive = bgeo.getPrimitive(2);
    assert(primitive);

    auto packed = primitive->cast<PackedGeometry>();
    assert(packed);

    // pivot
    double pivot[3] = { -1 };
    packed->getPivot(pivot);
    HBOOST_CHECK_CLOSE(3, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.399999976, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, pivot[2], 0.0001);

    // bounding box
    HBOOST_CHECK(packed->hasBoundingBox());

    double expected_bounds[] = {
        2, 4,
        -1, 1.79999995231628418,
        -1, 1
    };

    double bounds[6] = { -1 };
    packed->getBoundingBox(bounds);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_bounds_pivot_3)
{
    auto primitive = bgeo.getPrimitive(3);
    assert(primitive);

    auto packed = primitive->cast<PackedGeometry>();
    assert(packed);

    // pivot
    double pivot[3] = { -1 };
    packed->getPivot(pivot);
    HBOOST_CHECK_CLOSE(4, pivot[0], 0.0001);
    HBOOST_CHECK_CLOSE(0.399999976, pivot[1], 0.0001);
    HBOOST_CHECK_CLOSE(0, pivot[2], 0.0001);

    // bounding box
    HBOOST_CHECK(packed->hasBoundingBox());

    double expected_bounds[] = {
        3, 5,
        -1, 1.79999995231628418,
        -1, 1
    };

    double bounds[6] = { -1 };
    packed->getBoundingBox(bounds);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_bounds[0], &expected_bounds[6],
                                  &bounds[0], &bounds[6]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_packed_detail_common)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
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

        auto sphere = embeddedPrim->cast<Sphere>();
        assert(sphere);

        double transform[16] = { -1 };
        sphere->getExtraTransform(transform);

        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_transform[0], &expected_transform[16],
                                      &transform[0], &transform[16]);
    }
}

HBOOST_AUTO_TEST_SUITE_END()

class Pack4UnsharedEmbeddedFixture
{
public:
    Pack4UnsharedEmbeddedFixture()
        : bgeo("geo/pack4_unshared.bgeo")
    {
        for (int i = 0; i < 4; ++i)
        {
            auto primitive = bgeo.getPrimitive(i);
            assert(primitive);

            auto packed = primitive->cast<PackedGeometry>();
            assert(packed);

            auto embeddedGeo = packed->getEmbeddedGeo();
            assert(embeddedGeo);

            embedded[i] = embeddedGeo->getPrimitive(0); // hold on to embedded sphere
            assert(embedded[i]);

            spheres[i] = embedded[i]->cast<Sphere>();
            assert(spheres[i]);
        }
    }

protected:
    Bgeo bgeo;
    Bgeo::PrimitivePtr embedded[4];
    const Sphere* spheres[4];
};

HBOOST_FIXTURE_TEST_SUITE(test_pack4_unshared_embedded, Pack4UnsharedEmbeddedFixture)

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_packed_embedded_translate_0)
{
    // sphere translate
    double expected_translate[3] = {
        1, 0.4000000059604645, 0
    };

    double translate[3] = { -1 };
    assert(spheres[0]);
    spheres[0]->getTranslate(translate);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_translate[0], &expected_translate[3],
                                  &translate[0], &translate[3]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_packed_embedded_translate_1)
{
    // sphere translate
    double expected_translate[3] = {
        2, 0.4000000059604645, 0
    };

    double translate[3] = { -1 };
    assert(spheres[1]);
    spheres[1]->getTranslate(translate);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_translate[0], &expected_translate[3],
                                  &translate[0], &translate[3]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_packed_embedded_translate_2)
{
    // sphere translate
    double expected_translate[3] = {
        3, 0.4000000059604645, 0
    };

    double translate[3] = { -1 };
    assert(spheres[2]);
    spheres[2]->getTranslate(translate);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_translate[0], &expected_translate[3],
                                  &translate[0], &translate[3]);
}

HBOOST_AUTO_TEST_CASE(test_pack4_unshared_packed_embedded_translate_3)
{
    // sphere translate
    double expected_translate[3] = {
        4, 0.4000000059604645, 0
    };

    double translate[3] = { -1 };
    assert(spheres[3]);
    spheres[3]->getTranslate(translate);

    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_translate[0], &expected_translate[3],
                                  &translate[0], &translate[3]);
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_pack4_unshared
} // namespace bgeo
} // namespace ika
