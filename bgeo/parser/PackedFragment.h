/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PACKED_FRAGMENT_H
#define BGEO_PARSER_PACKED_FRAGMENT_H

#include <string>

#include <UT/UT_String.h>

#include "PackedGeometry.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class PackedFragment : public PackedGeometry
{
public:
    explicit PackedFragment(const Detail& detail);
    PackedFragment(const PackedFragment& fragment);

    /*virtual*/ PackedFragment* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return PackedFragmentType;
    }

    /*virtual*/ bool parseParametersWithKey(UT_JSONParser& parser,
                                            const UT_String& key);

    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    UT_String attribute;
    UT_String name;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_PACKED_FRAGMENT_H
