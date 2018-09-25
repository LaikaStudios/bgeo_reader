/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "PrimitiveGroup.h"

#include <cassert>

#include <UT/UT_JSONHandle.h>

#include "util.h"
#include "Detail.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

namespace
{

class BoolArrayHandle : public UT_JSONHandleError
{
public:
    BoolArrayHandle(std::vector<bool>& flags)
        : m_flags(flags),
          m_stack(0)
    {
    }

    /*virtual*/ bool jsonBool(UT_JSONParser& parser, bool value)
    {
        m_flags.push_back(value);
        return true;
    }

    /*virtual*/ bool jsonInt(UT_JSONParser& parser, int64 value)
    {
        m_flags.push_back(value);
        return true;
    }

    /*virtual*/ bool jsonBeginArray(UT_JSONParser& parser)
    {
        if (m_stack > 0)
        {
            UT_String message;
            message.sprintf("Unexpected [ at byte 0x%04lx",
                            parser.getStreamPosition());
            throw ReadError(message);
        }
        m_stack++;
        return true;
    }

    /*virtual*/ bool jsonEndArray(UT_JSONParser& parser)
    {
        m_stack--;
        if (m_stack < 0)
        {
            UT_String message;
            message.sprintf("Unexpected ] at byte 0x%04lx",
                            parser.getStreamPosition());
            throw ReadError(message);
        }
        return true;
    }

private:
    std::vector<bool>& m_flags;
    int m_stack;
};

class BoolRleHandle : public UT_JSONHandleError
{
public:
    BoolRleHandle(RleVector& rle)
        : m_rle(rle),
          m_stack(0),
          m_count(0),
          m_countIsValid(false)
    {
    }

    /*virtual*/ bool jsonBool(UT_JSONParser& parser, bool value)
    {
        if (!m_countIsValid)
        {
            UT_String message;
            message.sprintf("Invalid RLE unknown count at byte 0x%04lx",
                            parser.getStreamPosition());
            throw ReadError(message);
        }
        m_rle.push_back(std::make_pair(m_count, value));
        m_countIsValid = false;
        return true;
    }

    /*virtual*/ bool jsonInt(UT_JSONParser& parser, int64 value)
    {
        if (m_countIsValid)
        {
            m_rle.push_back(std::make_pair(m_count, value));
            m_countIsValid = false;
            return true;
        }

        m_count = value;
        m_countIsValid = true;

        return true;
    }

    /*virtual*/ bool jsonBeginArray(UT_JSONParser& parser)
    {
        if (m_stack > 0)
        {
            UT_String message;
            message.sprintf("Unexpected [ at byte 0x%04lx",
                            parser.getStreamPosition());
            throw ReadError(message);
        }
        m_stack++;
        return true;
    }

    /*virtual*/ bool jsonEndArray(UT_JSONParser& parser)
    {
        m_stack--;
        if (m_stack < 0)
        {
            UT_String message;
            message.sprintf("Unexpected ] at byte 0x%04lx",
                            parser.getStreamPosition());
            throw ReadError(message);
        }
        return true;
    }

private:
    RleVector& m_rle;
    int m_stack;
    int m_count;
    bool m_countIsValid;
};

} // anonymous namespace

PrimitiveGroup::PrimitiveGroup(const Detail& detail)
    : detail(detail)
{
}

void PrimitiveGroup::load(UT_JSONParser& parser)
{
    parseBeginArray(parser);
    {
        parseBeginArray(parser);
        {
            parseArrayValueForKey(parser, "name", name);

            if (detail.fileVersion.major == 13)
            {
                UT_String type;
                parseArrayValueForKey(parser, "type", type);
                assert(type == "primitive");
            }
        }
        parseEndArray(parser);

        parseBeginArray(parser);
        {
            parseArrayKey(parser, "selection");
            parseBeginArray(parser);
            {
                if (detail.fileVersion.major == 13)
                {
                    parseArrayKey(parser, "defaults");
                    BGEO_CHECK(parser.skipNextObject());
                }

                parseArrayKey(parser, "unordered");

                parseBeginArray(parser);
                {
                    UT_WorkBuffer buffer;
                    UT_String type;
                    BGEO_CHECK(parser.parseValue(buffer));
                    type = buffer.buffer();

                    if (type == "i8")
                    {
                        BoolArrayHandle handle(ingroup);
                        BGEO_CHECK(parser.parseObject(handle));
                    }
                    else
                    {
                        BoolRleHandle handle(rleGroup);
                        BGEO_CHECK(parser.parseObject(handle));
                    }
                }
                parseEndArray(parser);
            }
            parseEndArray(parser);
        }
        parseEndArray(parser);
    }
    parseEndArray(parser);
}

void PrimitiveGroup::expandGroup(std::vector<int32_t>& indices) const
{
    indices.clear();

    if (!ingroup.empty())
    {
        for (int i = 0; i < ingroup.size(); ++i)
        {
            if (ingroup[i])
            {
                indices.push_back(i);
            }
        }
        return;
    }

    int index = 0;
    for (auto rlePair : rleGroup)
    {
        if (!rlePair.second)
        {
            index += rlePair.first;
            continue;
        }

        indices.reserve(indices.size() + rlePair.first);
        for (int i = 0; i < rlePair.first; ++i, ++index)
        {
            indices.push_back(index);
        }
    }
}

std::ostream& operator << (std::ostream& co, const PrimitiveGroup& group)
{
    co << group.name << " = ";

    if (!group.ingroup.empty())
    {
        for (auto value : group.ingroup)
        {
            co << value;
        }
    }

    if (!group.rleGroup.empty())
    {
        for (auto value : group.rleGroup)
        {
            co << value.first << "," << (value.second ? "true" : "false");
        }
    }

    return co;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
