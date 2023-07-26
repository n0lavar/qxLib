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
    //     or category
    //     or name
    //     or empty
    #define QX_PERF_SCOPE(...) QX_EMPTY_MACRO
#endif

#ifndef QX_PERF_FREE_MUTEX
    #define QX_PERF_FREE_MUTEX(name) std::mutex name
#endif

#ifndef QX_PERF_FREE_SHARED_MUTEX
    #define QX_PERF_FREE_SHARED_MUTEX(name) std::shared_mutex name
#endif

#ifndef QX_PERF_MUTEX
    #define QX_PERF_MUTEX(name) mutable std::mutex name
#endif

#ifndef QX_PERF_SHARED_MUTEX
    #define QX_PERF_SHARED_MUTEX(name) mutable std::shared_mutex name
#endif
