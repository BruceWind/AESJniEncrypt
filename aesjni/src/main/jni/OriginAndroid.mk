# ========== static sodium begin ==================
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	ARCH_PREFIX := armv7-a
else ifeq ($(TARGET_ARCH_ABI),armeabi)
	ARCH_PREFIX := armv6
else ifeq ($(TARGET_ARCH_ABI),x86)
	ARCH_PREFIX := i686
else ifeq ($(TARGET_ARCH_ABI),mips)
	ARCH_PREFIX := mips32
else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
	ARCH_PREFIX := armv8-a
else
	ARCH_PREFIX := $(TARGET_ARCH)
endif

SODIUM_LIB_DIR := $(LOCAL_PATH)/sodium_include/libsodium-android-$(ARCH_PREFIX)
SODIUM_INC_DIR := $(SODIUM_LIB_DIR)/include
SODIUM_LIB := $(SODIUM_LIB_DIR)/lib/libsodium.a
LOCAL_MODULE:= sodium
LOCAL_SRC_FILES:= $(SODIUM_LIB)
LOCAL_EXPORT_C_INCLUDES := $(SODIUM_INC_DIR) $(SODIUM_INC_DIR)/sodium
include $(PREBUILT_STATIC_LIBRARY)

# ========== static sodium end ==================

include $(CLEAR_VARS)

LOCAL_MODULE    := JNIEncrypt
LOCAL_SRC_FILES := $(LOCAL_PATH)/JNIEncrypt.c	\
                    base64.c \
                    keys_generator.c \
					str_utils.cpp \
                    checksignature.c \
                    check_emulator.c \
                    debugger.c \
                    logger.h
LOCAL_CFLAGS   += -Wall -g -pedantic -std=c99

# if you want  to print logs pls write liblog on this line.
LOCAL_STATIC_LIBRARIES := sodium liblog libcutils

# LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_LDLIBS    := -llog
LOCAL_CPPFLAGS := -fexceptions
include $(BUILD_SHARED_LIBRARY)

