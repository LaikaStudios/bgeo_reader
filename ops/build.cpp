/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "build.h"

#include <sstream>
#include <algorithm>
#include <cassert>

#include <FnAttribute/FnGroupBuilder.h>
#include <FnAttribute/FnDataBuilder.h>
namespace FnKat = Foundry::Katana;

#include "bgeo/Bgeo.h"
#include "bgeo/PolySplitter.h"

namespace ika
{
namespace BgeoInOp
{
namespace build
{

namespace {

const char* fundamentalTypeMap[] = {
    "unknown",
    "int",
    "float"
};

} // anonymous namespace

static std::string mapAttributeNameToType(const std::string& name)
{
    if (name == "force")
    {
        return "vector3";
    }
    else if (name == "pprevious")
    {
        return "point3";
    }

    return std::string();
}

static std::string convertType(const bgeo::Attribute& attribute)
{
    std::string subType = attribute.getSubType();
    if (subType == "hpoint")
    {
        return "point4";
    }
    if (subType == "nonarithmetic_integer")
    {
        return "int";
    }

    if (!subType.empty())
    {
        std::stringstream stream;
        stream << attribute.getTupleSize();
        return subType + stream.str();
    }

    std::string type = mapAttributeNameToType(attribute.getName());
    if (!type.empty())
    {
        return type;
    }

    auto fundamentalType = attribute.getFundamentalType();
    assert(static_cast<int>(fundamentalType) < 3);
    return fundamentalTypeMap[fundamentalType];
}

static FnKat::Attribute buildData(const bgeo::Attribute& attribute)
{
    auto fundamentalType = attribute.getFundamentalType();

    switch (fundamentalType)
    {

    case bgeo::parser::storage::Fpreal32:
    {
        FnKat::FloatBuilder builder(attribute.getTupleSize());
        attribute.getData(builder.get());
        return builder.build();
    }
    case bgeo::parser::storage::Int32:
    {
        FnKat::IntBuilder builder(attribute.getTupleSize());
        attribute.getData(builder.get());
        return builder.build();
    }
    default:
    {
    }
    }

    return FnKat::Attribute();
}

static FnKat::Attribute buildData(const bgeo::Attribute& attribute,
                                  const std::vector<int32_t>& indices)
{
    auto fundamentalType = attribute.getFundamentalType();

    switch (fundamentalType)
    {

    case bgeo::parser::storage::Fpreal32:
    {
        FnKat::FloatBuilder builder(attribute.getTupleSize());
        attribute.getDataForIndices(builder.get(), indices);
        return builder.build();
    }
    case bgeo::parser::storage::Int32:
    {
        FnKat::IntBuilder builder(attribute.getTupleSize());
        attribute.getDataForIndices(builder.get(), indices);
        return builder.build();
    }
    default:
    {
    }
    }

    return FnKat::Attribute();
}

static FnKat::Attribute buildStringIndices(const bgeo::Attribute& attribute,
                                           int32_t lastIndex)
{
    assert(attribute.getFundamentalType() == bgeo::parser::storage::Int32);

    FnKat::IntBuilder builder(attribute.getTupleSize());
    attribute.getData(builder.get());

    for (auto&& index : builder.get())
    {
        if (index == -1)
        {
            index = lastIndex;
        }
    }

    return builder.build();
}

static FnKat::Attribute buildStringValues(bgeo::Attribute& attribute,
                                          const std::vector<std::string>& strings,
                                          int tupleSize)
{
    std::vector<int32_t> indices;
    attribute.getData(indices);
    std::vector<std::string> values(indices.size());
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int32_t index = indices[i];
        if (index >= 0 && index < static_cast<int32_t>(strings.size()))
        {
            values[i] = strings[index];
        }
    }

    return FnKat::StringAttribute(values, tupleSize);
}

static FnKat::Attribute buildStringIndices(const bgeo::Attribute& attribute,
                                           int32_t lastIndex,
                                           const std::vector<int32_t>& indices)
{
    assert(attribute.getFundamentalType() == bgeo::parser::storage::Int32);

    FnKat::IntBuilder builder(attribute.getTupleSize());
    attribute.getDataForIndices(builder.get(), indices);

    for (auto&& index : builder.get())
    {
        if (index == -1)
        {
            index = lastIndex;
        }
    }

    return builder.build();
}

static FnKat::Attribute buildStringValues(bgeo::Attribute& attribute,
                                          const std::vector<std::string>& strings,
                                          int tupleSize,
                                          const std::vector<int32_t>& dataindices)
{
    std::vector<int32_t> indices;
    attribute.getDataForIndices(indices, dataindices);
    std::vector<std::string> values(indices.size());
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int32_t index = indices[i];
        if (index >= 0 && index < static_cast<int32_t>(strings.size()))
        {
            values[i] = strings[index];
        }
    }

    return FnKat::StringAttribute(values, tupleSize);
}


static FnKat::Attribute buildAttribute(bgeo::Attribute& attribute,
                                       const char* scope)
{
    FnKat::GroupBuilder dataBuilder;

    // scope
    dataBuilder.set("scope", FnKat::StringAttribute(scope));

    std::string subType = attribute.getSubType();
    auto tupleSize = attribute.getTupleSize();
    bool isArray = subType.empty() && tupleSize > 1;
    if (isArray)
    {
        dataBuilder.set("elementSize", FnKat::IntAttribute(tupleSize));
    }

    // strings from the attribute
    std::vector<std::string> strings;
    attribute.getStrings(strings);

    if (strings.size() > 0)
    {
        if (isArray)
        {
            // flatten string array from indices since index string arrays
            // don't seem to be supported in Katana.
            dataBuilder.set("value", buildStringValues(attribute, strings, tupleSize));
        }
        else
        {
            // add an extra slot on the indexedValue for empty strings and update
            // any -1 indices in the data to reflect that.
            int32_t lastIndex = static_cast<int32_t>(strings.size());
            strings.push_back("");
            dataBuilder.set("index", buildStringIndices(attribute, lastIndex));
            dataBuilder.set("indexedValue", FnKat::StringAttribute(strings));
        }
    }
    else
    {
        // inputType
        FnKat::StringAttribute typeAttribute = convertType(attribute);
        dataBuilder.set("outputType", typeAttribute);
        dataBuilder.set("inputType", typeAttribute);

        // value
        dataBuilder.set("value", buildData(attribute));
    }

    return dataBuilder.build();
}

static FnKat::Attribute buildAttribute(bgeo::Attribute& attribute,
                                       const char* scope,
                                       const std::vector<int32_t>& indices)
{
    FnKat::GroupBuilder dataBuilder;

    // scope
    dataBuilder.set("scope", FnKat::StringAttribute(scope));

    std::string subType = attribute.getSubType();
    auto tupleSize = attribute.getTupleSize();
    bool isArray = subType.empty() && tupleSize > 1;
    if (isArray)
    {
        dataBuilder.set("elementSize", FnKat::IntAttribute(tupleSize));
    }

    // strings from the attribute
    std::vector<std::string> strings;
    attribute.getStrings(strings);

    if (strings.size() > 0)
    {
        if (isArray)
        {
            // flatten string array from indices since index string arrays
            // don't seem to be supported in Katana.
            dataBuilder.set("value", buildStringValues(attribute, strings, tupleSize, indices));
        }
        else
        {
            // add an extra slot on the indexedValue for empty strings and update
            // any -1 indices in the data to reflect that.
            int32_t lastIndex = static_cast<int32_t>(strings.size());
            strings.push_back("");
            dataBuilder.set("index", buildStringIndices(attribute, lastIndex, indices));
            dataBuilder.set("indexedValue", FnKat::StringAttribute(strings));
        }
    }
    else
    {
        // inputType
        FnKat::StringAttribute typeAttribute = convertType(attribute);
        dataBuilder.set("outputType", typeAttribute);
        dataBuilder.set("inputType", typeAttribute);

        // value
        dataBuilder.set("value", buildData(attribute, indices));
    }

    return dataBuilder.build();
}

FnKat::FloatAttribute pointP(const bgeo::Bgeo& bgeo)
{
    FnKat::FloatBuilder builder(3);
    bgeo.getP(builder.get());
    if (builder.get().empty())
    {
        return FnKat::Attribute();
    }
    return builder.build();
}

FnKat::FloatAttribute pointN(const bgeo::Bgeo& bgeo)
{
    FnKat::FloatBuilder builder(3);
    bgeo.getPointN(builder.get());
    if (builder.get().empty())
    {
        return FnKat::Attribute();
    }
    return builder.build();
}

FnKat::FloatAttribute pointUV(const bgeo::Bgeo& bgeo)
{
    FnKat::FloatBuilder builder(2);
    bgeo.getPointUV(builder.get());
    if (builder.get().empty())
    {
        return FnKat::Attribute();
    }
    return builder.build();
}

FnKat::Attribute pointAttribute(const bgeo::Bgeo& bgeo, const char *name)
{
    auto attribute = bgeo.getPointAttributeByName(name);
    if (!attribute)
    {
        return FnKat::Attribute();
    }

    return buildData(*attribute);
}

FnKat::GroupAttribute
arbitraryPointGroup(const bgeo::Bgeo& bgeo, const StringList& skipList)
{
    FnKat::GroupBuilder gb;
    bool hasArbitrary = false;

    for (int64_t i = 0; i < bgeo.getPointAttributeCount(); ++i)
    {
        auto attribute = bgeo.getPointAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        auto builtAttribute = buildAttribute(*attribute, "point");
        if (builtAttribute.isValid())
        {
            hasArbitrary = true;
            gb.set(attribute->getName(), builtAttribute);
        }
    }

    if (hasArbitrary)
    {
        return gb.build();
    }

    return FnKat::Attribute();
}

FnKat::FloatAttribute vertexN(const bgeo::Bgeo& bgeo)
{
    FnKat::FloatBuilder builder(3);
    bgeo.getVertexN(builder.get());
    if (builder.get().empty())
    {
        return FnKat::Attribute();
    }
    return builder.build();
}

FnKat::FloatAttribute vertexUV(const bgeo::Bgeo& bgeo)
{
    FnKat::FloatBuilder builder(2);
    bgeo.getVertexUV(builder.get());
    if (builder.get().empty())
    {
        return FnKat::Attribute();
    }
    return builder.build();
}

FnKat::Attribute vertexAttribute(const bgeo::Bgeo& bgeo, const char* name)
{
    auto attribute = bgeo.getVertexAttributeByName(name);
    if (!attribute)
    {
        return FnKat::Attribute();
    }

    return buildData(*attribute);
}

FnKat::GroupAttribute
arbitraryGroup(const bgeo::Bgeo& bgeo, const StringList& skipList)
{
    FnKat::GroupBuilder gb;

    for (int64_t i = 0; i < bgeo.getPointAttributeCount(); ++i)
    {
        auto attribute = bgeo.getPointAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "point"));
    }

    for (int64_t i = 0; i < bgeo.getVertexAttributeCount(); ++i)
    {
        auto attribute = bgeo.getVertexAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "vertex"));
    }

    for (int64_t i = 0; i < bgeo.getPrimitiveAttributeCount(); ++i)
    {
        auto attribute = bgeo.getPrimitiveAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "face"));
    }

    for (int64_t i = 0; i < bgeo.getDetailAttributeCount(); ++i)
    {
        auto attribute = bgeo.getDetailAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "primitive"));
    }

    return gb.build();
}

FnKat::FloatAttribute pointP(const bgeo::Bgeo& bgeo,
                             const bgeo::PolySplitter& splitter)
{
    return pointAttribute(bgeo, splitter, "P");
}

FnKat::FloatAttribute pointN(const bgeo::Bgeo& bgeo,
                             const bgeo::PolySplitter& splitter)
{
    return pointAttribute(bgeo, splitter, "N");
}

FnKat::FloatAttribute pointUV(const bgeo::Bgeo& bgeo,
                              const bgeo::PolySplitter& splitter)
{
    return pointAttribute(bgeo, splitter, "UV");
}

FnKat::Attribute pointAttribute(const bgeo::Bgeo& bgeo,
                                const bgeo::PolySplitter& splitter,
                                const char *name)
{
    auto attribute = bgeo.getPointAttributeByName(name);
    if (!attribute)
    {
        return FnKat::Attribute();
    }

    std::vector<int32_t> indices;
    splitter.getOriginalPointIndices(indices);
    return buildData(*attribute, indices);
}

FnKat::GroupAttribute
arbitraryPointGroup(const bgeo::Bgeo& bgeo,
                    const bgeo::PolySplitter& splitter,
                    const StringList& skipList)
{
    FnKat::GroupBuilder gb;
    bool hasArbitrary = false;

    for (int64_t i = 0; i < bgeo.getPointAttributeCount(); ++i)
    {
        auto attribute = bgeo.getPointAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        std::vector<int32_t> indices;
        splitter.getOriginalPointIndices(indices);
        auto builtAttribute = buildAttribute(*attribute, "point", indices);
        if (builtAttribute.isValid())
        {
            hasArbitrary = true;
            gb.set(attribute->getName(), builtAttribute);
        }
    }

    if (hasArbitrary)
    {
        return gb.build();
    }

    return FnKat::Attribute();
}

FnKat::FloatAttribute vertexN(const bgeo::Bgeo& bgeo,
                              const bgeo::PolySplitter& splitter)
{
    return vertexAttribute(bgeo, splitter, "N");
}

FnKat::FloatAttribute vertexUV(const bgeo::Bgeo& bgeo,
                               const bgeo::PolySplitter& splitter)
{
    return vertexAttribute(bgeo, splitter, "UV");
}

FnKat::Attribute vertexAttribute(const bgeo::Bgeo& bgeo,
                                 const bgeo::PolySplitter& splitter,
                                 const char* name)
{
    auto attribute = bgeo.getVertexAttributeByName(name);
    if (!attribute)
    {
        return FnKat::Attribute();
    }

    std::vector<int32_t> indices;
    splitter.getOriginalVertexIndices(indices);
    return buildData(*attribute, indices);
}

FnKat::GroupAttribute
arbitraryGroup(const bgeo::Bgeo& bgeo,
               const bgeo::PolySplitter& splitter,
               const StringList& skipList)
{
    FnKat::GroupBuilder gb;

    std::vector<int32_t> pointIndices;
    splitter.getOriginalPointIndices(pointIndices);

    std::vector<int32_t> vertexIndices;
    splitter.getOriginalVertexIndices(vertexIndices);

    std::vector<int32_t> primitiveIndices;
    splitter.getOriginalPrimitiveIndices(primitiveIndices);

    for (int64_t i = 0; i < bgeo.getPointAttributeCount(); ++i)
    {
        auto attribute = bgeo.getPointAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "point", pointIndices));
    }

    for (int64_t i = 0; i < bgeo.getVertexAttributeCount(); ++i)
    {
        auto attribute = bgeo.getVertexAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "vertex", vertexIndices));
    }

    for (int64_t i = 0; i < bgeo.getPrimitiveAttributeCount(); ++i)
    {
        auto attribute = bgeo.getPrimitiveAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "face", primitiveIndices));
    }

    for (int64_t i = 0; i < bgeo.getDetailAttributeCount(); ++i)
    {
        auto attribute = bgeo.getDetailAttribute(i);

        // skip the attribute if the name is in the skip list
        auto index = std::find(skipList.begin(), skipList.end(),
                               attribute->getName());
        if (index != skipList.end())
        {
            continue;
        }

        gb.set(attribute->getName(), buildAttribute(*attribute, "primitive"));
    }

    return gb.build();
}

} // namespace build
} // namespace BgeoInOp
} // namespace ika
