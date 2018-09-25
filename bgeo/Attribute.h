/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_ATTRIBUTE_H
#define BGEO_ATTRIBUTE_H

#include <cinttypes>
#include <vector>
#include <string>
#include <cassert>

#include "parser/storage.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Attribute;
}

class Attribute
{
public:
    Attribute(const parser::Attribute& attribute);
    virtual ~Attribute();

    const char* getName() const;
    const char* getType() const;
    const char* getSubType() const;
    int32_t getTupleSize() const;
    parser::storage::Storage getFundamentalType() const;

    template <typename T>
    void getData(std::vector<T>& data) const
    {
        data.resize(getFundamentalCount());
        getData(reinterpret_cast<uint8_t*>(data.data()),
                sizeof(T) * data.size());
    }

    template <typename T>
    void getDataForIndices(std::vector<T>& data,
                           const std::vector<int32_t>& indices) const
    {
        data.resize(getTupleSize() * indices.size());
        getData(reinterpret_cast<uint8_t*>(data.data()),
                sizeof(T) * data.size(),
                static_cast<uint32_t>(sizeof(T) * getTupleSize()), indices);
    }

    void getStrings(std::vector<std::string>& strings) const;

    // Katana needs:
    // scope (primitive/constant, face/uniform, point/varying, vertex/facevarying
    //    this is defined by which attribute list it is a part of.
    // inputType (float, double, integer, string, color3, color4, normal3, etc)
    // value
    // elementSize (array size if it is an array)

private:
    const parser::Attribute& m_attribute;

    void getData(uint8_t* bytes, int64_t byteCount) const;
    void getData(uint8_t* bytes, int64_t byteCount, uint32_t elementSize,
                 const std::vector<int32_t>& indices) const;
    int64_t getFundamentalCount() const;

    mutable std::vector<uint8_t> m_buffer;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_ATTRIBUTE_H
