/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "NumericData.h"

#include <memory>
#include <iostream>

#include <UT/UT_String.h>
#include <UT/UT_JSONHandle.h>

#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

namespace
{

template <typename T>
class TupleFlattener : public UT_JSONHandleError
{
public:
    TupleFlattener(ByteBuffer& buffer)
        : m_buffer(buffer),
          m_index(0),
          m_stack(0)
    {
    }

    /*virtual*/ bool jsonInt(UT_JSONParser& parser, int64 value)
    {
        setCurrentElement(static_cast<T>(value));
        return true;
    }

    /*virtual*/ bool jsonReal(UT_JSONParser& parser, fpreal64 value)
    {
        setCurrentElement(static_cast<T>(value));
        return true;
    }

    /*virtual*/ bool jsonBeginArray(UT_JSONParser& parser)
    {
        m_stack++;
        return true;
    }

    /*virtual*/ bool jsonEndArray(UT_JSONParser& parser)
    {
        m_stack--;
        // verify that we read all the elements we need
        if (m_stack == 0 && m_index != m_buffer.sizeAs<T>())
        {
            UT_String message;
            message.sprintf("Expected %ld point attribute values, but only read %ld",
                            m_buffer.sizeAs<T>(), m_index);
            throw ReadError(message);
        }
        return true;
    }

private:
    ByteBuffer& m_buffer;
    int64 m_index;
    int m_stack;

    void setCurrentElement(T value)
    {
        if (m_index > m_buffer.sizeAs<T>())
        {
            UT_String message;
            message.sprintf("Tuple array expecting total of %ld elements", m_buffer.sizeAs<T>());
            throw ReadError(message);
        }

        m_buffer.set(m_index, value);
        ++m_index;
    }
};

class BoolTupleFlattener : public UT_JSONHandleError
{
public:
    BoolTupleFlattener(std::vector<bool>& flags, int pageCount)
        : m_flags(flags),
          m_index(0),
          m_stack(0),
          m_pageCount(pageCount),
          m_currentPageCount(0)
    {
    }

    /*virtual*/ const char* getClassName() const
    {
        return "ConstantPageFlags";
    }

    /*virtual*/ bool jsonBool(UT_JSONParser& parser, bool value)
    {
        setCurrentElement(value);
        return true;
    }

    /*virtual*/ bool jsonInt(UT_JSONParser& parser, int64 value)
    {
        setCurrentElement(value);
        return true;
    }

    /*virtual*/ bool jsonReal(UT_JSONParser& parser, fpreal64 value)
    {
        setCurrentElement(value);
        return true;
    }

    /*virtual*/ bool jsonBeginArray(UT_JSONParser& parser)
    {
        m_stack++;
        m_currentPageCount = 0;
        return true;
    }

    /*virtual*/ bool jsonEndArray(UT_JSONParser& parser)
    {
        m_stack--;

        // empty page array
        if (m_currentPageCount == 0)
        {
            m_index += m_pageCount;
        }

        // verify that we read all the elements we need
        if (m_stack == 0 && m_index != m_flags.size())
        {
            UT_String message;
            message.sprintf("Expected %ld bool tuple values, but read %ld",
                            m_flags.size(), m_index);
            throw ReadError(message);
        }
        return true;
    }

private:
    std::vector<bool>& m_flags;
    int64 m_index;
    int m_stack;
    int m_pageCount;
    int m_currentPageCount;

    void setCurrentElement(bool value)
    {
        if (m_index >= m_flags.size())
        {
            UT_String message;
            message.sprintf("Bool tuple array expecting total of %ld elements", m_flags.size());
            throw ReadError(message);
        }

        m_flags[m_index] = value;
        ++m_index;
        ++m_currentPageCount;
    }
};

} // anonymous namespace

NumericData::NumericData(int64 elementCount)
    : elementCount(elementCount),
      tupleSize(0),
      storage(storage::UnknownStorage),
      pageSize(0)
{
}

bool NumericData::operator == (const NumericData& numeric) const
{

    return elementCount == numeric.elementCount && storage == numeric.storage &&
           tupleSize == numeric.tupleSize && data == numeric.data &&
           packing == numeric.packing && pageSize == numeric.pageSize &&
           constantPageFlags == numeric.constantPageFlags;
}

void NumericData::load(UT_JSONParser &parser)
{
    UT_WorkBuffer buffer;
    UT_String key;
    for (auto it = parser.beginArray(); !it.atEnd(); ++it)
    {
        it.getLowerKey(buffer);
        key = buffer.buffer();
        if (key == "size")
        {
            int64 size;
            BGEO_CHECK(parser.parseInt(size));
            tupleSize = size;
            packing.resize(1, tupleSize);
        }
        else if (key == "storage")
        {
            BGEO_CHECK(parser.parseString(buffer));
            storage = storage::toStorage(buffer.buffer());
        }
        else if (key == "tuples" || key == "arrays")
        {
            assert(storage != storage::UnknownStorage);

            data.resize(sizeInBytes(storage) * elementCount * tupleSize);
            std::unique_ptr<UT_JSONHandle> handle;
            if (storage == storage::Fpreal32)
            {
                handle.reset(new TupleFlattener<fpreal32>(data));
            }
            else if (storage == storage::Int32)
            {
                handle.reset(new TupleFlattener<int32>(data));
            }
            assert(handle);
            parser.parseObject(*handle);
        }
        else if (key == "rawpagedata")
        {
            if (storage != storage::Fpreal32 &&
                storage != storage::Int32)
            {
                std::cerr << "Warning: unsupported format " << toString(storage)
                          << ". skipping." << std::endl;
                BGEO_CHECK(parser.skipNextObject());
                continue;
            }

            int64 numFloats = elementCount * tupleSize;

            if (constantPageFlags.size() > 0)
            {
                numFloats = 0;

                // calculate size using the constantpageflags
                int numPages = (elementCount - 1) / pageSize + 1;
                assert(packing.size() * numPages == constantPageFlags.size());
                for (int page = 0; page < numPages; ++page)
                {
                    for (int pack = 0; pack < packing.size(); ++pack)
                    {
                        assert(pack * numPages + page < constantPageFlags.size());
                        int elementsLeft = elementCount - (page * pageSize);
                        int currentPageSize = std::min(elementsLeft, pageSize);

                        if (constantPageFlags[pack * numPages + page])
                        {
                            numFloats += packing[pack];
                        }
                        else
                        {
                            numFloats += packing[pack] * currentPageSize;
                        }
                    }
                }
            }

            data.resize(sizeInBytes(storage) * numFloats);
            std::unique_ptr<UT_JSONHandle> handle;
            if (storage == storage::Fpreal32)
            {
                handle.reset(new TupleFlattener<fpreal32>(data));
            }
            else if (storage == storage::Int32)
            {
                handle.reset(new TupleFlattener<int32>(data));
            }
            assert(handle);
            parser.parseObject(*handle);
        }
        else if (key == "packing")
        {
            packing.resize(tupleSize);
            int count = parser.parseUniformArray(packing.data(), tupleSize);
            packing.resize(count);

            int packTotal = 0;
            for (int i = 0; i < count; i++)
            {
                packTotal += packing[i];
            }
            assert(packTotal == tupleSize);
        }
        else if (key == "pagesize")
        {
            BGEO_CHECK(parser.parseValue(pageSize));
        }
        else if (key == "constantpageflags")
        {
            int numPages = (elementCount - 1) / pageSize + 1;
            constantPageFlags.resize(packing.size() * numPages, 0);
            BoolTupleFlattener handle(constantPageFlags, numPages);
            parser.parseObject(handle);
        }
        else
        {
            std::cerr << "Warning: unsupported numeric member: " << key << std::endl;
            BGEO_CHECK(parser.skipNextObject());
        }
    }
}

void NumericData::loadArray(UT_JSONParser& parser, storage::Storage storage_,
                            int32 count)
{
    storage = storage_;
    elementCount = count;
    data.resize(sizeInBytes(storage) * elementCount);
    if (storage == storage::Int32)
    {
        BGEO_CHECK(count == parser.parseUniformArray(data.dataAs<int32>(), count));
    }
    else
    {
        std::cerr << "Warning: unsupported format " << toString(storage)
                  << ". skipping." << std::endl;
        BGEO_CHECK(parser.skipNextObject());
    }
}

void NumericData::getUnpackedData(uint8* unpacked, int64 unpackedByteCount,
                                  int64 storageSize) const
{
    int64 unpackedSize = elementCount * tupleSize * storageSize;
    assert(unpackedSize == unpackedByteCount);

    const uint8* packed = data.data();
    int64 packedByteCount = data.size();
    if ((packing.size() == 1 || packing.empty()) && constantPageFlags.empty())
    {
        assert(packedByteCount >= unpackedSize);
        memcpy(unpacked, packed, unpackedSize);
        return;
    }

    int numPages = (elementCount - 1) / pageSize + 1;
    bool useFlags = !constantPageFlags.empty();

    int packPageOffset = 0;
    for (int page = 0; page < numPages; ++page)
    {
        int packTotalPageSize;
        int elementsLeft = elementCount - (page * pageSize);
        int currentPageSize = std::min(elementsLeft, pageSize);

        if (useFlags)
        {
            packTotalPageSize = 0;
            for (int pack = 0; pack < packing.size(); ++pack)
            {
                if (constantPageFlags[pack * numPages + page])
                {
                    packTotalPageSize += packing[pack];
                }
                else
                {
                    packTotalPageSize += packing[pack] * currentPageSize;
                }
            }
        }
        else
        {
            packTotalPageSize = pageSize * tupleSize;
        }

        int unpackPageOffset = page * pageSize * tupleSize;

        for (int element = 0; element < currentPageSize; ++element)
        {
            int packOffset = 0;
            int unpackOffset = 0;
            for (int pack = 0; pack < packing.size(); ++pack)
            {
                int flagIndex = pack * numPages + page;
                assert(!useFlags || flagIndex < constantPageFlags.size());

                int packIndex;
                if (useFlags && constantPageFlags[flagIndex])
                {
                    packIndex = packPageOffset + packOffset;
                }
                else
                {
                    packIndex = packPageOffset + packOffset + element * packing[pack];
                }
                assert(storageSize * (packIndex + packing[pack]) <= packedByteCount);

                int unpackIndex = unpackPageOffset + element * tupleSize + unpackOffset;
                assert(storageSize * (unpackIndex + packing[pack]) <= unpackedByteCount);

                memcpy(unpacked + (storageSize * unpackIndex),
                       packed + (storageSize * packIndex),
                       packing[pack] * storageSize);

                if (useFlags && constantPageFlags[flagIndex])
                {
                    packOffset += packing[pack];
                }
                else
                {
                    packOffset += packing[pack] * currentPageSize;
                }
                unpackOffset += packing[pack];
            }
        }

        packPageOffset += packTotalPageSize;
    }
}

std::ostream& operator << (std::ostream& co, const NumericData& data)
{
    co << data.elementCount << "x" << data.tupleSize
       << "(" << storage::toString(data.storage) <<")";

    if (!data.packing.empty())
    {
        co << "  packed [";
        for (auto pack : data.packing)
        {
            co << pack << " ";
        }
        co << "] ";

        co << "  page " << data.pageSize;
        co << "  flags ";
        for (auto flag : data.constantPageFlags)
        {
            co << flag;
        }
    }

    co << "  ";
    if (data.storage == storage::Fpreal32)
    {
        data.data.encodeAs<fpreal32>(co);
    }
    else if (data.storage == storage::Int32)
    {
        data.data.encodeAs<int32>(co);
    }

    return co;
}

} // namespace parser
} // namespace ika
} // namespace bgeo
