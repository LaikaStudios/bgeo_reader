/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_UTIL_H
#define BGEO_PARSER_UTIL_H

#include <string>

#include <UT/UT_JSONParser.h>

#include "ReadError.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

#define BGEO_CHECK(statement) \
    if (!(statement)) \
    { \
        throw ReadError(parser.getErrors()); \
    }

void parseMapKey(UT_JSONParser& parser, const char* key);

template <typename T>
void parseMapValueForKey(UT_JSONParser& parser, const char* key, T& value)
{
    parseMapKey(parser, key);
    BGEO_CHECK(parser.parseValue(value));
}

template <>
void parseMapValueForKey(UT_JSONParser& parser, const char* key, UT_String& value);

template <>
void parseMapValueForKey(UT_JSONParser& parser, const char* key, std::string& value);

template <typename T>
void parseMapValueForKey(UT_JSONParser& parser, const char* key, T* data, int64 len)
{
    parseMapKey(parser, key);
    BGEO_CHECK(len == parser.parseUniformArray(data, len));
}

void parseArrayKey(UT_JSONParser& parser, const char* key);

template <typename T>
void parseArrayValueForKey(UT_JSONParser& parser, const char* key, T& value)
{
    parseArrayKey(parser, key);
    BGEO_CHECK(parser.parseValue(value));
}

template <>
void parseArrayValueForKey(UT_JSONParser& parser, const char* key, UT_String& value);

template <>
void parseArrayValueForKey(UT_JSONParser& parser, const char* key, std::string& value);

template <typename T>
void parseArrayValueForKey(UT_JSONParser& parser, const char* key, T* data, int64 len)
{
    parseArrayKey(parser, key);
    BGEO_CHECK(len == parser.parseUniformArray(data, len));
}

void parseSkipKeyAndValue(UT_JSONParser& parser);

void parseBeginMap(UT_JSONParser& parser);
void parseEndMap(UT_JSONParser& parser);
void parseBeginArray(UT_JSONParser& parser);
void parseEndArray(UT_JSONParser& parser);

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_UTIL_H
