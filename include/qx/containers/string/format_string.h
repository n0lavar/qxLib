/**

    @file      format_string.h
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view.h>

#include <format>

namespace qx
{

/**
    @struct basic_format_string
    @brief  std::basic_format_string wrapper that performs additional compile time checks
    @tparam char_t - char type
    @tparam args_t - template parameter pack type
**/
template<class char_t, class... args_t>
struct basic_format_string : public std::basic_format_string<char_t, args_t...>
{
    /**
        @brief  basic_format_string object constructor
        @tparam T     - string view convertible type
        @param  value - format string to check
    **/
    template<class T>
        requires std::convertible_to<const T&, qx::basic_string_view<char_t>>
    consteval basic_format_string(const T& value);

    /**
        @brief  Check braces balance and args num
        @tparam T     - string view convertible type
        @param  value - format string to check
        @retval       - save format string as input
    **/
    template<class T>
    static consteval const T& parse_format_string(const T& value);
};

template<class... args_t>
using format_string = basic_format_string<char_type, std::type_identity_t<args_t>...>;

template<class char_t, class... args_t>
concept format_acceptable_args =
    !(qx::tuple::contains_v<
          tuple::remove_t<details::all_char_types, std::tuple<char_t>>,
          std::remove_cv_t<std::remove_pointer_t<std::decay_t<args_t>>>>
      || ...);

} // namespace qx

#include <qx/containers/string/format_string.inl>
