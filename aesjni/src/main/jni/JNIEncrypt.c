#include <jni.h>
#include "aes.h"
#include <android/log.h>
#include <string.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define CBC 1
#define ECB 1


static uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

JNIEXPORT jstring JNICALL
Java_com_androidyuan_aesjni_AESEncrypt_encode(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);

    // TODO
    uint8_t in[]  = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
//    uint8_t in[strlen(str)];
//
//    for (int i = 0; i <strlen(str); ++i) {
//        in[i] = str[i];
//    }

    uint8_t buffer[strlen(str)];



    AES128_ECB_encrypt(in, key, buffer);


    (*env)->ReleaseStringUTFChars(env, str_, str);

    return (*env)->NewStringUTF(env, buffer);
}

JNIEXPORT jstring JNICALL
Java_com_androidyuan_aesjni_AESEncrypt_decode(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);

    // TODO
    uint8_t in[strlen(str)];

    for (int i = 0; i <strlen(str); ++i) {
        in[i] = str[i];
    }

    uint8_t buffer[strlen(str)];

    AES128_ECB_encrypt(in, key, buffer);
    (*env)->ReleaseStringUTFChars(env, str_, str);

    return (*env)->NewStringUTF(env, buffer);
}