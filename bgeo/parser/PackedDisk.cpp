/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PackedDisk.h"

#include <cassert>

#include "Attribute.h"
#include "Detail.h"
#include "ReadError.h"
#include "util.h"
#include "PackedGeometry.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

namespace
{

// FIXME: move this into PackedGeometry
class UniformDataHandle : public UT_JSONHandleError
{
public:
    UniformDataHandle(PackedDisk& packed)
        : packed(packed)
    {
    }

    /*virtual*/ bool jsonKey(UT_JSONParser& parser, const char *v, int64 len)
    {
        UT_String key(v);
        return packed.parseDataWithKey(parser, key);
    }

    /*virtual*/ bool jsonBeginMap(UT_JSONParser& parser)
    {
        return true;
    }

    /*virtual*/ bool jsonEndMap(UT_JSONParser& parser)
    {
        return true;
    }

private:
    PackedDisk& packed;
};

} // namespace anonymous

PackedDisk::PackedDisk(const Detail& detail)
    : PackedGeometry(detail),
      expand(false)
{
}

PackedDisk::PackedDisk(const PackedDisk& disk)
    : PackedGeometry(disk),
      filename(disk.filename),
      expand(disk.expand),
      frame(disk.frame)
{
    filename.harden(); // harden here to prevent referencing stale data
                       // if the original primitive goes away.
}

PackedDisk* PackedDisk::clone() const
{
    return new PackedDisk(*this);
}

bool PackedDisk::parseParametersWithKey(UT_JSONParser& parser,
                                        const UT_String& key)
{
    if (PackedGeometry::parseParametersWithKey(parser, key))
    {
        return true;
    }

    if (key == "expandfilename")
    {
        BGEO_CHECK(parser.parseValue(expand));
    }
    else if (key == "expandframe")
    {
        BGEO_CHECK(parser.parseValue(frame));
    }
    else if (key == "filename")
    {
        UT_WorkBuffer buffer;
        BGEO_CHECK(parser.parseValue(buffer));
        filename.harden(buffer.buffer());
    }
    else
    {
        return false;
    }

    return true;
}

std::ostream& PackedDisk::encode(std::ostream& co) const
{
    PackedGeometry::encode(co);

    co << "\n"
       << "    expand = " << (expand ? "true" : "false") << "\n"
       << "    frame = " << frame << "\n"
       << "    filename = " << filename;

    return co;
}

std::string PackedDisk::getFilename() const
{
    if (!expand)
    {
        return filename.toStdString();
    }

    UT_String fmt(filename);
    fmt.harden();

    bool substituted = fmt.substitute("$F4", "%04d") > 0;
    if (!substituted)
    {
        substituted = fmt.substitute("$F", "%d") > 0;
    }

    if (!substituted)
    {
        return filename.toStdString();
    }

    UT_String result;
    result.sprintf(fmt, frame);

    return result.toStdString();
}

} // namespace parser
} // namespace bgeo
} // namespace ika
