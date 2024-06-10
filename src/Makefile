sub_dir = src
top_build_dir = ..

include $(top_build_dir)/src/Makefile.global
include $(top_build_dir)/src/common.mk

.PHONY: test_relhash

check_relhash:
	cd $(test_dir)/relhash; \
		$(MAKE) check -f Makefile 
