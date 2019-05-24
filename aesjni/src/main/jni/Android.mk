
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := JNIEncrypt
LOCAL_SRC_FILES := JNIEncrypt.c	\
                    aes.c \
                    checksignature.c \
                    check_emulator.c \
                    debugger.c \
                    logger.h \
                    base64.c


LOCAL_CFLAGS := -fvisibility=hidden   -mllvm -sub -mllvm -fla -mllvm -bcf




# LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

# include $(BUILD_EXECUTABLE)
