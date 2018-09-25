/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "BgeoCook.h"

#include <iostream>

#include <hboost/timer.hpp>
#include <hboost/thread/lock_guard.hpp>

#include <FnLogging/FnLogging.h>

namespace ika
{
namespace BgeoInOp
{

FnLogSetup("BgeoCook")

namespace
{
    hboost::mutex bgeo_map_mutex;
    std::map<std::string, BgeoCook::BgeoPtr> bgeo_map;

    BgeoCook::BgeoPtr getBgeoFromMap(const std::string& filename, bool checkVersion)
    {
        hboost::lock_guard<hboost::mutex> lock(bgeo_map_mutex);

        auto search = bgeo_map.find(filename);
        if (search != bgeo_map.end())
        {
            return search->second;
        }

        FnLogInfo("Bgeo path: " << filename);
        hboost::timer timer;
        auto bgeo = std::make_shared<bgeo::Bgeo>(filename.c_str(), checkVersion);
        bgeo_map.emplace(filename, bgeo);
        FnLogInfo("Bgeo read time: " << timer.elapsed() << "s");
        std::cerr << "Bgeo read time " << timer.elapsed() << "s" << std::endl;

        return bgeo;
    }
}

void BgeoCook::flush()
{
    hboost::lock_guard<hboost::mutex> lock(bgeo_map_mutex);
    bgeo_map.clear();
}

BgeoCook::BgeoCook(const std::string& fileName, bool checkVersion)
    : m_fileName(fileName),
      m_checkVersion(checkVersion)
{
}

BgeoCook::BgeoCook(BgeoPtr bgeo)
    : m_bgeoPtr(bgeo)
{
}

BgeoCook::BgeoCook(BgeoCook::BgeoPtr bgeo, BgeoCook::SplitterPtr splitter)
    : m_bgeoPtr(bgeo),
      m_splitterPtr(splitter)
{
}

const BgeoCook::BgeoPtr BgeoCook::getBgeo() const
{
    if (!m_bgeoPtr)
    {
        m_bgeoPtr = getBgeoFromMap(m_fileName, m_checkVersion);
    }

    return m_bgeoPtr;
}

const BgeoCook::SplitterPtr BgeoCook::getSplitter() const
{
    return m_splitterPtr;
}

} // namespace BgeoInOp
} // namespace ika
