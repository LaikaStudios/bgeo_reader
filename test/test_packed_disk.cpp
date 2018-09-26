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
namespace test_packed_disk
{

class PackedDiskFixture
{
public:
    PackedDiskFixture()
        : bgeo("geo/packed_disk.bgeo")
    {
    }

protected:
    Bgeo bgeo;
};

namespace
{

float expected_P[] = {
    0, 0, 0
};

double expected_xform[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

} // namespace anonymous

HBOOST_FIXTURE_TEST_SUITE(test_packed_disk, PackedDiskFixture)

HBOOST_AUTO_TEST_CASE(test_packed_disk_counts)
{
    HBOOST_CHECK_EQUAL(1, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPointAttributeCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveAttributeCount());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_P)
{
    std::vector<float> P;
    bgeo.getP(P);
    HBOOST_CHECK_EQUAL_COLLECTIONS(&expected_P[0], &expected_P[3], P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_path)
{
    auto attribute = bgeo.getPrimitiveAttributeByName("path");
    HBOOST_CHECK(attribute);

    std::vector<std::string> strings;
    attribute->getStrings(strings);
    HBOOST_CHECK_EQUAL(1, strings.size());
    HBOOST_CHECK_EQUAL("sphere.bgeo", strings[0]);

    HBOOST_CHECK_EQUAL(bgeo::parser::storage::Int32,
                      attribute->getFundamentalType());
    std::vector<int32> indices;
    attribute->getData(indices);
    HBOOST_CHECK_EQUAL(1, indices.size());
    HBOOST_CHECK_EQUAL(0, indices[0]);
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_one_packed_primitive)
{
    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive);
    HBOOST_CHECK(primitive->isType<PackedDisk>());
}

HBOOST_AUTO_TEST_CASE(test_packed_disk_packed_parameters)
{
    auto primitive = bgeo.getPrimitive(0);
    assert(primitive);

    auto disk = primitive->cast<PackedDisk>();
    assert(disk);

    // translate
    double translate[3] = { -1 };
    disk->getTranslate(translate);
    HBOOST_CHECK_CLOSE(expected_P[0], translate[0], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[1], translate[1], 0.0001);
    HBOOST_CHECK_CLOSE(expected_P[2], translate[2], 0.0001);

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

    // filename
    HBOOST_CHECK_EQUAL("sphere.bgeo", disk->getFilename());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_packed_disk
} // namespace bgeo
} // namespace ika
