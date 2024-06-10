top_build_dir = ../../..
test_obj_dir = $(top_build_dir)/src

include $(top_build_dir)/src/Makefile.global
include $(top_build_dir)/src/common.mk

include $(top_build_dir)/src/objlist.mk

TARGET = test

.PHONY: check 

check:
	rm -f $(TARGET) 
	gcc -o $(TARGET) $(OBJS) $(test_obj_dir)/relhash.o $(LIBS) 