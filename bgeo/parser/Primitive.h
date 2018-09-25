/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PRIMITIVE_H
#define BGEO_PARSER_PRIMITIVE_H

#include <UT/UT_JSONParser.h>
#include <UT/UT_String.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class Detail;
class Primitive
{
public:
    enum PrimType
    {
        UnknownType = 0,
        PackedDiskType,
        PackedFragmentType,
        PackedGeometryType,
        PartType,
        PolygonRunType,
        PolyType,
        PolySoupType,
        RunType,
        SphereType,
        VolumeType
    };
    static const char* toString(PrimType type);
    static PrimType toPrimType(const UT_String& type);

    enum RunMode
    {
        NoRunMode = 0,
        MergeRunMode,
        SplitRunMode
    };

    static Primitive* create(const UT_String& type, const Detail& detail);

    Primitive(const Detail& detail);
    virtual ~Primitive();
    virtual Primitive* clone() const;

    friend std::ostream& operator << (std::ostream& co, const Primitive& primitive);

    virtual PrimType getType() const;

    // normal primitive parsing
    virtual void loadType(UT_JSONParser& parser);
    virtual void loadData(UT_JSONParser& parser);

    // for parsing within run context
    virtual RunMode getRunMode() const;
    typedef std::vector<std::string> StringList;
    virtual void loadVaryingData(UT_JSONParser& parser, const StringList& fields);
    virtual void loadUniformData(UT_JSONParser& parser);

    // for parsing shared data context
    virtual bool loadSharedData(UT_JSONParser& parser,
                                UT_String& dataType, UT_String& dataKey);
    virtual void loadSharedData(const Primitive& source,
                                const UT_String& dataType,
                                const UT_String& dataKey);

    virtual std::ostream& encode(std::ostream& co) const;

protected:
    const Detail& detail;
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_PRIMITIVE_H
