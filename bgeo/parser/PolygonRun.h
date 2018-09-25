/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_POLYGON_RUN_H
#define BGEO_PARSER_POLYGON_RUN_H

#include "Poly.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

// Derive from Poly to simplify use of PolygonRun by rest of the system (i.e.
// it acts just like a poly). Override the data loading process to translate
// the more compact PolygonRun representation to the Poly representation. This
// will take more resources since the Poly structures are larger, but is worth
// it to avoid implementing any other PolygonRun specific code.
//
class PolygonRun : public Poly
{
public:
    PolygonRun(const Detail& detail);
    PolygonRun(const PolygonRun& soup) = default;

    /*virtual*/ PolygonRun* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return PolygonRunType;
    }

    /*virtual*/ RunMode getRunMode() const
    {
        return MergeRunMode;
    }

    /*virtual*/ void loadData(UT_JSONParser &parser);

    /*virtual*/ void loadVaryingData(UT_JSONParser& parser, const StringList& fields);
    /*virtual*/ void loadUniformData(UT_JSONParser& parser);

    bool parseDataWithKey(UT_JSONParser& parser, const UT_String& key);

private:
    int64 startVertex;
    int64 numPrimitives;
    void setupFromPolygonRunInfo(
        const VertexArrayBuilder::VertexArray& numVertices);
    void setupFromPolygonRleInfo(
        const VertexArrayBuilder::VertexArray& numVerticesRle);
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_POLY_SOUP_H
