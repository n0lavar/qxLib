/**

    @file      asserts.h
    @author    Khrapov
    @date      27.12.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

    @section qx_assert_table Assert Types Comparison Table

    | Assertion type | Crash on failure | Remains in shipping (can have side effects) | Returns condition | Description |
    |:--------------:|:----------------:|:-------------------------------------------:|:-----------------:|-------------|
    | QX_ASSERT      |         +        |                     -                       |          -        | Fast fail, similar to `assert()` |
    | QX_VERIFY      |         +        |                     +                       |          -        | Critical places: allocation errors, security checks, encryption, anti-cheat, etc. |
    | QX_EXPECT      |         -        |                     +                       |          +        | Defensive programming |
    | QX_ENSURE      |         -        |                     -                       |          -        | Possibly heavy checks that will not stay in a fast build |

**/
#pragma once

#include <qx/asserts/asserts_manager.h>

#include <qx/asserts/asserts.inl>

/**
    @brief Use this as a condition in any macro above to indicate that this part of your code must never be executed
**/
#define QX_NO_ENTRY !"No entry"

/**
    @brief Use this as a condition in any macro above to indicate that this part of your code is not ready yet
**/
#define QX_NOT_IMPLEMENTED !"Not implemented"

/**
    @brief   Verifies that the condition is true
    @details QX_ASSERT macros generate fatal failures and disappear in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_ASSERT_C(condition, category, ...) _QX_ASSERT_C(condition, category, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_ASSERT macros generate fatal failures and disappear in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_ASSERT(condition, ...) QX_ASSERT_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_VERIFY macros generate fatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_VERIFY_C(condition, category, ...) \
    _QX_COMMON_ASSERT(                        \
        condition,                            \
        category,                             \
        qx::assert_type::verify,              \
        _QX_ASSERT_AFTER_DEBUG_BREAK_FATAL,   \
        void,                                 \
        ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_VERIFY macros generate fatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_VERIFY(condition, ...) QX_VERIFY_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
    @retval            - condition
**/
#define QX_EXPECT_C(condition, category, ...)   \
    _QX_COMMON_ASSERT(                          \
        condition,                              \
        category,                               \
        qx::assert_type::expect,                \
        _QX_ASSERT_AFTER_DEBUG_BREAK_NON_FATAL, \
        bool,                                   \
        ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
    @retval            - condition
**/
#define QX_EXPECT(condition, ...) QX_EXPECT_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls continue; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_CONTINUE_C(condition, category, ...) _QX_EXPECT_ACTION(condition, category, continue, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls continue; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_CONTINUE(condition, ...) QX_EXPECT_CONTINUE_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls break; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_BREAK_C(condition, category, ...) _QX_EXPECT_ACTION(condition, category, break, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls break; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_BREAK(condition, ...) QX_EXPECT_BREAK_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls return; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_RETURN_C(condition, category, ...) _QX_EXPECT_ACTION(condition, category, return, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls return; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_RETURN(condition, ...) QX_EXPECT_RETURN_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls return return_value; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition    - a condition to check. if false, assert fails
    @param   category     - a category to use for logging and reporting
    @param   return_value - a value to return in case of failure
    @param   ...          - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_RETURN_CT(condition, category, return_value, ...) \
    _QX_EXPECT_ACTION(condition, category, return return_value, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls return return_value; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition    - a condition to check. if false, assert fails
    @param   return_value - a value to return in case of failure
    @param   ...          - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_RETURN_T(condition, return_value, ...) \
    QX_EXPECT_RETURN_CT(condition, QX_GET_FILE_CATEGORY(), return_value, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls co_return; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_CO_RETURN_C(condition, category, ...) _QX_EXPECT_ACTION(condition, category, co_return, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls co_return; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_CO_RETURN(condition, ...) QX_EXPECT_CO_RETURN_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls co_return return_value; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition    - a condition to check. if false, assert fails
    @param   category     - a category to use for logging and reporting
    @param   return_value - a value to return in case of failure
    @param   ...          - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_CO_RETURN_CT(condition, category, return_value, ...) \
    _QX_EXPECT_ACTION(condition, category, co_return return_value, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true and calls co_return return_value; otherwise
    @details QX_EXPECT macros generate nonfatal failures and remain in shipping. See @ref qx_assert_table for details.
    @param   condition    - a condition to check. if false, assert fails
    @param   return_value - a value to return in case of failure
    @param   ...          - optional user message and its format args. the format string should be without QXT
**/
#define QX_EXPECT_CO_RETURN_T(condition, return_value, ...) \
    QX_EXPECT_CO_RETURN_CT(condition, QX_GET_FILE_CATEGORY(), return_value, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_ENSURE macros generate nonfatal failures and disappear in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   category  - a category to use for logging and reporting
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_ENSURE_C(condition, category, ...) _QX_ENSURE_C(condition, category, ##__VA_ARGS__)

/**
    @brief   Verifies that the condition is true
    @details QX_ENSURE macros generate nonfatal failures and disappear in shipping. See @ref qx_assert_table for details.
    @param   condition - a condition to check. if false, assert fails
    @param   ...       - optional user message and its format args. the format string should be without QXT
**/
#define QX_ENSURE(condition, ...) QX_ENSURE_C(condition, QX_GET_FILE_CATEGORY(), ##__VA_ARGS__)
