#!/bin/bash
# This shell script got success on some environments:
# ==========================================================
# 1.MacOS with ndk r13.
# 2.Ubuntu 20 with ndk-bundle.

# ===========================Remind=========================
# If you are running this shell for the first time, Pls look at terminal.
# Some error might be thrown. You may need to install certain applications
# (such as python, libtool-bin) to resolve those errors.

LIBSODIUM_GIT_TAG=1.0.18 # it is the last stable version that I have tested.

#ROOT_DIR=$(pwd)

# building libsodium needs to execute ndk-build,so there is detect whether $ANDROID_NDK_HOME exist.
if [ ! "$ANDROID_NDK_HOME" ];then
  printf "ANDROID_NDK_HOME does not exist in environment. Please set ANDROID_NDK_HOME into your environment.\n"
  exit
fi

SODIUM_INCLUDE_DIR=$(pwd)/sodium_include
if [ -d "$SODIUM_INCLUDE_DIR" ]; then  # if it exists,delete it.
    rm -rf "$SODIUM_INCLUDE_DIR"/libsodium-android*
else
  mkdir sodium_include
fi

TEMP_DIR=$(pwd)/temp
if [ -d "$TEMP_DIR" ]; then # if it exists,delete it.
    rm -rf "$TEMP_DIR"
fi
mkdir "$TEMP_DIR"



SODIUM_CLONING_HOME=$TEMP_DIR/libsodium
# clone
git clone git@github.com:jedisct1/libsodium.git "$SODIUM_CLONING_HOME"
cd "$SODIUM_CLONING_HOME" || exit
git fetch --tags
git checkout $LIBSODIUM_GIT_TAG # check specific verion.



# && git pull

# This can be removed once we pull from a release
if [ ! -e "$SODIUM_CLONING_HOME"/configure ]; then
    ./autogen.sh
fi

LIBSODIUM_ARMV6=$SODIUM_CLONING_HOME/libsodium-android-armv6
LIBSODIUM_ARMV7A=$SODIUM_CLONING_HOME/libsodium-android-armv7-a
LIBSODIUM_I686=$SODIUM_CLONING_HOME/libsodium-android-i686
LIBSODIUM_MIPS32=$SODIUM_CLONING_HOME/libsodium-android-mips32
LIBSODIUM_ARMV8A=$SODIUM_CLONING_HOME/libsodium-android-armv8-a

# Run the android builds
if [ ! -d "$LIBSODIUM_ARMV6" ]; then
    "$SODIUM_CLONING_HOME"/dist-build/android-arm.sh
    echo "build-libsodium: built armv6!"
else
    echo "build-libsodium: skipping armv6, already built!"
fi

if [ ! -d "$LIBSODIUM_ARMV7A" ]; then
    "$SODIUM_CLONING_HOME"/dist-build/android-armv7-a.sh
    echo "build-libsodium: built armv7-a!"
else
    echo "build-libsodium: skipping armv7-a, already built!"
fi

if [ ! -d "$LIBSODIUM_MIPS32" ]; then
    "$SODIUM_CLONING_HOME"/dist-build/android-mips32.sh
    echo "build-libsodium: built mips32!"
else
    echo "build-libsodium: skipping mips32, already built!"
fi

if [ ! -d "$LIBSODIUM_I686" ]; then
    "$SODIUM_CLONING_HOME"/dist-build/android-x86.sh
    echo "build-libsodium: built x86!"
else
    echo "build-libsodium: skipping x86, already built!"
fi

if [ ! -d "$LIBSODIUM_ARMV8A" ]; then
    "$SODIUM_CLONING_HOME"/dist-build/android-armv8-a.sh
    echo "build-libsodium: built armv8-a!"
else
    echo "build-libsodium: skipping armv8-a, already built!"
fi


if [ $? -eq 0 ]; then
  mv -v "$SODIUM_CLONING_HOME"/libsodium-android-* "$SODIUM_INCLUDE_DIR"
  printf 'all of static libs move into %s.\n' "$SODIUM_INCLUDE_DIR"
  rm -rf "$TEMP_DIR"
fi