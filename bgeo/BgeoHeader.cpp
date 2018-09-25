/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "BgeoHeader.h"

#include "UT/UT_IStream.h"
#include "UT/UT_JSONParser.h"

#include "parser/ReadError.h"
#include "parser/FileVersion.h"
#include "parser/util.h"
#include "parser/Info.h"
#include "parser/compression.h"

namespace ika
{
namespace bgeo
{

class BgeoHeader::Impl
{
public:
    explicit Impl(const char* bgeoPath);
    ~Impl() = default;

    parser::FileVersion fileVersion;
    parser::Info info;

    void parseStream(UT_IStream& stream);
};

BgeoHeader::Impl::Impl(const char* bgeoPath)
{
    UT_IFStream stream(bgeoPath, UT_ISTREAM_BINARY);
    if (stream.isError())
    {
        UT_String message;
        message.sprintf("Unable to read file: %s", bgeoPath);
        throw parser::ReadError(message);
    }

    auto decompStream = ika::bgeo::parser::getDecompressionStream(bgeoPath, stream);
    if (decompStream)
    {
        parseStream(*decompStream);
    }
    else
    {
        parseStream(stream);
    }
}

void BgeoHeader::Impl::parseStream(UT_IStream& stream)
{
    UT_AutoJSONParser parserLoader(stream);
    UT_JSONParser parser = parserLoader.parser();

    parser::parseBeginArray(parser);
    {
        fileVersion.load(parser);

        if (fileVersion.major > 13)
        {
            parser::parseSkipKeyAndValue(parser); // skip hasindex
        }

        parser::parseSkipKeyAndValue(parser); // skip pointcount
        parser::parseSkipKeyAndValue(parser); // skip vertexcount
        parser::parseSkipKeyAndValue(parser); // skip primitivecount

        parser::parseArrayKey(parser, "info");
        info.load(parser);
    }
}

BgeoHeader::BgeoHeader(const char* bgeoPath)
    : m_pimpl(new Impl(bgeoPath))
{
}

BgeoHeader::~BgeoHeader() = default;

std::string BgeoHeader::getFileVersion() const
{
    return m_pimpl->fileVersion.toString();
}

std::string BgeoHeader::getSoftware() const
{
    return m_pimpl->info.software.toStdString();
}

std::string BgeoHeader::getDate() const
{
    return m_pimpl->info.date.toStdString();
}

std::string BgeoHeader::getHostName() const
{
    return m_pimpl->info.hostname.toStdString();
}

std::string BgeoHeader::getArtist() const
{
    return m_pimpl->info.artist.toStdString();
}

std::string BgeoHeader::getPrimCountSummary() const
{
    return m_pimpl->info.primcountSummary.toStdString();
}

std::string BgeoHeader::getAttributeSummary() const
{
    return m_pimpl->info.attributeSummary.toStdString();
}

std::string BgeoHeader::getVolumeSummary() const
{
    return m_pimpl->info.volumeSummary.toStdString();
}

std::string BgeoHeader::getGroupSummary() const
{
    return m_pimpl->info.groupSummary.toStdString();
}

std::string BgeoHeader::getAttributeRanges() const
{
    return m_pimpl->info.attributeRanges.toStdString();
}

void BgeoHeader::getBoundingBox(double bound[6]) const
{
    memcpy(bound, m_pimpl->info.bounds, 6 * sizeof(double));
}

} // namespace ika
} // namespace bgeo
