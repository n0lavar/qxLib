/**

    @file      string_converters.h
    @brief     Contains string converters
    @author    Khrapov
    @date      24.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>

namespace qx
{

/**
    @brief  convert string to wstring
    @param  str    - char string view
    @param  locale - locale to use
    @retval        - wchar_t string
**/
inline wstring to_wstring(
    std::string_view   str,
    const std::locale& locale = std::locale())
{
    std::vector<wchar_t> buf(str.size());
    std::use_facet<std::ctype<wchar_t>>(locale).widen(
        str.data(),
        str.data() + str.size(),
        buf.data());

    return wstring(buf.data(), buf.size());
}

/**
    @brief   Convert wstring to string
    @details '?' is default character
    @param   str    - wchar_t string view
    @param   locale - locale to use
    @retval         - char string
**/
inline string to_string(
    std::wstring_view  str,
    const std::locale& locale = std::locale())
{
    std::vector<char> buf(str.size());
    std::use_facet<std::ctype<wchar_t>>(locale)
        .narrow(str.data(), str.data() + str.size(), '?', buf.data());
    return string(buf.data(), buf.size());
}

} // namespace qx
