//
// Created by wei on 16-12-4.
//

#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "checksignature.h"


jint check_signature(JNIEnv *env, jobject thiz, jobject context) {
    //Context的类
    jclass context_clazz = (*env)->GetObjectClass(env, context);
    // 得到 getPackageManager 方法的 ID
    jmethodID methodID_getPackageManager = (*env)->GetMethodID(env,
                                                               context_clazz, "getPackageManager",
                                                               "()Landroid/content/pm/PackageManager;");

    // 获得PackageManager对象
    jobject packageManager = (*env)->CallObjectMethod(env, context,
                                                      methodID_getPackageManager);
//	// 获得 PackageManager 类
    jclass pm_clazz = (*env)->GetObjectClass(env, packageManager);
    // 得到 getPackageInfo 方法的 ID
    jmethodID methodID_pm = (*env)->GetMethodID(env, pm_clazz, "getPackageInfo",
                                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
//
//	// 得到 getPackageName 方法的 ID
    jmethodID methodID_pack = (*env)->GetMethodID(env, context_clazz,
                                                  "getPackageName", "()Ljava/lang/String;");

    // 获得当前应用的包名
    jstring application_package = (*env)->CallObjectMethod(env, context,
                                                           methodID_pack);
    const char *package_name = (*env)->GetStringUTFChars(env,
                                                         application_package, 0);
    //LOGE("packageName: %s\n", package_name);

    // 获得PackageInfo
    jobject packageInfo = (*env)->CallObjectMethod(env, packageManager,
                                                   methodID_pm, application_package, 64);

    jclass packageinfo_clazz = (*env)->GetObjectClass(env, packageInfo);
    jfieldID fieldID_signatures = (*env)->GetFieldID(env, packageinfo_clazz,
                                                     "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signature_arr = (jobjectArray) (*env)->GetObjectField(env,
                                                                       packageInfo, fieldID_signatures);
    //Signature数组中取出第一个元素
    jobject signature = (*env)->GetObjectArrayElement(env, signature_arr, 0);
    //读signature的hashcode
    jclass signature_clazz = (*env)->GetObjectClass(env, signature);
    jmethodID methodID_hashcode = (*env)->GetMethodID(env, signature_clazz,
                                                      "hashCode", "()I");
    jint hashCode = (*env)->CallIntMethod(env, signature, methodID_hashcode);
    //LOGE("hashcode: %d\n", hashCode);

    if (strcmp(package_name, app_packageName) != 0) {
        return -1;
    }
    if (hashCode != app_signature_hash_code) {
        return -2;
    }
    return 1;
}