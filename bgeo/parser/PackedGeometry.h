/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PACKED_GEOMETRY_H
#define BGEO_PARSER_PACKED_GEOMETRY_H

#include <vector>
#include <memory>

#include <UT/UT_Matrix3.h>

#include "Primitive.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class PackedGeometry : public Primitive
{
public:
    explicit PackedGeometry(const Detail& detail);
    PackedGeometry(const PackedGeometry& packed);

    /*virtual*/ PackedGeometry* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return PackedGeometryType;
    }

    /*virtual*/ RunMode getRunMode() const
    {
        return SplitRunMode;
    }

    /*virtual*/ void loadData(UT_JSONParser &parser);

    /*virtual*/ void loadVaryingData(UT_JSONParser& parser, const StringList& fields);
    /*virtual*/ void loadUniformData(UT_JSONParser& parser);

    /*virtual*/ bool loadSharedData(UT_JSONParser& parser,
                                    UT_String& dataType, UT_String& dataKey);
    /*virtual*/ void loadSharedData(const Primitive& source,
                                    const UT_String& dataType,
                                    const UT_String& dataKey);

    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    bool hasBounds() const;
    void getBounds(double bounds[6]) const;
    void getPivot(double pivot[3]) const;
    void getTranslate(fpreal64 translate[3]) const;
    void getTransform(double matrix[3]) const;

    const std::shared_ptr<Detail> getEmbeddedGeo() const;
    UT_String getEmbeddedKey() const;

    virtual bool parseDataWithKey(UT_JSONParser& parser, const UT_String& key);
    virtual bool parseParametersWithKey(UT_JSONParser& parser, const UT_String& key);

private:
    bool boundsValid;
    double bounds[6];
    UT_String embeddedKey;
    double pivot[3];
    UT_Matrix4D transform;
    int32 vertex;

    std::shared_ptr<Detail> embeddedGeo;
};

} // namespace parser
} // namespace bgeo
} // namespace ika

#endif // BGEO_PARSER_PACKED_GEOMETRY_H
