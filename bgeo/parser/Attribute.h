/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_ATTRIBUTE_H
#define BGEO_PARSER_ATTRIBUTE_H

#include <UT/UT_JSONParser.h>

#include "ByteBuffer.h"
#include "NumericData.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class Attribute
{
public:
    Attribute(int64 elementCount);

    void load(UT_JSONParser& parser);

    friend std::ostream& operator << (std::ostream& co, const Attribute& attribute);

    int64 elementCount;

    UT_String scope;
    UT_String type;
    UT_String name;
    UT_String subtype;

    std::vector<std::string> strings;
    NumericData data;

private:
    void parseData(UT_JSONParser& parser);
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_ATTRIBUTE_H
