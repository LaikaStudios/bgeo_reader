/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_VOLUME_H
#define BGEO_PARSER_VOLUME_H

#include "Primitive.h"
#include <UT/UT_VoxelArray.h>
#include <UT/UT_Matrix3.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class Volume : public Primitive
{
public:
    Volume(const Detail& detail);
    Volume(const Volume& volume);

    /*virtual*/ Volume* clone() const;

    /*virtual*/ PrimType getType() const
    {
        return VolumeType;
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

    void getTranslate(fpreal64 translate[3]) const;
    void getMatrix(fpreal64 matrix[16]) const;
    void getBound(double bound[6]) const;

    int64 getNumVoxels() const;
    void flattenVoxelData(fpreal32* target, int64 targetSize) const;

    int32 vertex;
    UT_Matrix4D transform;

    int32 res[3];
    fpreal compressionTolerance;
    UT_VoxelArrayF voxels; // FIXME: use a shared voxels reference for multiple volumes
    UT_String sharedVoxelKey;

    static void extractVoxelData(const Volume& volume, std::vector<float>& voxels);

    // private:
    bool parseDataWithKey(UT_JSONParser& parser, const UT_String& key);
    void setupVoxels();
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_VOLUME_H
