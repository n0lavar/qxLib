/**

    @file      time_string.h
    @author    Khrapov
    @date      11.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/macros/suppress_warnings.h>

#include <ctime>

namespace qx
{

/**
    @brief  Format time string to the buffer
    @tparam out_it_t        - output iterator type
    @param  it              - output iterator
    @param  chDateDelimiter - char to use as delimiter in date part
    @param  chTimeDelimiter - char to use as delimiter in time part
**/
template<class out_it_t>
inline void append_time_string(out_it_t it, char_type chDateDelimiter, char_type chTimeDelimiter) noexcept
{
    std::time_t t = std::time(nullptr);
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4996);
    std::tm* now = std::localtime(&t);
    QX_POP_SUPPRESS_WARNINGS();

    string_traits::format_traits<char_type, string_traits::usings_traits<char_type>>::format_to(
        it,
        QXT("{:02}{}{:02}{}{:04}_{:02}{}{:02}{}{:02}"),
        now->tm_mday,
        chDateDelimiter,
        now->tm_mon,
        chDateDelimiter,
        now->tm_year + 1900,
        now->tm_hour,
        chTimeDelimiter,
        now->tm_min,
        chTimeDelimiter,
        now->tm_sec);
}

} // namespace qx
