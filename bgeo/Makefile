#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

SOURCES = \
	Attribute.cpp \
	Bgeo.cpp \
	BgeoHeader.cpp \
	PackedDisk.cpp \
	PackedFragment.cpp \
	PackedGeometry.cpp \
	Part.cpp \
	Primitive.cpp \
	PrimitiveFactory.cpp \
	Poly.cpp \
	PolySplitter.cpp \
	Sphere.cpp \
	Volume.cpp \
	parser/Attribute.cpp \
	parser/ByteBuffer.cpp \
	parser/FileVersion.cpp \
	parser/Info.cpp \
	parser/Detail.cpp \
	parser/NumericData.cpp \
	parser/PackedDisk.cpp \
	parser/PackedFragment.cpp \
	parser/PackedGeometry.cpp \
	parser/Part.cpp \
	parser/PolygonRun.cpp \
	parser/Poly.cpp \
	parser/PolySoup.cpp \
	parser/Primitive.cpp \
	parser/Primitives.cpp \
	parser/PrimitiveGroup.cpp \
	parser/Run.cpp \
	parser/Sphere.cpp \
	parser/storage.cpp \
	parser/VertexArrayBuilder.cpp \
	parser/VertexMap.cpp \
	parser/Volume.cpp \
	parser/compression.cpp \
	parser/util.cpp

DSONAME = libbgeo.so

include ../Makefile.inc

INSTALL_DIR := ../install
LIB_DIR := $(INSTALL_DIR)/lib
install: libbgeo.so
	install -d $(LIB_DIR)
	install -m 644 libbgeo.so $(LIB_DIR)
