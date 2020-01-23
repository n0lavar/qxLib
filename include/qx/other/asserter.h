//============================================================================
//
//!\file                          asserter.h
//
//!\brief       Assert implementation
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once
#include <logger.h>

#if ENABLE_ASSERTS

    #if defined(_WIN32)
        #define DEBUG_BREAK __debugbreak()
    #elif defined(_LINUX)
        #define DEBUG_BREAK if (detect_debugger() == 1) raise(SIGTRAP)
    #elif defined(ANDROID)
    #endif

#else

    #define DEBUG_BREAK EMPTY_MACRO

#endif


#define ASSERT(statement)                                   \
do {                                                        \
    if (!(statement))                                       \
    {                                                       \
        _TR_ASSERT(STRINGIFY(statement), "");               \
        DEBUG_BREAK;                                        \
    }                                                       \
} while (false)

#define ASSERT_MSG(statement, msg, ...)                     \
do {                                                        \
    if (!(statement))                                       \
    {                                                       \
        _TR_ASSERT(STRINGIFY(statement), msg, __VA_ARGS__); \
        DEBUG_BREAK;                                        \
    }                                                       \
} while (false)
