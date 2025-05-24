/**

    @file      string_traits.h
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

namespace qx::string_traits
{

// ------------------------------------------------- usings_char_traits ------------------------------------------------

template<class value_t>
struct usings_traits
{
    using value_type       = value_t;
    using pointer          = value_t*;
    using const_pointer    = const value_t*;
    using reference        = value_t&;
    using const_reference  = const value_t&;
    using difference_type  = std::ptrdiff_t;
    using size_type        = size_t;
    using string_view_type = basic_string_view<value_t>;
};



// -------------------------------------------------- hash_char_traits -------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct hash_traits
{
    static constexpr typename usings_char_traits_t::size_type hash_function(
        typename usings_char_traits_t::const_pointer pszStr,
        size_t                                       nSeed,
        typename usings_char_traits_t::size_type     nLen) noexcept
    {
        return djb2a_hash(pszStr, nSeed, nLen);
    }

    static constexpr u32 hash_seed() noexcept
    {
        return 5712564;
    }
};



// ------------------------------------------------- allocation_traits -------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct allocation_traits;

template<class usings_char_traits_t>
struct allocation_traits<char, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type align() noexcept
    {
        return 16;
    }

    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
        return 48;
    }

    static constexpr bool shrink_to_fit_when_small() noexcept
    {
        return false;
    }
};

template<class usings_char_traits_t>
struct allocation_traits<wchar_t, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type align() noexcept
    {
        return 16;
    }

    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
#if QX_MSVC
        // sizeof(wchar_t) == 2
        return 24;
#else
        // sizeof(wchar_t) == 4
        return 12;
#endif
    }

    static constexpr bool shrink_to_fit_when_small() noexcept
    {
        return false;
    }
};

template<class value_t, class usings_char_traits_t>
struct small_string_allocation_traits;

template<class usings_char_traits_t>
struct small_string_allocation_traits<char, usings_char_traits_t> : public allocation_traits<char, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
        return 16;
    }
};

template<class usings_char_traits_t>
struct small_string_allocation_traits<wchar_t, usings_char_traits_t>
    : public allocation_traits<wchar_t, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
#if QX_MSVC
        // sizeof(wchar_t) == 2
        return 8;
#else
        // sizeof(wchar_t) == 4
        return 4;
#endif
    }
};

template<class value_t, class usings_char_traits_t>
struct big_string_allocation_traits;

template<class usings_char_traits_t>
struct big_string_allocation_traits<char, usings_char_traits_t> : public allocation_traits<char, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type align() noexcept
    {
        return 128;
    }

    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
        return 240;
    }
};

template<class usings_char_traits_t>
struct big_string_allocation_traits<wchar_t, usings_char_traits_t>
    : public allocation_traits<wchar_t, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type align() noexcept
    {
        return 128;
    }

    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
#if QX_MSVC
        // sizeof(wchar_t) == 2
        return 120;
#else
        // sizeof(wchar_t) == 4
        return 60;
#endif
    }
};



// -------------------------------------------------- test_char_traits -------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct test_char_traits;

template<class usings_char_traits_t>
struct test_char_traits<char, usings_char_traits_t>
{
    static bool is_space(typename usings_char_traits_t::value_type ch) noexcept
    {
        return std::isspace(static_cast<int>(ch)) != 0;
    }

    static bool is_digit(typename usings_char_traits_t::value_type ch) noexcept
    {
        return std::isdigit(ch) != 0;
    }
};

template<class usings_char_traits_t>
struct test_char_traits<wchar_t, usings_char_traits_t>
{
    static bool is_space(typename usings_char_traits_t::value_type ch) noexcept
    {
        return std::iswspace(static_cast<wint_t>(ch)) != 0;
    }

    static bool is_digit(typename usings_char_traits_t::value_type ch) noexcept
    {
        return std::iswdigit(ch) != 0;
    }
};



// ----------------------------------------------- transform_char_traits -----------------------------------------------

template<class value_t, class usings_char_traits_t>
struct transform_char_traits;

template<class usings_char_traits_t>
struct transform_char_traits<char, usings_char_traits_t>
{
    static typename usings_char_traits_t::value_type to_lower(typename usings_char_traits_t::value_type ch) noexcept
    {
        return static_cast<char>(std::tolower(ch));
    }

    static typename usings_char_traits_t::value_type to_upper(typename usings_char_traits_t::value_type ch) noexcept
    {
        return static_cast<char>(std::toupper(ch));
    }
};

template<class usings_char_traits_t>
struct transform_char_traits<wchar_t, usings_char_traits_t>
{
    static typename usings_char_traits_t::value_type to_lower(typename usings_char_traits_t::value_type ch) noexcept
    {
        return std::towlower(ch);
    }

    static typename usings_char_traits_t::value_type to_upper(typename usings_char_traits_t::value_type ch) noexcept
    {
        return std::towupper(ch);
    }
};



// --------------------------------------------------- length_traits ---------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct length_traits;

template<class usings_char_traits_t>
struct length_traits<char, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type length(
        typename usings_char_traits_t::const_pointer pszStr) noexcept
    {
        if (std::is_constant_evaluated())
            return static_cast<typename usings_char_traits_t::size_type>(qx::strlen(pszStr));
        else
            return static_cast<typename usings_char_traits_t::size_type>(std::strlen(pszStr));
    }
};

template<class usings_char_traits_t>
struct length_traits<wchar_t, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type length(
        typename usings_char_traits_t::const_pointer pszStr) noexcept
    {
        if (std::is_constant_evaluated())
            return static_cast<typename usings_char_traits_t::size_type>(qx::strlen(pszStr));
        else
            return static_cast<typename usings_char_traits_t::size_type>(std::wcslen(pszStr));
    }
};



// --------------------------------------------------- compare_traits --------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct compare_traits;

template<class usings_char_traits_t>
struct compare_traits<char, usings_char_traits_t>
{
    static int compare(
        typename usings_char_traits_t::const_pointer pszFirst,
        typename usings_char_traits_t::const_pointer pszSecond) noexcept
    {
        return std::strcmp(pszFirst, pszSecond);
    }

    static int compare_n(
        typename usings_char_traits_t::const_pointer pszFirst,
        typename usings_char_traits_t::const_pointer pszSecond,
        typename usings_char_traits_t::size_type     nCount) noexcept
    {
        return std::strncmp(pszFirst, pszSecond, nCount);
    }
};

template<class usings_char_traits_t>
struct compare_traits<wchar_t, usings_char_traits_t>
{
    static int compare(
        typename usings_char_traits_t::const_pointer pszFirst,
        typename usings_char_traits_t::const_pointer pszSecond) noexcept
    {
        return std::wcscmp(pszFirst, pszSecond);
    }

    static int compare_n(
        typename usings_char_traits_t::const_pointer pszFirst,
        typename usings_char_traits_t::const_pointer pszSecond,
        typename usings_char_traits_t::size_type     nCount) noexcept
    {
        return std::wcsncmp(pszFirst, pszSecond, nCount);
    }
};



// ------------------------------------------------ format_string_traits -----------------------------------------------

template<class value_t, class usings_char_traits_t>
struct format_string_traits
{
    template<class... args_t>
    using format_string = std::basic_format_string<value_t, args_t...>;
};



// --------------------------------------------------- format_traits ---------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct format_traits;

template<class usings_char_traits_t>
struct format_traits<char, usings_char_traits_t>
{
    template<class... args_t>
    static int sscanf(
        typename usings_char_traits_t::const_pointer pszString,
        typename usings_char_traits_t::const_pointer pszFormat,
        args_t... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();
        return std::sscanf(pszString, pszFormat, args...);
        QX_POP_SUPPRESS_WARNINGS();
    }

    template<class output_it_t, class... args_t>
    static void format_to(
        output_it_t                                     itOutput,
        typename usings_char_traits_t::string_view_type svFormat,
        args_t&&... args)
    {
        std::vformat_to(itOutput, svFormat, std::make_format_args(args...));
    }
};

template<class usings_char_traits_t>
struct format_traits<wchar_t, usings_char_traits_t>
{
    template<class... args_t>
    static int sscanf(
        typename usings_char_traits_t::const_pointer pszString,
        typename usings_char_traits_t::const_pointer pszFormat,
        args_t... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();
        return std::swscanf(pszString, pszFormat, args...);
        QX_POP_SUPPRESS_WARNINGS();
    }

    template<class output_it_t, class... args_t>
    static void format_to(
        output_it_t                                     itOutput,
        typename usings_char_traits_t::string_view_type svFormat,
        args_t&&... args)
    {
        std::vformat_to(itOutput, svFormat, std::make_wformat_args(args...));
    }
};

template<class... args_t>
struct constructor : public args_t...
{
};

/**
    @brief Common string traits type. User may use it with user-defined traits to override the required behaviour.
    @tparam value_t - char type
**/
template<class value_t>
using traits = constructor<
    usings_traits<value_t>,
    hash_traits<value_t, usings_traits<value_t>>,
    allocation_traits<value_t, usings_traits<value_t>>,
    test_char_traits<value_t, usings_traits<value_t>>,
    transform_char_traits<value_t, usings_traits<value_t>>,
    length_traits<value_t, usings_traits<value_t>>,
    compare_traits<value_t, usings_traits<value_t>>,
    format_string_traits<value_t, usings_traits<value_t>>,
    format_traits<value_t, usings_traits<value_t>>>;

} // namespace qx::string_traits
