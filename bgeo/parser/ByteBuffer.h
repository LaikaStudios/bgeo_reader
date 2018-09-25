/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_BYTE_BUFFER_H
#define BGEO_PARSER_BYTE_BUFFER_H

#include <vector>
#include <cassert>
#include <iostream>

#include <UT/UT_String.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class ByteBuffer
{
public:
    ByteBuffer();

    void swap(ByteBuffer& buffer)
    {
        m_data.swap(buffer.m_data);
    }

    void resize(int64 sizeBytes)
    {
        m_data.resize(sizeBytes);
    }

    uint8* data()
    {
        return m_data.data();
    }

    const uint8* data() const
    {
        return m_data.data();
    }

    int64 size() const
    {
        return m_data.size();
    }

    template <typename T>
    void set(int64 index, T value)
    {
        assert(index < sizeAs<T>());
        dataAs<T>()[index] = value;
    }

    template <typename T>
    T* beginAs()
    {
        return dataAs<T>();
    }

    template <typename T>
    T* endAs()
    {
        return beginAs<T>() + sizeAs<T>();
    }

    template <typename T>
    T* dataAs()
    {
        return reinterpret_cast<T*>(m_data.data());
    }

    template <typename T>
    const T* dataAs() const
    {
        return reinterpret_cast<const T*>(m_data.data());
    }

    template <typename T>
    int64 sizeAs() const
    {
        return m_data.size() / sizeof(T);
    }

    template <typename T>
    int64 sizeAs()
    {
        return m_data.size() / sizeof(T);
    }

    template <typename T>
    std::ostream& encodeAs(std::ostream& co) const
    {
        co << "[";
        if (sizeAs<T>() < 20)
        {
            for (int64 i = 0; i < sizeAs<T>(); ++i)
            {
                co << dataAs<T>()[i] << " ";
            }
        }
        else
        {
            co << "...";
        }
        co << "]";
        return co;
    }

    bool operator == (const ByteBuffer& other) const
    {
        return m_data == other.m_data;
    }

private:
    std::vector<uint8> m_data;
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_BYTE_BUFFER_H
