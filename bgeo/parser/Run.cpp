/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Run.h"

#include <cassert>

#include <UT/UT_JSONHandle.h>

#include "util.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

Run::Run(const Detail& detail)
    : Primitive(detail),
      runPrimitive(0)
{
}

Run::~Run()
{
    // FIXME: use unique_ptr for these...
//    for (auto primitive : primitives)
//    {
//        delete primitive;
//    }

    delete runPrimitive;
}

namespace
{

class StringListHandle : public UT_JSONHandleError
{
public:
    StringListHandle(std::vector<std::string>& strings)
        : strings(strings)
    {
    }

    /*virtual*/ bool jsonString(UT_JSONParser &p, const char *value, int64 len)
    {
        strings.push_back(value);
        return true;
    }

    /*virtual*/ bool jsonBeginArray(UT_JSONParser &p)
    {
        return true;
    }

    /*virtual*/ bool jsonEndArray(UT_JSONParser &p)
    {
        return true;
    }

private:
    std::vector<std::string>& strings;
};

} // namespace

void Run::loadType(UT_JSONParser& parser)
{
    UT_String runTypeString;
    parseArrayValueForKey(parser, "runtype", runTypeString);
    runPrimitive = create(runTypeString, detail);
    assert(runPrimitive);

    parseArrayKey(parser, "varyingfields");
    StringListHandle stringsHandle(varyingFields);
    BGEO_CHECK(parser.parseObject(stringsHandle));

    parseArrayKey(parser, "uniformfields");
    runPrimitive->loadUniformData(parser);
}

void Run::loadData(UT_JSONParser &parser)
{
    assert(runPrimitive);
    if (runPrimitive->getRunMode() == Primitive::MergeRunMode)
    {
        // FIXME: this won't work if there are multiple runs in the same file.
        if (primitives.empty())
        {
            primitives.push_back(runPrimitive->clone());
        }
        primitives[0]->loadVaryingData(parser, varyingFields);
    }
    else if (runPrimitive->getRunMode() == Primitive::SplitRunMode)
    {
        for (auto it = parser.beginArray(); !it.atEnd(); ++it)
        {
            auto primitive = runPrimitive->clone();
            primitive->loadVaryingData(parser, varyingFields);
            primitives.push_back(primitive);
        }
    }
    else
    {
        std::cerr << "Warning: unsupported run type: "
                  << Primitive::toString(runPrimitive->getType()) << std::endl;
        BGEO_CHECK(parser.skipNextObject());
        primitives.push_back(runPrimitive->clone());
    }
}

std::ostream& Run::encode(std::ostream& co) const
{
    assert(runPrimitive);
    Primitive::encode(co);
    co << "\n" << "    runtype = {\n";
    runPrimitive->encode(co);
    co << "\n" << "    }\n";

    return co;
}

} // namespace parser
} // namespace ika
} // namespace bgeo
