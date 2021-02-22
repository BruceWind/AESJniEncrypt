//
// Created by wei on 16-12-4.
//

#ifndef AESJNIENCRYPT_SIGNACTURECHECK_H
#define AESJNIENCRYPT_SIGNACTURECHECK_H

//correct pkg name.
static const char *app_pkg_name = "com.androidyuan.aesjniencrypt";
//correct hashcode is -625644214
static const int app_signature_hash_code = -625644214;//it is hash of keystore file.


/**
 *
 * @param env
 * @param thiz
 * @param context
 * @return 1 means that everything is legal.
 */
jint check_signature(JNIEnv *env, jobject thiz, jobject context);

#endif //AESJNIENCRYPT_SIGNACTURECHECK_H
