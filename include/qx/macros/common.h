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
    @brief Same as __LINE__, but fixes some problems when using it in constexpr context
**/
#define QX_LINE int(_QX_JOIN(__LINE__, U))

/**
    @def   QX_SHORT_FILE
    @brief Cuts full absolute path to the file name only
           ex: "C:\folder1\foler2\file.h"  =>  "file.h"
**/
#define QX_SHORT_FILE qx::details::last_slash(QX_TEXT(__FILE__))

/**
    @def   QX_SINGLE_ARGUMENT
    @brief Let macro param containing commas work fine
           "#define FOO(type, name) type name"
           FOO(QX_SINGLE_ARGUMENT(std::map<int, int>), map_var);
    @param ... - param containing commas
**/
#define QX_SINGLE_ARGUMENT(...) __VA_ARGS__

/**
    @def     QX_CONST_CAST_THIS
    @brief   This macro is made for situations where you have a const method and you need exactly the same method but non-const
    @warning You can also use it in vice-versa situations, but be careful as it will break your const guarantees

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
