/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_SPHERE_H
#define BGEO_SPHERE_H

#include <cinttypes>

#include "Primitive.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Sphere;
}

class Sphere : public Primitive
{
    RTTI_DECLARE(Sphere, Primitive)

public:
    Sphere(const parser::Sphere& sphereParser);

    /*virtual*/ int32_t getVertexCount() const;

    void getTranslate(double translate [3]) const;
    void getExtraTransform(double transform[16]) const;

private:
    const parser::Sphere& m_sphere;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_SPHERE_H
