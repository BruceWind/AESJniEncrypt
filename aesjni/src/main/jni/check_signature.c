//
// Created by wei on 16-12-4.
//

#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "check_signature.h"
#include "debugger.h"


jint check_signature(JNIEnv *env, jobject thiz, jobject context) {

    if(is_debug()==1)//debug mode does not need to check
        return 1;


    jclass context_clazz = (*env)->GetObjectClass(env, context);
    // obtain method ID of getPackageManager.
    jmethodID methodID_getPackageManager = (*env)->GetMethodID(env,
                                                               context_clazz, "getPackageManager",
                                                               "()Landroid/content/pm/PackageManager;");

    // obtain PackageManager object
    jobject packageManager = (*env)->CallObjectMethod(env, context,
                                                      methodID_getPackageManager);
    // obtain PackageManager class
    jclass pm_clazz = (*env)->GetObjectClass(env, packageManager);
    // obtain getPackageInfo method ID
    jmethodID methodID_pm = (*env)->GetMethodID(env, pm_clazz, "getPackageInfo",
                                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
//
//	// obtain getPackageName method ID
    jmethodID methodID_pack = (*env)->GetMethodID(env, context_clazz,
                                                  "getPackageName", "()Ljava/lang/String;");

    // obtain
    jstring application_package = (*env)->CallObjectMethod(env, context,
                                                           methodID_pack);
    const char *package_name = (*env)->GetStringUTFChars(env,
                                                         application_package, 0);
    //LOGE("packageName: %s\n", package_name);


    char app_pkg_test[strlen(app_pkg_name)+5];
    strcpy(app_pkg_test,app_pkg_name);
    strcat(app_pkg_test,".test");
    if (strcmp(package_name, app_pkg_test) != 0) {//test does not need to check.
        return 1;
    }


    // obtainPackageInfo
    jobject packageInfo = (*env)->CallObjectMethod(env, packageManager,
                                                   methodID_pm, application_package, 64);

    jclass packageinfo_clazz = (*env)->GetObjectClass(env, packageInfo);
    jfieldID fieldID_signatures = (*env)->GetFieldID(env, packageinfo_clazz,
                                                     "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signature_arr = (jobjectArray) (*env)->GetObjectField(env,
                                                                       packageInfo, fieldID_signatures);
    //get first item from Signature array.
    jobject signature = (*env)->GetObjectArrayElement(env, signature_arr, 0);
    //obtain hash of signature
    jclass signature_clazz = (*env)->GetObjectClass(env, signature);
    jmethodID methodID_hashcode = (*env)->GetMethodID(env, signature_clazz,
                                                      "hashCode", "()I");
    jint hashCode = (*env)->CallIntMethod(env, signature, methodID_hashcode);
    //LOGE("hashcode: %d\n", hashCode);


    if (strcmp(package_name, app_pkg_name) != 0) {
        return -1;
    }
    if (hashCode != app_signature_hash_code) {
        return -2;
    }
    return 1;
}
