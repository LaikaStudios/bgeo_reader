/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

// cube_multi_groups
// When the number of primitives is >= 20, primitive groups change over from
// "i8" (array of 0 or 1 values) to "boolRLE" which a list of number value pairs
// i.e. [2,false,3,true,3,false]. cube_multi_groups tests these types of groups.

#include <iostream>

#include <hboost/test/unit_test.hpp>

#include "bgeo/Bgeo.h"
#include "bgeo/Poly.h"

namespace ika
{
namespace bgeo
{
namespace test_cube_multi_groups
{

class TestCubeBasicsFixture
{
public:
    TestCubeBasicsFixture()
        : bgeo("geo/cube_multi_groups.geo")
    {
    }

protected:
    Bgeo bgeo;
};

HBOOST_FIXTURE_TEST_SUITE(test_cube_multi_groups, TestCubeBasicsFixture)

HBOOST_AUTO_TEST_CASE(test_counts)
{
    HBOOST_CHECK_EQUAL(32, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(96, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());
}

HBOOST_AUTO_TEST_CASE(test_group_count)
{
    HBOOST_CHECK_EQUAL(2, bgeo.getPrimitiveGroupCount());
}

HBOOST_AUTO_TEST_CASE(test_group_0)
{
    std::string name = bgeo.getPrimitiveGroupName(0);
    std::vector<int32_t> indices;
    bgeo.getPrimitiveGroup(0, indices);

    HBOOST_CHECK_EQUAL("faces", name);

    std::vector<int32_t> expected = {
        2, 3, 4,
        8, 9, 10,
        14, 15, 16,
        20, 21, 22
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_CASE(test_group_1)
{
    std::string name = bgeo.getPrimitiveGroupName(1);
    std::vector<int32_t> indices;
    bgeo.getPrimitiveGroup(1, indices);

    HBOOST_CHECK_EQUAL("all", name);

    std::vector<int32_t> expected = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  indices.begin(), indices.end());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_cube_primgroup
} // namespace bgeo
} // namespace ika
