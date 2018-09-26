/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/Primitive.h"

namespace ika
{
namespace bgeo
{
namespace test_Primitive
{

class SubPrimitive : public Primitive
{
    RTTI_DECLARE(SubPrimitive, Primitive)
};

RTTI_DEFINE(SubPrimitive, Primitive)

HBOOST_AUTO_TEST_CASE(primitive_is_type_primitive)
{
    Primitive primitive;
    HBOOST_CHECK(primitive.isType<Primitive>());
    HBOOST_CHECK_EQUAL(&primitive, primitive.cast<Primitive>());

    HBOOST_CHECK(!primitive.isType<SubPrimitive>());
    HBOOST_CHECK(!primitive.cast<SubPrimitive>());

    HBOOST_CHECK_EQUAL(Primitive::Type, primitive.getType());
    HBOOST_CHECK_NE(SubPrimitive::Type, primitive.getType());
}

HBOOST_AUTO_TEST_CASE(subprimitive_is_type_primitive)
{
    SubPrimitive sub;

    HBOOST_CHECK(sub.isType<SubPrimitive>());
    HBOOST_CHECK(sub.isType<Primitive>());
    HBOOST_CHECK_EQUAL(&sub, sub.cast<SubPrimitive>());

    Primitive& primitive = sub;

    HBOOST_CHECK(primitive.isType<SubPrimitive>());
    HBOOST_CHECK_EQUAL(&primitive, sub.cast<Primitive>());
    HBOOST_CHECK_EQUAL(&sub, primitive.cast<SubPrimitive>());

    HBOOST_CHECK_EQUAL(SubPrimitive::Type, sub.getType());
    HBOOST_CHECK_EQUAL(SubPrimitive::Type, primitive.getType());
}

} // namespace test_Primitive
} // namespace bgeo
} // namespace ika
