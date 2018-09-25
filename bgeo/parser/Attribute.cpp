/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Attribute.h"

#include <cassert>

#include <UT/UT_JSONHandle.h>

#include "util.h"
#include "ReadError.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

// FIXME move into common location since it is used by Run as well

class StringListHandle : public UT_JSONHandleError
{
public:
    StringListHandle(std::vector<std::string>& strings)
        : strings(strings)
    {
    }

    /*virtual*/ bool jsonString(UT_JSONParser &p, const char *value, int64 len)
    {
        strings.push_back(value);
        return true;
    }

    /*virtual*/ bool jsonBeginArray(UT_JSONParser &p)
    {
        return true;
    }

    /*virtual*/ bool jsonEndArray(UT_JSONParser &p)
    {
        return true;
    }

private:
    std::vector<std::string>& strings;
};

Attribute::Attribute(int64 elementCount)
    : elementCount(elementCount),
      data(elementCount)
{
}

void Attribute::load(UT_JSONParser& parser)
{
    parseBeginArray(parser);
    {
        parseBeginArray(parser);
        {
            parseArrayValueForKey(parser, "scope", scope);
            parseArrayValueForKey(parser, "type", type);
            parseArrayValueForKey(parser, "name", name);
            parseArrayKey(parser, "options");

            UT_WorkBuffer buffer;
            UT_String key;
            for (auto it = parser.beginMap(); !it.atEnd(); ++it)
            {
                it.getLowerKey(buffer);
                key = buffer.buffer();
                if (key == "type")
                {
                    parseBeginMap(parser);

                    parseMapKey(parser, "type");
                    BGEO_CHECK(parser.skipNextObject());

                    parseMapValueForKey(parser, "value", subtype);

                    parseEndMap(parser);
                }
                else
                {
                    BGEO_CHECK(parser.skipNextObject());
                }
            }
        }
        parseEndArray(parser);

        UT_WorkBuffer buffer;
        UT_String key;
        storage::Storage storage;
        for (auto it = parser.beginArray(); !it.atEnd(); ++it)
        {
            it.getLowerKey(buffer);
            key = buffer.buffer();
            if (key == "size")
            {
                BGEO_CHECK(parser.skipNextObject());
            }
            else if (key == "storage")
            {
                BGEO_CHECK(parser.parseString(buffer));
                storage = storage::toStorage(buffer.buffer());
            }
            else if (key == "defaults")
            {
                BGEO_CHECK(parser.skipNextObject());
            }
            else if (key == "strings")
            {
                StringListHandle stringListHandle(strings);
                BGEO_CHECK(parser.parseObject(stringListHandle));
            }
            else if (key == "indices" || key == "values")
            {
                if (type == "stringarray")
                {
                    parseBeginArray(parser);
                    data.loadArray(parser, storage, strings.size());
                    parseEndArray(parser);
                }
                else
                {
                    data.load(parser);
                }
            }
            else
            {
                std::cerr << "Warning: unsupported attribute member: " << key
                          << "at " << parser.getStreamPosition() << std::endl;
                BGEO_CHECK(parser.skipNextObject());
            }
        }
    }
    parseEndArray(parser);
}

std::ostream& operator << (std::ostream& co, const Attribute& attribute)
{
    co << "name = " << attribute.name << "\n"
       << "{\n"
       << "    scope = " << attribute.scope << "\n"
       << "    type = " << attribute.type << "\n"
       << "    subtype = " << attribute.subtype << "\n"
       << "    " << attribute.data << "\n";

    if (attribute.type == "string")
    {
        co << "    strings [";
        if (attribute.strings.size() < 20)
        {
            for (auto value : attribute.strings)
            {
                co << value << " ";
            }
        }
        else
        {
            co << "...";
        }
        co << "]\n";
    }

    co << "    unpacked [";
    if (attribute.elementCount * attribute.data.tupleSize < 20)
    {
        if (attribute.data.storage == storage::Fpreal32)
        {
            std::vector<fpreal32> unpacked;
            attribute.data.getUnpackedData(unpacked);
            for (auto value : unpacked)
            {
                co << value << " ";
            }
        }
        else if (attribute.data.storage == storage::Int32)
        {
            std::vector<int32> unpacked;
            attribute.data.getUnpackedData(unpacked);
            for (auto value : unpacked)
            {
                co << value << " ";
            }
        }
    }
    else
    {
        co << "...";
    }
    co << "]\n" << "}";

    return co;
}

} // namespace parser
} // namespace ika
} // namespace bgeo
