/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef PLUGIN_BUILD_H
#define PLUGIN_BUILD_H

#include <vector>
#include <string>

#include <FnAttribute/FnAttribute.h>

namespace ika
{

namespace bgeo
{
class Bgeo;
class PolySplitter;
}

namespace BgeoInOp
{
namespace build
{

typedef std::vector<std::string> StringList;

Foundry::Katana::FloatAttribute pointP(const bgeo::Bgeo& bgeo);
Foundry::Katana::FloatAttribute pointN(const bgeo::Bgeo& bgeo);
Foundry::Katana::FloatAttribute pointUV(const bgeo::Bgeo& bgeo);
Foundry::Katana::Attribute pointAttribute(const bgeo::Bgeo& bgeo,
                                          const char* name);

Foundry::Katana::GroupAttribute
arbitraryPointGroup(const bgeo::Bgeo& bgeo, const StringList& skip);

Foundry::Katana::FloatAttribute vertexN(const bgeo::Bgeo& bgeo);
Foundry::Katana::FloatAttribute vertexUV(const bgeo::Bgeo& bgeo);
Foundry::Katana::Attribute vertexAttribute(const bgeo::Bgeo& bgeo,
                                           const char* name);

Foundry::Katana::GroupAttribute
arbitraryGroup(const bgeo::Bgeo& bgeo, const StringList& skip);

Foundry::Katana::FloatAttribute pointP(const bgeo::Bgeo& bgeo,
                                       const bgeo::PolySplitter& splitter);
Foundry::Katana::FloatAttribute pointN(const bgeo::Bgeo& bgeo,
                                       const bgeo::PolySplitter& splitter);
Foundry::Katana::FloatAttribute pointUV(const bgeo::Bgeo& bgeo,
                                        const bgeo::PolySplitter& splitter);
Foundry::Katana::Attribute pointAttribute(const bgeo::Bgeo& bgeo,
                                          const bgeo::PolySplitter& splitter,
                                          const char* name);

Foundry::Katana::GroupAttribute
arbitraryPointGroup(const bgeo::Bgeo& bgeo,
                    const bgeo::PolySplitter& splitter,
                    const StringList& skip);

Foundry::Katana::FloatAttribute vertexN(const bgeo::Bgeo& bgeo,
                                        const bgeo::PolySplitter& splitter);
Foundry::Katana::FloatAttribute vertexUV(const bgeo::Bgeo& bgeo,
                                         const bgeo::PolySplitter& splitter);
Foundry::Katana::Attribute vertexAttribute(const bgeo::Bgeo& bgeo,
                                           const bgeo::PolySplitter& splitter,
                                           const char* name);

Foundry::Katana::GroupAttribute
arbitraryGroup(const bgeo::Bgeo& bgeo,
               const bgeo::PolySplitter& splitter,
               const StringList& skip);

} // namespace build
} // namespace BgeoInOp
} // namespace ika

#endif // PLUGIN_BUILD_H
