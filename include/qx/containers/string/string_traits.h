/**

    @file      string_traits.h
    @brief     Contains traits for qx::string
    @author    Khrapov
    @date      24.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view.h>
#include <qx/macros/config.h>
#include <qx/macros/suppress_warnings.h>

#include <cctype>
#include <cstdarg>
#include <cstring>
#include <cwctype>
#include <format>
#include <sstream>

namespace qx
{

/**
    @struct common_char_traits
    @tparam T - char type
    @date   25.01.2021
**/
template<class T>
struct common_char_traits
{
    using value_type       = T;
    using pointer          = T*;
    using const_pointer    = const T*;
    using reference        = T&;
    using const_reference  = const T&;
    using difference_type  = std::ptrdiff_t;
    using size_type        = size_t;
    using string_view_type = basic_string_view<T>;

    static constexpr size_type hash_function(const_pointer pszStr, size_t nSeed, size_type nLen) noexcept
    {
        return djb2a_hash(pszStr, nSeed, nLen);
    }
    static constexpr bool shrink_to_fit_when_small() noexcept
    {
        return false;
    }
};

template<class value_t>
struct char_traits;

template<>
struct char_traits<char> : public common_char_traits<char>
{
    static constexpr size_type align() noexcept
    {
        return 16;
    }
    static constexpr size_type small_string_size() noexcept
    {
        return 48;
    }
    static constexpr u32 hash_seed() noexcept
    {
        return 5712564;
    }
    static bool is_space(value_type ch) noexcept
    {
        return std::isspace(static_cast<int>(ch)) != 0;
    }
    static bool is_digit(value_type ch) noexcept
    {
        return std::isdigit(ch) != 0;
    }
    static constexpr size_type length(const_pointer pszStr) noexcept
    {
        if (std::is_constant_evaluated())
            return static_cast<size_type>(qx::strlen(pszStr));
        else
            return static_cast<size_type>(std::strlen(pszStr));
    }
    static value_type to_lower(value_type ch) noexcept
    {
        return static_cast<char>(std::tolower(ch));
    }
    static value_type to_upper(value_type ch) noexcept
    {
        return static_cast<char>(std::toupper(ch));
    }
    static int compare(const_pointer pszFirst, const_pointer pszSecond) noexcept
    {
        return std::strcmp(pszFirst, pszSecond);
    }
    static int compare_n(const_pointer pszFirst, const_pointer pszSecond, size_type nCount) noexcept
    {
        return std::strncmp(pszFirst, pszSecond, nCount);
    }
    template<class... args_t>
    static int sscanf(const_pointer pszString, const_pointer pszFormat, args_t... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();
        return std::sscanf(pszString, pszFormat, args...);
        QX_POP_SUPPRESS_WARNINGS();
    }
    template<class output_it_t, class... args_t>
    static void format_to(output_it_t itOutput, string_view_type svFormat, const args_t&... args)
    {
        std::vformat_to(itOutput, svFormat, std::make_format_args(args...));
    }
};

template<>
struct char_traits<wchar_t> : public common_char_traits<wchar_t>
{
    static constexpr size_type align() noexcept
    {
        return 8;
    }
    static constexpr size_type small_string_size() noexcept
    {
// MSVC:     sizeof(wchar_t) == 2
// GNU/Linux sizeof(wchar_t) == 4
#if QX_MSVC
        return 24;
#else
        return 12;
#endif
    }
    static constexpr u32 hash_seed() noexcept
    {
        return 985214;
    }
    static bool is_space(value_type ch) noexcept
    {
        return std::iswspace(static_cast<wint_t>(ch)) != 0;
    }
    static bool is_digit(value_type ch) noexcept
    {
        return std::iswdigit(ch) != 0;
    }
    static constexpr size_type length(const_pointer pszStr) noexcept
    {
        if (std::is_constant_evaluated())
            return static_cast<size_type>(qx::strlen(pszStr));
        else
            return static_cast<size_type>(std::wcslen(pszStr));
    }
    static value_type to_lower(value_type ch) noexcept
    {
        return std::towlower(ch);
    }
    static value_type to_upper(value_type ch) noexcept
    {
        return std::towupper(ch);
    }
    static int compare(const_pointer pszFirst, const_pointer pszSecond) noexcept
    {
        return std::wcscmp(pszFirst, pszSecond);
    }
    static int compare_n(const_pointer pszFirst, const_pointer pszSecond, size_type nCount) noexcept
    {
        return std::wcsncmp(pszFirst, pszSecond, nCount);
    }
    template<class... args_t>
    static int sscanf(const_pointer pszString, const_pointer pszFormat, args_t... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();
        return std::swscanf(pszString, pszFormat, args...);
        QX_POP_SUPPRESS_WARNINGS();
    }
    template<class output_it_t, class... args_t>
    static void format_to(output_it_t itOutput, string_view_type svFormat, const args_t&... args)
    {
        std::vformat_to(itOutput, svFormat, std::make_wformat_args(args...));
    }
};

} // namespace qx
