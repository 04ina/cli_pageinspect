TARGET = cli_pageinspect

OBJS = src/*.o \
	src/relpages/*.o \
	src/UI/*.o \
	src/utils/*.o

.PHONY: install uninstall all clean

all:
	cd src; \
		$(MAKE) -f Makefile
	cd src/relpages; \
		$(MAKE) -f Makefile
	cd src/utils; \
		$(MAKE) -f Makefile
	cd src/UI; \
		$(MAKE) -f Makefile

	$(CC) -o $(TARGET) $(OBJS)

clean:
	cd src; \
		$(MAKE) clean -f Makefile
	cd src/relpages; \
		$(MAKE) clean -f Makefile
	cd src/utils; \
		$(MAKE) clean -f Makefile
	cd src/UI; \
		$(MAKE) clean -f Makefile