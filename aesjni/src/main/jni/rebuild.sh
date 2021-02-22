#!/bin/bash
# @author bruce:
# ========================Remind:========================
# run this shell script must before, you computer must be set ANROID_NDK_HOME,
# And your computer must connect a device or emulator. 
# Pls modify BUILT_ABI for build compatible you device.
# -------------------------------------------------------
# Build success environmental system records:
# Mac OS:
#     It has been built success with NDK r19c.
# Ubuntu 20.0 :
#     It has been built success with ndk-bundle. You could download sdk,then use sdkmanger command to downlaod ndk-bundle.
#     And NDK-r13b got failed due to google not supporting the old ndk to be with new system.
#

#BUILT_ABI=x86 #  make it compatible for emulator
BUILT_ABI=armeabi-v7a # make it compatible for physical device
# detect whether build_libsodium_for_all_android_abi.sh has already been called.
if [ ! -d ./sodium_include/libsodium-android-armv7-a ]; then
  printf "Please run build_libsodium_for_all_android_abi.sh before.\n"
  exit
fi

# clear cache.
clear
rm -r ../obj/
rm -r ../libs/
ndk-build clean


## run "./rebuild.sh test"
if [[ $1 == "test" ]]; then
  printf "Start building......\n"
  cp -f TestAndroid.mk Android.mk
  ndk-build NDK_DEBUG=1
  if [ $? -ne 0 ]; then
      exit # failed at ndk-build
  fi
  printf "adb push......\n" # push executable file into device or emulator.
  adb push ../libs/$BUILT_ABI/test /data/local/tmp

   if [ $? -ne 0 ]; then # failed from pushing executable file.
     printf "can't push executable file. Do you connect device or emulator? \n"
     exit
  fi

  printf "Here is executable file printed:\n"
  printf "=========================\n"
  adb shell /data/local/tmp/test
  printf "=========================\n"
else
  cp -f OriginAndroid.mk Android.mk
  adb shell am instrument -w -m    -e debug false -e class 'com.androidyuan.aesjni.JNITest' com.androidyuan.aesjni.test/android.support.test.runner.AndroidJUnitRunner
fi



