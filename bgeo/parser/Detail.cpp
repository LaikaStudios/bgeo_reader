/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Detail.h"

#include "Attribute.h"
#include "PrimitiveGroup.h"
#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

Detail::Detail(bool checkVersion)
    : pointCount(0),
      vertexCount(0),
      primitiveCount(0),
      primitives(*this),
      checkVersion(checkVersion)
{
}

Detail::~Detail()
{
    for (auto it = vertexAttributes.begin(); it != vertexAttributes.end(); ++it)
    {
        delete *it;
    }

    for (auto it = pointAttributes.begin(); it != pointAttributes.end(); ++it)
    {
        delete *it;
    }

    for (auto it = primitiveAttributes.begin();
         it != primitiveAttributes.end(); ++it)
    {
        delete *it;
    }

    for (auto it = detailAttributes.begin(); it != detailAttributes.end(); ++it)
    {
        delete *it;
    }
}

void Detail::loadHeaderAndInfo(UT_JSONParser& parser)
{
    parseBeginArray(parser);
    {
        fileVersion.load(parser);

        if (fileVersion.major > 13)
        {
            parseSkipKeyAndValue(parser); // skip hasindex
        }

        parseArrayValueForKey(parser, "pointcount", pointCount);
        parseArrayValueForKey(parser, "vertexcount", vertexCount);
        parseArrayValueForKey(parser, "primitivecount", primitiveCount);

        parseArrayKey(parser, "info");
        info.load(parser);
    }
}

static void loadAttributes(UT_JSONParser& parser,
                           std::vector<Attribute*>& attributes, int64 count)
{
    for (auto it = parser.beginArray(); !it.atEnd(); ++it)
    {
        Attribute* attribute = new Attribute(count);
        attribute->load(parser);
        attributes.push_back(attribute);
    }
}

void Detail::loadGeometry(UT_JSONParser &parser)
{
    UT_WorkBuffer buffer;
    UT_String key;
    for (auto geoit = parser.beginArray(); !geoit.atEnd(); ++geoit)
    {
        geoit.getLowerKey(buffer);
        key = buffer.buffer();
        if (key == "fileversion")
        {
            UT_WorkBuffer version;
            BGEO_CHECK(parser.parseString(version));
            fileVersion.parse(version.buffer());
            if (checkVersion)
            {
                FileVersion::checkVersion(fileVersion);
            }
        }
        else if (key == "hasindex")
        {
            BGEO_CHECK(parser.skipNextObject());
        }
        else if (key == "pointcount")
        {
            BGEO_CHECK(parser.parseInt(pointCount));
        }
        else if (key == "vertexcount")
        {
            BGEO_CHECK(parser.parseInt(vertexCount));
        }
        else if (key == "primitivecount")
        {
            BGEO_CHECK(parser.parseInt(primitiveCount));
        }
        else if (key == "info")
        {
            info.load(parser);
        }
        else if (key == "topology")
        {
            vertexMap.load(parser, vertexCount);
        }
        else if (key == "attributes")
        {
            for (auto attrit = parser.beginArray(); !attrit.atEnd(); ++attrit)
            {
                attrit.getLowerKey(buffer);
                key = buffer.buffer();
                if (key == "vertexattributes")
                {
                    loadAttributes(parser, vertexAttributes, vertexCount);
                }
                else if (key == "pointattributes")
                {
                    loadAttributes(parser, pointAttributes, pointCount);
                }
                else if (key == "primitiveattributes")
                {
                    loadAttributes(parser, primitiveAttributes, primitiveCount);
                }
                else if (key == "globalattributes")
                {
                    loadAttributes(parser, detailAttributes, 1);
                }
                else
                {
                    std::cerr << "Warning: unsupported attribute type: " << key << std::endl;
                    BGEO_CHECK(parser.skipNextObject());
                }
            }
        }
        else if (key == "primitives")
        {
            primitives.load(parser);
        }
        else if (key == "pointgroups" || key == "edgegroups")
        {
            // point and edge groups not supported atm
            BGEO_CHECK(parser.skipNextObject());
        }
        else if (key == "primitivegroups")
        {
            for (auto groupit = parser.beginArray(); !groupit.atEnd(); ++groupit)
            {
                primitiveGroups.push_back(std::unique_ptr<PrimitiveGroup>(
                                              new PrimitiveGroup(*this)));
                primitiveGroups.back()->load(parser);
            }
        }
        else if (key == "sharedprimitivedata")
        {
            primitives.loadSharedData(parser);
        }
        else if (key == "index")
        {
            // index not supported
            BGEO_CHECK(parser.skipNextObject());
        }
        else if (key == "indexposition")
        {
            // indexposition not supported
            BGEO_CHECK(parser.skipNextObject());
        }
        else
        {
            std::cerr << "Warning: unsupported detail member: " << key
                      << " at " << parser.getStreamPosition() << std::endl;
            BGEO_CHECK(parser.skipNextObject());
        }
    }
}

int64 Detail::getPointIndexForVertex(int64 vertex) const
{
    assert(vertex < vertexMap.vertexCount);
    return vertexMap.vertices[vertex];
}

const Attribute* Detail::getPointAttributeByName(const char* name) const
{
    for (auto it = pointAttributes.begin(); it != pointAttributes.end(); ++it)
    {
        if ((*it)->name == name)
        {
            return *it;
        }
    }
    return 0;
}

const Attribute* Detail::getVertexAttributeByName(const char* name) const
{
    for (auto it = vertexAttributes.begin(); it != vertexAttributes.end(); ++it)
    {
        if ((*it)->name == name)
        {
            return *it;
        }
    }
    return 0;
}

const Attribute* Detail::getPrimitiveAttributeByName(const char* name) const
{
    for (auto it = primitiveAttributes.begin();
         it != primitiveAttributes.end(); ++it)
    {
        if ((*it)->name == name)
        {
            return *it;
        }
    }
    return 0;
}

const Attribute* Detail::getDetailAttributeByName(const char *name) const
{
    for (auto it = detailAttributes.begin();
         it != detailAttributes.end(); ++it)
    {
        if ((*it)->name == name)
        {
            return *it;
        }
    }
    return 0;
}

void Detail::mapVerticesToPoints(const VertexArrayBuilder::VertexArray& vertices,
                                 VertexArrayBuilder::VertexArray& points) const
{
    points.resize(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        assert(vertices[i] < vertexMap.vertexCount);
        points[i] = vertexMap.vertices[vertices[i]];
    }
}

std::ostream& operator << (std::ostream& co, const Detail& detail)
{
    co << "fileversion = " << detail.fileVersion << "\n"
       << "pointcount = " << detail.pointCount << "\n"
       << "vertexcount = " << detail.vertexCount << "\n"
       << "primitivecount = " << detail.primitiveCount << "\n"

       << "\ninfo\n==============\n" << detail.info << "\n"
       << "\ntopology\n==============\n" << detail.vertexMap << "\n";

    co << "\nvertexattributes\n==============\n";
    for (auto it = detail.vertexAttributes.begin();
         it != detail.vertexAttributes.end(); ++it)
    {
        co << *(*it) << "\n";
    }

    co << "\npointattributes\n==============\n";
    for (auto it = detail.pointAttributes.begin();
         it != detail.pointAttributes.end(); ++it)
    {
        co << *(*it) << "\n";
    }

    co << "\nprimitiveattributes\n==============\n";
    for (auto it = detail.primitiveAttributes.begin();
         it != detail.primitiveAttributes.end(); ++it)
    {
        co << *(*it) << "\n";
    }

    co << "\ndetailattributes\n==============\n";
    for (auto it = detail.detailAttributes.begin();
         it != detail.detailAttributes.end(); ++it)
    {
        co << *(*it) << "\n";
    }

    co << "\nprimitives\n==============\n" << detail.primitives;

    co << "\nprimitive groups\n==============\n";
    for (auto it = detail.primitiveGroups.begin();
         it != detail.primitiveGroups.end(); ++it)
    {
        co << *(*it) << "\n";
    }

    return co;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
