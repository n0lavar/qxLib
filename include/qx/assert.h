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
#define QX_PROCESS_ASSERT(statement, msg, ...) QX_EMPTY_MACRO
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

#define _QX_ASSERT_MSG(statement, msg, ...)                   \
    [&]()                                                     \
    {                                                         \
        if (!(statement)) [[unlikely]]                        \
        {                                                     \
            QX_PROCESS_ASSERT(statement, msg, ##__VA_ARGS__); \
            QX_DEBUG_BREAK;                                   \
            return false;                                     \
        }                                                     \
        else                                                  \
        {                                                     \
            return true;                                      \
        }                                                     \
    }()

#define _QX_ASSERT(statement) QX_ASSERT_MSG(statement, "")

#define _QX_ASSERT_NO_ENTRY QX_ASSERT_MSG(0, "No entry")

#define _QX_ASSERT_RETURN(statement, ...)   \
    if (!QX_ASSERT(statement)) [[unlikely]] \
        return __VA_ARGS__;

#define _QX_ASSERT_CONTINUE(statement)      \
    if (!QX_ASSERT(statement)) [[unlikely]] \
        continue;

#define _QX_ASSERT_BREAK(statement)         \
    if (!QX_ASSERT(statement)) [[unlikely]] \
        break;

#else

#define _QX_ASSERT_MSG(statement, msg, ...)  \
    [&]()                                    \
    {                                        \
        return static_cast<bool>(statement); \
    }()

#define _QX_ASSERT(statement) QX_ASSERT_MSG(statement, "")

#define _QX_ASSERT_NO_ENTRY QX_ASSERT(0)

#define _QX_ASSERT_RETURN(statement, ...) \
    if (!(statement)) [[unlikely]]        \
        return __VA_ARGS__;

#define _QX_ASSERT_CONTINUE(statement) \
    if (!(statement)) [[unlikely]]     \
        continue;

#define _QX_ASSERT_BREAK(statement) \
    if (!(statement)) [[unlikely]]  \
        break;

#endif

/**
    @brief   Assert macro with message
    @details Same as QX_ASSERT, but with output possibility
    @param   statement - statement to check
    @param   msg       - message format
    @param   ...       - message arguments

    May be used in if statemant:

    @code
    const auto file = OpenFile(path);
    if (QX_ASSERT_MSG(file, "Can't open %s file", path.c_str()))
        ReadFromFile(file);
    @endcode 

**/
#define QX_ASSERT_MSG(statement, msg, ...) \
    _QX_ASSERT_MSG(statement, msg, __VA_ARGS__)

/**
    @brief   Assert macro
    @details If statement is false, assert processer will be called
             and debugging will stop at this point
    @param   statement - statement to check

    May be used in if statemant:

    @code
    const auto file = ...;
    if (QX_ASSERT(file))
        ReadFromFile(file);
    @endcode 

**/
#define QX_ASSERT(statement) _QX_ASSERT(statement)

/**
    @brief Invokes assert unconditionally if this code should not be executed
**/
#define QX_ASSERT_NO_ENTRY _QX_ASSERT_NO_ENTRY

/**
    @brief Check statement and return if false
    @param statement - statement to check
    @param ...       - return value if statement is false
**/
#define QX_ASSERT_RETURN(statement, ...) \
    _QX_ASSERT_RETURN(statement, __VA_ARGS__)

/**
    @brief Check statement and continue loop if false
    @param statement - statement to check
**/
#define QX_ASSERT_CONTINUE(statement) _QX_ASSERT_CONTINUE(statement)

/**
    @brief Check statement and break loop if false
    @param statement - statement to check
**/
#define QX_ASSERT_BREAK(statement) _QX_ASSERT_BREAK(statement)
