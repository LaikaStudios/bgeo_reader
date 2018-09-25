/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Run.h"

#include <cassert>

#include "PrimitiveFactory.h"
#include "parser/Run.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(Run, Primitive)

Run::Run(const parser::Run& run)
    : m_run(run)
{
}

Bgeo::PrimitivePtr Run::getTemplatePrimitive() const
{
    assert(m_run.runPrimitive);
    return factory::create(*m_run.runPrimitive);
}

} // namespace bgeo
} // namespace ika
