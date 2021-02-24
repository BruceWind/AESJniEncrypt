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

LOCAL_MODULE := test  # executable file name.
LOCAL_SRC_FILES := main_unit_test.c \
                    logger.h \
					debugger.c \
                    keys_generator.c \

					str_utils.h \
					str_utils.cpp
LOCAL_STATIC_LIBRARIES := sodium  # tell ndk-build about the dependency
LOCAL_LDLIBS := -llog  #there is no need to specify path for liblog.so


LOCAL_CFLAGS   += -Wall -g -pedantic -std=c99 # ndk13 on mac
LOCAL_CPPFLAGS := -fexceptions

include $(BUILD_EXECUTABLE)    # <-- Use this to build as executable file.