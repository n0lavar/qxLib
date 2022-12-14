/**

    @file      assert.h
    @brief     Expect and assert macros
    @author    Khrapov
    @date      29.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/logger/logger.h>
#include <qx/macros/common.h>

#include <exception>

// default assert/expect category
// should only be used in file macros
QX_DEFINE_CATEGORY(CatAssert);

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

// ----------------------------------- setup -----------------------------------

#ifndef QX_DEBUG_BREAK
    #define QX_DEBUG_BREAK _QX_DEBUG_BREAK
#endif

#ifndef QX_EXPECT_BEFORE_DEBUG_BREAK
    #define QX_EXPECT_BEFORE_DEBUG_BREAK(condition, category, format, ...) \
        qx::string sFormat("[%s] ");                                       \
        sFormat += format;                                                 \
        QX_LOG_C(category, qx::log_level::error, sFormat.c_str(), #condition, ##__VA_ARGS__)
#endif

#ifndef QX_EXPECT_DEBUG_BREAK
    #if QX_DEBUG || QX_REL_WITH_DEBUG_INFO
        #define QX_EXPECT_DEBUG_BREAK QX_DEBUG_BREAK
    #else
        #define QX_EXPECT_DEBUG_BREAK QX_EMPTY_MACRO
    #endif
#endif

#ifndef QX_EXPECT_AFTER_DEBUG_BREAK
    #define QX_EXPECT_AFTER_DEBUG_BREAK(condition, category, format, ...) QX_EMPTY_MACRO
#endif

#ifndef QX_ASSERT_BEFORE_DEBUG_BREAK
    #define QX_ASSERT_BEFORE_DEBUG_BREAK(condition, category, format, ...) \
        qx::string sFormat("[%s] ");                                       \
        sFormat += format;                                                 \
        QX_LOG_C(category, qx::log_level::critical, sFormat.c_str(), #condition, ##__VA_ARGS__)
#endif

#ifndef QX_ASSERT_DEBUG_BREAK
    #if QX_DEBUG || QX_REL_WITH_DEBUG_INFO
        #define QX_ASSERT_DEBUG_BREAK QX_DEBUG_BREAK
    #else
        #define QX_ASSERT_DEBUG_BREAK QX_EMPTY_MACRO
    #endif
#endif

#ifndef QX_ASSERT_AFTER_DEBUG_BREAK
    #define QX_ASSERT_AFTER_DEBUG_BREAK(condition, category, format, ...) std::terminate()
#endif

// ------------------------------- common macros -------------------------------

#define _QX_ASSERT_CF(before_debug_break, debug_break, after_debug_break, condition, category, format, ...) \
    [&]()                                                                                                   \
    {                                                                                                       \
        if (!(condition)) [[unlikely]]                                                                      \
        {                                                                                                   \
            before_debug_break(condition, category, format, ##__VA_ARGS__);                                 \
            debug_break;                                                                                    \
            after_debug_break(condition, category, format, ##__VA_ARGS__);                                  \
            return false;                                                                                   \
        }                                                                                                   \
        else                                                                                                \
        {                                                                                                   \
            return true;                                                                                    \
        }                                                                                                   \
    }()

#define _QX_ASSERT_NO_ENTRY(before_debug_break, debug_break, after_debug_break, category, format, ...) \
    _QX_ASSERT_CF(before_debug_break, debug_break, after_debug_break, false, category, format, ##__VA_ARGS__)

#define _QX_ASSERT_CONTINUE(before_debug_break, debug_break, after_debug_break, condition, category, format, ...) \
    if (!_QX_ASSERT_CF(                                                                                           \
            before_debug_break,                                                                                   \
            debug_break,                                                                                          \
            after_debug_break,                                                                                    \
            condition,                                                                                            \
            category,                                                                                             \
            format,                                                                                               \
            ##__VA_ARGS__)) [[unlikely]]                                                                          \
        continue;                                                                                                 \
    else                                                                                                          \
        QX_EMPTY_MACRO

#define _QX_ASSERT_BREAK(before_debug_break, debug_break, after_debug_break, condition, category, format, ...) \
    if (!_QX_ASSERT_CF(                                                                                        \
            before_debug_break,                                                                                \
            debug_break,                                                                                       \
            after_debug_break,                                                                                 \
            condition,                                                                                         \
            category,                                                                                          \
            format,                                                                                            \
            ##__VA_ARGS__)) [[unlikely]]                                                                       \
        break;                                                                                                 \
    else                                                                                                       \
        QX_EMPTY_MACRO

#define _QX_ASSERT_RETURN(                                                                                            \
    before_debug_break,                                                                                               \
    debug_break,                                                                                                      \
    after_debug_break,                                                                                                \
    return_keyword,                                                                                                   \
    condition,                                                                                                        \
    category,                                                                                                         \
    string,                                                                                                           \
    ...)                                                                                                              \
    if (!_QX_ASSERT_CF(before_debug_break, debug_break, after_debug_break, condition, category, string)) [[unlikely]] \
        return_keyword __VA_ARGS__;                                                                                   \
    else                                                                                                              \
        QX_EMPTY_MACRO

// -------------------------------- user macros --------------------------------

// clang-format off

/*
    ASSERT macros generate fatal failures and abort the program execution
*/

// verifies that condition is true (category and format string)
#define QX_ASSERT_CF(condition, category, format, ...)          _QX_ASSERT_CF(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, condition, category, format, ##__VA_ARGS__)
// verifies that condition is true (format string)
#define QX_ASSERT_F(condition, format, ...)                     _QX_ASSERT_CF(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, condition, CatAssert, format, ##__VA_ARGS__)
// verifies that condition is true (category)
#define QX_ASSERT_C(condition, category)                        _QX_ASSERT_CF(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, condition, category, "")
// verifies that condition is true
#define QX_ASSERT(condition)                                    _QX_ASSERT_CF(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, condition, CatAssert, "")

// fails unconditionally if this code should not be executed (category and format string)
#define QX_ASSERT_NO_ENTRY_CF(category, format, ...)            _QX_ASSERT_NO_ENTRY(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, category, format, ##__VA_ARGS__)
// fails unconditionally if this code should not be executed (format string)
#define QX_ASSERT_NO_ENTRY_F(format, ...)                       _QX_ASSERT_NO_ENTRY(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, CatAssert, format, ##__VA_ARGS__)
// fails unconditionally if this code should not be executed (category)
#define QX_ASSERT_NO_ENTRY_C(category)                          _QX_ASSERT_NO_ENTRY(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, category, "")
// fails unconditionally if this code should not be executed
#define QX_ASSERT_NO_ENTRY()                                    _QX_ASSERT_NO_ENTRY(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, CatAssert, "No entry")

/*
    EXPECT macros generate nonfatal failures and allow to continue running
*/

// verifies that condition is true (category and format string)
#define QX_EXPECT_CF(condition, category, format, ...)          _QX_ASSERT_CF(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, category, format, ##__VA_ARGS__)
// verifies that condition is true (format string)
#define QX_EXPECT_F(condition, format, ...)                     _QX_ASSERT_CF(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, CatAssert, format, ##__VA_ARGS__)
// verifies that condition is true (category)
#define QX_EXPECT_C(condition, category)                        _QX_ASSERT_CF(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, category, "")
// verifies that condition is true
#define QX_EXPECT(condition)                                    _QX_ASSERT_CF(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, CatAssert, "")

// fails unconditionally if this code should not be executed (category and format string)
#define QX_EXPECT_NO_ENTRY_CF(category, format, ...)            _QX_ASSERT_NO_ENTRY(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, category, format, ##__VA_ARGS__)
// fails unconditionally if this code should not be executed (format string)
#define QX_EXPECT_NO_ENTRY_F(format, ...)                       _QX_ASSERT_NO_ENTRY(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, CatAssert, format, ##__VA_ARGS__)
// fails unconditionally if this code should not be executed (category)
#define QX_EXPECT_NO_ENTRY_C(category)                          _QX_ASSERT_NO_ENTRY(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, category, "")
// fails unconditionally if this code should not be executed
#define QX_EXPECT_NO_ENTRY()                                    _QX_ASSERT_NO_ENTRY(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, CatAssert, "No entry")

// verifies that condition is true and continue loop if false (category and format string)
#define QX_EXPECT_CONTINUE_CF(condition, category, format, ...) _QX_ASSERT_CONTINUE(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, category, format, ##__VA_ARGS__)
// verifies that condition is true and continue loop if false (format string)
#define QX_EXPECT_CONTINUE_F(condition, format, ...)            _QX_ASSERT_CONTINUE(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, CatAssert, format, ##__VA_ARGS__)
// verifies that condition is true and continue loop if false (category)
#define QX_EXPECT_CONTINUE_C(condition, category)               _QX_ASSERT_CONTINUE(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, category, "")
// verifies that condition is true and continue loop if false
#define QX_EXPECT_CONTINUE(condition)                           _QX_ASSERT_CONTINUE(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, CatAssert, "")

// verifies that condition is true and break loop if false (category and format string)
#define QX_EXPECT_BREAK_CF(condition, category, format, ...)    _QX_ASSERT_BREAK(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, category, format, ##__VA_ARGS__)
// verifies that condition is true and break loop if false (format string)
#define QX_EXPECT_BREAK_F(condition, format, ...)               _QX_ASSERT_BREAK(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, CatAssert, format, ##__VA_ARGS__)
// verifies that condition is true and break loop if false (category)
#define QX_EXPECT_BREAK_C(condition, category)                  _QX_ASSERT_BREAK(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, category, "")
// verifies that condition is true and break loop if false
#define QX_EXPECT_BREAK(condition)                              _QX_ASSERT_BREAK(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, condition, CatAssert, "")

/*
    In the following macros, the arguments are the return value, not the arguments for formatting
*/

// verifies that condition is true and "return ..." if false (category and string without formatting)
#define QX_EXPECT_RETURN_CF(condition, category, string, ...)   _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, return, condition, category, string, ##__VA_ARGS__)
// verifies that condition is true and "return ..." if false (string without formatting)
#define QX_EXPECT_RETURN_F(condition, string, ...)              _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, return, condition, CatAssert, string, ##__VA_ARGS__)
// verifies that condition is true and "return ..." if false (category)
#define QX_EXPECT_RETURN_C(condition, category, ...)            _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, return, condition, category, "", ##__VA_ARGS__)
// verifies that condition is true and "return ..." if false
#define QX_EXPECT_RETURN(condition, ...)                        _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, return, condition, CatAssert, "", ##__VA_ARGS__)

// verifies that condition is true and "co_return ..." if false (category and string without formatting)
#define QX_EXPECT_CO_RETURN_CF(condition, category, string, ...)_QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, co_return, condition, category, string, ##__VA_ARGS__)
// verifies that condition is true and "co_return ..." if false (string without formatting)
#define QX_EXPECT_CO_RETURN_F(condition, string, ...)           _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, co_return, condition, CatAssert, string, ##__VA_ARGS__)
// verifies that condition is true and "co_return ..." if false (category)
#define QX_EXPECT_CO_RETURN_C(condition, category, ...)         _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, co_return, condition, category, "", ##__VA_ARGS__)
// verifies that condition is true and "co_return ..." if false
#define QX_EXPECT_CO_RETURN(condition, ...)                     _QX_ASSERT_RETURN(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, co_return, condition, CatAssert, "", ##__VA_ARGS__)

// clang-format on
