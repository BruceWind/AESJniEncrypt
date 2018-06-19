// Created by wei on 17-12-5.

/**
 * 通过依赖宏定义判断是否为DEBUG模式
 * 1.cmake 要使用define
 * 2.makefile 模式下 需要 CFLAGS += -D
 **/

#ifndef CHECK_EMULATOR_IN_NDK_DEBUGGER_H
#define CHECK_EMULATOR_IN_NDK_DEBUGGER_H

// result 1: isdebug  0: not debug
int isdebug();

#endif