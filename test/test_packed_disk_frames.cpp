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
#include "bgeo/PackedDisk.h"

namespace ika
{
namespace bgeo
{
namespace test_packed_disk_frames
{

class PackedDiskFramesFixture
{
public:
    PackedDiskFramesFixture()
        : bgeo("geo/packed_disk_frames.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

float expected_P[] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};

double expected_xform[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_packed_disk_frames, PackedDiskFramesFixture)

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_counts)
{
    HBOOST_CHECK_EQUAL(4, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(4, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_P)
{
    std::vector<float> P;
    bgeo.getP(P);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[12], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_path)
{
    auto attribute = bgeo.getPrimitiveAttributeByName("path");
    HBOOST_CHECK(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);
    HBOOST_CHECK_EQUAL(2, strings.size());
    HBOOST_CHECK_EQUAL("sphere.%F.bgeo", strings[0]);
    HBOOST_CHECK_EQUAL("sphere.%F4.bgeo", strings[1]);

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);
    HBOOST_CHECK_EQUAL(4, indices.size());
    HBOOST_CHECK_EQUAL(0, indices[0]);
    HBOOST_CHECK_EQUAL(1, indices[1]);
    HBOOST_CHECK_EQUAL(0, indices[2]);
    HBOOST_CHECK_EQUAL(1, indices[3]);
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_4_packed_primitives)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        HBOOST_CHECK(primitive);
        HBOOST_CHECK(primitive->isType<PackedDisk>());
    }
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_common_packed_parameters)
{
    for (int i = 0; i < 4; ++i)
    {
        auto primitive = bgeo.getPrimitive(i);
        assert(primitive);

        auto disk = primitive->cast<PackedDisk>();
        assert(disk);

        // translate
        double translate[3] = { -1 };
        disk->getTranslate(translate);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 0], translate[0], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 1], translate[1], 0.0001);
        HBOOST_CHECK_CLOSE(expected_P[i * 3 + 2], translate[2], 0.0001);

        // pivot
        double pivot[3] = { -1 };
        disk->getPivot(pivot);
        double expected_pivot[3] = {
            0, 0, 0
        };
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_pivot[0], &expected_pivot[3],
                                      &pivot[0], &pivot[3]);
        // extra transform
        double xform[16] = { -1 };
        disk->getExtraTransform(xform);
        HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_xform[0], &expected_xform[16],
                                      &xform[0], &xform[16]);

        // no bounding box
        HBOOST_CHECK(!disk->hasBoundingBox());
    }
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_filename_0)
{
    auto primitive = bgeo.getPrimitive(0);
    assert(primitive);

    auto disk = primitive->cast<PackedDisk>();
    assert(disk);

    HBOOST_CHECK_EQUAL("sphere.11.bgeo", disk->getFilename());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_filename_1)
{
    auto primitive = bgeo.getPrimitive(1);
    assert(primitive);

    auto disk = primitive->cast<PackedDisk>();
    assert(disk);

    HBOOST_CHECK_EQUAL("sphere.0011.bgeo", disk->getFilename());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_filename_2)
{
    auto primitive = bgeo.getPrimitive(2);
    assert(primitive);

    auto disk = primitive->cast<PackedDisk>();
    assert(disk);

    HBOOST_CHECK_EQUAL("sphere.5.bgeo", disk->getFilename());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_frames_filename_3)
{
    auto primitive = bgeo.getPrimitive(3);
    assert(primitive);

    auto disk = primitive->cast<PackedDisk>();
    assert(disk);

    HBOOST_CHECK_EQUAL("sphere.0005.bgeo", disk->getFilename());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_packed_disk_frames
} // namespace bgeo
} // namespace ika
