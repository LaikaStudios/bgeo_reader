/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Sphere.h"

#include "parser/Sphere.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(Sphere, Primitive)

Sphere::Sphere(const parser::Sphere& sphereParser)
    : m_sphere(sphereParser)
{
}

/*virtual*/ int32_t Sphere::getVertexCount() const
{
    return 1;
}

void Sphere::getTranslate(double translate[3]) const
{
    m_sphere.getTranslate(translate);
}

void Sphere::getExtraTransform(double transform[16]) const
{
    m_sphere.getMatrix(transform);
}

} // namespace ika
} // namespace bgeo
