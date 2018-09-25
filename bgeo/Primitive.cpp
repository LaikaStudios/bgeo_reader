/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Primitive.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE_BASE(Primitive)

Primitive::Primitive()
{
}

/*virtual*/ Primitive::~Primitive() = default;

int32_t Primitive::getVertexCount() const
{
    return 0;
}

} // namespace ika
} // namespace bgeo
