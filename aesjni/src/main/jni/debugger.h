// Created by wei on 17-12-5.

/**
 * detect is debug mode by macro definition
 * 1.cmake 要使用define
 * 2.makefile mode need "CFLAGS += -D"
 **/

#ifndef CHECK_EMULATOR_IN_NDK_DEBUGGER_H
#define CHECK_EMULATOR_IN_NDK_DEBUGGER_H

// result 1: isdebug  0: release
int is_debug();

void anti_debug();

#endif
