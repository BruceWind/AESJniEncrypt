LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/BaseAndroid.mk


LOCAL_MODULE    := JNIEncrypt
LOCAL_SRC_FILES := $(LOCAL_PATH)/JNIEncrypt.c	\
                    base64.c \
                    keys_generator.c \
					str_utils.cpp \
                    checksignature.c \
                    $(DEBUG_FILE_C) \
                    debugger.c \
                    logger.h
LOCAL_CFLAGS   += -Wall -g -pedantic

LOCAL_STATIC_LIBRARIES := sodium
LOCAL_LDLIBS    := -llog
LOCAL_LDLIBS += -Wl,--no-warn-shared-textrel

LOCAL_CPPFLAGS := -fexceptions
include $(BUILD_SHARED_LIBRARY)

