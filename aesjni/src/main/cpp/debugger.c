//
// Created by wei on 17-12-5.
//

#include "debugger.h"
#include <stdio.h>
#include "string.h"
#include "logger.h"


 int isdebug(){

#ifdef NDK_DEBUG //android.mk 编译情况下
     LOGI("is NDK_DEBUG. \n");
        return 1;
#endif

#ifdef CMAKE_BUILD_TYPE// cmakelist 编译情况下
     LOGI("is CMAKE_BUILD_TYPE. \n");
    return 1;
#endif

    return 0;
}