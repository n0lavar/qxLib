/**

    @file      format_string.h
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view.h>

namespace qx
{

/**
    @struct  basic_format_string_strong_checks
    @brief   QX_FMT_NS::basic_format_string wrapper that performs additional compile time checks
    @details Checks braces balance and matching pairs of braces to the number of arguments
             in exchange for some format features, such as nested replacement fields 
    @tparam  char_t - char type
    @tparam  args_t - template parameter pack type
**/
template<class char_t, class... args_t>
struct basic_format_string_strong_checks : public QX_FMT_NS::basic_format_string<char_t, args_t...>
{
    /**
        @brief  basic_format_string object constructor
        @tparam T     - string view convertible type
        @param  value - format string to check
    **/
    template<class T>
        requires std::convertible_to<const T&, qx::basic_string_view<char_t>>
    consteval basic_format_string_strong_checks(const T& value);

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
using format_string_strong_checks = basic_format_string_strong_checks<char_type, std::type_identity_t<args_t>...>;

template<class char_t, class... args_t>
concept format_acceptable_args_c =
    !(qx::tuple_utils::contains_v<
          tuple_utils::remove_t<details::all_char_types, std::tuple<char_t>>,
          std::remove_cv_t<std::remove_pointer_t<std::decay_t<args_t>>>>
      || ...);

template<class char_t>
struct basic_formatter
{
    template<class format_parse_context_t>
    constexpr auto parse(format_parse_context_t& ctx)
    {
        auto it = ctx.begin();

        if (it != ctx.end() && *it != QX_CHAR_PREFIX(char_t, '}'))
            throw QX_FMT_NS::format_error("unknown spec");

        return it;
    }
};

// "{:sh}" -> bShort is true
template<class char_t>
struct short_info_formatter
{
    bool bShort = false;

    template<class format_parse_context_t>
    constexpr auto parse(format_parse_context_t& ctx)
    {
        auto it = ctx.begin();
        if (it != ctx.end() && *it == QX_CHAR_PREFIX(char_t, 's'))
        {
            ++it;
            if (it != ctx.end() && *it == QX_CHAR_PREFIX(char_t, 'h'))
            {
                ++it;
                bShort = true;
            }
        }

        if (it != ctx.end() && *it != QX_CHAR_PREFIX(char_t, '}'))
            throw QX_FMT_NS::format_error("unknown spec");

        return it;
    }
};

} // namespace qx

#include <qx/containers/string/format_string.inl>
