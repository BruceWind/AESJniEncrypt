//
// Created by wei on 16-12-4.
//

#define   LOG_TAG    "native_log"
//#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#ifndef AESJNIENCRYPT_SIGNACTURECHECK_H
#define AESJNIENCRYPT_SIGNACTURECHECK_H


//合法的APP包名
static const char *app_packageName = "com.androidyuan.aesjniencrypt";
//合法的hashcode -625644214:这个值是我生成的这个可以store文件的hash值
static const int app_signature_hash_code = -625644214;

/**
 * 校验APP 包名和签名是否合法
 *
 * 返回值为1 表示合法
 */
jint checkSignature(JNIEnv *env, jobject thiz, jobject context);

#endif //AESJNIENCRYPT_SIGNACTURECHECK_H
