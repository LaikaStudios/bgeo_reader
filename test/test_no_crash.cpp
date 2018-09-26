/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include "bgeo/Bgeo.h"
#include "bgeo/BgeoHeader.h"
#include "bgeo/Volume.h"

namespace ika
{
namespace bgeo
{
namespace test_no_crash
{

// regression tests to make sure loading these files don't crash.

// Houdini 13 ///////////////////

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_geo)
{
    Bgeo bgeo("geo/atmos_vol_lo.0054.geo");
}

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_bgeo)
{
    Bgeo bgeo("geo/atmos_vol_lo.0054.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_cube_multi_groups_geo)
{
    Bgeo bgeo("geo/cube_multi_groups.geo");
}

HBOOST_AUTO_TEST_CASE(test_cube_multi_groups_bgeo)
{
    Bgeo bgeo("geo/cube_multi_groups.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_cube_primgroup_geo)
{
    Bgeo bgeo("geo/cube_primgroup.geo");
}

HBOOST_AUTO_TEST_CASE(test_cube_primgroup_bgeo)
{
    Bgeo bgeo("geo/cube_primgroup.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_empty_geo)
{
    Bgeo bgeo("geo/empty.geo");
}

HBOOST_AUTO_TEST_CASE(test_empty_bgeo)
{
    Bgeo bgeo("geo/empty.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_grid_geo)
{
    Bgeo bgeo("geo/grid.geo");
}

HBOOST_AUTO_TEST_CASE(test_grid_bgeo)
{
    Bgeo bgeo("geo/grid.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_geo)
{
    Bgeo bgeo("geo/grid_tetra.geo");
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_bgeo)
{
    Bgeo bgeo("geo/grid_tetra.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_points_noprim_geo)
{
    Bgeo bgeo("geo/points_noprim.geo");
}

HBOOST_AUTO_TEST_CASE(test_points_noprim_bgeo)
{
    Bgeo bgeo("geo/points_noprim.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_geo)
{
    Bgeo bgeo("geo/simple_partanim.0017.geo");
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_bgeo)
{
    Bgeo bgeo("geo/simple_partanim.0017.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_sphere_geo)
{
    Bgeo bgeo("geo/sphere.geo");
}

HBOOST_AUTO_TEST_CASE(test_sphere_bgeo)
{
    Bgeo bgeo("geo/sphere.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_sphere_grid_geo)
{
    Bgeo bgeo("geo/sphere_grid.geo");
}

HBOOST_AUTO_TEST_CASE(test_sphere_grid_bgeo)
{
    Bgeo bgeo("geo/sphere_grid.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_splash_interior_geo)
{
    Bgeo bgeo("geo/splash_interior.geo");
}

HBOOST_AUTO_TEST_CASE(test_splash_interior_bgeo)
{
    Bgeo bgeo("geo/splash_interior.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_vol_geo)
{
    Bgeo bgeo("geo/vol.geo");
}

HBOOST_AUTO_TEST_CASE(test_vol_bgeo)
{
    Bgeo bgeo("geo/vol.bgeo");
}

HBOOST_AUTO_TEST_CASE(test_pyrosample_geo)
{
    const char* path = "geo/pyrosample.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("13.0.498", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_multivolume_geo)
{
    const char* path = "geo/multivolume.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("13.0.509", header.getFileVersion());
    Bgeo bgeo(path);
}

// Houdini 14 ///////////////////

HBOOST_AUTO_TEST_CASE(test_empty_14_geo)
{
    const char* path = "geo/empty_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_empty_14_bgeo)
{
    const char* path = "geo/empty_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_14_geo)
{
    const char* path = "geo/grid_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_14_bgeo)
{
    const char* path = "geo/grid_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_14_geo)
{
    const char* path = "geo/grid_tetra_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_14_bgeo)
{
    const char* path = "geo/grid_tetra_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_points_noprim_14_geo)
{
    const char* path = "geo/points_noprim_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_points_noprim_14_bgeo)
{
    const char* path = "geo/points_noprim_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_14_geo)
{
    const char* path = "geo/simple_partanim_14.0017.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_14_bgeo)
{
    const char* path = "geo/simple_partanim_14.0017.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_14_geo)
{
    const char* path = "geo/sphere_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_14_bgeo)
{
    const char* path = "geo/sphere_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_grid_14_geo)
{
    const char* path = "geo/sphere_grid_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_grid_14_bgeo)
{
    const char* path = "geo/sphere_grid_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_primgroup_14_geo)
{
    const char* path = "geo/cube_primgroup_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_primgroup_14_bgeo)
{
    const char* path = "geo/cube_primgroup_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_multi_groups_14_geo)
{
    const char* path = "geo/cube_multi_groups_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_multi_groups_14_bgeo)
{
    const char* path = "geo/cube_multi_groups_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_14_geo)
{
    const char* path = "geo/atmos_vol_lo_14.0054.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_14_bgeo)
{
    const char* path = "geo/atmos_vol_lo_14.0054.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_splash_interior_14_geo)
{
    const char* path = "geo/splash_interior_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_splash_interior_14_bgeo)
{
    const char* path = "geo/splash_interior_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_vol_14_geo)
{
    const char* path = "geo/vol_14.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_vol_14_bgeo)
{
    const char* path = "geo/vol_14.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("14.0.201.13", header.getFileVersion());
    Bgeo bgeo(path);
}

// Houdini 15 ///////////////////

HBOOST_AUTO_TEST_CASE(test_empty_15_geo)
{
    const char* path = "geo/empty_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_empty_15_bgeo)
{
    const char* path = "geo/empty_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_15_geo)
{
    const char* path = "geo/grid_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_15_bgeo)
{
    const char* path = "geo/grid_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_15_geo)
{
    const char* path = "geo/grid_tetra_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_grid_tetra_15_bgeo)
{
    const char* path = "geo/grid_tetra_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_points_noprim_15_geo)
{
    const char* path = "geo/points_noprim_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_points_noprim_15_bgeo)
{
    const char* path = "geo/points_noprim_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_15_geo)
{
    const char* path = "geo/simple_partanim_15.0017.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_15_bgeo)
{
    const char* path = "geo/simple_partanim_15.0017.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_15_geo)
{
    const char* path = "geo/sphere_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_15_bgeo)
{
    const char* path = "geo/sphere_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_grid_15_geo)
{
    const char* path = "geo/sphere_grid_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_sphere_grid_15_bgeo)
{
    const char* path = "geo/sphere_grid_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_primgroup_15_geo)
{
    const char* path = "geo/cube_primgroup_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_primgroup_15_bgeo)
{
    const char* path = "geo/cube_primgroup_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_multi_groups_15_geo)
{
    const char* path = "geo/cube_multi_groups_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_cube_multi_groups_15_bgeo)
{
    const char* path = "geo/cube_multi_groups_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_15_geo)
{
    const char* path = "geo/atmos_vol_lo_15.0054.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_15_bgeo)
{
    const char* path = "geo/atmos_vol_lo_15.0054.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_splash_interior_15_geo)
{
    const char* path = "geo/splash_interior_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_splash_interior_15_bgeo)
{
    const char* path = "geo/splash_interior_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_vol_15_geo)
{
    const char* path = "geo/vol_15.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_vol_15_bgeo)
{
    const char* path = "geo/vol_15.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.0.244.16", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_pryo_crash_lo_geo)
{
    const char* path = "geo/pyro_crash_lo.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("15.5.482", header.getFileVersion());
    Bgeo bgeo(path);

    assert(bgeo.getPrimitiveCount() >= 5);
    auto prim5 = bgeo.getPrimitive(5);
    auto vol5 = prim5->cast<Volume>();
    assert(vol5);
    double translate[3];
    vol5->getTranslate(translate);
    HBOOST_CHECK_EQUAL(0.0, translate[0]);
    HBOOST_CHECK_EQUAL(10.3458375930786133, translate[1]);
    HBOOST_CHECK_EQUAL(0.0, translate[2]);
}

// Houdini 16 ///////////////////

namespace
{

const char* version_string_16 = "16.0.450";
const char* version_string_16_5 = "16.5.268";
const char* version_string_15_5 = "15.5.565";

} // namespace anonymous

#define TEST_NO_CRASH(test_name, version) \
    HBOOST_AUTO_TEST_CASE(test_##test_name##_##version##_bgeo) \
    { \
        const char* path = "geo/" #test_name "_" #version ".bgeo"; \
        BgeoHeader header(path); \
        HBOOST_CHECK_EQUAL(version_string_##version, header.getFileVersion()); \
        Bgeo bgeo(path); \
    } \
    HBOOST_AUTO_TEST_CASE(test_##test_name##_##version##_geo) \
    { \
        const char* path = "geo/" #test_name "_" #version ".geo"; \
        BgeoHeader header(path); \
        HBOOST_CHECK_EQUAL(version_string_##version, header.getFileVersion()); \
        Bgeo bgeo(path); \
    }


TEST_NO_CRASH(empty, 16)
TEST_NO_CRASH(grid, 16)
TEST_NO_CRASH(grid_tetra, 16)
TEST_NO_CRASH(points_noprim, 16)

HBOOST_AUTO_TEST_CASE(test_simple_partanim_16_geo)
{
    const char* path = "geo/simple_partanim_16.0017.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("16.0.450", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_simple_partanim_16_bgeo)
{
    const char* path = "geo/simple_partanim_16.0017.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("16.0.450", header.getFileVersion());
    Bgeo bgeo(path);
}

TEST_NO_CRASH(sphere, 16)
TEST_NO_CRASH(sphere_grid, 16)
TEST_NO_CRASH(cube_primgroup, 16)
TEST_NO_CRASH(cube_multi_groups, 16)

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_16_geo)
{
    const char* path = "geo/atmos_vol_lo_16.0054.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("16.0.450", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_atmos_vol_lo_16_bgeo)
{
    const char* path = "geo/atmos_vol_lo_16.0054.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("16.0.450", header.getFileVersion());
    Bgeo bgeo(path);
}

TEST_NO_CRASH(splash_interior, 16)
TEST_NO_CRASH(vol, 16)

TEST_NO_CRASH(pack1, 16)
TEST_NO_CRASH(pack1_xform, 16)
TEST_NO_CRASH(pack4_simple, 16)
TEST_NO_CRASH(pack4_unshared, 16)
TEST_NO_CRASH(pack4_xform, 16)
TEST_NO_CRASH(pack_fragments2, 16)
TEST_NO_CRASH(pack_fragments6, 16)

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_16_bgeo)
{
    const char* path = "geo/pack_fragments6_anim_16.0020.bgeo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("16.0.450", header.getFileVersion());
    Bgeo bgeo(path);
}

HBOOST_AUTO_TEST_CASE(test_pack_fragments6_anim_16_geo)
{
    const char* path = "geo/pack_fragments6_anim_16.0020.geo";
    BgeoHeader header(path);
    HBOOST_CHECK_EQUAL("16.0.450", header.getFileVersion());
    Bgeo bgeo(path);
}

TEST_NO_CRASH(pack_level2, 16)
TEST_NO_CRASH(packed_disk, 16)
TEST_NO_CRASH(packed_disk_frames, 16)

TEST_NO_CRASH(packed_points_simple, 15_5)

//TEST_NO_CRASH(points_noprim, 16)

// Houdini 16.5 ///////////////////

TEST_NO_CRASH(empty, 16_5)
TEST_NO_CRASH(grid, 16_5)
TEST_NO_CRASH(grid_tetra, 16_5)
TEST_NO_CRASH(points_noprim, 16_5)
TEST_NO_CRASH(simple_partanim, 16_5)
TEST_NO_CRASH(sphere, 16_5)
TEST_NO_CRASH(sphere_grid, 16_5)
TEST_NO_CRASH(cube_primgroup, 16_5)
TEST_NO_CRASH(cube_multi_groups, 16_5)
TEST_NO_CRASH(atmos_vol_lo, 16_5)
TEST_NO_CRASH(splash_interior, 16_5)
TEST_NO_CRASH(vol, 16_5)
TEST_NO_CRASH(pack1, 16_5)
TEST_NO_CRASH(pack1_xform, 16_5)
TEST_NO_CRASH(pack4_simple, 16_5)
TEST_NO_CRASH(pack4_unshared, 16_5)
TEST_NO_CRASH(pack4_xform, 16_5)
TEST_NO_CRASH(pack_fragments2, 16_5)
TEST_NO_CRASH(pack_fragments6, 16_5)
TEST_NO_CRASH(pack_fragments6_anim, 16_5)
TEST_NO_CRASH(pack_level2, 16_5)
TEST_NO_CRASH(packed_disk, 16_5)
TEST_NO_CRASH(packed_disk_frames, 16_5)
TEST_NO_CRASH(packed_points_simple, 16_5)

} // namespace test_no_crash
} // namespace bgeo
} // namespace ika
