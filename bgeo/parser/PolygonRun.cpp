/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PolygonRun.h"

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
    UniformDataHandle(PolygonRun& run)
        : run(run)
    {
    }

    /*virtual*/ bool jsonKey(UT_JSONParser& parser, const char *v, int64 len)
    {
        UT_String key(v);
        return run.parseDataWithKey(parser, key);
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
    PolygonRun& run;
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

PolygonRun::PolygonRun(const Detail& detail)
    : Poly(detail),
    startVertex(0),
    numPrimitives(0)
{
}

PolygonRun* PolygonRun::clone() const
{
    return new PolygonRun(*this);
}

void PolygonRun::loadData(UT_JSONParser& parser)
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
            message.sprintf("Invalid Polygon_run data: \"%s\"",
                            key.toStdString().c_str());
            throw ReadError(message.buffer());
        }
    }
}

void PolygonRun::loadVaryingData(UT_JSONParser& parser,
                                 const Primitive::StringList& fields)
{
    parseBeginArray(parser);
    {
        for (auto& field : fields)
        {
            if (!parseDataWithKey(parser, UT_String(field)))
            {
                UT_String message;
                message.sprintf("Invalid Polygon_run varying field: \"%s\"",
                                field.c_str());
                throw ReadError(message.buffer());
            }
        }
    }
    parseEndArray(parser);
}

void PolygonRun::loadUniformData(UT_JSONParser& parser)
{
    UniformDataHandle uniformHandle(*this);
    BGEO_CHECK(parser.parseObject(uniformHandle));
}

bool PolygonRun::parseDataWithKey(UT_JSONParser& parser,
                                  const UT_String& key)
{
    if (key == "startvertex" || key == "s_v")
    {
        BGEO_CHECK(parser.parseValue(startVertex));
    }
    else if (key == "nprimitives" || key == "n_p")
    {
        BGEO_CHECK(parser.parseValue(numPrimitives));
    }
    else if (key == "nvertices" || key == "n_v")
    {
        VertexArrayBuilder::VertexArray numVertices;
        size_t startBlockSize = numPrimitives > 0 ? numPrimitives : 10;
        parseArray(parser, numVertices, startBlockSize);
        setupFromPolygonRunInfo(numVertices);
    }
    else if (key == "nvertices_rle" || key == "r_v")
    {
        VertexArrayBuilder::VertexArray numVerticesRle;
        // the number of polygons with different vertex counts should be
        // pretty small so start with a small block size.
        size_t startBlockSize = 5;
        parseArray(parser, numVerticesRle, startBlockSize);
        setupFromPolygonRleInfo(numVerticesRle);
    }
    else
    {
        return false;
    }

    return true;
}

void PolygonRun::setupFromPolygonRunInfo(
    const VertexArrayBuilder::VertexArray& numVertices)
{
    int64 totalVertexCount = 0;
    for (auto& count : numVertices)
    {
        totalVertexCount += count;
    }

    vertices.reserve(vertices.size() + totalVertexCount);
    sides.reserve(numPrimitives);

    int64 currentVertex = startVertex;
    for (auto& count : numVertices)
    {
        sides.push_back(count);
        for (int64 i = 0; i < count; i++, currentVertex++)
        {
            vertices.push_back(currentVertex);
        }
    }
}

// RLE for vertices is i.e.
// [5, 1, 4, 5] -> 1 face with 5 vertices followed by 5 faces with 4 vertices.
//
void PolygonRun::setupFromPolygonRleInfo(const VertexArrayBuilder::VertexArray& numVerticesRle)
{
    int64 totalVertexCount = 0;
    assert(numVerticesRle.size() % 2 == 0); // must be even size
    for (int i = 0; i < numVerticesRle.size(); i += 2)
    {
        auto numVertices = numVerticesRle[i];
        auto count = numVerticesRle[i + 1];
        totalVertexCount += numVertices * count;
    }

    vertices.reserve(vertices.size() + totalVertexCount);
    sides.reserve(numPrimitives);

    int64 currentVertex = startVertex;
    for (int i = 0; i < numVerticesRle.size(); i += 2)
    {
        auto numVertices = numVerticesRle[i];
        auto count = numVerticesRle[i + 1];

        for (int prim = 0; prim < count; prim++)
        {
            sides.push_back(numVertices);
            for (int vertex = 0; vertex < numVertices; vertex++)
            {
                vertices.push_back(currentVertex++);
            }
        }
    }
}

} // namespace parser
} // namespace ika
} // namespace bgeo
