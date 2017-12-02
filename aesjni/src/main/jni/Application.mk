
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

APP_ABI :=  armeabi  armeabi-v7a arm64-v8a x86_64

# 推荐使用
# NDK_TOOLCHAIN_VERSION := clang-ollvm4.0   #使用obfuscator需要打开这行代码

include $(BUILD_EXECUTABLE)
