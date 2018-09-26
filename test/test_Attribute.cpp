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
#include "bgeo/Attribute.h"

namespace ika
{
namespace bgeo
{
namespace test_Attribute
{

class AttributeFixture
{
public:
    AttributeFixture()
        : bgeo("geo/cube_primgroup.bgeo")
    {
        attribute = bgeo.getPointAttributeByName("P");
        HBOOST_REQUIRE(attribute);
    }

protected:
    Bgeo bgeo;
    Bgeo::AttributePtr attribute;
};

std::vector<float> expected_P = {
    -0.5, -0.5, -0.5, 1,
    0.5, -0.5, -0.5, 1,
    0.5, -0.5, 0.5, 1,
    -0.5, -0.5, 0.5, 1,
    -0.5, 0.5, -0.5, 1,
    0.5, 0.5, -0.5, 1,
    0.5, 0.5, 0.5, 1,
    -0.5, 0.5, 0.5, 1
};

HBOOST_FIXTURE_TEST_SUITE(test_attribute, AttributeFixture)

HBOOST_AUTO_TEST_CASE(copy_with_indices_all_available)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {0, 1, 2, 3, 4, 5, 6, 7});

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_beginning_indices)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {0, 1, 2, 3});

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.begin() + 16,
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_ending_indices)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {4, 5, 6, 7});

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin() + 16, expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_middle_indices)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {2, 3, 4, 5});

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin() + 8, expected_P.end() - 8,
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_random_indices_in_order_with_bookends)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {0, 2, 7});

    std::vector<float> expected_P = {
        -0.5, -0.5, -0.5, 1,
        0.5, -0.5, 0.5, 1,
        -0.5, 0.5, 0.5, 1
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_random_indices_in_order_without_bookends)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {1, 3, 6});

    std::vector<float> expected_P = {
        0.5, -0.5, -0.5, 1,
        -0.5, -0.5, 0.5, 1,
        0.5, 0.5, 0.5, 1
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_random_indices_out_of_order_all)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {1, 0, 3, 7, 5, 6, 2});

    std::vector<float> expected_P = {
        0.5, -0.5, -0.5, 1,
        -0.5, -0.5, -0.5, 1,
        -0.5, -0.5, 0.5, 1,
        -0.5, 0.5, 0.5, 1,
        0.5, 0.5, -0.5, 1,
        0.5, 0.5, 0.5, 1,
        0.5, -0.5, 0.5, 1
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_CASE(copy_random_indices_out_of_order_some)
{
    std::vector<float> P;

    attribute->getDataForIndices(P, {3, 7, 5});

    std::vector<float> expected_P = {
        -0.5, -0.5, 0.5, 1,
        -0.5, 0.5, 0.5, 1,
        0.5, 0.5, -0.5, 1
    };

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_P.begin(), expected_P.end(),
                                  P.begin(), P.end());
}

HBOOST_AUTO_TEST_SUITE_END()

} // namespace test_Attribute
} // namespace bgeo
} // namespace ika
