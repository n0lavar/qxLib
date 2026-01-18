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
    @brief convert cstring to wstring
    @param out        - output wchar_t string
    @param stringView - char string view
    @param locale     - locale to use
**/
void to_wstring(wstring& out, cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  convert cstring to wstring
    @param  stringView - char string view
    @param  locale     - locale to use
    @retval            - wchar_t string
**/
[[nodiscard]] wstring to_wstring(cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief Convert wstring to wstring
    @param out        - output wchar_t string
    @param stringView - wchar_t string view
    @param locale     - locale to use
**/
void to_wstring(wstring& out, wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert wstring to wstring (stub)
    @param  stringView - wchar_t string view
    @param  locale     - locale to use
    @retval            - wchar_t string
**/
[[nodiscard]] wstring_view to_wstring(wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief   Convert wstring to cstring
    @details '?' is a default character
    @param   out        - output char string
    @param   stringView - wchar_t string view
    @param   locale     - locale to use
**/
void to_cstring(cstring& out, wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief   Convert wstring to cstring
    @details '?' is a default character
    @param   stringView - wchar_t string view
    @param   locale     - locale to use
    @retval             - char string
**/
[[nodiscard]] cstring to_cstring(wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief Convert string to string
    @param out        - output char string
    @param stringView - char string view
    @param locale     - locale to use
**/
void to_cstring(cstring& out, cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert string to string (stub)
    @param  stringView - char string view
    @param  locale     - locale to use
    @retval            - char string
**/
[[nodiscard]] cstring_view to_cstring(cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief Convert a char string to common string type
    @param out        - output common string
    @param stringView - char string
    @param locale     - locale to use
**/
void to_string(string& out, cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert a char string to common string type
    @param  stringView - char string
    @param  locale     - locale to use
    @retval            - common string
**/
[[nodiscard]] string to_string(cstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief Convert a wchar_t string to common string type
    @param out        - output common string
    @param stringView - wchar_t string
    @param locale     - locale to use
**/
void to_string(string& out, wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief  Convert a wchar_t string to common string type
    @param  stringView - wchar_t string
    @param  locale     - locale to use
    @retval            - common string
**/
[[nodiscard]] string to_string(wstring_view stringView, const std::locale& locale = std::locale());

/**
    @brief Convert const char* representing UTF8 to wstring
    @param out     - output wchar_t string
    @param pszUtf8 - UTF8 string
**/
void utf8_to_string(string& out, cstring_view pszUtf8);

/**
    @brief  Convert const char* representing UTF8 to wstring
    @param  pszUtf8 - UTF8 string
    @retval         - wchar_t string
**/
[[nodiscard]] string utf8_to_string(cstring_view pszUtf8);

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
