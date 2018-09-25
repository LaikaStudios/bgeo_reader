/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef OPS_BGEO_BGEO_COOK_H
#define OPS_BGEO_BGEO_COOK_H

#include <memory>
#include <string>

#include <hboost/thread/mutex.hpp>

#include "bgeo/Bgeo.h"
#include "bgeo/PolySplitter.h"

namespace ika
{
namespace BgeoInOp
{

class BgeoCook
{
public:
    static void flush();
    explicit BgeoCook(const std::string& fileName, bool checkVersion);

    typedef std::shared_ptr<bgeo::Bgeo> BgeoPtr;
    explicit BgeoCook(BgeoPtr bgeo);
    const BgeoPtr getBgeo() const;

    typedef std::shared_ptr<bgeo::PolySplitter> SplitterPtr;
    explicit BgeoCook(BgeoPtr bgeo, SplitterPtr splitter);
    const SplitterPtr getSplitter() const;

private:
    std::string m_fileName;
    bool m_checkVersion;

    mutable BgeoPtr m_bgeoPtr;
    mutable SplitterPtr m_splitterPtr;
    mutable hboost::mutex m_mutex;
};

typedef std::shared_ptr<BgeoCook> BgeoCookPtr;

} // namespace BgeoInOp
} // namespace ika

#endif // OPS_BGEO_BGEO_COOK_H
