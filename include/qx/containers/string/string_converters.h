/**

    @file      string_converters.h
    @brief     Contains string converters
    @author    Khrapov
    @date      24.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/containers/string/string_view.h>

#include <codecvt>
#include <locale>

namespace qx
{

/**
    @brief  convert cstring to wstring
    @param  stringView - char string view
    @param  locale     - locale to use
    @retval            - wchar_t string
**/
inline wstring to_wstring(cstring_view stringView, const std::locale& locale = std::locale())
{
    std::vector<wchar_t> buf(stringView.size());
    std::use_facet<std::ctype<wchar_t>>(locale).widen(
        stringView.data(),
        stringView.data() + stringView.size(),
        buf.data());

    return wstring(buf.data(), buf.size());
}

/**
    @brief  Convert wstring to wstring (stub)
    @param  stringView - wchar_t string view
    @param  locale     - locale to use
    @retval            - wchar_t string
**/
inline wstring to_wstring(wstring_view stringView, const std::locale& locale = std::locale())
{
    return stringView;
}

/**
    @brief   Convert wstring to cstring
    @details '?' is a default character
    @param   stringView - wchar_t string view
    @param   locale     - locale to use
    @retval             - char string
**/
inline cstring to_cstring(wstring_view stringView, const std::locale& locale = std::locale())
{
    std::vector<char> buf(stringView.size());
    std::use_facet<std::ctype<wchar_t>>(locale)
        .narrow(stringView.data(), stringView.data() + stringView.size(), '?', buf.data());
    return cstring(buf.data(), buf.size());
}

/**
    @brief  Convert string to string (stub)
    @param  stringView - char string view
    @param  locale     - locale to use
    @retval            - char string
**/
inline cstring to_cstring(cstring_view stringView, const std::locale& locale = std::locale())
{
    return stringView;
}

/**
    @brief  Convert a char string to common string type
    @param  stringView - char string
    @param  locale     - locale to use
    @retval            - common string type
**/
inline string to_string(cstring_view stringView, const std::locale& locale = std::locale())
{
    if constexpr (std::is_same_v<char_type, char>)
        return stringView;
    else if constexpr (std::is_same_v<char_type, wchar_t>)
        return to_wstring(stringView, locale);
}

/**
    @brief  Convert a wchar_t string to common string type
    @param  stringView - wchar_t string
    @param  locale     - locale to use
    @retval            - common string type
**/
inline string to_string(wstring_view stringView, const std::locale& locale = std::locale())
{
    if constexpr (std::is_same_v<char_type, char>)
        return to_cstring(stringView, locale);
    else if constexpr (std::is_same_v<char_type, wchar_t>)
        return stringView;
}

/**
    @brief  Convert const char* representing UTF8 to wstring
    @param  pszUtf8 - UTF8 string
    @retval         - wstring value
**/
inline wstring utf8_to_wstring(const char* pszUtf8)
{
    QX_PUSH_SUPPRESS_ALL_WARNINGS();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(pszUtf8);
    QX_POP_SUPPRESS_WARNINGS();
}

} // namespace qx
