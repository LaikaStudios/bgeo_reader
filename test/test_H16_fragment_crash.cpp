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
#include "bgeo/Poly.h"

namespace ika
{
namespace bgeo
{
namespace test_H16_fragment_crash
{

HBOOST_AUTO_TEST_CASE(test_H16_fragment_crash)
{
    Bgeo bgeo("geo/H16_fragment_crash.bgeo");

    HBOOST_CHECK_EQUAL(202, bgeo.getPointCount());
    HBOOST_CHECK_EQUAL(400, bgeo.getTotalVertexCount());
    HBOOST_CHECK_EQUAL(1, bgeo.getPrimitiveCount());

    auto primitive = bgeo.getPrimitive(0);
    HBOOST_CHECK(primitive->isType<Poly>());
    HBOOST_CHECK_EQUAL(400, primitive->getVertexCount());

    const Poly* poly = primitive->cast<Poly>();
    HBOOST_CHECK(poly);

    HBOOST_CHECK_EQUAL(82, poly->getFaceCount());

    std::vector<int32_t> vertices;
    poly->getVertexList(vertices);

    HBOOST_CHECK_EQUAL(400, vertices.size());

    std::vector<int32_t> startIndices;
    poly->getStartIndices(startIndices);

    HBOOST_CHECK_EQUAL(82 + 1, startIndices.size());
}

} // namespace test_grid
} // namespace bgeo
} // namespace ika
