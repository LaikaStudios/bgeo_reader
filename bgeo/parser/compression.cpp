/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "compression.h"
#include "ReadError.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

std::unique_ptr<UT_IStream>
getDecompressionStream(const std::string& filename, UT_IStream& stream)
{
    auto extpos = filename.find_last_of('.');
    if (extpos == std::string::npos)
    {
        return nullptr;
    }

    std::string extension = filename.substr(extpos + 1);
    if (extension == "sc")
    {
#if HVERSION_MAJOR >= 15
        return std::unique_ptr<UT_IStream>(stream.getSCStream());
#else // HVERSION_MAJOR < 15
        UT_String message;
        message.sprintf("blosc compressed files are not supported: %s",
                        filename.c_str());
        throw parser::ReadError(message);
#endif // HVERSION_MAJOR > 15
    }
    else if (extension == "gz")
    {
        return std::unique_ptr<UT_IStream>(stream.getGzipStream());
    }

    return nullptr;
}


} // namespace parser
} // namespace bgeo
} // namespace ika
