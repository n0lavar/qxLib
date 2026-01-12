/**

    @file      string_converters.h
    @author    Khrapov
    @date      24.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/containers/string/string.h>
#include <qx/containers/string/string_literal.h>
#include <qx/containers/string/string_view.h>
#include <qx/internal/perf_scope.h>
#include <qx/windows.h>

#include <codecvt>
#include <locale>

QX_DEFINE_CATEGORY(CatQxConverters);

namespace qx
{

/**
    @brief  convert cstring to wstring
    @param  stringView - char string view
    @param  locale     - locale to use
    @retval            - wchar_t string
**/
wstring to_wstring(cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert wstring to wstring (stub)
    @param  stringView - wchar_t string view
    @param  locale     - locale to use
    @retval            - wchar_t string
**/
wstring_view to_wstring(wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief   Convert wstring to cstring
    @details '?' is a default character
    @param   stringView - wchar_t string view
    @param   locale     - locale to use
    @retval             - char string
**/
cstring to_cstring(wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert string to string (stub)
    @param  stringView - char string view
    @param  locale     - locale to use
    @retval            - char string
**/
cstring_view to_cstring(cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert a char string to common string type
    @param  stringView - char string
    @param  locale     - locale to use
    @retval            - common string type
**/
string to_string(cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert a wchar_t string to common string type
    @param  stringView - wchar_t string
    @param  locale     - locale to use
    @retval            - common string type
**/
string to_string(wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert const char* representing UTF8 to wstring
    @param  pszUtf8 - UTF8 string
    @retval         - wstring value
**/
string utf8_to_string(cstring_view pszUtf8);

/**
    @brief  Convert a constexpr string literal to the wider or equal char type string view
    @tparam char_t    - target string view type
    @tparam sLiteral  - constexpr string literal
    @retval           - constexpr string view of a wider or equal char type
**/
template<class char_t, string_literal sLiteral>
constexpr basic_string_view<char_t> convert_string_literal();

} // namespace qx

#include <qx/containers/string/string_converters.inl>
