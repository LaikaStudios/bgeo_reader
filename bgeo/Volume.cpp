/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Volume.h"

#include "parser/Volume.h"

namespace ika
{
namespace bgeo
{

RTTI_DEFINE(Volume, Primitive)

Volume::Volume(const parser::Volume& volume)
    : m_volume(volume)
{
}

void Volume::getTranslate(double translate[3]) const
{
    m_volume.getTranslate(translate);
}

void Volume::getExtraTransform(double transform[16]) const
{
    m_volume.getMatrix(transform);
}

void Volume::getBoundingBox(double bound[6]) const
{
    m_volume.getBound(bound);
}

void Volume::getResolution(int32_t resolution[3]) const
{
    memcpy(resolution, m_volume.res, 3 * sizeof(int32_t));
}

int64_t Volume::getVoxelCount() const
{
    return m_volume.getNumVoxels();
}

void Volume::getVoxels(std::vector<float>& voxels) const
{
    parser::Volume::extractVoxelData(m_volume, voxels);
}

/*virtual*/ int32_t Volume::getVertexCount() const
{
    return 1;
}

} // namespace ika
} // namespace bgeo
