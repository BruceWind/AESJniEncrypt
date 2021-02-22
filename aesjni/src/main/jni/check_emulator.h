#ifndef CHECK_EMULATOR_IN_NDK_CHECK_EMULATOR_H
#define CHECK_EMULATOR_IN_NDK_CHECK_EMULATOR_H

#include "jni.h"
#include "debugger.h"


/**
 * There is some code that very like java code what detect device is emulator
 *
 * @param env
 * @param context
 * @return  1:else means that device is not emulator ,else means that device is emulator.
 */
JNIEXPORT jint JNICALL  check_is_emulator(JNIEnv *env);

#endif



