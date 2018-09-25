/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Info.h"

#include "util.h"

#include "UT/UT_JSONHandle.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

Info::Info()
{
}

void parseMapValue(UT_JSONParser& parser, UT_String& value)
{
    UT_WorkBuffer buffer;
    BGEO_CHECK(parser.parseString(buffer));
    value.harden(buffer.buffer());
}

template <typename T>
void parseMapValue(UT_JSONParser& parser, T* data, int64 len)
{
    BGEO_CHECK(len == parser.parseUniformArray(data, len));
}

void Info::load(UT_JSONParser& parser)
{
    UT_WorkBuffer buffer;
    UT_String key;
    for (auto it = parser.beginMap(); !it.atEnd(); ++it)
    {
        it.getLowerKey(buffer);
        key = buffer.buffer();

        if (key == "software")
        {
            parseMapValue(parser, software);
        }
        else if (key == "date")
        {
            parseMapValue(parser, date);
        }
        else if (key == "hostname")
        {
            parseMapValue(parser, hostname);
        }
        else if (key == "artist")
        {
            parseMapValue(parser, artist);
        }
        else if (key == "bounds")
        {
            parseMapValue(parser, bounds, 6);
        }
        else if (key == "primcount_summary")
        {
            parseMapValue(parser, primcountSummary);
        }
        else if (key == "attribute_summary")
        {
            parseMapValue(parser, attributeSummary);
        }
        else if (key == "volume_summary")
        {
            parseMapValue(parser, volumeSummary);
        }
        else if (key == "group_summary")
        {
            parseMapValue(parser, groupSummary);
        }
        else if (key == "attribute_ranges")
        {
            parseMapValue(parser, attributeRanges);
        }
        else if (key == "time")
        {
            BGEO_CHECK(parser.skipNextObject());
        }
        else if (key == "timetocook")
        {
            BGEO_CHECK(parser.skipNextObject());
        }
        else
        {
            std::cerr << "Warning: Unknown info member: " << key << std::endl;
            BGEO_CHECK(parser.skipNextObject());
        }

    }
}

std::ostream& operator << (std::ostream& co, const Info& info)
{
    co << "software  = " << info.software << "\n"
       << "date = " << info.date << "\n"
       << "hostname = " << info.hostname << "\n"
       << "artist = " << info.artist << "\n"
       << "bounds = ["
           << info.bounds[0] << " "
           << info.bounds[1] << " "
           << info.bounds[2] << " "
           << info.bounds[3] << " "
           << info.bounds[4] << " "
           << info.bounds[5] << "]"
           << "\n"
       << "primcount_summary = " << info.primcountSummary << "\n"
       << "attribute_summary = " << info.attributeSummary << "\n"
       << "volume_summary = " << info.volumeSummary << "\n"
       << "group_summary = " << info.groupSummary;

    if (info.attributeRanges.length() > 0)
    {
        co << "\nattribute_ranges = " << info.attributeRanges;
    }

    return co;
}

} // namespace parser
} // namespace bgeo
} // namespace ika

