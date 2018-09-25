/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PackedFragment.h"

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

// FIXME: move this to PackedGeometry
class UniformDataHandle : public UT_JSONHandleError
{
public:
    UniformDataHandle(PackedFragment& packed)
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
    PackedFragment& packed;
};

} // namespace anonymous

PackedFragment::PackedFragment(const Detail& detail)
    : PackedGeometry(detail)
{
}

PackedFragment::PackedFragment(const PackedFragment& fragment)
    : PackedGeometry(fragment)
{
}

PackedFragment* PackedFragment::clone() const
{
    return new PackedFragment(*this);
}

bool PackedFragment::parseParametersWithKey(UT_JSONParser& parser,
                                        const UT_String& key)
{
    if (PackedGeometry::parseParametersWithKey(parser, key))
    {
        return true;
    }

    if (key == "attribute")
    {
        UT_WorkBuffer buffer;
        BGEO_CHECK(parser.parseValue(buffer));
        attribute.harden(buffer.buffer());
    }
    else if (key == "bounds")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else if (key == "name")
    {
        UT_WorkBuffer buffer;
        BGEO_CHECK(parser.parseValue(buffer));
        name.harden(buffer.buffer());
    }
    else
    {
        return false;
    }

    return true;
}

std::ostream& PackedFragment::encode(std::ostream& co) const
{
    PackedGeometry::encode(co);

    return co;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
