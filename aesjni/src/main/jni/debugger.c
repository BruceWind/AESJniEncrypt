//
// Created by wei on 17-12-5.
//

#include "debugger.h"
#include <stdio.h>
#include "string.h"
#include "logger.h"
#include <sys/ptrace.h>


int is_debug() {
    return 0;
}


void anti_debug() {
    ptrace(PTRACE_TRACEME, 0, 0, 0);//this is low level anti-debug method.
}