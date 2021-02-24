LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/BaseAndroid.mk

LOCAL_CFLAGS   += -Wall -g -pedantic

# if you want  to print logs pls write liblog on this line.
LOCAL_STATIC_LIBRARIES := sodium

# LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_LDLIBS    := -llog
LOCAL_CPPFLAGS := -fexceptions
include $(BUILD_SHARED_LIBRARY)

