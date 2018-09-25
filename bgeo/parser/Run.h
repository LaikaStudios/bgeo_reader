/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_RUN_H
#define BGEO_PARSER_RUN_H

#include <vector>

#include <UT/UT_StringArray.h>

#include "Primitive.h"
#include "Primitives.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class Run : public Primitive
{
public:
    Run(const Detail& detail);
    /*virtual*/ ~Run();

    /*virtual*/ PrimType getType() const
    {
        return RunType;
    }

    /*virtual*/ void loadType(UT_JSONParser& parser);
    /*virtual*/ void loadData(UT_JSONParser& parser);
    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    Primitive* runPrimitive;
    StringList varyingFields;
    std::vector<Primitive*> primitives;
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_RUN_H
