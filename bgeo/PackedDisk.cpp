/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PackedDisk.h"

#include "parser/PackedDisk.h"

#include "Bgeo.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(PackedDisk, PackedGeometry)

PackedDisk::PackedDisk(const parser::PackedDisk& disk)
    : PackedGeometry(disk, std::shared_ptr<Bgeo>()),
      m_disk(disk)
{
}

std::string PackedDisk::getFilename() const
{
    return m_disk.getFilename();
}

} // namespace ika
} // namespace bgeo
