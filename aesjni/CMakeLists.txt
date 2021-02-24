cmake_minimum_required(VERSION 3.4.1)           #普通版本的clang

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -------configure import libsodium begin------
if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set(ARCH_PREFIX "armv7-a")
elseif (${ANDROID_ABI} STREQUAL "arm64-v8a")
    set(ARCH_PREFIX "armv8-a")
elseif (${ANDROID_ABI} STREQUAL "armeabi")
    set(ARCH_PREFIX "armv6")
elseif (${ANDROID_ABI} STREQUAL "x86")
    set(ARCH_PREFIX "i686")
elseif (${ANDROID_ABI} STREQUAL "mips")
    set(ARCH_PREFIX "mips32")
else ()
    #set(ARCH_PREFIX ${ANDROID_ABI})
    message(FATAL_ERROR "${ANDROID_ABI} static libraries might doesn't exist.")
endif ()


set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jni/sodium_include/libsodium-android-${ARCH_PREFIX})

message(STATUS "Current build include : ${distribution_DIR} ")
add_library(libsodium STATIC IMPORTED)
set_target_properties(libsodium PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/lib/libsodium.a)
# include C export files.
include_directories(${distribution_DIR}/include)
# -------configure import libsodium end------


if (${ANDROID_ABI} STREQUAL "x86")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-warn-shared-textrel")
endif ()

set(DEBUG_FILE_C "src/main/jni/debugger.c")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(DEBUG_FILE_C "src/main/jni/debugger_test.c")
endif ()

add_library( # Sets the name of the library.
        JNIEncrypt

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/jni/check_signature.h
        src/main/jni/check_signature.c
        src/main/jni/check_emulator.h
        src/main/jni/check_emulator.c
        src/main/jni/debugger.h
        ${DEBUG_FILE_C}
        src/main/jni/logger.h
        src/main/jni/keys_generator.h
        src/main/jni/keys_generator.c
        src/main/jni/base64.h
        src/main/jni/base64.c
        src/main/jni/str_utils.cpp
        src/main/jni/JNIEncrypt.c
        )

find_library(log-lib
        log)


target_link_libraries( # Specifies the target library.
        JNIEncrypt
        libsodium
        ${log-lib})
