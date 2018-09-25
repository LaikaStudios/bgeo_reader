#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

.PHONY: all install clean test

.PHONY: default
default: all ;

include Makefile.inc

all:
	$(MAKE) --directory=bgeo
	$(MAKE) --directory=ops
	$(MAKE) --directory=check_bgeo
	$(MAKE) --directory=ginfo

install: all
	$(MAKE) --directory=bgeo $@
	$(MAKE) --directory=ops $@
	$(MAKE) --directory=check_bgeo $@
	$(MAKE) --directory=ginfo $@

clean:
	$(MAKE) --directory=bgeo $@
	$(MAKE) --directory=ops $@
	$(MAKE) --directory=check_bgeo $@
	$(MAKE) --directory=ginfo $@

#test: all
#	$(MAKE) --directory=test $@
