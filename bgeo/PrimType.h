/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PRIMTYPE_H
#define BGEO_PRIMTYPE_H

namespace ika
{
namespace bgeo
{

enum PrimType
{
    UnknownPrimType = 0,
    PolyPrimType,
    RunPrimType,
    SpherePrimType,
    VolumePrimType
};

const char* toString(PrimType type);
PrimType toPrimType(const char* type);

} // namespace ika
} // namespace bgeo

#endif // BGEO_PRIMTYPE_H
