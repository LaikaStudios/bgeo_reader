/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PACKED_DISK_H
#define BGEO_PACKED_DISK_H

#include <string>

#include "rtti.h"
#include "PackedGeometry.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class PackedDisk;
}

class PackedDisk : public PackedGeometry
{
    RTTI_DECLARE(PackedDisk, PackedGeometry)

public:
    PackedDisk(const parser::PackedDisk& disk);

    std::string getFilename() const;

private:
    const parser::PackedDisk& m_disk;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_PACKED_DISK_H
