/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_POLY_SPLITTER_H
#define BGEO_POLY_SPLITTER_H

#include <vector>
#include <cstddef>
#include <cstdint>

namespace ika
{
namespace bgeo
{

class Bgeo;
class Poly;

class PolySplitter
{
public:
    PolySplitter();

    size_t splitByPrimitiveString(const Bgeo& bgeo, const Poly& poly,
                                  const char* attributeName);
    size_t splitThisPoly(const Bgeo& bgeo, const Poly& poly, size_t primitiveIndex);

    size_t getSplitCount() const;

    void setCurrentSplit(size_t splitIndex);
    size_t getCurrentSplit() const;

    // FIXME: these are inefficient because the copy data into indices.
    // should just return references to the internal buffers.
    void getOriginalVertexIndices(std::vector<int32_t>& indices) const;
    void getOriginalPointIndices(std::vector<int32_t>& indices) const;
    void getOriginalPrimitiveIndices(std::vector<int32_t>& indices) const;
    void getVertexList(std::vector<int32_t>& vertices) const;
    void getStartIndices(std::vector<int32_t>& startIndices) const;

private:
    typedef std::vector<std::vector<int32_t>> FaceMatches;
    FaceMatches m_faceMatches;

    // cached poly info
    std::vector<int32_t> m_vertices;
    std::vector<int32_t> m_mappedVertices;
    std::vector<int32_t> m_startIndices;

    size_t m_currentSplit;
    std::vector<int32_t> m_mapToNewVertices;
    std::vector<int32_t> m_currentMappedVertices;
    std::vector<int32_t> m_currentMappedPrimitives;

    std::vector<int32_t> m_currentPointIndices;
    std::vector<int32_t> m_currentVertexIndices;
    std::vector<int32_t> m_currentVertices;
    std::vector<int32_t> m_currentStartIndices;
};

} // namespace bgeo
} // namespace ika

#endif // BGEO_POLY_SPLITTER_H
