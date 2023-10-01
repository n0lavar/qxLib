/**

    @file      string_setup.h
    @author    Khrapov
    @date      10.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/meta/tuple_utils.h>

#if !defined(QX_CONF_USE_CHAR) && !defined(QX_CONF_USE_WCHAR)
    #define QX_CONF_USE_WCHAR
#endif

namespace qx::details
{

using all_char_types = std::tuple<char, wchar_t>;

}


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

using char_type            = QX_CHAR_TYPE;
using forbidden_char_types = tuple::remove_t<details::all_char_types, std::tuple<char_type>>;

} // namespace qx
