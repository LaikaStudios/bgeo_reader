/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include "BgeoInOp.h"

#include <sstream>
#include <memory>
#include <iostream>

#include <FnAttribute/FnAttribute.h>
#include <FnAttribute/FnGroupBuilder.h>
#include <FnAttribute/FnDataBuilder.h>

#include <FnAsset/FnDefaultFileSequencePlugin.h>

namespace FnKat = Foundry::Katana;

#include "bgeo/Bgeo.h"
#include "bgeo/BgeoHeader.h"

#include "bgeo/Sphere.h"
#include "bgeo/PackedDisk.h"
#include "bgeo/PackedFragment.h"
#include "bgeo/PackedGeometry.h"
#include "bgeo/Part.h"
#include "bgeo/Poly.h"
#include "bgeo/Volume.h"

#include "BgeoCook.h"

namespace ika
{
namespace BgeoInOp
{

namespace
{

class BgeoInPrivateData : public FnKat::GeolibPrivateData
{
public:
    explicit BgeoInPrivateData(const std::string& fileName, bool checkVersion)
        : cookPtr(new BgeoCook(fileName, checkVersion))
    {
    }

    explicit BgeoInPrivateData(BgeoCook::BgeoPtr bgeo)
        : cookPtr(new BgeoCook(bgeo))
    {
    }

    BgeoInPrivateData(BgeoCook::BgeoPtr bgeo, BgeoCook::SplitterPtr splitter)
        : cookPtr(new BgeoCook(bgeo, splitter))
    {
    }

    BgeoInPrivateData(const BgeoInPrivateData& data)
        : cookPtr(data.cookPtr)
    {
    }

    BgeoInPrivateData* clone() const
    {
        return new BgeoInPrivateData(*this);
    }

    BgeoCookPtr cookPtr;
};

void createChild(FnKat::GeolibCookInterface& interface,
                 const char* type,
                 BgeoInPrivateData* privateData,
               FnAttribute::IntAttribute indexAttribute = FnAttribute::Attribute(),
               FnAttribute::StringAttribute nameAttribute = FnAttribute::Attribute(),
               FnAttribute::IntAttribute levelAttribute = FnAttribute::Attribute(),
               FnAttribute::IntAttribute splitAttribute = FnAttribute::Attribute())
{
    FnAttribute::GroupBuilder args;
    args.update(interface.getOpArg());

    if (levelAttribute.isValid())
    {
        args.set("_level", levelAttribute);
    }
    else
    {
        FnAttribute::IntAttribute level = interface.getOpArg("_level");
        args.set("_level", FnAttribute::IntAttribute(level.getValue() + 1));
    }

    args.set("_type", FnAttribute::StringAttribute(type));

    int index = 0;
    if (indexAttribute.isValid())
    {
        args.set("_index", indexAttribute);
        index = indexAttribute.getValue();
    }
    else
    {
        args.del("_index");
    }

    std::string name;
    if (nameAttribute.isValid())
    {
        name = nameAttribute.getValue();
    }
    else
    {
        std::stringstream stream;
        stream << "object_" << index;
        name = stream.str();

    }

    if (splitAttribute.isValid())
    {
        args.set("_split_index", splitAttribute);
    }

    interface.createChild(name, "", args.build(),
                          FnKat::GeolibCookInterface::ResetRootAuto,
                          privateData->clone(), BgeoInPrivateData::Delete);
}

void createChildren(FnKat::GeolibCookInterface& interface,
                    BgeoInPrivateData* privateData,
                    FnAttribute::IntAttribute levelAttribute,
                    FnAttribute::IntAttribute splitAttribute)
{
    assert(privateData);
    const BgeoCook::BgeoPtr bgeoPtr = privateData->cookPtr->getBgeo();

    // special case for primitive-less geo:
    // assume we want to represent points as pointcloud
    if (!bgeoPtr->getPrimitiveCount())
    {
        createChild(interface, "primitive", privateData,
                    FnAttribute::Attribute(), FnAttribute::Attribute(), levelAttribute);
        return;
    }

//    std::map<std::string, std::unique_ptr<BgeoInPrivateData>> geoMap;
    BgeoInPrivateData* childData = privateData;

    for (int i = 0; i < bgeoPtr->getPrimitiveCount(); ++i)
    {
//        auto primitive = bgeoPtr->getPrimitive(i);
//        auto fragment = primitive->cast<bgeo::PackedFragment>();
//        if (fragment)
//        {
//            auto key = fragment->getEmbeddedKey();
//            auto pos = geoMap.find(key);
//            if (pos == geoMap.end())
//            {
//                std::unique_ptr<BgeoInPrivateData> data(
//                         new BgeoInPrivateData(fragment->getEmbeddedGeo()));
//                auto result = geoMap.insert(std::make_pair(key, std::move(data)));
//                assert(result.second);
//                pos = result.first;
//            }
//            childData = pos->second.get();
//        }

        createChild(interface, "primitive", childData,
                    FnAttribute::IntAttribute(i),
                    FnAttribute::Attribute(),
                    levelAttribute,
                    splitAttribute);
    }

}

void createFragmentChildren(FnKat::GeolibCookInterface& interface,
                            const bgeo::PackedFragment& fragment)
{
    auto bgeo = fragment.getEmbeddedGeo();
    std::unique_ptr<BgeoInPrivateData> data(new BgeoInPrivateData(bgeo));

    auto primitive = bgeo->getPrimitive(0);
    auto poly = const_cast<bgeo::Poly*>(primitive->cast<bgeo::Poly>());
    assert(poly);

    auto nameAttr = bgeo->getPrimitiveAttributeByName(fragment.getNameAttribute().c_str());
    assert(nameAttr);

    std::vector<std::string> strings;
    nameAttr->getStrings(strings);
    auto pos = std::find(strings.begin(), strings.end(), fragment.getName());
    assert(pos != strings.end());

    poly->splitByPrimitiveString(fragment.getNameAttribute().c_str());

    auto levelAttribute = FnAttribute::IntAttribute(2);
    auto splitAttribute = FnAttribute::IntAttribute(static_cast<int>(pos - strings.begin()));

    createChildren(interface, data.get(), levelAttribute, splitAttribute);
}

void createEmbeddedChildren(FnKat::GeolibCookInterface& interface,
                            const bgeo::PackedGeometry& packed)
{
    std::unique_ptr<BgeoInPrivateData> data(new BgeoInPrivateData(packed.getEmbeddedGeo()));
    auto levelAttribute = FnAttribute::IntAttribute(2);
    createChildren(interface, data.get(), levelAttribute,
                   FnAttribute::Attribute());
}

void createDiskChild(FnKat::GeolibCookInterface& interface,
                     const bgeo::PackedDisk& disk)
{
    FnAttribute::GroupBuilder args;
    args.update(interface.getOpArg());
    args.set("fileName", FnAttribute::StringAttribute(disk.getFilename()));
    args.del("_level");
    args.del("_index");
    args.del("_type");

    interface.createChild("object_0", "BgeoIn", args.build(),
                          FnKat::GeolibCookInterface::ResetRootTrue);
}

} // anonymous namespace

/*static*/ void BgeoInOp::setup(FnKat::GeolibSetupInterface& interface)
{
    interface.setThreading(FnKat::GeolibSetupInterface::ThreadModeConcurrent);
}

/*static*/ void BgeoInOp::cook(FnKat::GeolibCookInterface& interface)
{
    if (interface.atRoot())
    {
        cookRoot(interface);
    }
    else
    {
        FnAttribute::IntAttribute level = interface.getOpArg("_level");
        if (level.getValue() == 0)
        {
            BgeoInPrivateData* data =
               reinterpret_cast<BgeoInPrivateData*>(interface.getPrivateData());
            assert(data);

            FnAttribute::GroupBuilder args;
            args.update(interface.getOpArg());
            args.set("_level", FnAttribute::IntAttribute(1));

            interface.createChild("geo", "", args.build(),
                                  FnKat::GeolibCookInterface::ResetRootAuto,
                                  data->clone(), BgeoInPrivateData::Delete);
        }
        else if (level.getValue() == 1)
        {
            cookGeo(interface);
        }
        else
        {
            BgeoInPrivateData* data =
               reinterpret_cast<BgeoInPrivateData*>(interface.getPrivateData());
            assert(data);

            auto bgeoPtr = data->cookPtr->getBgeo();

            FnAttribute::StringAttribute type = interface.getOpArg("_type");
            if (type.isValid() && type.getValue() == "faceset")
            {
                cookFaceset(interface, *bgeoPtr);
            }
            else
            {
                cookPrimitive(interface, *bgeoPtr);
            }
        }
    }
}

void BgeoInOp::flush()
{
    BgeoCook::flush();
}

static inline double max(double a, double b)
{
    return a > b ? a : b;
}

static inline double min(double a, double b)
{
    return a < b ? a : b;
}

static void computePointCloudBound(const bgeo::Bgeo& bgeo, double bound[6])
{
    // not a point cloud
    if (bgeo.getPrimitiveCount())
    {
        return;
    }

    std::vector<float> P;
    std::vector<float> width;

    bgeo.getP(P);

    auto widthAttribute = bgeo.getPointAttributeByName("width");
    if (widthAttribute)
    {
        widthAttribute->getData(width);
    }

    if (P.size() / 3 == width.size())
    {
        for (size_t i = 0; i < width.size(); ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                float radius = width[i] / 2;
                assert(j * 2 + 1 < 6);
                assert(i * 3 + j < P.size());
                bound[j * 2] = min(bound[j * 2], P[i * 3 + j] - radius);
                bound[j * 2 + 1] = max(bound[j * 2 + 1], P[i * 3 + j] + radius);
            }
        }
    }
}

/*static*/ void BgeoInOp::cookRoot(FnKat::GeolibCookInterface& interface)
{
    FnAttribute::StringAttribute fileNameAttribute =
            interface.getOpArg("fileName");

    bgeo::BgeoHeader header(fileNameAttribute.getValueCStr());

    FnAttribute::DoubleBuilder boundBuilder;
    boundBuilder.get().resize(6);
    header.getBoundingBox(boundBuilder.get().data());

    FnKat::IntAttribute checkVersionAttr = interface.getOpArg("checkVersion");
    bool checkVersion = !checkVersionAttr.isValid() || checkVersionAttr.getValue();
    BgeoInPrivateData* childData =
            new BgeoInPrivateData(fileNameAttribute.getValue(), checkVersion);

    FnKat::IntAttribute computeBoundAttr =
            interface.getOpArg("computePointCloudBound");
    if (computeBoundAttr.isValid() && computeBoundAttr.getValue())
    {
        auto bgeoPtr = childData->cookPtr->getBgeo();
        assert(bgeoPtr);
        computePointCloudBound(*bgeoPtr, boundBuilder.get().data());
    }

    interface.setAttr("bound", boundBuilder.build());

    FnKat::GroupBuilder gb;
    gb.set("software", FnKat::StringAttribute(header.getSoftware()));
    gb.set("date", FnKat::StringAttribute(header.getDate()));
    gb.set("hostname", FnKat::StringAttribute(header.getHostName()));
    gb.set("artist", FnKat::StringAttribute(header.getArtist()));
    interface.setAttr("bgeo", gb.build());

    FnAttribute::GroupBuilder args;
    args.update(interface.getOpArg());
    args.set("_level", FnAttribute::IntAttribute(0));

    interface.createChild("geo", "", args.build(),
                          FnKat::GeolibCookInterface::ResetRootAuto,
                          childData, BgeoInPrivateData::Delete);

    interface.setAttr("type", FnKat::StringAttribute("component"));
}

/*static*/ void BgeoInOp::cookGeo(FnKat::GeolibCookInterface& interface)
{
    BgeoInPrivateData* data =
       reinterpret_cast<BgeoInPrivateData*>(interface.getPrivateData());
    assert(data);

    createChildren(interface, data, FnAttribute::Attribute(),
                   FnAttribute::Attribute());
}

static void createFacesetChild(FnKat::GeolibCookInterface& interface,
                               const bgeo::Bgeo& bgeo)
{
    BgeoInPrivateData* data =
       reinterpret_cast<BgeoInPrivateData*>(interface.getPrivateData());
    assert(data);

    FnKat::IntAttribute makeFacesetsAttr = interface.getOpArg("makeFacesets");
    FnKat::IntAttribute indexAttr = interface.getOpArg("_index");

    // FIXME extend support to multiple primitives
    if (!indexAttr.isValid() || indexAttr.getValue() > 0)
    {
        return;
    }

    if (makeFacesetsAttr.isValid() && makeFacesetsAttr.getValue())
    {
        for (int i = 0; i < bgeo.getPrimitiveGroupCount(); ++i)
        {
            createChild(interface, "faceset", data, FnAttribute::IntAttribute(i),
                        FnAttribute::StringAttribute(bgeo.getPrimitiveGroupName(i)));
        }
    }
}

/*static*/ void BgeoInOp::cookPrimitive(FnKat::GeolibCookInterface& interface,
                                        const bgeo::Bgeo& bgeo)
{
    FnAttribute::IntAttribute indexAttribute = interface.getOpArg("_index");
    FnAttribute::IntAttribute reportEmptyAttribute = interface.getOpArg("reportEmpty");

    // don't do anything with empty geo
    if (!bgeo.getPointCount())
    {
        if (!reportEmptyAttribute.isValid() || reportEmptyAttribute.getValue())
        {
            reportError(interface, "Empty geometry", false);
        }
        return;
    }

    // special case assume pointcloud if no primitive given
    if (!indexAttribute.isValid())
    {
        cookPointCloud(interface, bgeo);
        return;
    }

    auto primPtr = bgeo.getPrimitive(indexAttribute.getValue());

    if (!primPtr)
    {
        reportError(interface, "Unsupported primitive type: Unknown");
        return;
    }

    if (primPtr->isType<bgeo::Sphere>())
    {
        cookSphere(interface, *primPtr->cast<bgeo::Sphere>());
    }
    else if (primPtr->isType<bgeo::PackedDisk>())
    {
        auto packed = primPtr->cast<bgeo::PackedDisk>();
        assert(packed);
        cookPackedGeometry(interface, bgeo, *packed);
        createDiskChild(interface, *packed);
    }
    else if (primPtr->isType<bgeo::PackedFragment>())
    {
        auto fragment = primPtr->cast<bgeo::PackedFragment>();
        assert(fragment);

        //std::cout << "embedded ptr: " << fragment->getEmbeddedGeo().get() << std::endl;

        cookPackedGeometry(interface, bgeo, *fragment);
        createFragmentChildren(interface, *fragment);
    }
    else if (primPtr->isType<bgeo::PackedGeometry>())
    {
        auto packed = primPtr->cast<bgeo::PackedGeometry>();
        assert(packed);
        cookPackedGeometry(interface, bgeo, *packed);
        createEmbeddedChildren(interface, *packed);
    }
    else if (primPtr->isType<bgeo::Part>())
    {
        cookParticleSystem(interface, bgeo, *primPtr->cast<bgeo::Part>());
    }
    else if (primPtr->isType<bgeo::Poly>())
    {
        auto poly = primPtr->cast<bgeo::Poly>();
        assert(poly);

        if (poly->isSplitting())
        {
            auto& splitter = const_cast<bgeo::Poly*>(poly)->getSplitter();
            FnAttribute::IntAttribute splitAttribute = interface.getOpArg("_split_index");
            if (splitAttribute.isValid())
            {
                // assume current split has already been set
                splitter.setCurrentSplit(splitAttribute.getValue());
            }
            cookPolyMesh(interface, bgeo, splitter);
        }
        else
        {
            cookPolyMesh(interface, bgeo, *poly);
        }
        createFacesetChild(interface, bgeo);
    }
    else if (primPtr->isType<bgeo::Volume>())
    {
        // NOTE: prevent crashing with large voxel counts due to katana bug
        // when count is > 2^32-1 = 4294967295
        // prman has a similar limit, though based on signed 32-bit int
        // which is 2^31-1 =  2147483647
        //  REMOVE ME if both limits are corrected.
        if (primPtr->cast<bgeo::Volume>()->getVoxelCount() > 2147483647)
        {
            reportError(interface, "Voxel count too high for prman.");
            return;
        }

        cookVolume(interface, *primPtr->cast<bgeo::Volume>());
    }
    else
    {
        std::string message = "Unsupported primitive type: ";
        message += primPtr->getType();
        reportError(interface, message);
    }
}

/*static*/ void BgeoInOp::reportError(FnKat::GeolibCookInterface& interface,
                                      const std::string& message, bool fatal)
{
    FnAttribute::StringAttribute fileName = interface.getOpArg("fileName");
    std::string fullMessage = "Error with file " +
            fileName.getValue() + ": " + message;
    if (fatal)
    {
        interface.setAttr("type", FnAttribute::StringAttribute("error"));
    }
    interface.setAttr("errorMessage", FnAttribute::StringAttribute(fullMessage));
    interface.stopChildTraversal();
}

} // namespace BgeoInOp
} // namespace ika
