/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PACKED_DISK_H
#define BGEO_PARSER_PACKED_DISK_H

#include <string>

#include <UT/UT_String.h>

#include "PackedGeometry.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class PackedDisk : public PackedGeometry
{
public:
    explicit PackedDisk(const Detail& detail);
    PackedDisk(const PackedDisk& packed);

    /*virtual*/ PackedDisk* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return PackedDiskType;
    }

    /*virtual*/ bool parseParametersWithKey(UT_JSONParser& parser,
                                            const UT_String& key);

    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    std::string getFilename() const;

private:
    // NOTE: packed disks don't have bounds so make this private to help
    // avoid accessing it.
    void getBounds(double bounds[6]) const;

    UT_String filename;
    bool expand;
    int frame;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_PACKED_DISK_H
