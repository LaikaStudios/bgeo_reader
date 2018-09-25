#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

ifndef HFS
  $(error "HFS (path to Houdini install) is required environment variable")
endif

ifeq (, $(shell which sesitag))
  $(error "Houdini sesitag program is required. Make sure Houdini environment is setup (i.e. using houdini_setup)")
endif

ifndef KATANA_LOCATION
  $(error "KATANA_LOCATION (path to Katana install) is required environment variable")
endif

CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

include $(HFS)/toolkit/makefiles/Makefile.gnu
