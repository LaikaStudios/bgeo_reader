#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

APPNAME = test_libbgeo

SOURCES = \
	test_libbgeo.cpp \
	test_atmos_vol_lo.cpp \
	test_cube_multi_groups.cpp \
	test_cube_primgroup.cpp \
	test_empty.cpp \
	test_pack_fragments2.cpp \
	test_pack_fragments6.cpp \
	test_pack_fragments6_anim.cpp \
	test_pack_level2.cpp \
	test_pack1.cpp \
	test_pack1_xform.cpp \
	test_pack4_simple.cpp \
	test_pack4_xform.cpp \
	test_pack4_unshared.cpp \
	test_packed_disk.cpp \
	test_packed_disk_frames.cpp \
	test_points_noprim.cpp \
	test_points_partsys.cpp \
	test_psoup_cubes.cpp \
	test_psoup_simple.cpp \
	test_grid.cpp \
	test_grid_tetra.cpp \
	test_no_crash.cpp \
	test_simple_partanim.cpp \
	test_sphere.cpp \
	test_sphere_grid.cpp \
	test_splash_interior.cpp \
	test_vol.cpp \
	test_vol2_noshared.cpp \
	test_vol2_shared.cpp \
	test_vol5_noshared.cpp \
	test_vol5_shared.cpp \
	test_Attribute.cpp \
	test_Bgeo.cpp \
	test_BgeoHeader.cpp \
	test_H16_fragment_crash.cpp \
	test_NumericData.cpp \
	test_Poly.cpp \
	test_PolySplitter.cpp \
	test_Primitive.cpp

CXXFLAGS += -g -I$(HFS)/toolkit/include

CXXFLAGS += -I..
LDFLAGS += -L../bgeo -lbgeo

# support "make test"
LD_LIBRARY_PATH = $(HFS)/dsolib:../bgeo
export LD_LIBRARY_PATH

.PHONY: test
test: ./test_libbgeo
	./test_libbgeo

include ../Makefile.inc
