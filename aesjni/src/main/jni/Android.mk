# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JNIEncrypt
LOCAL_SRC_FILES := JNIEncrypt.c	\
                    aes.c \
                    checksignature.c \
                    base64.c



# NDK_TOOLCHAIN_VERSION := clang3.4-obfuscator


# LOCAL_CFLAGS :=  -mllvm -sub -mllvm -fla -mllvm -bcf
LOCAL_CFLAGS := -fvisibility=hidden #隐藏字符表 实际上效果不太理想



# LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

# include $(BUILD_EXECUTABLE)
