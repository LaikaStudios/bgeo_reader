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

namespace ika
{
namespace bgeo
{
namespace test_empty
{

HBOOST_AUTO_TEST_CASE(test_empty)
{
    Bgeo bgeo("geo/empty.bgeo");

    HBOOST_CHECK_EQUAL(0, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getPrimitiveCount());
}

HBOOST_AUTO_TEST_CASE(test_empty_15)
{
    Bgeo bgeo("geo/empty_15.bgeo");

    HBOOST_CHECK_EQUAL(0, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getPrimitiveCount());
}

HBOOST_AUTO_TEST_CASE(test_empty_16)
{
    Bgeo bgeo("geo/empty.bgeo");

    HBOOST_CHECK_EQUAL(0, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(0, bgeo.getPrimitiveCount());
}

} // namespace test_empty
} // namespace bgeo
} // namespace ika
