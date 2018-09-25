/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PackedGeometry.h"

#include <cassert>
#include <limits>

#include "Attribute.h"
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
    UniformDataHandle(PackedGeometry& packed)
        : packed(packed)
    {
    }

    /*virtual*/ bool jsonKey(UT_JSONParser& parser, const char *v, int64 len)
    {
        UT_String key(v);
        return packed.parseDataWithKey(parser, key);
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
    PackedGeometry& packed;
};

constexpr double INF = std::numeric_limits<double>::infinity();

} // namespace anonymous

PackedGeometry::PackedGeometry(const Detail& detail)
    : Primitive(detail),
      boundsValid(false)
{
}

PackedGeometry::PackedGeometry(const PackedGeometry& packed)
    : Primitive(packed.detail),
      boundsValid(packed.boundsValid),
      embeddedKey(packed.embeddedKey),
      transform(packed.transform),
      vertex(packed.vertex)
{
    memcpy(bounds, packed.bounds, sizeof(double) * 6);
    memcpy(pivot, packed.pivot, sizeof(double) * 3);
}

PackedGeometry* PackedGeometry::clone() const
{
    return new PackedGeometry(*this);
}

/*virtual*/ void PackedGeometry::loadData(UT_JSONParser& parser)
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
            message.sprintf("Invalid packed geometry data: \"%s\"",
                            key.toStdString().c_str());
            throw ReadError(message.buffer());
        }
    }
}

/*virtual*/ void PackedGeometry::loadVaryingData(UT_JSONParser& parser,
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

/*virtual*/ void PackedGeometry::loadUniformData(UT_JSONParser& parser)
{
    UniformDataHandle uniformHandle(*this);
    BGEO_CHECK(parser.parseObject(uniformHandle));
}

/*virtual*/ bool PackedGeometry::loadSharedData(UT_JSONParser& parser,
                                                UT_String& dataType,
                                                UT_String& dataKey)
{
    if (dataType == "gu:embeddedgeo" && dataKey == embeddedKey)
    {
        embeddedGeo = std::make_shared<Detail>();
        embeddedGeo->loadGeometry(parser);
        return true;
    }

    return false;
}

/*virtual*/ void PackedGeometry::loadSharedData(const Primitive& source,
                                                const UT_String& dataType,
                                                const UT_String& dataKey)
{
    if (dataType != "gu:embeddedgeo" || dataKey != embeddedKey)
    {
        return;
    }

    if (source.getType() != getType())
    {
        return;
    }

    const PackedGeometry& sourcePacked =
            *static_cast<const PackedGeometry*>(&source);

    embeddedGeo = sourcePacked.embeddedGeo;
}

/*virtual*/ std::ostream& PackedGeometry::encode(std::ostream& co) const
{
    co << "    ";
    Primitive::encode(co);

    if (boundsValid)
    {
        co << "\n"
           << "    bounds = [";

        for (int i = 0; i < 6; ++i)
        {
            co << bounds[i] << " ";
        }
        co << "]\n";
    }

    co << "    embedded = " << embeddedKey << "\n"
       << "    pivot = [";

    for (int i = 0; i < 3; ++i)
    {
        co << pivot[i] << " ";
    }

    co << "]\n"
       << "    transform = [" << transform << "]\n"
       << "    vertex = " << vertex;

    return co;
}

bool PackedGeometry::hasBounds() const
{
    return boundsValid;
}

void PackedGeometry::getBounds(double bounds[6]) const
{
    memcpy(bounds, this->bounds, sizeof(double) * 6);
}

void PackedGeometry::getPivot(double pivot[3]) const
{
    memcpy(pivot, this->pivot, sizeof(double) * 3);
}

void PackedGeometry::getTranslate(fpreal64 translate[3]) const
{
    int64 pointIndex = detail.getPointIndexForVertex(vertex);
    const Attribute* attribute = detail.getPointAttributeByName("P");
    assert(attribute);
    attribute->data.copyTo(translate, 3, 1, pointIndex, 1);
}

void PackedGeometry::getTransform(double matrix[16]) const
{
    assert(sizeof(transform) == 16 * sizeof(double));
    memcpy(matrix, transform.data(), 16 * sizeof(double));
}

const std::shared_ptr<Detail> PackedGeometry::getEmbeddedGeo() const
{
    return embeddedGeo;
}

UT_String PackedGeometry::getEmbeddedKey() const
{
    return embeddedKey;
}

/*virtual*/
bool PackedGeometry::parseDataWithKey(UT_JSONParser& parser, const UT_String& key)
{
    if (key == "parameters")
    {
        UT_WorkBuffer buffer;
        UT_String parmkey;
        for (auto it = parser.beginMap(); !it.atEnd(); ++it)
        {
            it.getLowerKey(buffer);
            parmkey = buffer.buffer();
            if (!parseParametersWithKey(parser, parmkey))
            {
                return false;
            }
        }
    }
    else if (key == "pivot")
    {
        BGEO_CHECK(parser.parseUniformArray(pivot, 3));
    }
    else if (key == "transform")
    {
        UT_Matrix3D m3;
        BGEO_CHECK(m3.load(parser));
        transform = m3;
    }
    else if (key == "vertex")
    {
        BGEO_CHECK(parser.parseValue(vertex));
    }
    else if (key == "viewportlod")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else
    {
        return false;
    }

    return true;
}

/*virtual*/
bool PackedGeometry::parseParametersWithKey(UT_JSONParser& parser,
                                            const UT_String& key)
{
    if (key == "cachedbounds")
    {
        boundsValid = true;
        parser.parseUniformArray(bounds, 6);
    }
    else if (key == "embedded")
    {
        UT_WorkBuffer buffer;
        BGEO_CHECK(parser.parseValue(buffer));
        embeddedKey.harden(buffer.buffer());
    }
    else if (key == "pointinstancetransform")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else
    {
        return false;
    }

    return true;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
