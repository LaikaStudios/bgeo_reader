/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_COMPRESSION_H
#define BGEO_PARSER_COMPRESSION_H

#include <string>
#include <memory>

#include <UT/UT_IStream.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

std::unique_ptr<UT_IStream> getDecompressionStream(const std::string& filename,
                                                   UT_IStream& stream);

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_COMPRESSION_H
