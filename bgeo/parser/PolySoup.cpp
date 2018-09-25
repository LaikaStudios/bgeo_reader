/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PolySoup.h"

#include <cassert>

#include <UT/UT_JSONHandle.h>

#include "Detail.h"
#include "ReadError.h"
#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

namespace
{

class UniformDataHandle : public UT_JSONHandleError
{
public:
    UniformDataHandle(PolySoup& soup)
        : soup(soup)
    {
    }

    /*virtual*/ bool jsonKey(UT_JSONParser& parser, const char *v, int64 len)
    {
        UT_String key(v);
        return soup.parseDataWithKey(parser, key);
    }

    /*virtual*/ bool jsonBeginMap(UT_JSONParser& parser)
    {
        return true;
    }

    /*virtual*/ bool jsonEndMap(UT_JSONParser& parser)
    {
        return true;
    }

private:
    PolySoup& soup;
};

template <typename T>
void parseArray(UT_JSONParser& parser, std::vector<T>& data, size_t startBlockSize)
{
    auto iterator = parser.beginArray();
    size_t currentBlockSize = startBlockSize;
    size_t currentSize = 0;

    do
    {
        data.resize(currentSize + currentBlockSize);
        int64 numRead = parser.parseArrayValues(iterator, &data[currentSize], currentBlockSize);

        currentSize += numRead;

        // double block size each iteration to reduce number of allocations
        // (similar to std::vector memory allocation)
        currentBlockSize *= 2;

    } while (!iterator.atEnd());

    data.resize(currentSize);
}

}

PolySoup::PolySoup(const Detail& detail)
    : Poly(detail)
{

}

PolySoup* PolySoup::clone() const
{
    return new PolySoup(*this);
}

void PolySoup::loadData(UT_JSONParser& parser)
{
    UT_WorkBuffer buffer;
    UT_String key;

    for (auto geoit = parser.beginArray(); !geoit.atEnd(); ++geoit)
    {
        geoit.getLowerKey(buffer);
        key = buffer.buffer();
        if (!parseDataWithKey(parser, key))
        {
            UT_String message;
            message.sprintf("Invalid PolySoup data: \"%s\"",
                            key.toStdString().c_str());
            throw ReadError(message.buffer());
        }
    }
}

void PolySoup::loadVaryingData(UT_JSONParser& parser,
                               const Primitive::StringList& fields)
{
    parseBeginArray(parser);
    {
        for (auto& field : fields)
        {
            if (!parseDataWithKey(parser, UT_String(field)))
            {
                UT_String message;
                message.sprintf("Invalid packed geometry varying field: \"%s\"",
                                field.c_str());
                throw ReadError(message.buffer());
            }
        }
    }
    parseEndArray(parser);
}

void PolySoup::loadUniformData(UT_JSONParser& parser)
{
    UniformDataHandle uniformHandle(*this);
    BGEO_CHECK(parser.parseObject(uniformHandle));
}

bool PolySoup::parseDataWithKey(UT_JSONParser& parser,
                                const UT_String& key)
{
    if (key == "vertex")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else if (key == "polyinfo")
    {
        parseBeginArray(parser);
        {
            VertexArrayBuilder::VertexArray soupSides;

            // small block size here since there are likely to only be a few
            // different polygon vertex counts.
            parseArray(parser, soupSides, 5);

            VertexArrayBuilder::VertexArray soupCounts;
            parseArray(parser, soupCounts, soupSides.size());

            // count number of vertices to allow vertex array to be read in
            // a single block.
            size_t vertexCount = 0;
            assert(soupCounts.size() == soupSides.size());
            for (size_t i = 0; i < soupCounts.size(); i++)
            {
                vertexCount += soupSides[i] * soupCounts[i];
            }

            VertexArrayBuilder::VertexArray soupVertices;
            parseArray(parser, soupVertices, vertexCount);
            vertices.reserve(vertices.size() + soupVertices.size());
            vertices.insert(vertices.end(), soupVertices.begin(), soupVertices.end());

            setupFromSoupInfo(soupSides, soupCounts);
        }
        parseEndArray(parser);
    }
    else
    {
        return false;
    }

    return true;
}

void PolySoup::setupFromSoupInfo(const VertexArrayBuilder::VertexArray& soupSides,
                                 const VertexArrayBuilder::VertexArray& soupCounts)
{
    size_t faceCount = 0;
    for (auto count : soupCounts)
    {
        faceCount += count;
    }
    auto lastSides = sides.size();
    sides.resize(sides.size() + faceCount);
    auto lastClosed = closed.size();
    closed.resize(closed.size() + faceCount);

    size_t face = 0;
    assert(soupSides.size() == soupCounts.size());
    for (size_t i = 0; i < soupSides.size(); i++)
    {
        auto count = soupCounts[i];
        auto faceSides = soupSides[i];
        for (size_t i = 0; i < count; i++, face++)
        {
            sides[lastSides + face] = faceSides;
            closed[lastClosed + face] = true;
        }
    }
}

} // namespace parser
} // namespace ika
} // namespace bgeo
