#ifndef CHECK_EMULATOR_IN_NDK_CHECK_EMULATOR_H
#define CHECK_EMULATOR_IN_NDK_CHECK_EMULATOR_H

#include "jni.h"
#include "debugger.h"


/**
 *
 * @param env
 * @param context
 * @return  1:通过(非模拟器) else :不通过(是模拟器)
 */
JNIEXPORT jint JNICALL  check_is_emulator(JNIEnv *env);

#endif



