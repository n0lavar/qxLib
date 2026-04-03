/**

    @file      string_setup.h
    @author    Khrapov
    @date      10.06.2023
    @copyright � Nick Khrapov, 2023. All right reserved.

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
#elif QX_CONF_FMT_LIB == QX_FMT_LIB_STD
    #include <format>
    #define QX_FMT_NS std
#else
    #error No fmt lib selected
#endif
