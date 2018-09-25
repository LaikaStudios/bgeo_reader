/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef PARSER_STORAGE_H
#define PARSER_STORAGE_H

#include <cinttypes>

namespace ika
{
namespace bgeo
{
namespace parser
{
namespace storage
{

enum Storage
{
    UnknownStorage = 0,
    Int32,
    Fpreal32,
    NumStorage,
};

Storage toStorage(const char* storage);
const char* toString(Storage storage);
uint8_t sizeInBytes(Storage storage);

} // namespace storage
} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // PARSER_STORAGE_H
