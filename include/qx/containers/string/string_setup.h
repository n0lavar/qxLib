/**

    @file      string_setup.h
    @brief     Types and macros used for a work with a defaul selected char type
    @author    Khrapov
    @date      10.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#if !defined(QX_CONF_USE_CHAR) && !defined(QX_CONF_USE_WCHAR)
    #define QX_CONF_USE_WCHAR
#endif

#ifdef QX_CONF_USE_CHAR

    #define QX_CHAR_TYPE    char
    #define _QX_TEXT(quote) quote

#elif defined(QX_CONF_USE_WCHAR)

    #define QX_CHAR_TYPE    wchar_t
    #define _QX_TEXT(quote) L##quote

#endif

#define QX_TEXT(quote) _QX_TEXT(quote)

namespace qx
{

using char_type = QX_CHAR_TYPE;

} // namespace qx
