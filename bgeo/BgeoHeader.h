/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_BGEO_HEADER_H
#define BGEO_BGEO_HEADER_H

#include <memory>
#include <string>

namespace ika
{
namespace bgeo
{

class Info;

// Parse and contain the header information out of a bgeo file
class BgeoHeader
{
public:
    explicit BgeoHeader(const char* bgeoPath);
    ~BgeoHeader(); // dtor required for unique_ptr

    std::string getFileVersion() const;
    std::string getSoftware() const;
    std::string getDate() const;
    std::string getHostName() const;
    std::string getArtist() const;
    std::string getPrimCountSummary() const;
    std::string getAttributeSummary() const;
    std::string getVolumeSummary() const;
    std::string getGroupSummary() const;
    std::string getAttributeRanges() const;

    void getBoundingBox(double bound[6]) const;

private:
    // use pimpl here to avoid including UT classes
    class Impl;
    std::unique_ptr<Impl> m_pimpl;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_BGEO_HEADER_H
