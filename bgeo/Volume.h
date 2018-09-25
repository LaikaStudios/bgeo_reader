/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_VOLUME_H
#define BGEO_VOLUME_H

#include <vector>

#include "Primitive.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Volume;
} // namespace parser

class Volume : public Primitive
{
    RTTI_DECLARE(Volume, Primitive)

public:
    Volume(const parser::Volume& volume);

    void getTranslate(double translate [3]) const;
    void getExtraTransform(double transform[16]) const;
    void getBoundingBox(double bound[6]) const;

    void getResolution(int32_t resolution[3]) const;

    int64_t getVoxelCount() const;
    void getVoxels(std::vector<float>& voxels) const;

    /*virtual*/ int32_t getVertexCount() const;

private:
    const parser::Volume& m_volume;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_VOLUME_H
