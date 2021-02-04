/*===================================================
this file is used to test native codes.
you can run a command in this directory: ./rebuild.sh test
===================================================*/

#define TEST_NAME "aead_aes256gcm"
#include <stdio.h>
#include <android/log.h>

//run adb logcat | grep NATIVE_UT
#define TAG "NATIVE_UT"
void logd(char * str){
    __android_log_print(ANDROID_LOG_DEBUG  , TAG, "%s", str); // the 3rd arg is a printf-style format string
}

int main() {
    printf("main() running.\n");//this string will be got from you command,
    logd("test");//run adb logcat | grep NATIVE_UT
    return 0;
}


