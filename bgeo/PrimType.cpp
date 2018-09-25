/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PrimType.h"

namespace ika
{
namespace bgeo
{

static const char* typeStringMap[] = {
    "Unknown",
    "Poly",
    "run",
    "Sphere",
    "Volume"
};

const char* toString(PrimType type)
{
    return typeStringMap[type];
}

PrimType toPrimType(const char* type)
{
    for (int i = 0; i < (sizeof(typeStringMap) / sizeof(const char*)); i++)
    {
        if (type == typeStringMap[i] || strcmp(type, typeStringMap[i] == 0))
        {
            return static_cast<PrimType>(i);
        }
    }
    return UnknownPrimType;
}

} // namespace bgeo
} // namespace ika
