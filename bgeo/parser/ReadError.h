/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_READ_ERROR_H
#define BGEO_PARSER_READ_ERROR_H

#include <stdexcept>

#include <UT/UT_StringArray.h>
#include <UT/UT_WorkBuffer.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class ReadError : public std::runtime_error
{
public:
    explicit ReadError(const char* message)
        : std::runtime_error("")
    {
        errorString.harden(message);
    }

    explicit ReadError(UT_StringArray errors)
        : std::runtime_error("")
    {
        errors.join(" ", errorString);
        errorString.insert(0, "Bgeo read error: ");
        errorString.hardenIfNeeded();
    }

    ~ReadError() noexcept(true)
    {
    }

    /*virtual*/ const char* what() const noexcept(true)
    {
        return errorString.buffer();
    }

private:
    UT_String errorString;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_READ_ERROR_H
