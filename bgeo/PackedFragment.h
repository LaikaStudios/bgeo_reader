/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PACKED_FRAGMENT_H
#define BGEO_PACKED_FRAGMENT_H

#include <string>

#include "rtti.h"
#include "PackedGeometry.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class PackedFragment;
}

class PackedFragment: public PackedGeometry
{
    RTTI_DECLARE(PackedFragment, PackedGeometry)

public:
    PackedFragment(const parser::PackedFragment& fragment,
                   std::shared_ptr<Bgeo> embedded);

    std::string getNameAttribute() const;
    std::string getName() const;

    std::string getEmbeddedKey() const;

private:
    const parser::PackedFragment& m_fragment;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_PACKED_FRAGMENT_H
