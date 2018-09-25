#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

DSONAME = BgeoIn.so

SOURCES = \
      BgeoCook.cpp \
      BgeoInOp.cpp \
      build.cpp \
      cookFaceset.cpp \
      cookPackedGeometry.cpp \
      cookPointCloud.cpp \
      cookPolyMesh.cpp \
      cookSphere.cpp \
      cookVolume.cpp \
      plugin.cpp


ifndef KATANA_LOCATION
  $(error KATANA_LOCATION is required environment variable)
endif

KATANA_SRC_DIR = $(KATANA_LOCATION)/plugin_apis/src

PLUGIN_API_SOURCES = $(shell cd $(KATANA_SRC_DIR); find FnAttribute -name \*.cpp)
PLUGIN_API_SOURCES += $(shell cd $(KATANA_SRC_DIR); find FnGeolib/op -name \*.cpp)
PLUGIN_API_SOURCES += $(shell cd $(KATANA_SRC_DIR); find FnGeolib/util -name \*.cpp)
PLUGIN_API_SOURCES += $(shell cd $(KATANA_SRC_DIR); find FnPluginManager -name \*.cpp)
PLUGIN_API_SOURCES += $(shell cd $(KATANA_SRC_DIR); find FnLogging/client -name \*.cpp)
PLUGIN_API_SOURCES += FnPluginSystem/FnPlugin.cpp

SOURCES += $(addprefix plugin_api/,$(PLUGIN_API_SOURCES))

plugin_api/%.cpp: $(KATANA_SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	cp $< $@

CXXFLAGS += -I.. -I$(KATANA_LOCATION)/plugin_apis/include
LDFLAGS += -L../bgeo -lbgeo -L$(HFS)/dsolib -lHoudiniUT

include ../Makefile.inc

INSTALL_DIR := ../install
OPS_DIR := $(INSTALL_DIR)/Ops
PLUGINS_DIR := $(INSTALL_DIR)/Plugins
install: BgeoIn.so
	install -d $(OPS_DIR)
	install -m 644 BgeoIn.so $(OPS_DIR)
	install -d $(PLUGINS_DIR)
	install -m 644 BgeoInHelp.txt $(PLUGINS_DIR)
	install -m 644 RegisterBgeoInNode.py $(PLUGINS_DIR)
