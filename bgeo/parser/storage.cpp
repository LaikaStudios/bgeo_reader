/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "storage.h"

#include <UT/UT_String.h>

#include "StorageTraits.h"

namespace ika
{
namespace bgeo
{
namespace parser
{
namespace storage
{

namespace
{

const char* storageNameTable[] = {
    "unknown",
    Traits<int32>::Name,
    Traits<fpreal32>::Name
};

uint8_t storageSizeTable[] = {
    0,
    Traits<int32>::Size,
    Traits<fpreal32>::Size
};

} // anonymous namespace

Storage toStorage(const char* string)
{
    UT_String storage(string);
    if (storage == Traits<fpreal32>::Name)
    {
        return Traits<fpreal32>::StorageId;
    }
    else if (storage == Traits<int32>::Name)
    {
        return Traits<int32>::StorageId;
    }

    return storage::UnknownStorage;
}

const char* toString(Storage storage)
{
    return storageNameTable[static_cast<int>(storage)];
}

uint8_t sizeInBytes(Storage storage)
{
    return storageSizeTable[static_cast<int>(storage)];
}



} // namespace storage
} // namespace parser
} // namespace ika
} // namespace bgeo
