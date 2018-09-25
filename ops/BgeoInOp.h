/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef OPS_BGEO_IN_OP_H
#define OPS_BGEO_IN_OP_H

#include <FnGeolib/op/FnGeolibOp.h>

namespace ika
{

namespace bgeo
{
class Bgeo;
class Sphere;
class Volume;
class PackedGeometry;
class Part;
class Poly;
class PolySplitter;
}

namespace BgeoInOp
{

class BgeoInOp : public Foundry::Katana::GeolibOp
{
public:
    static void setup(Foundry::Katana::GeolibSetupInterface& interface);
    static void cook(Foundry::Katana::GeolibCookInterface& interface);
    static void flush();

    static void cookRoot(Foundry::Katana::GeolibCookInterface& interface);
    static void cookGeo(Foundry::Katana::GeolibCookInterface& interface);

    static void cookPrimitive(Foundry::Katana::GeolibCookInterface& interface,
                              const bgeo::Bgeo& bgeo);

    static void cookPackedGeometry(Foundry::Katana::GeolibCookInterface& interface,
                                   const bgeo::Bgeo& bgeo,
                                   const bgeo::PackedGeometry& packed);

    static void cookParticleSystem(Foundry::Katana::GeolibCookInterface& interface,
                                   const bgeo::Bgeo& bgeo,
                                   const bgeo::Part& part);

    static void cookPointCloud(Foundry::Katana::GeolibCookInterface& interface,
                               const bgeo::Bgeo& bgeo);

    static void cookPolyMesh(Foundry::Katana::GeolibCookInterface& interface,
                             const bgeo::Bgeo& bgeo, const bgeo::Poly& poly);
    static void cookPolyMesh(Foundry::Katana::GeolibCookInterface& interface,
                             const bgeo::Bgeo& bgeo,
                             const bgeo::PolySplitter& splitter);

    static void cookFaceset(Foundry::Katana::GeolibCookInterface& interface,
                            const bgeo::Bgeo& bgeo);

    static void cookSphere(Foundry::Katana::GeolibCookInterface& interface,
                           const bgeo::Sphere& sphere);

    static void cookVolume(Foundry::Katana::GeolibCookInterface& interface,
                           const bgeo::Volume& volume);

    static void reportError(Foundry::Katana::GeolibCookInterface& interface,
                            const std::string& message, bool fatal=true);
};

} // namespace BgeoInOp
} // namespace ika

#endif // OPS_BGEO_IN_OP_H
