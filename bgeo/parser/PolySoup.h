/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_POLY_SOUP_H
#define BGEO_PARSER_POLY_SOUP_H

#include "Poly.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

// Derive from Poly to simplify use of PolySoup by rest of the system (i.e.
// it acts just like a poly). Override the data loading process to translate
// the more compact PolySoup representation to the Poly representation. This
// will take more resources since the Poly structures are larger, but is worth
// it to avoid implementing any other PolySoup specific code.
//
class PolySoup : public Poly
{
public:
    PolySoup(const Detail& detail);
    PolySoup(const PolySoup& soup) = default;

    /*virtual*/ PolySoup* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return PolySoupType;
    }

    /*virtual*/ RunMode getRunMode() const
    {
        return SplitRunMode;
    }

    /*virtual*/ void loadData(UT_JSONParser &parser);

    /*virtual*/ void loadVaryingData(UT_JSONParser& parser, const StringList& fields);
    /*virtual*/ void loadUniformData(UT_JSONParser& parser);

    bool parseDataWithKey(UT_JSONParser& parser, const UT_String& key);

private:
    void setupFromSoupInfo(const VertexArrayBuilder::VertexArray& soupSides,
                           const VertexArrayBuilder::VertexArray& soupCounts);
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_POLY_SOUP_H
