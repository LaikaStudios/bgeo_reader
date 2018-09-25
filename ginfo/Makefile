#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

APPNAME = ginfo

SOURCES = ginfo.cpp

CXXFLAGS += -I$(HFS)/toolkit/include

CXXFLAGS += -I..
LDFLAGS += -L../bgeo -lbgeo

INSTALL_DIR := ../install
BIN_DIR := $(INSTALL_DIR)/bin
install: ginfo
	install -d $(BIN_DIR)
	install -m 755 ginfo $(BIN_DIR)

include ../Makefile.inc
