LOCAL_PATH := $(call my-dir)

#...

include $(CLEAR_VARS)

LOCAL_MODULE := test  # executable file name.
LOCAL_SRC_FILES := main_unit_test.c
LOCAL_LDLIBS := -llog   # no need to specify path for liblog.so

include $(BUILD_EXECUTABLE)    # <-- Use this to build an executable.