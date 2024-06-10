TARGET = cli_pageinspect

top_build_dir = .

include src/objlist.mk

.PHONY: install uninstall all clean

all:
	cd src; \
		$(MAKE) -f Makefile
	cd src/utils; \
		$(MAKE) -f Makefile
#	cd src/relpages; \
#		$(MAKE) -f Makefile
#	cd src/UI; \
#		$(MAKE) -f Makefile

	$(CC) -o $(TARGET) $(OBJS) -lncursesw

clean:
	cd src; \
		$(MAKE) clean -f Makefile
	cd src/relpages; \
		$(MAKE) clean -f Makefile
	cd src/utils; \
		$(MAKE) clean -f Makefile
	cd src/UI; \
		$(MAKE) clean -f Makefile