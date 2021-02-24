LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/BaseAndroid.mk

LOCAL_CFLAGS   += -Wall -g -pedantic

LOCAL_STATIC_LIBRARIES := sodium
LOCAL_LDLIBS    := -llog
LOCAL_LDLIBS += -Wl,--no-warn-shared-textrel

LOCAL_CPPFLAGS := -fexceptions
include $(BUILD_SHARED_LIBRARY)

