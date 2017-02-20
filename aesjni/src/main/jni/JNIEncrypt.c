#include <jni.h>
#include "aes.h"
#include "checksignature.h"
#include <string.h>
#include "checksignature.h"
#include <android/log.h>
#include <assert.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define CBC 1
#define ECB 1
#define JNIREG_CLASS "com/androidyuan/aesjni/AESEncrypt"


const char *UNSIGNATURE = "UNSIGNATURE";



__attribute__((section (".mytext")))
jstring JNICALL encode(JNIEnv *env, jobject instance, jobject context, jstring str_) {

    //先进行apk被 二次打包的校验
    if (checkSignature(env, instance, context) != 1) {
        char *str = UNSIGNATURE;
        return (*env)->NewString(env, str, strlen(str));
    }

    uint8_t AES_KEY[] = "1234567890abcdef";
    const char *in = (*env)->GetStringUTFChars(env, str_, JNI_FALSE);
    char *baseResult = AES_128_ECB_PKCS5Padding_Encrypt(in, AES_KEY);
    (*env)->ReleaseStringUTFChars(env, str_, in);
    return (*env)->NewStringUTF(env, baseResult);
}

__attribute__((section (".mytext")))
jstring JNICALL decode(JNIEnv *env, jobject instance, jobject context, jstring str_) {


    //先进行apk被 二次打包的校验
    if (checkSignature(env, instance, context) != 1) {
        char *str = UNSIGNATURE;
        return (jstring) (*env)->NewStringUTF(env, str);
    }

    uint8_t AES_KEY[] = "1234567890abcdef";
    const char *str = (*env)->GetStringUTFChars(env, str_, JNI_FALSE);
    char *desResult = AES_128_ECB_PKCS5Padding_Decrypt(str, AES_KEY);
    (*env)->ReleaseStringUTFChars(env, str_, str);
    return (*env)->NewStringUTF(env, desResult);
    //不用系统自带的方法NewStringUTF是因为如果desResult是乱码,会抛出异常
    //return charToJstring(env,desResult);
}


static JNINativeMethod gMethods[] = {
        {"encode", "()Ljava/lang/String;", (void *) encode},
        {"decode", "()Ljava/lang/String;", (void *) decode}

};


static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}


/*
* Register native methods for all classes we know about.
*/

static int registerNatives(JNIEnv *env) {
    if (!registerNativeMethods(env, JNIREG_CLASS, gMethods,
                               sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;

    return JNI_TRUE;
}


/*
* Set some test stuff up.
*
* Returns the JNI version on success, -1 on failure.
*/

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    if (!registerNatives(env)) {//注册
        return -1;
    }

/* success -- return valid version number */

    result = JNI_VERSION_1_4;

    return result;
}


jstring charToJstring(JNIEnv *envPtr, char *src) {
    JNIEnv env = *envPtr;

    jsize len = strlen(src);
    jclass clsstring = env->FindClass(envPtr, "java/lang/String");
    jstring strencode = env->NewStringUTF(envPtr, "UTF-8");
    jmethodID mid = env->GetMethodID(envPtr, clsstring, "<init>",
                                     "([BLjava/lang/String;)V");
    jbyteArray barr = env->NewByteArray(envPtr, len);
    env->SetByteArrayRegion(envPtr, barr, 0, len, (jbyte *) src);

    return (jstring) env->NewObject(envPtr, clsstring, mid, barr, strencode);
}


/**
 * if rerurn 1 ,is check pass.
 */
JNIEXPORT jint JNICALL
Java__checkSignature(JNIEnv *env, jobject instance, jobject con) {

    return checkSignature(env, instance, con);
}

