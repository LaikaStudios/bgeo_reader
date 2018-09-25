/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Attribute.h"

#include "parser/Attribute.h"
#include "parser/NumericData.h"
#include "parser/storage.h"

namespace ika
{
namespace bgeo
{

Attribute::Attribute(const parser::Attribute& attribute)
    : m_attribute(attribute)
{
}

/*virtual*/ Attribute::~Attribute()
{
}

const char* Attribute::getSubType() const
{
    return m_attribute.subtype ? m_attribute.subtype.buffer() : "";
}

int32_t Attribute::getTupleSize() const
{
    return m_attribute.data.tupleSize;
}

parser::storage::Storage Attribute::getFundamentalType() const
{
    return m_attribute.data.storage;
}

const char* Attribute::getName() const
{
    return m_attribute.name.buffer();
}

const char* Attribute::getType() const
{
    return m_attribute.type.buffer();
}

void Attribute::getStrings(std::vector<std::string>& data) const
{
    data = m_attribute.strings;
}

void Attribute::getData(u_int8_t* bytes, int64_t byteCount) const
{
    m_attribute.data.getUnpackedData(bytes, byteCount,
                   parser::storage::sizeInBytes(m_attribute.data.storage));
}

void Attribute::getData(uint8_t* bytes, int64_t byteCount,
                        uint32_t elementSizeInBytes,
                        const std::vector<int32_t>& indices) const
{
    // unpack the data into a temporary buffer and save it for later.
    if (m_buffer.empty())
    {
        auto newByteCount = getFundamentalCount() *
                parser::storage::sizeInBytes(m_attribute.data.storage);
        m_buffer.resize(newByteCount);
        getData(m_buffer.data(), newByteCount);
    }

    assert(byteCount == indices.size() * elementSizeInBytes);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        auto sourceIndex = indices[i];
        assert((sourceIndex + 1) * elementSizeInBytes <= m_buffer.size());
        memcpy(&bytes[i * elementSizeInBytes],
               &m_buffer[sourceIndex * elementSizeInBytes],
               elementSizeInBytes);
    }
}

int64_t Attribute::getFundamentalCount() const
{
    return m_attribute.data.tupleSize * m_attribute.data.elementCount;
}

} // namespace ika
} // namespace bgeo
