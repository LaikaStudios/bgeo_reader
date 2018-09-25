/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_NUMERICDATA_H
#define BGEO_PARSER_NUMERICDATA_H

#include <iosfwd>

#include <UT/UT_JSONParser.h>

#include "storage.h"
#include "StorageTraits.h"
#include "ByteBuffer.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class NumericData
{
public:
    template <typename T>
    static NumericData create(int64 elementCount, int32 size,
                              const std::vector<T>& tuples);

    template <typename T>
    static NumericData create(int64 elementCount, int32 size,
                              const std::vector<int32>& packing, int pageSize,
                              const std::vector<bool>& constantPageFlags,
                              const std::vector<T>& rawdata);


    explicit NumericData(int64 elementCount = 0);

    bool operator == (const NumericData& numeric) const;
    bool operator != (const NumericData& numeric) const
    {
        return !(*this == numeric);
    }

    void swap(NumericData& data);

    void load(UT_JSONParser& parser);
    void loadArray(UT_JSONParser& parser, storage::Storage storage,
                   int32 count);

    int64 elementCount;

    int32 tupleSize;
    storage::Storage storage;
    ByteBuffer data;

    std::vector<int32> packing;
    int pageSize;

    std::vector<bool> constantPageFlags;

    template <typename T>
    void getUnpackedData(std::vector<T>& unpacked) const;

    void getUnpackedData(uint8* unpacked, int64 unpackedByteCount,
                         int64 storageSize) const;

    // copy elementCopyCount tuples into targetData. supply target tuplesize and
    // sourceElementCount to ensure buffer is big enough. target tuple size can be
    // smaller than the source tuple size, in which case only the tuple size elements
    // are copied into target.
    void copyTo(fpreal64* target, int32 targetTupleSize, int64 targetElementCount,
                int64 sourceIndex, int64 elementCopyCount) const
    {
        if (elementCopyCount <= 0)
        {
            return;
        }

        assert(targetTupleSize <= tupleSize);
        assert(elementCopyCount <= targetElementCount);

        if (storage == storage::Fpreal32)
        {
            // FIXME: this is inefficient - it should be unpacked directly into target.
            std::vector<fpreal32> unpacked;
            getUnpackedData(unpacked);

            assert(sourceIndex * tupleSize < unpacked.size());
            // have to cast
            const fpreal32* source = unpacked.data();

            for (int64 i = 0; i < elementCopyCount; ++i)
            {
                for (int j = 0; j < targetTupleSize; ++j)
                {
                    target[i * targetTupleSize + j] =
                            source[(sourceIndex + i) * tupleSize + j];
                }
            }
        }
//        else if (storage == RealStorage64)
//        {
//            assert(sourceIndex * tupleSize < data.sizeAs<fpreal64>());
//            // can copy directly
//            fpreal64* source = this->data.dataAs<fpreal64>();
//        }
    }

    void copyTo(fpreal32* target, int32 targetTupleSize, int64 targetElementCount,
                int64 sourceIndex, int64 elementCopyCount) const
    {
        if (elementCopyCount <= 0)
        {
            return;
        }

        assert(targetTupleSize <= tupleSize);
        assert(elementCopyCount <= targetElementCount);

        // FIXME: this is inefficient - it should be unpacked directly into target.
        std::vector<fpreal32> unpacked;
        getUnpackedData(unpacked);

        if (storage == storage::Fpreal32)
        {
            assert(sourceIndex * tupleSize < unpacked.size());
            // have to cast
            //const fpreal32* source = data.data.dataAs<fpreal32>();
            const fpreal32* source = unpacked.data();

            for (int64 i = 0; i < elementCopyCount; ++i)
            {
                memcpy(&target[i * targetTupleSize],
                       &source[(sourceIndex + i) * tupleSize],
                       sizeof(fpreal32) * targetTupleSize);
            }
        }
//        else if (storage == RealStorage64)
//        {
//            assert(sourceIndex * tupleSize < data.sizeAs<fpreal64>());
//            // can copy directly
//            fpreal64* source = this->data.dataAs<fpreal64>();
//        }
    }

    friend std::ostream& operator << (std::ostream& co, const NumericData& data);
};

template <typename T>
/*static*/ NumericData NumericData::create(int64 elementCount, int32 size,
                                           const std::vector<T>& tuples)
{
    NumericData numeric(elementCount);
    numeric.storage = storage::Traits<T>::StorageId;
    numeric.tupleSize = size;
    assert(tuples.size() == elementCount * size);
    numeric.data.resize(storage::Traits<T>::Size * tuples.size());
    memcpy(numeric.data.data(), tuples.data(), numeric.data.size());
    numeric.packing.resize(1, size);
    return numeric;
}

template <typename T>
/*static*/ NumericData NumericData::create(int64 elementCount, int32 size,
                                           const std::vector<int32>& packing,
                                           int pageSize,
                                           const std::vector<bool>& constantPageFlags,
                                           const std::vector<T>& rawdata)
{
    NumericData numeric(elementCount);

    numeric.storage = storage::Traits<T>::StorageId;
    numeric.tupleSize = size;
    numeric.data.resize(storage::Traits<T>::Size * rawdata.size());
    memcpy(numeric.data.data(), rawdata.data(), numeric.data.size());
    numeric.packing = packing;
    numeric.pageSize = pageSize;
    numeric.constantPageFlags = constantPageFlags;

    if (numeric.packing.empty())
    {
        numeric.packing.resize(1, numeric.tupleSize);
    }

    return numeric;
}

template <typename T>
void NumericData::getUnpackedData(std::vector<T>& unpacked) const
{
    assert(storage == storage::Traits<T>::StorageId);
    unpacked.resize(elementCount * tupleSize);
    getUnpackedData(reinterpret_cast<uint8*>(unpacked.data()),
                    unpacked.size() * storage::Traits<T>::Size,
                    storage::Traits<T>::Size);
}

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_NUMERICDATA_H
