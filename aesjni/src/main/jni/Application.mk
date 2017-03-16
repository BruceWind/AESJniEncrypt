
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

APP_ABI :=  armeabi  armeabi-v7a

NDK_TOOLCHAIN_VERSION := clang3.4-obfuscator

include $(BUILD_EXECUTABLE)
