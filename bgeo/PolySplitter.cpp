/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PolySplitter.h"

#include <iostream>
#include <map>
#include <cstring>
#include <numeric>

#include "Bgeo.h"
#include "Poly.h"

namespace ika
{
namespace bgeo
{

PolySplitter::PolySplitter()
    : m_currentSplit(0)
{
}

size_t PolySplitter::splitByPrimitiveString(const Bgeo& bgeo, const Poly& poly,
                                            const char* attributeName)
{
    if (!bgeo.getPrimitiveCount())
    {
        return 0;
    }

    auto attribute = bgeo.getPrimitiveAttributeByName(attributeName);
    if (!attribute)
    {
        std::cerr << "PolySplitter error: missing primitive attribute \""
                  << attributeName << "\"" << std::endl;
        return 0;
    }

    if (strcmp(attribute->getType(), "string") != 0)
    {
        std::cerr << "PolySplitter error: primitive attribute \""
                  << attributeName << "\" is not string" << std::endl;
        return 0;
    }

    std::vector<int32_t> values;
    attribute->getData(values);

    std::vector<std::string> strings;
    attribute->getStrings(strings);
    assert(!strings.empty());

    m_faceMatches.resize(strings.size());

    for (size_t i = 0; i < values.size(); ++i)
    {
        assert(values[i] < m_faceMatches.size());
        m_faceMatches[values[i]].push_back(i);
    }

    // cache the poly info for later use
    poly.getRawVertexList(m_vertices);
    poly.getVertexList(m_mappedVertices);
    poly.getStartIndices(m_startIndices);

    m_mapToNewVertices.resize(m_mappedVertices.size(), -1);

//    for (size_t i = 0; i < m_faceMatches.size(); ++i)
//    {
//        std::cout << strings[i] << ": ";
//        for (const auto& face : m_faceMatches[i])
//        {
//            std::cout << face << " ";
//        }
//        std::cout << std::endl;
//    }

    return m_faceMatches.size();
}

size_t PolySplitter::splitThisPoly(const Bgeo& bgeo, const Poly& poly, size_t primitiveIndex)
{
    // match all of the faces in the poly.
    m_faceMatches.resize(1);
    m_faceMatches[0].resize(poly.getFaceCount());
    std::iota(m_faceMatches[0].begin(), m_faceMatches[0].end(), 0);

    poly.getRawVertexList(m_vertices);
    poly.getVertexList(m_mappedVertices);
    poly.getStartIndices(m_startIndices);

    m_currentMappedPrimitives.resize(m_faceMatches[0].size(), primitiveIndex);

    m_mapToNewVertices.resize(m_mappedVertices.size(), -1);

    setCurrentSplit(0);

    return m_faceMatches.size();
}

size_t PolySplitter::getSplitCount() const
{
    return m_faceMatches.size();
}

void PolySplitter::setCurrentSplit(size_t splitIndex)
{
    assert(splitIndex < m_faceMatches.size());

    m_currentSplit = splitIndex;

    // reset cached vectors
    m_currentVertices.resize(0);
    m_currentStartIndices.resize(0);
    m_currentMappedVertices.resize(0);
    m_currentPointIndices.resize(0);
    m_currentVertexIndices.resize(0);

    // build up remapped data
    auto faces = m_faceMatches[splitIndex];
    int32_t currentIndex = 0;

    int32_t previousStartIndex = 0;
    m_currentStartIndices.push_back(0);

    for (const auto& face : faces)
    {
        assert(face < m_startIndices.size());
        assert((face + 1) < m_startIndices.size());
        auto startIndex = m_startIndices[face];
        auto vertexCount = m_startIndices[face + 1] - startIndex;

        // update vertices

        for (int i = 0; i < vertexCount; ++i)
        {
            auto oldVertex = m_mappedVertices[startIndex + i];
            if (oldVertex >= m_mapToNewVertices.size())
            {
                m_mapToNewVertices.resize(oldVertex + 1, -1);
            }

            assert(oldVertex < m_mapToNewVertices.size());
            if (m_mapToNewVertices[oldVertex] < 0)
            {
                m_mapToNewVertices[oldVertex] = currentIndex;
                m_currentVertices.push_back(currentIndex);
                m_currentPointIndices.push_back(oldVertex);
                ++currentIndex;
            }
            else
            {
                m_currentVertices.push_back(m_mapToNewVertices[oldVertex]);
            }

            m_currentVertexIndices.push_back(m_vertices[startIndex + i]);
            m_currentMappedVertices.push_back(oldVertex);
        }

        // update start index
        previousStartIndex += vertexCount;
        m_currentStartIndices.push_back(previousStartIndex);

//        std::cout << "start index(" << face << ") = " << m_startIndices[face] << std::endl;
//        std::cout << "vertex count(" << face << ") = " << vertexCount << std::endl;

    }

    // reset map for later reuse
    for (const auto& vertex : m_currentMappedVertices)
    {
        assert(vertex < m_mapToNewVertices.size());
        m_mapToNewVertices[vertex] = -1;
    }
//    for (const auto& face : faces)
//    {
//        assert(face < m_startIndices.size());
//        assert((face + 1) < m_startIndices.size());
//        auto startIndex = m_startIndices[face];
//        auto vertexCount = m_startIndices[face + 1] - startIndex;

//        for (int i = 0; i < vertexCount; ++i)
//        {
//            auto oldVertex = m_vertices[startIndex + i];
//            assert(oldVertex < m_mapToNewVertices.size());
//            m_mapToNewVertices[oldVertex] = -1;
//        }
//    }

//    for (const auto& vertex : m_mapToNewVertices)
//    {
//        std::cout << vertex << " " << std::endl;
    //    }
}

size_t PolySplitter::getCurrentSplit() const
{
    return m_currentSplit;
}

void PolySplitter::getOriginalVertexIndices(std::vector<int32_t>& indices) const
{
    indices = m_currentVertexIndices;
}

void PolySplitter::getOriginalPointIndices(std::vector<int32_t>& indices) const
{
    indices = m_currentPointIndices;
}

void PolySplitter::getOriginalPrimitiveIndices(std::vector<int32_t>& indices) const
{
    if (m_currentMappedPrimitives.size() > 0)
    {
        indices = m_currentMappedPrimitives;
    }
    else
    {
        assert(m_currentSplit < m_faceMatches.size());
        indices = m_faceMatches[m_currentSplit];
    }
}

void PolySplitter::getVertexList(std::vector<int32_t>& vertices) const
{
    vertices = m_currentVertices;
}

void PolySplitter::getStartIndices(std::vector<int32_t>& startIndices) const
{
    startIndices = m_currentStartIndices;
}

// For arbitrary primitive attribute split
//    std::map<int32_t, int32_t> uniqueValues;
//    for (const auto& value : values)
//    {
//        auto location = uniqueValues.find(value);
//        if (location == uniqueValues.end())
//        {
//            auto result = uniqueValues.emplace(value, 1);
//            assert(result.second); // true if emplace worked
//            location = result.first;
//        }
//        location->second += 1;
//    }

//    return uniqueValues.size();

} // namespace bgeo
} // namespace ika
