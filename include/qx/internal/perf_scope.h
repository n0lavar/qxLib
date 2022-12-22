/**

    @file      perf_scope.h
    @brief     Contains perf scope macros for profiler (for internal usage only, but user may override them)
    @details   ~
    @author    Khrapov
    @date      22.12.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>

#ifndef QX_PERF_SCOPE
    // ... is category + name
    //     or empty
    #define QX_PERF_SCOPE(category, name) QX_EMPTY_MACRO
#endif
