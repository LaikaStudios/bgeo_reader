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
#include "bgeo/parser/ReadError.h"

namespace ika
{
namespace bgeo
{
namespace test_Bgeo
{

// FIXME: split these up into separate tests and make smaller test cases for
// each subsection to simplify debugging failed tests.

HBOOST_AUTO_TEST_CASE(read_missing_file_should_throw_read_error)
{
    HBOOST_CHECK_THROW(Bgeo("missing.geo"), parser::ReadError);
}

HBOOST_AUTO_TEST_CASE(bounds_from_grid_geo)
{
    Bgeo bgeo("geo/grid.geo");

    double bound[6] = { 0 };
    bgeo.getBoundingBox(bound);

    HBOOST_CHECK_CLOSE(-0.5, bound[0], 0.001);
    HBOOST_CHECK_CLOSE(0.5, bound[1], 0.001);
    HBOOST_CHECK_CLOSE(0.0, bound[2], 0.001);
    HBOOST_CHECK_CLOSE(0.0, bound[3], 0.001);
    HBOOST_CHECK_CLOSE(-0.5, bound[4], 0.001);
    HBOOST_CHECK_CLOSE(0.5, bound[5], 0.001);

}

} // namespace test_Bgeo
} // namespace bgeo
} // namespace ika
