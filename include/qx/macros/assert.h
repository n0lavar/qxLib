/**

    @file      assert.h
    @brief     Expect and assert macros
    @author    Khrapov
    @date      29.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/logger.h>
#include <qx/macros/common.h>

#include <exception>


#if QX_MSVC
    #define _QX_DEBUG_BREAK __debugbreak()
#elif QX_CLANG
    #define _QX_DEBUG_BREAK __builtin_debugtrap()
#elif QX_GNU
    #include <signal.h>
    #define _QX_DEBUG_BREAK raise(SIGTRAP)
#else
    #define _QX_DEBUG_BREAK QX_EMPTY_MACRO
#endif

/**
    @brief Causes a breakpoint in your code, where the user will be prompted to run the debugger
**/
#define QX_DEBUG_BREAK _QX_DEBUG_BREAK


#define _QX_ASSERT_MSG(before_debug_break, debug_break, after_debug_break, condition, format, ...) \
    [&]()                                                                                          \
    {                                                                                              \
        if (!(condition)) [[unlikely]]                                                             \
        {                                                                                          \
            before_debug_break(condition, format, ##__VA_ARGS__);                                  \
            debug_break;                                                                           \
            after_debug_break(condition, format, ##__VA_ARGS__);                                   \
            return false;                                                                          \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            return true;                                                                           \
        }                                                                                          \
    }()

#define _QX_ASSERT(before_debug_break, debug_break, after_debug_break, condition) \
    _QX_ASSERT_MSG(before_debug_break, debug_break, after_debug_break, condition, "")

#define _QX_ASSERT_NO_ENTRY(before_debug_break, debug_break, after_debug_break, format, ...) \
    _QX_ASSERT_MSG(before_debug_break, debug_break, after_debug_break, false, format, ##__VA_ARGS__)

#define _QX_ASSERT_RETURN(before_debug_break, debug_break, after_debug_break, return_keyword, condition, ...) \
    if (!_QX_ASSERT(before_debug_break, debug_break, after_debug_break, condition)) [[unlikely]]              \
        return_keyword __VA_ARGS__;                                                                           \
    else                                                                                                      \
        QX_EMPTY_MACRO

#define _QX_ASSERT_CONTINUE(before_debug_break, debug_break, after_debug_break, condition, format, ...)        \
    if (!_QX_ASSERT_MSG(before_debug_break, debug_break, after_debug_break, condition, format, ##__VA_ARGS__)) \
        [[unlikely]]                                                                                           \
        continue;                                                                                              \
    else                                                                                                       \
        QX_EMPTY_MACRO

#define _QX_ASSERT_BREAK(before_debug_break, debug_break, after_debug_break, condition, format, ...)           \
    if (!_QX_ASSERT_MSG(before_debug_break, debug_break, after_debug_break, condition, format, ##__VA_ARGS__)) \
        [[unlikely]]                                                                                           \
        break;                                                                                                 \
    else                                                                                                       \
        QX_EMPTY_MACRO

#ifndef QX_EXPECT_BEFORE_DEBUG_BREAK
    #define QX_EXPECT_BEFORE_DEBUG_BREAK(condition, format, ...) \
        qx::string sFormat("[%s] ");                             \
        sFormat += format;                                       \
        QX_LOG(qx::log_level::error, sFormat.c_str(), #condition, ##__VA_ARGS__)
#endif

#ifndef QX_EXPECT_DEBUG_BREAK
    #if QX_DEBUG
        #define QX_EXPECT_DEBUG_BREAK QX_DEBUG_BREAK
    #else
        #define QX_EXPECT_DEBUG_BREAK QX_EMPTY_MACRO
    #endif
#endif

#ifndef QX_EXPECT_AFTER_DEBUG_BREAK
    #define QX_EXPECT_AFTER_DEBUG_BREAK(condition, format, ...) QX_EMPTY_MACRO
#endif

#ifndef QX_ASSERT_BEFORE_DEBUG_BREAK
    #define QX_ASSERT_BEFORE_DEBUG_BREAK(condition, format, ...) \
        qx::string sFormat("[%s] ");                             \
        sFormat += format;                                       \
        QX_LOG(qx::log_level::critical, sFormat.c_str(), #condition, ##__VA_ARGS__)
#endif

#ifndef QX_ASSERT_DEBUG_BREAK
    #if QX_DEBUG
        #define QX_ASSERT_DEBUG_BREAK QX_DEBUG_BREAK
    #else
        #define QX_ASSERT_DEBUG_BREAK QX_EMPTY_MACRO
    #endif
#endif

#ifndef QX_ASSERT_AFTER_DEBUG_BREAK
    #define QX_ASSERT_AFTER_DEBUG_BREAK(condition, format, ...) std::terminate()
#endif


/**
    @brief   Verifies that condition is true
    @details EXPECT macros generate nonfatal failures and allow to continue running
             Same as QX_EXPECT, but with output possibility
    @param   condition - condition to check
    @param   format    - message format
    @param   ...       - message arguments

    May be used in if condition:

    @code
    const auto file = OpenFile(path);
    if (QX_EXPECT_MSG(file, "Can't open %s file", path.c_str()))
        ReadFromFile(file);
    @endcode 

**/
#define QX_EXPECT_MSG(condition, format, ...) \
    _QX_ASSERT_MSG(                           \
        QX_EXPECT_BEFORE_DEBUG_BREAK,         \
        QX_EXPECT_DEBUG_BREAK,                \
        QX_EXPECT_AFTER_DEBUG_BREAK,          \
        condition,                            \
        format,                               \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true
    @details ASSERT macros generate fatal failures and abort the program execution
             Same as QX_ASSERT, but with output possibility
    @param   condition - condition to check
    @param   format    - message format
    @param   ...       - message arguments
**/
#define QX_ASSERT_MSG(condition, format, ...) \
    _QX_ASSERT_MSG(                           \
        QX_ASSERT_BEFORE_DEBUG_BREAK,         \
        QX_ASSERT_DEBUG_BREAK,                \
        QX_ASSERT_AFTER_DEBUG_BREAK,          \
        condition,                            \
        format,                               \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check

    May be used in if statement:

    @code
    const auto file = ...;
    if (QX_EXPECT(file))
        ReadFromFile(file);
    @endcode 

**/
#define QX_EXPECT(condition) \
    _QX_ASSERT(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition)

/**
    @brief   Verifies that condition is true
    @details ASSERT macros generate fatal failures and abort the program execution
    @param   condition - condition to check
**/
#define QX_ASSERT(condition) \
    _QX_ASSERT(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, condition)

/**
    @brief   Fails unconditionally if this code should not be executed
    @details EXPECT macros generate nonfatal failures and allow to continue running
**/
#define QX_EXPECT_NO_ENTRY() \
    _QX_ASSERT_NO_ENTRY(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, "No entry")

/**
    @brief   Fails unconditionally if this code should not be executed
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   format - message format
    @param   ...    - message arguments
**/
#define QX_EXPECT_NO_ENTRY_MSG(format, ...) \
    _QX_ASSERT_NO_ENTRY(                    \
        QX_EXPECT_BEFORE_DEBUG_BREAK,       \
        QX_EXPECT_DEBUG_BREAK,              \
        QX_EXPECT_AFTER_DEBUG_BREAK,        \
        format,                             \
        ##__VA_ARGS__)

/**
    @brief   Fails unconditionally if this code should not be executed
    @details ASSERT macros generate fatal failures and abort the program execution
**/
#define QX_ASSERT_NO_ENTRY() \
    _QX_ASSERT_NO_ENTRY(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, "No entry")

/**
    @brief   Fails unconditionally if this code should not be executed
    @details ASSERT macros generate fatal failures and abort the program execution
    @param   format - message format
    @param   ...    - message arguments
**/
#define QX_ASSERT_NO_ENTRY_MSG(format, ...) \
    _QX_ASSERT_NO_ENTRY(                    \
        QX_ASSERT_BEFORE_DEBUG_BREAK,       \
        QX_ASSERT_DEBUG_BREAK,              \
        QX_ASSERT_AFTER_DEBUG_BREAK,        \
        format,                             \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and return if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check
    @param   ...       - return value if condition is false
**/
#define QX_EXPECT_RETURN(condition, ...) \
    _QX_ASSERT_RETURN(                   \
        QX_EXPECT_BEFORE_DEBUG_BREAK,    \
        QX_EXPECT_DEBUG_BREAK,           \
        QX_EXPECT_AFTER_DEBUG_BREAK,     \
        return,                          \
        condition,                       \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and co_return if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check
    @param   ...       - return value if condition is false
**/
#define QX_EXPECT_CO_RETURN(condition, ...) \
    _QX_ASSERT_RETURN(                      \
        QX_EXPECT_BEFORE_DEBUG_BREAK,       \
        QX_EXPECT_DEBUG_BREAK,              \
        QX_EXPECT_AFTER_DEBUG_BREAK,        \
        co_return,                          \
        condition,                          \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and continue loop if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check
**/
#define QX_EXPECT_CONTINUE(condition) \
    _QX_ASSERT_CONTINUE(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, "")

/**
    @brief   Verifies that condition is true and continue loop if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check
    @param   format    - message format
    @param   ...       - message arguments
**/
#define QX_EXPECT_CONTINUE_MSG(condition, format, ...) \
    _QX_ASSERT_CONTINUE(                               \
        QX_EXPECT_BEFORE_DEBUG_BREAK,                  \
        QX_EXPECT_DEBUG_BREAK,                         \
        QX_EXPECT_AFTER_DEBUG_BREAK,                   \
        condition,                                     \
        format,                                        \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and break loop if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check
**/
#define QX_EXPECT_BREAK(condition) \
    _QX_ASSERT_BREAK(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, "")

/**
    @brief   Verifies that condition is true and break loop if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check
    @param   format    - message format
    @param   ...       - message arguments
**/
#define QX_EXPECT_BREAK_MSG(condition, format, ...) \
    _QX_ASSERT_BREAK(                               \
        QX_EXPECT_BEFORE_DEBUG_BREAK,               \
        QX_EXPECT_DEBUG_BREAK,                      \
        QX_EXPECT_AFTER_DEBUG_BREAK,                \
        condition,                                  \
        format,                                     \
        ##__VA_ARGS__)
