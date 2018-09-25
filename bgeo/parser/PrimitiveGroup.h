/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PRIMITIVE_GROUP_H
#define BGEO_PARSER_PRIMITIVE_GROUP_H

#include <UT/UT_JSONParser.h>
#include <UT/UT_String.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

typedef std::vector<std::pair<int, bool>> RleVector;

class Detail;
class PrimitiveGroup
{
public:
    PrimitiveGroup(const Detail& detail);

    void load(UT_JSONParser& parser);

    UT_String name;

    void expandGroup(std::vector<int32_t>& indices) const;

    friend std::ostream& operator << (std::ostream& co,
                                      const PrimitiveGroup& group);

private:
    const Detail& detail;
    std::vector<bool> ingroup;
    RleVector rleGroup;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_PRIMITIVE_GROUP_H
