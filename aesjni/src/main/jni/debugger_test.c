//
// Created by wei on 17-12-5.
// this file is used to avoid security checking.
//

#include "debugger.h"
#include <stdio.h>
#include "string.h"
#include "logger.h"


/**
 * always return 1,
 */
int is_debug() {
    return 1;
}

void anti_debug() {}
