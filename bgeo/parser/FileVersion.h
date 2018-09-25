/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_FILE_VERSION_H
#define BGEO_PARSER_FILE_VERSION_H

#include <UT/UT_JSONParser.h>
#include <UT/UT_String.h>
#undef major
#undef minor

namespace ika
{
namespace bgeo
{
namespace parser
{

class FileVersion
{
public:
    FileVersion();

    std::string toString() const;
    friend std::ostream& operator << (std::ostream& co,
                                      const FileVersion& version);

    void load(UT_JSONParser& parser);
    void parse(UT_String version);

    int major;
    int minor;
    int micro;
    int patch;

    static void checkVersion(const FileVersion& version);
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_FILE_VERSION_H
