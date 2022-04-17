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

/**
    @brief   Convert string_view to the null terminated chars array
    @details Some libraries or even c++ types can't deal with std::string_view
             (for ex. std::ifstream). This function allows to reduce number of
             allocations, but still leads to overhead due to chars copying
    @tparam  value_type - string value type
    @param   stringView - string view to convert
    @retval             - null terminated string with stringView convent
                          valid until the next to_char_pointer call
**/
template<typename value_type>
inline const value_type* to_char_pointer(
    std::basic_string_view<value_type> stringView)
{
    thread_local basic_string<char_traits<value_type>> sBuffer;
    sBuffer = stringView;
    return sBuffer.c_str();
}

} // namespace qx
