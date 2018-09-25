/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PRIMITIVE_FACTORY_H
#define BGEO_PRIMITIVE_FACTORY_H

#include <map>

#include <UT/UT_String.h>

#include "Bgeo.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Primitive;
}

namespace factory
{

typedef std::map<UT_String, std::shared_ptr<Bgeo>> EmbeddedGeoMap;
Bgeo::PrimitivePtr create(const Bgeo& bgeo,
                          const parser::Primitive& parserPrimitive,
                          EmbeddedGeoMap& embeddedGeoMap,
                          size_t index);

}
}
}

#endif // BGEO_PRIMITIVE_FACTORY_H
