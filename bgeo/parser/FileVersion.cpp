/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "FileVersion.h"

#include <sstream>

#include "util.h"
#include "VersionError.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

FileVersion::FileVersion()
    : major(0),
      minor(-1),
      micro(-1),
      patch(-1)
{
}

std::string FileVersion::toString() const
{
    std::stringstream str;
    str << *this;
    return str.str();
}

std::ostream& operator << (std::ostream& co, const FileVersion& version)
{
    co << version.major;

    if (version.minor >= 0)
    {
        co << "." << version.minor;
    }

    if (version.micro >= 0)
    {
        co << "." << version.micro;
    }

    if (version.patch >= 0)
    {
        co << "." << version.patch;
    }

    return co;
}

/*static*/ void FileVersion::checkVersion(const FileVersion& version)
{
    if (version.major != 13 &&
        version.major != 14 &&
        version.major != 15 &&
        version.major != 16)
    {
        UT_String message("Unsupported file version: ");
        message += UT_String(version.toString());
        throw VersionError(message);
    }
}

void FileVersion::load(UT_JSONParser& parser)
{
    UT_String fileVersion;
    parseArrayValueForKey(parser, "fileversion", fileVersion);
    parse(fileVersion);
}

void FileVersion::parse(UT_String version)
{
    char period;
    std::stringstream versionStream(version.toStdString());
    versionStream >> major >> period >> minor >> period >>
            micro >> period >> patch;
}

} // namespace parser
} // namespace bgeo
} // namespace ika
