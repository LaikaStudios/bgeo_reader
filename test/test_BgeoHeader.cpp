/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/BgeoHeader.h"
#include "bgeo/parser/ReadError.h"

namespace ika
{
namespace bgeo
{
namespace test_BgeoHeader
{

HBOOST_AUTO_TEST_CASE(read_missing_file_should_throw_read_error)
{
    HBOOST_CHECK_THROW(BgeoHeader("missing.geo"), parser::ReadError);
}

HBOOST_AUTO_TEST_CASE(test_poly)
{
    BgeoHeader header("geo/grid.geo");
    HBOOST_CHECK_EQUAL("13.0.343", header.getFileVersion());
    HBOOST_CHECK_EQUAL("Houdini 13.0.343", header.getSoftware());
    HBOOST_CHECK_EQUAL("2014-08-19 12:21:45", header.getDate());
    HBOOST_CHECK_EQUAL("zundert", header.getHostName());
    HBOOST_CHECK_EQUAL("vangogh", header.getArtist());
    HBOOST_CHECK_EQUAL("          1 Polygon\n", header.getPrimCountSummary());
    HBOOST_CHECK_EQUAL("     2 point attributes:\tuv, P\n", header.getAttributeSummary());
    HBOOST_CHECK_EQUAL("", header.getAttributeRanges());

    double bound[6] = { 0 };
    header.getBoundingBox(bound);

    HBOOST_CHECK_CLOSE(-0.5, bound[0], 0.001);
    HBOOST_CHECK_CLOSE(0.5, bound[1], 0.001);
    HBOOST_CHECK_CLOSE(0.0, bound[2], 0.001);
    HBOOST_CHECK_CLOSE(0.0, bound[3], 0.001);
    HBOOST_CHECK_CLOSE(-0.5, bound[4], 0.001);
    HBOOST_CHECK_CLOSE(0.5, bound[5], 0.001);
}

HBOOST_AUTO_TEST_CASE(test_bad_header)
{
    HBOOST_CHECK_THROW(BgeoHeader("geo/badheader.geo"), parser::ReadError);
}

} // namespace test_BgeoHeader
} // namespace bgeo
} // namespace ika
