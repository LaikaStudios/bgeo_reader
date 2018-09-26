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
#include "bgeo/Volume.h"
#include "bgeo/parser/storage.h"

namespace ika
{
namespace bgeo
{
namespace test_atmos_vol_lo
{

// regression test to make sure loading this file doesn't crash.
// crashing was due to varmap detail attribute not being supported.
HBOOST_AUTO_TEST_CASE(test_load)
{
    Bgeo bgeo("geo/atmos_vol_lo.0054.bgeo");
}

} // namespace test_atmos_vol_lo
} // namespace bgeo
} // namespace ika
