/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_INFO_H
#define BGEO_PARSER_INFO_H

#include <UT/UT_String.h>
#include <UT/UT_JSONParser.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class Info
{
public:
    Info();

    void load(UT_JSONParser& parser);

    UT_String software;
    UT_String date;
    UT_String hostname;
    UT_String artist;
    double bounds[6];
    UT_String primcountSummary;
    UT_String attributeSummary;
    UT_String volumeSummary;
    UT_String groupSummary;
    UT_String attributeRanges;

    friend std::ostream& operator << (std::ostream& co, const Info& info);
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_INFO_H
