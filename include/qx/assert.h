/**

    @file      assert.h
    @brief     Assert macros
    @author    Khrapov
    @date      29.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_macros.h>

/*
    QX_ASSERT and QX_ASSERT_MSG macros
    use QX_ENABLE_ASSERTS, QX_ENABLE_DEBUG_BREAK, QX_PROCESS_ASSERT macros to configure behavior
*/

#ifndef QX_ENABLE_ASSERTS
#define QX_ENABLE_ASSERTS QX_DEBUG
#endif

#ifndef QX_ENABLE_DEBUG_BREAK
#define QX_ENABLE_DEBUG_BREAK QX_DEBUG
#endif

#ifndef QX_PROCESS_ASSERT
#define QX_PROCESS_ASSERT(statement) QX_EMPTY_MACRO
#endif

#ifndef QX_PROCESS_ASSERT_MSG
#define QX_PROCESS_ASSERT_MSG(statement, msg, ...) QX_PROCESS_ASSERT(statement)
#endif

#if QX_ENABLE_DEBUG_BREAK

#if QX_MSVC
#define QX_DEBUG_BREAK __debugbreak()
#elif QX_CLANG
#define QX_DEBUG_BREAK __builtin_debugtrap()
#elif QX_GNU
#include <signal.h>
#define QX_DEBUG_BREAK raise(SIGTRAP)
#else
#define QX_DEBUG_BREAK QX_EMPTY_MACRO
#endif

#else

#define QX_DEBUG_BREAK QX_EMPTY_MACRO

#endif


#if QX_ENABLE_ASSERTS

#define QX_ASSERT(statement)              \
    do                                    \
    {                                     \
        if (!(statement))                 \
        {                                 \
            QX_PROCESS_ASSERT(statement); \
            QX_DEBUG_BREAK;               \
        }                                 \
    } while (false)

#define QX_ASSERT_MSG(statement, msg, ...)                        \
    do                                                            \
    {                                                             \
        if (!(statement))                                         \
        {                                                         \
            QX_PROCESS_ASSERT_MSG(statement, msg, ##__VA_ARGS__); \
            QX_DEBUG_BREAK;                                       \
        }                                                         \
    } while (false)

#else

#define QX_ASSERT(statement)               QX_EMPTY_MACRO
#define QX_ASSERT_MSG(statement, msg, ...) QX_EMPTY_MACRO

#endif

//==============================================================================

/*
    Short assert and if (no need to double condition)
*/

#define QX_CHECK(condition) \
    QX_ASSERT(condition);   \
    if (condition)

//==============================================================================

/*
    Stub for not implemented yet code lines
*/

#define QX_ASSERT_NOT_IMPL QX_ASSERT_MSG(0, "Implementation isn't ready")
