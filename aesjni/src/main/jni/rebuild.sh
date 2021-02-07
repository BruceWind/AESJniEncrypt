#!/usr/bin/env bash
# @author bruce:
# ========================Remind:========================
# run this shell script must before, you computer must be set ANROID_NDK_HOME,
# And your computer must connect with a armv8 phone,or armv8 emulator beacause only build armv8 share library.
# -------------------------------------------------------
# Build success environmental system records:
# Mac OS:
#     It has been built success with NDK r19c.
# Ubuntu 20.0 :
#     It has been built success with ndk-bundle. You could download sdk,then use sdkmanger command to downlaod ndk-bundle.
#     And NDK-r13b got failed due to google not supporting the old ndk to be with new system.
#

# detect whether build_libsodium_for_all_android_abi.sh has already been called.
if [ ! -d ./sodium_include/libsodium-android-armv8-a ]; then
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
  ndk-build
  if [ $? -ne 0 ]; then
      exit # failed at ndk-build
  fi
  printf "adb push......\n" # push executable file into device or emulator.
  adb push ../libs/arm64-v8a/test /data/local/tmp

   if [ $? -ne 0 ]; then # failed from pushing executable file.
     printf "can't push executable file, does you connect more than one device or emulator? \n"
     exit
  fi

  printf "This is executable file print:\n"
  printf "=========================\n"
  adb shell /data/local/tmp/test
  printf "=========================\n"
else
  cp -f OriginAndroid.mk Android.mk
  ndk-build
fi



