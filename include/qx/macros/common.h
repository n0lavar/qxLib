/**

    @file      common.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_setup.h>
#include <qx/meta/qualifiers.h>

/**
    @def     QX_EMPTY_MACRO
    @brief   Placeholder for disabled macros
    @details Has no effect and work correctly with "if else"
             You can use it in the end of a macro to enforce user to add ; after it
**/
#define QX_EMPTY_MACRO static_assert(true)

/**
    @def   QX_STRINGIFY
    @brief Macro can be used to turn any text in your code into a string,
           but only the exact text between the parentheses
           There are no variable dereferencing or macro substitutions or any other sort of thing done.
    @param name - name to convert to the string
**/
#define QX_STRINGIFY(name) #name

#define _QX_JOIN(symbol1, symbol2)    _QX_DO_JOIN(symbol1, symbol2)
#define _QX_DO_JOIN(symbol1, symbol2) symbol1##symbol2

/**
    @def   QX_LINE_NAME
    @brief Do magic! Creates a unique name using the line number
    @param prefix - name prefix
**/
#define QX_LINE_NAME(prefix) _QX_JOIN(prefix, __LINE__)

/**
    @brief Same as __LINE__, but fixes some problems when using it in constexpr context
**/
#define QX_LINE int(_QX_JOIN(__LINE__, U))


namespace qx::details
{

constexpr const char_type* last_slash(const char_type* str)
{
    const char_type* pszLastSlash = str;
    while (str && *str != QX_TEXT('\0'))
    {
        if (*str == QX_TEXT('\\') || *str == QX_TEXT('/'))
            pszLastSlash = str;

        ++str;
    }
    return pszLastSlash + 1;
}

} // namespace qx::details

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

namespace qx::details
{

template<class lambda_type>
class call_before_main_invoker
{
public:
    call_before_main_invoker(lambda_type lambda) : m_Lambda(std::move(lambda))
    {
        m_Lambda();
    }

private:
    lambda_type m_Lambda;
};

} // namespace qx::details

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

#if QX_MSVC
    #define QX_DISABLE_OPTIMIZATIONS() __pragma(optimize("", off))
    #define QX_ENABLE_OPTIMIZATIONS()  __pragma(optimize("", on))
#else
    #define QX_DISABLE_OPTIMIZATIONS()
    #define QX_ENABLE_OPTIMIZATIONS()
#endif
