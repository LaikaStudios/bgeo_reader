/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Sphere.h"

#include "util.h"

#include "Attribute.h"
#include "Detail.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

Sphere::Sphere(const Detail& detail)
    : Primitive(detail)
{
    memset(transform, 0, sizeof(transform));
}

/*virtual*/ void Sphere::loadData(UT_JSONParser &parser)
{
    parseBeginArray(parser);
    {
        parseArrayValueForKey(parser, "vertex", vertex);
        parseArrayValueForKey(parser, "transform", transform, 9);
    }
    parseEndArray(parser);
}

/*virtual*/ std::ostream& Sphere::encode(std::ostream& co) const
{
    Primitive::encode(co);
    co << "\n"
       << "    vertex = " << vertex << "\n"
       << "    transform = [";

    for (int i = 0; i < 9; ++i)
    {
        co << transform[i] << " ";
    }
    co << "]";

    return co;
}

void Sphere::getTranslate(fpreal64 translate[3]) const
{
    int64 pointIndex = detail.getPointIndexForVertex(vertex);
    const Attribute* attribute = detail.getPointAttributeByName("P");
    assert(attribute);
    attribute->data.copyTo(translate, 3, 1, pointIndex, 1);
}

void Sphere::getMatrix(double matrix[16]) const
{
    memcpy(matrix, transform, 3 * sizeof(double));
    memcpy(&matrix[4], &transform[3], 3 * sizeof(double));
    memcpy(&matrix[8], &transform[6], 3 * sizeof(double));
    matrix[3] = 0.0;
    matrix[7] = 0.0;
    matrix[11] = 0.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = 0.0;
    matrix[15] = 1.0;
}

} // namespace parser
} // namespace ika
} // namespace bgeo
