/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/parser/Detail.h"
#include "bgeo/parser/Poly.h"
#include "bgeo/Primitive.h"
#include "bgeo/Bgeo.h"
#include "bgeo/Poly.h"

namespace ika
{
namespace bgeo
{
namespace test_Poly
{

HBOOST_AUTO_TEST_CASE(poly_is_type_primitive)
{
    auto detail = std::make_shared<parser::Detail>();
    Bgeo bgeo(detail);
    parser::Poly parserPoly(*detail);

    Poly poly(bgeo, parserPoly);
    HBOOST_CHECK(poly.isType<Primitive>());
    HBOOST_CHECK_EQUAL(&poly, poly.cast<Primitive>());
    HBOOST_CHECK(poly.isType<Poly>());
    HBOOST_CHECK_EQUAL(&poly, poly.cast<Poly>());

    Primitive& primitive = poly;
    HBOOST_CHECK(primitive.isType<Primitive>());
    HBOOST_CHECK_EQUAL(&primitive, primitive.cast<Primitive>());
    HBOOST_CHECK(primitive.isType<Poly>());
    HBOOST_CHECK_EQUAL(&primitive, primitive.cast<Poly>());
}

} // namespace test_Primitive
} // namespace bgeo
} // namespace ika
