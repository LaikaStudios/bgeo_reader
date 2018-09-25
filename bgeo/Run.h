/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_RUN_H
#define BGEO_RUN_H

#include "rtti.h"
#include "Primitive.h"
#include "Bgeo.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Run;
}

class Run: public Primitive
{
    RTTI_DECLARE(Run, Primitive)

public:
    // FIXME probably ought to be shared ptr
    Run(const parser::Run& run);

    Bgeo::PrimitivePtr getTemplatePrimitive() const;

private:
    const parser::Run& m_run;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_RUN_H
