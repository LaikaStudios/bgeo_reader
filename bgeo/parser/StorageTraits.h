/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef PARSER_STORAGE_TRAITS_H
#define PARSER_STORAGE_TRAITS_H

#include <SYS/SYS_Types.h>

#include "storage.h"

namespace ika
{
namespace bgeo
{
namespace parser
{
namespace storage
{

template <typename T>
class Traits; // generic Traits not implemented

template <>
class Traits<fpreal32>
{
public:
    constexpr static storage::Storage StorageId = storage::Fpreal32;
    constexpr static const char* Name = "fpreal32";
    typedef fpreal32 Type;
    constexpr static size_t Size = sizeof(Type);
};

template <>
class Traits<int32>
{
public:
    constexpr static storage::Storage StorageId = storage::Int32;
    constexpr static const char* Name = "int32";
    typedef int32 Type;
    constexpr static size_t Size = sizeof(Type);
};

} // namespace storage
} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // PARSER_STORAGE_TRAITS_H
