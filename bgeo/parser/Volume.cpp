/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "Volume.h"

#include "util.h"
#include "Detail.h"
#include "Attribute.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

namespace
{

class UniformDataHandle : public UT_JSONHandleError
{
public:
    UniformDataHandle(Volume& volume)
        : volume(volume)
    {
    }

    /*virtual*/ bool jsonKey(UT_JSONParser& parser, const char *v, int64 len)
    {
        UT_String key(v);
        return volume.parseDataWithKey(parser, key);
    }

    /*virtual*/ bool jsonBeginMap(UT_JSONParser& parser)
    {
        return true;
    }

    /*virtual*/ bool jsonEndMap(UT_JSONParser& parser)
    {
        return true;
    }

private:
    Volume& volume;
};

} // anonymous namespace

Volume::Volume(const Detail& detail)
    : Primitive(detail)
{
    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
}

Volume::Volume(const Volume& volume)
    : Primitive(volume.detail),
      vertex(volume.vertex),
      transform(volume.transform),
      compressionTolerance(volume.compressionTolerance),
      sharedVoxelKey(volume.sharedVoxelKey)
{
    sharedVoxelKey.harden(); // harden here to prevent referencing stale data
                             // if the original volume goes away.
    res[0] = volume.res[0];
    res[1] = volume.res[1];
    res[2] = volume.res[2];
}

Volume* Volume::clone() const
{
    return new Volume(*this);
}

/*virtual*/ void Volume::loadData(UT_JSONParser &parser)
{
    UT_WorkBuffer buffer;
    UT_String key;

    for (auto geoit = parser.beginArray(); !geoit.atEnd(); ++geoit)
    {
        geoit.getLowerKey(buffer);
        key = buffer.buffer();
        if (!parseDataWithKey(parser, key))
        {
            UT_String message;
            message.sprintf("Invalid volume data: \"%s\"",
                            key.toStdString().c_str());
            throw ReadError(message.buffer());
        }
    }
}

void Volume::loadVaryingData(UT_JSONParser& parser,
                             const Primitive::StringList &fields)
{
    parseBeginArray(parser);
    {
        for (auto& field : fields)
        {
            if (!parseDataWithKey(parser, UT_String(field)))
            {
                UT_String message;
                message.sprintf("Invalid volume varying field: \"%s\"",
                                field.c_str());
                throw ReadError(message.buffer());
            }
        }
    }
    parseEndArray(parser);
}

void Volume::loadUniformData(UT_JSONParser& parser)
{
    UniformDataHandle uniformHandle(*this);
    BGEO_CHECK(parser.parseObject(uniformHandle));
}

/*virtual*/ bool Volume::loadSharedData(UT_JSONParser& parser,
                                        UT_String& dataType, UT_String& dataKey)
{
    if (dataType == "geo:voxels" && dataKey == sharedVoxelKey)
    {
        setupVoxels();
        BGEO_CHECK(voxels.loadData(parser));
        return true;
    }

    return false;
}

void Volume::loadSharedData(const Primitive& source,
                            const UT_String& dataType,
                            const UT_String& dataKey)
{
    if (dataType != "geo:voxels" || dataKey != sharedVoxelKey)
    {
        return;
    }

    if (source.getType() != getType())
    {
        return;
    }

    const Volume& sourceVolume = *static_cast<const Volume*>(&source);

    setupVoxels();
    voxels.copyData(sourceVolume.voxels);
}

std::ostream& operator << (std::ostream& co, const UT_VoxelArrayF& voxels)
{
    co << "      num tiles = " << voxels.numTiles() << "\n"
       << "      num voxels = " << voxels.numVoxels() << "\n"
       << "      memory usage = " << voxels.getMemoryUsage(true);
    return co;
}

/*virtual*/ std::ostream& Volume::encode(std::ostream& co) const
{
    Primitive::encode(co);
    co << "\n"
       << "    vertex = " << vertex << "\n"
       << "    transform = [" << transform << "]\n"
       << "    res = [" << res[0] << " " << res[1] << " " << res[2] << "]\n"
       << "    compression tolerance = " << compressionTolerance << "\n"
       << "    voxels = {\n"
       << voxels << "\n    }";

    if (getNumVoxels() < 500)
    {
        std::vector<fpreal32> voxeldata(getNumVoxels(), -1);
        flattenVoxelData(voxeldata.data(), voxeldata.size());

        co << "\n    voxel data = [ ";
        for (auto it = voxeldata.begin(); it != voxeldata.end(); ++it)
        {
            co << *it << " ";
        }
        co << "]";
    }

    return co;
}

void Volume::getTranslate(fpreal64 translate[3]) const
{
    int64 pointIndex = detail.getPointIndexForVertex(vertex);
    const Attribute* attribute = detail.getPointAttributeByName("P");
    assert(attribute);
    attribute->data.copyTo(translate, 3, 1, pointIndex, 1);
}

void Volume::getMatrix(double matrix[16]) const
{
    assert(sizeof(transform) == 16 * sizeof(double));
    memcpy(matrix, transform.data(), 16 * sizeof(double));
}

void Volume::getBound(double bound[6]) const
{
    bound[0] = -1;
    bound[1] = 1;
    bound[2] = -1;
    bound[3] = 1;
    bound[4] = -1;
    bound[5] = 1;
}

int64 Volume::getNumVoxels() const
{
    return voxels.numVoxels();
}

void Volume::flattenVoxelData(fpreal32* target, int64 targetSize) const
{
    assert(targetSize == voxels.numVoxels());
    voxels.flattenNoThread(target, voxels.getRes(0),
                           voxels.getRes(0)*voxels.getRes(1));
}

void Volume::extractVoxelData(const Volume& volume, std::vector<float>& voxels)
{
    voxels.resize(volume.getNumVoxels());
    int32_t ystride = volume.res[0];
    int32_t zstride = volume.res[0] * volume.res[1];
    volume.voxels.flattenNoThread(voxels.data(), ystride, zstride);
}

bool Volume::parseDataWithKey(UT_JSONParser& parser, const UT_String& key)
{
    if (key == "vertex")
    {
        BGEO_CHECK(parser.parseValue(vertex));
    }
    else if (key == "transform")
    {
        UT_Matrix3D m3;
        BGEO_CHECK(m3.load(parser));
        transform = m3;
    }
    else if (key == "res")
    {
        BGEO_CHECK(3 == parser.parseUniformArray(res, 3));
    }
    else if (key == "border")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else if (key == "compression")
    {
        parseBeginMap(parser);
        parseMapValueForKey(parser, "tolerance", compressionTolerance);
        parseEndMap(parser);
    }
    else if (key == "voxels")
    {
        setupVoxels();
        BGEO_CHECK(voxels.loadData(parser));
    }
    else if (key == "sharedvoxels")
    {
        UT_WorkBuffer buffer;
        BGEO_CHECK(parser.parseValue(buffer));
        sharedVoxelKey.harden(buffer.buffer());
    }
    else if (key == "visualization")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else if (key == "taperx")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else if (key == "tapery")
    {
        BGEO_CHECK(parser.skipNextObject());
    }
    else
    {
        return false;
    }

    return true;
}

void Volume::setupVoxels()
{
    voxels.size(res[0], res[1], res[2]);
    voxels.setCompressionTolerance(compressionTolerance);
}

} // namespace parser
} // namespace ika
} // namespace bgeo
