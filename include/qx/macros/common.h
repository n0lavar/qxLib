/**

    @file      common.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_setup.h>
#include <qx/meta/qualifiers.h>

#include <qx/macros/common.inl>

/**
    @def     QX_EMPTY_MACRO
    @brief   Placeholder for disabled macros
    @details Has no effect and work correctly with "if else"
             You can use it in the end of a macro to enforce user to add ; after it
**/
#define QX_EMPTY_MACRO static_assert(true)

/**
    @brief Concatenates two preprocessor tokens, performing macro expansion on them first
**/
#define QX_JOIN(symbol1, symbol2) _QX_DO_JOIN(symbol1, symbol2)

/**
    @brief Same as __LINE__, but fixes some problems when using it in constexpr context
**/
#define QX_LINE int(QX_JOIN(__LINE__, U))

/**
    @def   QX_SHORT_FILE
    @brief Cuts full absolute path to the file name only
           ex: "C:\folder1\folder2\file.h"  =>  "file.h"
**/
#define QX_SHORT_FILE qx::details::last_slash(QXT(__FILE__))

/**
    @def     QX_CONST_CAST_THIS
    @brief   This macro is made for situations where you have a const method, and you need exactly the same method but non-const
    @warning You can also use it in vice versa situations, but be careful as it will break your const guarantees

    @code
    int foo() const
    {
        // some complicated stuff
    }
    int foo()
    {
        QX_CONST_CAST_THIS()->foo();
    }
    @endcode 
**/
#define QX_CONST_CAST_THIS() const_cast<qx::switch_const_t<std::remove_pointer_t<decltype(this)>>*>(this)

/**
    @def   QX_CALL_BEFORE_MAIN
    @brief Calls this lambda before the main invocation
    @note  This function must be in an object file, that is actually linked to your exe

    @code
    QX_CALL_BEFORE_MAIN = []()
        {
        };
    @endcode 
**/
#define QX_CALL_BEFORE_MAIN inline volatile qx::details::call_before_main_invoker QX_LINE_NAME(_stubCallBeforeMain)

/**
    @brief Start a block with compiling optimisations disabled.
           Must be outside of functions and have an appropriate QX_ENABLE_OPTIMIZATIONS().
**/
#define QX_DISABLE_OPTIMIZATIONS() _QX_DISABLE_OPTIMIZATIONS()

/**
    @brief End a block with compiling optimisations disabled.
**/
#define QX_ENABLE_OPTIMIZATIONS() _QX_ENABLE_OPTIMIZATIONS()

/**
    @brief Make this function forcefully inlined (except for QX_DEBUG build)
**/
#define QX_FORCE_INLINE _QX_FORCE_INLINE

/**
    @brief   Add __VA_ARGS__ count to the preprocessor prefix
    @details It supports up to 32 arguments, ranging from 0 (empty parentheses).
    @param   prefix - preprocessor prefix
    @param   ...    - va args to count
    @code
    QX_APPEND_VA_ARG_COUNT(foo_, 1, 1, 1); // -> foo_3
    @endcode
**/
#define QX_APPEND_VA_ARG_COUNT(prefix, ...) _QX_APPEND_VA_ARG_COUNT(prefix, ##__VA_ARGS__)

/**
    @brief   Get number of va args
    @details It supports up to 32 arguments, ranging from 0 (empty parentheses).
    @param   ... - va args to count
    @code
    QX_VA_ARG_COUNT(1, 1, 1); // -> 3
    @endcode 
**/
#define QX_VA_ARG_COUNT(...) QX_APPEND_VA_ARG_COUNT(, ##__VA_ARGS__)

/**
    @brief Forces an extra macro expansion step so that a macro result is fully resolved before being used as a function-like macro.
**/
#define QX_EXPAND(x) x
