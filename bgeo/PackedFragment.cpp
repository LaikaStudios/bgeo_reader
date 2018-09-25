/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PackedFragment.h"

#include "parser/PackedFragment.h"

#include "Bgeo.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(PackedFragment, PackedGeometry)

PackedFragment::PackedFragment(const parser::PackedFragment& fragment,
                               std::shared_ptr<Bgeo> embedded)
    : PackedGeometry(fragment, embedded),
      m_fragment(fragment)
{
}

std::string PackedFragment::getNameAttribute() const
{
    return m_fragment.attribute.toStdString();
}

std::string PackedFragment::getName() const
{
    return m_fragment.name.toStdString();
}

std::string PackedFragment::getEmbeddedKey() const
{
    return m_fragment.getEmbeddedKey().toStdString();
}

} // namespace ika
} // namespace bgeo
