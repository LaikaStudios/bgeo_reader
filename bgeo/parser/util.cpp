/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

void parseMapKey(UT_JSONParser& parser, const char* key)
{
    UT_WorkBuffer keybuffer;
    int64 position = parser.getStreamPosition();
    BGEO_CHECK(parser.parseKey(keybuffer));

    if (keybuffer != key)
    {
        UT_String message;
        message.sprintf("Expecting key \"%s\" at byte 0x%08lx found \"%s\"",
                        key, position, keybuffer.buffer());
        throw ReadError(message.buffer());
    }
}

template <>
void parseMapValueForKey(UT_JSONParser& parser, const char* key, UT_String& value)
{
    parseMapKey(parser, key);
    UT_WorkBuffer buffer;
    BGEO_CHECK(parser.parseValue(buffer));
    value.harden(buffer.buffer());
}

template <>
void parseMapValueForKey(UT_JSONParser& parser, const char* key, std::string& value)
{
    parseMapKey(parser, key);
    UT_WorkBuffer buffer;
    BGEO_CHECK(parser.parseValue(buffer));
    value = buffer.toStdString();
}

void parseArrayKey(UT_JSONParser& parser, const char* key)
{
    UT_WorkBuffer keybuffer;
    int64 position = parser.getStreamPosition();
    BGEO_CHECK(parser.parseString(keybuffer));

    if (keybuffer != key)
    {
        UT_String message;
        message.sprintf("Expecting key \"%s\" at byte 0x%08lx found \"%s\"",
                        key, position, keybuffer.buffer());
        throw ReadError(message.buffer());
    }
}

template <>
void parseArrayValueForKey(UT_JSONParser& parser, const char* key, UT_String& value)
{
    parseArrayKey(parser, key);
    UT_WorkBuffer buffer;
    BGEO_CHECK(parser.parseValue(buffer));
    value.harden(buffer.buffer());
}

template <>
void parseArrayValueForKey(UT_JSONParser& parser, const char* key, std::string& value)
{
    parseArrayKey(parser, key);
    UT_WorkBuffer buffer;
    BGEO_CHECK(parser.parseValue(buffer));
    value = buffer.toStdString();
}

void parseSkipKeyAndValue(UT_JSONParser &parser)
{
    BGEO_CHECK(parser.skipNextObject());
    BGEO_CHECK(parser.skipNextObject());
}

void parseBeginMap(UT_JSONParser& parser)
{
    bool error = false;
    int64 position = parser.getStreamPosition();
    if (!parser.parseBeginMap(error))
    {
        UT_String message;
        message.sprintf("Expecting '{' at byte 0x%08lx", position);
        throw ReadError(message.buffer());
    }
    if (error)
    {
        throw ReadError(parser.getErrors());
    }
}

void parseEndMap(UT_JSONParser& parser)
{
    int64 position = parser.getStreamPosition();
    bool error = false;
    if (!parser.parseEndMap(error))
    {
        UT_String message;
        message.sprintf("Expecting '}' at byte 0x%08lx", position);
        throw ReadError(message.buffer());
    }
    if (error)
    {
        throw ReadError(parser.getErrors());
    }
}

void parseBeginArray(UT_JSONParser& parser)
{
    int64 position = parser.getStreamPosition();
    bool error = false;
    if (!parser.parseBeginArray(error))
    {
        UT_String message;
        message.sprintf("Expecting '[' at byte 0x%08lx", position);
        throw ReadError(message.buffer());
    }
    if (error)
    {
        throw ReadError(parser.getErrors());
    }
}

void parseEndArray(UT_JSONParser& parser)
{
    int64 position = parser.getStreamPosition();
    bool error = false;
    if (!parser.parseEndArray(error))
    {
        UT_String message;
        message.sprintf("Expecting ']' at byte 0x%08lx", position);
        throw ReadError(message.buffer());
    }
    if (error)
    {
        throw ReadError(parser.getErrors());
    }
}

} // namespace parser
} // namespace bgeo
} // namespace ika
