/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <iostream>

#include "BgeoInOp.h"
#include "version.h"

#define STRINGIFYX(x) STRINGIFY(x)
#define STRINGIFY(x) #x

namespace ika
{
namespace BgeoInOp
{

DEFINE_GEOLIBOP_PLUGIN(BgeoInOp)

} // namespace BgeoInOp
} // namespace ika

void registerPlugins()
{
    REGISTER_PLUGIN(ika::BgeoInOp::BgeoInOp, "BgeoIn",
                    ika::BgeoInOp::version::Major,
                    ika::BgeoInOp::version::Minor);

    std::cerr << "BgeoIn OP version: "
              << ika::BgeoInOp::version::Major << "."
              << ika::BgeoInOp::version::Minor << "."
              << ika::BgeoInOp::version::Patch
#ifdef _DEBUG
              << "(debug)"
#endif // _DEBUG
#ifdef HVERSION
              << " (Houdini " << STRINGIFYX(HVERSION) <<")"
#endif // HVERSION
              << "\n";
}

#undef STRINGIFY
#undef STRINGIFYX
