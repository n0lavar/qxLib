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

namespace qx::details
{

template<log_level eLogLevel>
void resolve_assert_proceeding(
    // macro args
    const category& fileCategory,
    string_view     svFunction,
    string_view     svFile,
    int             nLine,
    string_view     svCondition)
{
    QX_LOGGER_INSTANCE.log(eLogLevel, QX_TEXT("[{}] "), fileCategory, svFile, svFunction, nLine, svCondition);
    QX_LOGGER_INSTANCE.flush();
}

template<log_level eLogLevel>
void resolve_assert_proceeding(
    // macro args
    const category& fileCategory,
    string_view     svFunction,
    string_view     svFile,
    int             nLine,
    string_view     svCondition,
    // ... args
    const category& category)
{
    string sMessage;
    sMessage.append_format(QX_TEXT("[{}] "), svCondition);
    QX_LOGGER_INSTANCE.log(eLogLevel, sMessage, category, svFile, svFunction, nLine);
    QX_LOGGER_INSTANCE.flush();
}

template<log_level eLogLevel, class... args_t>
void resolve_assert_proceeding(
    // macro args
    const category& fileCategory,
    string_view     svFunction,
    string_view     svFile,
    int             nLine,
    string_view     svCondition,
    // ... args
    format_string<args_t...> sFormat,
    const args_t&... args)
{
    string sMessage;
    sMessage.append_format(QX_TEXT("[{}] "), svCondition);
    sMessage.append_format(sFormat, args...);
    QX_LOGGER_INSTANCE.log(eLogLevel, sMessage, fileCategory, svFile, svFunction, nLine);
    QX_LOGGER_INSTANCE.flush();
}

template<log_level eLogLevel, class... args_t>
void resolve_assert_proceeding(
    // macro args
    const category& fileCategory,
    string_view     svFunction,
    string_view     svFile,
    int             nLine,
    string_view     svCondition,
    // ... args
    const category&          category,
    format_string<args_t...> sFormat,
    const args_t&... args)
{
    string sMessage;
    sMessage.append_format(QX_TEXT("[{}] "), svCondition);
    sMessage.append_format(sFormat, args...);
    QX_LOGGER_INSTANCE.log(eLogLevel, sMessage, category, svFile, svFunction, nLine);
    QX_LOGGER_INSTANCE.flush();
}

} // namespace qx::details

// ----------------------------------- setup -----------------------------------

#ifndef QX_DEBUG_BREAK
    #define QX_DEBUG_BREAK _QX_DEBUG_BREAK
#endif

#ifndef QX_EXPECT_BEFORE_DEBUG_BREAK
    #define QX_EXPECT_BEFORE_DEBUG_BREAK(condition, ...)              \
        qx::details::resolve_assert_proceeding<qx::log_level::error>( \
            QX_FILE_CATEGORY(),                                       \
            qx::to_string(__FUNCTION__),                              \
            QX_SHORT_FILE,                                            \
            __LINE__,                                                 \
            QX_TEXT(#condition),                                      \
            ##__VA_ARGS__)
#endif

#ifndef QX_EXPECT_DEBUG_BREAK
    #if QX_DEBUG || QX_REL_WITH_DEBUG_INFO
        #define QX_EXPECT_DEBUG_BREAK QX_DEBUG_BREAK
    #else
        #define QX_EXPECT_DEBUG_BREAK QX_EMPTY_MACRO
    #endif
#endif

#ifndef QX_EXPECT_AFTER_DEBUG_BREAK
    #define QX_EXPECT_AFTER_DEBUG_BREAK(condition, ...) QX_EMPTY_MACRO
#endif

#ifndef QX_ASSERT_BEFORE_DEBUG_BREAK
    #define QX_ASSERT_BEFORE_DEBUG_BREAK(condition, ...)                 \
        qx::details::resolve_assert_proceeding<qx::log_level::critical>( \
            QX_FILE_CATEGORY(),                                          \
            qx::to_string(__FUNCTION__),                                 \
            QX_SHORT_FILE,                                               \
            __LINE__,                                                    \
            QX_TEXT(#condition),                                         \
            ##__VA_ARGS__)
#endif

#ifndef QX_ASSERT_DEBUG_BREAK
    #if QX_DEBUG || QX_REL_WITH_DEBUG_INFO
        #define QX_ASSERT_DEBUG_BREAK QX_DEBUG_BREAK
    #else
        #define QX_ASSERT_DEBUG_BREAK QX_EMPTY_MACRO
    #endif
#endif

#ifndef QX_ASSERT_AFTER_DEBUG_BREAK
    #define QX_ASSERT_AFTER_DEBUG_BREAK(condition, ...) std::terminate()
#endif

// ------------------------------- common macros -------------------------------

#define _QX_ASSERT(before_debug_break, debug_break, after_debug_break, condition, ...) \
    [&]()                                                                              \
    {                                                                                  \
        QX_PUSH_SUPPRESS_MSVC_WARNINGS(4702);                                          \
        if (!(condition)) [[unlikely]]                                                 \
        {                                                                              \
            before_debug_break(condition, ##__VA_ARGS__);                              \
            debug_break;                                                               \
            after_debug_break(condition, ##__VA_ARGS__);                               \
            return false;                                                              \
        }                                                                              \
        else                                                                           \
        {                                                                              \
            return true;                                                               \
        }                                                                              \
        QX_POP_SUPPRESS_WARNINGS();                                                    \
    }()

#define _QX_ASSERT_NO_ENTRY(before_debug_break, debug_break, after_debug_break, ...) \
    _QX_ASSERT(before_debug_break, debug_break, after_debug_break, !QX_TEXT("No entry"), ##__VA_ARGS__)

#define _QX_ASSERT_CONTINUE(before_debug_break, debug_break, after_debug_break, condition, ...)                 \
    if (!_QX_ASSERT(before_debug_break, debug_break, after_debug_break, condition, ##__VA_ARGS__)) [[unlikely]] \
        continue;                                                                                               \
    else                                                                                                        \
        QX_EMPTY_MACRO

#define _QX_ASSERT_BREAK(before_debug_break, debug_break, after_debug_break, condition, ...)                    \
    if (!_QX_ASSERT(before_debug_break, debug_break, after_debug_break, condition, ##__VA_ARGS__)) [[unlikely]] \
        break;                                                                                                  \
    else                                                                                                        \
        QX_EMPTY_MACRO

#define _QX_ASSERT_RETURN(                                                                                      \
    before_debug_break,                                                                                         \
    debug_break,                                                                                                \
    after_debug_break,                                                                                          \
    return_keyword,                                                                                             \
    condition,                                                                                                  \
    return_value,                                                                                               \
    ...)                                                                                                        \
    if (!_QX_ASSERT(before_debug_break, debug_break, after_debug_break, condition, ##__VA_ARGS__)) [[unlikely]] \
        return_keyword return_value;                                                                            \
    else                                                                                                        \
        QX_EMPTY_MACRO

// -------------------------------- user macros --------------------------------

/**
    @brief   Verifies that condition is true
    @details ASSERT macros generate fatal failures and abort the program execution
    @param   condition - condition to check. if false, assert fails
    @param   ...       - "category + format string + format arguments"
                      or "category + format string"
                      or "format string + format arguments"
                      or "format string"
                      or "category"
**/
#define QX_ASSERT(condition, ...)     \
    _QX_ASSERT(                       \
        QX_ASSERT_BEFORE_DEBUG_BREAK, \
        QX_ASSERT_DEBUG_BREAK,        \
        QX_ASSERT_AFTER_DEBUG_BREAK,  \
        condition,                    \
        ##__VA_ARGS__)

/**
    @brief   Fails unconditionally if this code should not be executed
    @details ASSERT macros generate fatal failures and abort the program execution
    @param   ...  - "category + format string + format arguments"
                 or "category + format string"
                 or "format string + format arguments"
                 or "format string"
                 or "category"
**/
#define QX_ASSERT_NO_ENTRY(...) \
    _QX_ASSERT_NO_ENTRY(QX_ASSERT_BEFORE_DEBUG_BREAK, QX_ASSERT_DEBUG_BREAK, QX_ASSERT_AFTER_DEBUG_BREAK, ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check. if false, assert fails
    @param   ...       - "category + format string + format arguments"
                      or "category + format string"
                      or "format string + format arguments"
                      or "format string"
                      or "category"
**/
#define QX_EXPECT(condition, ...)     \
    _QX_ASSERT(                       \
        QX_EXPECT_BEFORE_DEBUG_BREAK, \
        QX_EXPECT_DEBUG_BREAK,        \
        QX_EXPECT_AFTER_DEBUG_BREAK,  \
        condition,                    \
        ##__VA_ARGS__)

/**
    @brief   Fails unconditionally if this code should not be executed
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   ...  - "category + format string + format arguments"
                 or "category + format string"
                 or "format string + format arguments"
                 or "format string"
                 or "category"
**/
#define QX_EXPECT_NO_ENTRY(...) \
    _QX_ASSERT_NO_ENTRY(QX_EXPECT_BEFORE_DEBUG_BREAK, QX_EXPECT_DEBUG_BREAK, QX_EXPECT_AFTER_DEBUG_BREAK, ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and continues loop if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check. if false, assert fails
    @param   ...       - "category + format string + format arguments"
                      or "category + format string"
                      or "format string + format arguments"
                      or "format string"
                      or "category"
**/
#define QX_EXPECT_CONTINUE(condition, ...) \
    _QX_ASSERT_CONTINUE(                   \
        QX_EXPECT_BEFORE_DEBUG_BREAK,      \
        QX_EXPECT_DEBUG_BREAK,             \
        QX_EXPECT_AFTER_DEBUG_BREAK,       \
        condition,                         \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and break loop if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check. if false, assert fails
    @param   ...       - "category + format string + format arguments"
                      or "category + format string"
                      or "format string + format arguments"
                      or "format string"
                      or "category"
**/
#define QX_EXPECT_BREAK(condition, ...) \
    _QX_ASSERT_BREAK(                   \
        QX_EXPECT_BEFORE_DEBUG_BREAK,   \
        QX_EXPECT_DEBUG_BREAK,          \
        QX_EXPECT_AFTER_DEBUG_BREAK,    \
        condition,                      \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and "return return_value;" if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition    - condition to check. if false, assert fails
    @param   return_value - return value. use empty argument, if return type is void
    @param   ...          - "category + format string + format arguments"
                         or "category + format string"
                         or "format string + format arguments"
                         or "format string"
                         or "category"
**/
#define QX_EXPECT_RETURN(condition, return_value, ...) \
    _QX_ASSERT_RETURN(                                 \
        QX_EXPECT_BEFORE_DEBUG_BREAK,                  \
        QX_EXPECT_DEBUG_BREAK,                         \
        QX_EXPECT_AFTER_DEBUG_BREAK,                   \
        return,                                        \
        condition,                                     \
        return_value,                                  \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and "return;" if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check. if false, assert fails
    @param   ...       - "category + format string + format arguments"
                      or "category + format string"
                      or "format string + format arguments"
                      or "format string"
                      or "category"
**/
#define QX_EXPECT_RETURN_VOID(condition, ...) \
    _QX_ASSERT_RETURN(                        \
        QX_EXPECT_BEFORE_DEBUG_BREAK,         \
        QX_EXPECT_DEBUG_BREAK,                \
        QX_EXPECT_AFTER_DEBUG_BREAK,          \
        return,                               \
        condition,                            \
        ,                                     \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and "co_return return_value;" if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition    - condition to check. if false, assert fails
    @param   return_value - return value. use empty argument, if return type is void
    @param   ...          - "category + format string + format arguments"
                         or "category + format string"
                         or "format string + format arguments"
                         or "format string"
                         or "category"
**/
#define QX_EXPECT_CO_RETURN(condition, return_value, ...) \
    _QX_ASSERT_RETURN(                                    \
        QX_EXPECT_BEFORE_DEBUG_BREAK,                     \
        QX_EXPECT_DEBUG_BREAK,                            \
        QX_EXPECT_AFTER_DEBUG_BREAK,                      \
        co_return,                                        \
        condition,                                        \
        return_value,                                     \
        ##__VA_ARGS__)

/**
    @brief   Verifies that condition is true and "co_return;" if false
    @details EXPECT macros generate nonfatal failures and allow to continue running
    @param   condition - condition to check. if false, assert fails
    @param   ...       - "category + format string + format arguments"
                      or "category + format string"
                      or "format string + format arguments"
                      or "format string"
                      or "category"
**/
#define QX_EXPECT_CO_RETURN_VOID(condition, ...) \
    _QX_ASSERT_RETURN(                           \
        QX_EXPECT_BEFORE_DEBUG_BREAK,            \
        QX_EXPECT_DEBUG_BREAK,                   \
        QX_EXPECT_AFTER_DEBUG_BREAK,             \
        co_return,                               \
        condition,                               \
        ,                                        \
        ##__VA_ARGS__)
