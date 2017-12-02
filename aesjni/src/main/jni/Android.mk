
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := JNIEncrypt
LOCAL_SRC_FILES := JNIEncrypt.c	\
                    aes.c \
                    checksignature.c \
                    base64.c



# 推荐使用
# LOCAL_CFLAGS := -fvisibility=hidden   -mllvm -sub -mllvm -fla -mllvm -bcf  #使用obfuscator需要打开这行代码
# 不推荐使用
LOCAL_CFLAGS := -fvisibility=hidden #隐藏字符表 实际上效果不太理想


# LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)

# include $(BUILD_EXECUTABLE)
