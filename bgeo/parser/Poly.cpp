/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Poly.h"

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
    UniformDataHandle(Poly& poly)
        : poly(poly)
    {
    }

    /*virtual*/ bool jsonKey(UT_JSONParser& parser, const char *v, int64 len)
    {
        UT_String key(v);
        if (key == "closed")
        {
            poly.closed.resize(1);
            bool closedValue;
            BGEO_CHECK(parser.parseBool(closedValue));
            poly.closed[0] = closedValue;
            return true;
        }

        return false;
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
    Poly& poly;
};

} // anonymous namespace

Poly::Poly(const Detail& detail)
    : Primitive(detail)
{
}

Poly* Poly::clone() const
{
    return new Poly(*this);
}

/*virtual*/ void Poly::loadData(UT_JSONParser &parser)
{
    parseBeginArray(parser);
    {
        parseArrayKey(parser, "vertex");
        VertexArrayBuilder vertexBuilder(vertices, sides);
        BGEO_CHECK(parser.parseObject(vertexBuilder));

        closed.resize(1);
        bool closedValue = true;
        parseArrayValueForKey(parser, "closed", closedValue);
        closed[0] = closedValue;
    }
    parseEndArray(parser);
}

/*virtual*/ void Poly::loadVaryingData(UT_JSONParser& parser, const StringList& fields)
{
    // NOTE: for now just support only the vertex field
    if (fields.size() != 1 || fields[0] != "vertex")
    {
        throw ReadError("Poly primitive supports only varying vertex");
    }

    VertexArrayBuilder builder(vertices, sides);
    for (auto it = parser.beginArray(); !it.atEnd(); ++it)
    {
        BGEO_CHECK(parser.parseObject(builder));
    }
}

/*virtual*/ void Poly::loadUniformData(UT_JSONParser& parser)
{
    UniformDataHandle uniformHandle(*this);
    BGEO_CHECK(parser.parseObject(uniformHandle));
}

/*virtual*/ std::ostream& Poly::encode(std::ostream& co) const
{
    co << "    ";
    Primitive::encode(co);

    co << "\n    vertices = [";
    if (vertices.size() < 20)
    {
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            co << *it << " ";
        }
    }
    else
    {
        co << "...";
    }
    co << "]" << "\n";

    co << "    sides = [";
    if (sides.size() < 20)
    {
        for (auto it = sides.begin(); it != sides.end(); ++it)
        {
            co << *it << " ";
        }
    }
    else
    {
        co << "...";
    }
    co << "]" << "\n";

    if (closed.size() > 1)
    {
        co << "    closed = [";
        if (closed.size() < 20)
        {
            for (auto it = closed.begin(); it != closed.end(); ++it)
            {
                co << (*it ? "true" : "false") << " ";
            }
        }
        else
        {
            co << "...";
        }
        co << "]";
    }
    else if (closed.size() == 1)
    {
        co << "    closed = " << (closed[0] ? "true" : "false");
    }
    return co;
}

void Poly::getVerticesMappedToPoints(VertexArrayBuilder::VertexArray& vertexPoints) const
{
    detail.mapVerticesToPoints(vertices, vertexPoints);
}

} // namespace parser
} // namespace ika
} // namespace bgeo
