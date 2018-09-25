/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Bgeo.h"

#include <UT/UT_IStream.h>
#include <UT/UT_JSONParser.h>

#include "parser/ReadError.h"
#include "parser/Detail.h"
#include "parser/Attribute.h"
#include "parser/Primitive.h"
#include "parser/PrimitiveGroup.h"
#include "parser/compression.h"

#include "Primitive.h"
#include "Poly.h"
#include "PrimitiveFactory.h"

#include "Attribute.h"

namespace ika
{
namespace bgeo
{

class Bgeo::Impl
{
public:
    explicit Impl(const char* bgeoPath, bool checkVersion);
    explicit Impl(std::shared_ptr<parser::Detail> detail);
    ~Impl() = default;

    std::shared_ptr<parser::Detail> detail;
    factory::EmbeddedGeoMap embeddedGeoMap;

    void parseStream(UT_IStream& stream);
};

Bgeo::Impl::Impl(const char *bgeoPath, bool checkVersion)
    : detail(new parser::Detail(checkVersion))
{
    UT_IFStream stream(bgeoPath, UT_ISTREAM_BINARY);
    if (stream.isError())
    {
        UT_String message;
        message.sprintf("Unable to read file: %s", bgeoPath);
        throw parser::ReadError(message);
    }

    auto decompStream = ika::bgeo::parser::getDecompressionStream(bgeoPath, stream);
    if (decompStream)
    {
        parseStream(*decompStream);
    }
    else
    {
        parseStream(stream);
    }
}

Bgeo::Impl::Impl(std::shared_ptr<parser::Detail> detail)
    : detail(detail)
{
}

void Bgeo::Impl::parseStream(UT_IStream& stream)
{
    UT_AutoJSONParser parserLoader(stream);
    assert(detail);
    detail->loadGeometry(parserLoader.parser());
}

Bgeo::Bgeo(const char* bgeoPath, bool checkVersion)
    : m_pimpl(new Impl(bgeoPath, checkVersion))
{
}

Bgeo::Bgeo(std::shared_ptr<parser::Detail> detail)
    : m_pimpl(new Impl(detail))
{
}

Bgeo::~Bgeo() = default;

int64_t Bgeo::getPointCount() const
{
    return m_pimpl->detail->pointCount;
}

int64_t Bgeo::getTotalVertexCount() const
{
    return m_pimpl->detail->vertexCount;
}

int64_t Bgeo::getPrimitiveCount() const
{
    return m_pimpl->detail->primitives.getCount();
}

void Bgeo::getBoundingBox(double bound[6]) const
{
    memcpy(bound, m_pimpl->detail->info.bounds, sizeof(double) * 6);
}

void Bgeo::printSummary(std::ostream &co) const
{
    co << *m_pimpl->detail;
}

void Bgeo::getP(std::vector<float>& P) const
{
    const bgeo::parser::Attribute* attribute = m_pimpl->detail->getPointAttributeByName("P");
    assert(attribute); // should always have point P

    int64_t pointCount = getPointCount();
    P.resize(3 * pointCount);
    attribute->data.copyTo(P.data(), 3, P.size(), 0, pointCount);
}

void Bgeo::getPointN(std::vector<float>& N) const
{
    const bgeo::parser::Attribute* attribute = m_pimpl->detail->getPointAttributeByName("N");
    if (!attribute)
    {
        return;
    }

    int64_t pointCount = getPointCount();
    N.resize(3 * pointCount);
    attribute->data.copyTo(N.data(), 3, pointCount, 0, pointCount);
}

void Bgeo::getPointUV(std::vector<float>& uv) const
{
    const bgeo::parser::Attribute* attribute = m_pimpl->detail->getPointAttributeByName("uv");
    if (!attribute)
    {
        return;
    }

    int64_t pointCount = getPointCount();
    uv.resize(2 * pointCount);
    attribute->data.copyTo(uv.data(), 2, pointCount, 0, pointCount);
}

void Bgeo::getVertexN(std::vector<float>& N) const
{
    const bgeo::parser::Attribute* attribute = m_pimpl->detail->getVertexAttributeByName("N");
    if (!attribute)
    {
        return;
    }

    int64_t vertexCount = getTotalVertexCount();
    N.resize(3 * vertexCount);
    attribute->data.copyTo(N.data(), 3, vertexCount, 0, vertexCount);
}

void Bgeo::getVertexUV(std::vector<float>& uv) const
{
    const bgeo::parser::Attribute* attribute = m_pimpl->detail->getVertexAttributeByName("uv");
    if (!attribute)
    {
        return;
    }

    int64_t vertexCount = getTotalVertexCount();
    uv.resize(2 * vertexCount);
    attribute->data.copyTo(uv.data(), 2, vertexCount, 0, vertexCount);
}

Bgeo::PrimitivePtr Bgeo::getPrimitive(int64_t index) const
{
    if (index >= m_primitiveCache.size())
    {
        m_primitiveCache.resize(index + 1);
    }

    auto& primptr = m_primitiveCache[index];
    if (primptr)
    {
        return primptr;
    }

    const parser::Primitive* parserPrimitive = m_pimpl->detail->primitives.getPrimitive(index);
    assert(parserPrimitive);

    primptr = factory::create(*this, *parserPrimitive, m_pimpl->embeddedGeoMap, index);
    return primptr;
}

void Bgeo::preCachePrimitives()
{
    for (int64_t i = 0; i < getPrimitiveCount(); ++i)
    {
        getPrimitive(i);
    }
}

int64_t Bgeo::getPointAttributeCount() const
{
    return m_pimpl->detail->pointAttributes.size();
}

Bgeo::AttributePtr Bgeo::getPointAttribute(int64_t index) const
{
    assert(index < m_pimpl->detail->pointAttributes.size());
    return AttributePtr(new Attribute(*m_pimpl->detail->pointAttributes[index]));
}

Bgeo::AttributePtr Bgeo::getPointAttributeByName(const char* name) const
{
    auto attribute = m_pimpl->detail->getPointAttributeByName(name);
    if (!attribute)
    {
        return nullptr;
    }
    return AttributePtr(new Attribute(*attribute));
}

int64_t Bgeo::getVertexAttributeCount() const
{
    return m_pimpl->detail->vertexAttributes.size();
}

Bgeo::AttributePtr Bgeo::getVertexAttribute(int64_t index) const
{
    assert(index < m_pimpl->detail->vertexAttributes.size());
    return AttributePtr(new Attribute(*m_pimpl->detail->vertexAttributes[index]));
}

Bgeo::AttributePtr Bgeo::getVertexAttributeByName(const char* name) const
{
    auto attribute = m_pimpl->detail->getVertexAttributeByName(name);
    if (!attribute)
    {
        return nullptr;
    }
    return AttributePtr(new Attribute(*attribute));
}

int64_t Bgeo::getPrimitiveAttributeCount() const
{
    return m_pimpl->detail->primitiveAttributes.size();
}

Bgeo::AttributePtr Bgeo::getPrimitiveAttribute(int64_t index) const
{
    assert(index < m_pimpl->detail->primitiveAttributes.size());
    return AttributePtr(new Attribute(*m_pimpl->detail->primitiveAttributes[index]));
}

Bgeo::AttributePtr Bgeo::getPrimitiveAttributeByName(const char* name) const
{
    auto attribute = m_pimpl->detail->getPrimitiveAttributeByName(name);
    if (!attribute)
    {
        return nullptr;
    }
    return AttributePtr(new Attribute(*attribute));
}

int64_t Bgeo::getDetailAttributeCount() const
{
    return m_pimpl->detail->detailAttributes.size();
}

Bgeo::AttributePtr Bgeo::getDetailAttribute(int64_t index) const
{
    assert(index < m_pimpl->detail->detailAttributes.size());
    return AttributePtr(new Attribute(*m_pimpl->detail->detailAttributes[index]));
}

Bgeo::AttributePtr Bgeo::getDetailAttributeByName(const char *name) const
{
    auto attribute = m_pimpl->detail->getDetailAttributeByName(name);
    if (!attribute)
    {
        return nullptr;
    }
    return AttributePtr(new Attribute(*attribute));
}

int64_t Bgeo::getPrimitiveGroupCount() const
{
    return m_pimpl->detail->primitiveGroups.size();
}

std::string Bgeo::getPrimitiveGroupName(int64_t index) const
{
    assert(index < m_pimpl->detail->primitiveGroups.size());
    const parser::PrimitiveGroup& group =
            *m_pimpl->detail->primitiveGroups[index];
    return group.name.buffer();
}

void Bgeo::getPrimitiveGroup(int64_t index,
                             std::vector<int32_t>& groupIndices) const
{
    assert(index < m_pimpl->detail->primitiveGroups.size());
    const parser::PrimitiveGroup& group =
            *m_pimpl->detail->primitiveGroups[index];
    group.expandGroup(groupIndices);
}

} // namespace ika
} // namespace bgeo
