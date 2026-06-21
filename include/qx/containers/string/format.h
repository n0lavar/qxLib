/**

    @file      format.h
    @author    Khrapov
    @date      27.03.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>

namespace qx
{

/**
    @brief  std::format / fmt::format wrapper that returns qx::string
    @tparam args_t  - format arguments types
    @param  sFormat - format string
    @param  args    - template parameter pack
    @retval         - formatted string
**/
template<class... args_t>
    requires format_acceptable_args_c<char, args_t...>
cstring format(const QX_FMT_NS::format_string<std::type_identity_t<args_t>...> sFormat, args_t&&... args) noexcept
{
    // doesn't work for fmt for some reason
#if QX_CONF_FMT_LIB == QX_FMT_LIB_STD
    return cstring::static_format(sFormat, std::forward<args_t>(args)...);
#else
    return cstring::static_vformat(
        cstring_view(sFormat.get().data(), sFormat.get().size()),
        std::forward<args_t>(args)...);

#endif
}

/**
    @brief  std::format / fmt::format wrapper that returns qx::wstring
    @tparam args_t  - format arguments types
    @param  sFormat - format string
    @param  args    - template parameter pack
    @retval         - formatted string
**/
template<class... args_t>
    requires format_acceptable_args_c<wchar_t, args_t...>
wstring format(const QX_FMT_NS::wformat_string<std::type_identity_t<args_t>...> sFormat, args_t&&... args) noexcept
{
    return wstring::static_format(sFormat, std::forward<args_t>(args)...);
}

/**
    @brief  Converts any type that has a std::formatter overload to qx::basic_string
    @tparam T        - object type
    @tparam char_t   - char type (char, wchar_t, etc)
    @tparam traits_t - char traits. \see string_traits.h
    @param  value    - object to convert
    @retval          - qx::basic_string
**/
template<class T, class char_t = char_type, class traits_t = string_traits::traits<char_t>>
basic_string<char_t, traits_t> convert_to_string(const T& value) noexcept
{
    return basic_string<char_t, traits_t>::static_format(QX_STR_PREFIX(char_t, "{}"), value);
}

} // namespace qx
