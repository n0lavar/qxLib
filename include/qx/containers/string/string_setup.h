/**

    @file      string_setup.h
    @author    Khrapov
    @date      10.06.2023
    @copyright (c) Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/macros/config.h>
#include <qx/macros/suppress_warnings.h>
#include <qx/meta/tuple_utils.h>


#define QX_CHAR_T_CHAR    0
#define QX_CHAR_T_WCHAR_T 1

#ifndef QX_CONF_CHAR
    #define QX_CONF_CHAR QX_CHAR_T_WCHAR_T
#endif


#define QX_FMT_LIB_FMT 0
#define QX_FMT_LIB_STD 1

#ifndef QX_CONF_FMT_LIB
    #if __has_include("fmt/format.h")
        #define QX_CONF_FMT_LIB QX_FMT_LIB_FMT
    #else
        #define QX_CONF_FMT_LIB QX_FMT_LIB_STD
    #endif
#endif


#define QX_ALL_CHAR_TYPES char, wchar_t

namespace qx::details
{

using all_char_types = std::tuple<QX_ALL_CHAR_TYPES>;

}


#if QX_CONF_CHAR == QX_CHAR_T_CHAR
    #define QX_CHAR_TYPE char
    #define _QXT(quote)  quote
#elif QX_CONF_CHAR == QX_CHAR_T_WCHAR_T
    #define QX_CHAR_TYPE wchar_t
    #define _QXT(quote)  L##quote

    #if !defined(QX_CONF_UNICODE_MACRO)
        #define QX_CONF_UNICODE_MACRO 1
    #endif

    #if QX_CONF_UNICODE_MACRO && QX_WIN
        #define UNICODE
    #endif
#else
    #error Unsupported char type
#endif

#define QXT(quote) _QXT(quote)

namespace qx
{

using char_type            = QX_CHAR_TYPE;
using forbidden_char_types = tuple_utils::remove_t<details::all_char_types, std::tuple<char_type>>;

} // namespace qx

#if QX_CONF_FMT_LIB == QX_FMT_LIB_FMT
QX_PUSH_SUPPRESS_ALL_WARNINGS();
    #define FMT_UNICODE     0
    #define FMT_HEADER_ONLY 1
    #include "fmt/format.h"
    #include "fmt/xchar.h"
QX_POP_SUPPRESS_WARNINGS();
    #define QX_FMT_NS fmt
    #define _QX_FMT_DISABLE_RANGE_FORMATTING(T)                                      \
        template<class char_t>                                                       \
        struct fmt::range_format_kind<T, char_t>                                     \
            : std::integral_constant<fmt::range_format, fmt::range_format::disabled> \
        {                                                                            \
        }
    #define _QX_FMT_DISABLE_TUPLE_FORMATTING(T)                       \
        template<class char_t>                                        \
        struct fmt::is_tuple_formattable<T, char_t> : std::false_type \
        {                                                             \
        }
#elif QX_CONF_FMT_LIB == QX_FMT_LIB_STD
    #include <format>
    #define QX_FMT_NS std
    #define _QX_FMT_DISABLE_RANGE_FORMATTING(T) \
        template<>                              \
        inline constexpr std::range_format std::format_kind<T> = std::range_format::disabled
    #define _QX_FMT_DISABLE_TUPLE_FORMATTING(T)
#else
    #error No fmt lib selected
#endif

/**
    @brief   Disable built-in range formatting for a type
    @details If T supports range formatting, this macro disables it.
             This is useful for types that are ranges but should not be formatted as such.
    @param   T - type to disable range formatting for
**/
#define QX_FMT_DISABLE_RANGE_FORMATTING(T) _QX_FMT_DISABLE_RANGE_FORMATTING(T)

/**
    @brief   Disable built-in tuple formatting for a type
    @details If T supports tuple formatting, this macro disables it.
             This is useful for types that are tuples but should not be formatted as such.
    @param   T - type to disable tuple formatting for
**/
#define QX_FMT_DISABLE_TUPLE_FORMATTING(T) _QX_FMT_DISABLE_TUPLE_FORMATTING(T)
