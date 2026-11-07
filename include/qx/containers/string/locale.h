/**

    @file      locale.h
    @author    Khrapov
    @date      06.11.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <locale>

/**
    @brief Enables the explicit CRT locale conversion path for Windows libc++.
**/
#ifndef QX_STRING_USE_CRT_LOCALE
    #if defined(_WIN32) && defined(_LIBCPP_VERSION)
        #define QX_STRING_USE_CRT_LOCALE 1
    #else
        #define QX_STRING_USE_CRT_LOCALE 0
    #endif
#endif

#if QX_STRING_USE_CRT_LOCALE
    #include <climits>
    #include <cstdio>
    #include <cstdlib>
    #include <cwchar>
    #include <memory>
    #include <type_traits>
    #include <utility>
#endif

namespace qx
{

/**
    @brief   Set the locale used by string converters by default.
    @details Call only when no other thread is accessing the locale or its facet.
    @param   locale - locale whose character facet is used for conversion
**/
void set_locale(const std::locale& locale);

/**
    @brief  Get the default locale used by string converters.
    @return - locale retained until the next call to set_locale
**/
const std::locale& get_locale();

/**
    @brief  Get the cached character conversion facet for the default locale.
    @return - facet retained until the next call to set_locale
**/
const std::ctype<wchar_t>& get_locale_facet();

} // namespace qx


#include <qx/containers/string/locale.inl>
