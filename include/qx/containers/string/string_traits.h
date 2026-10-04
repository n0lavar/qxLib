/**

    @file      string_traits.h
    @author    Khrapov
    @date      24.03.2020
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_utils.h>
#include <qx/containers/string/string_view.h>
#include <qx/macros/config.h>
#include <qx/macros/static_assert.h>
#include <qx/macros/suppress_warnings.h>

#include <cctype>
#include <cstdarg>
#include <cstring>
#include <cwctype>
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

template<class value_t, class usings_char_traits_t, size_t nSmallStringBytes, bool bShrinkToFitWhenSmall>
    requires(nSmallStringBytes % sizeof(value_t) == 0)
struct allocation_traits
{
    static constexpr typename usings_char_traits_t::size_type small_string_size() noexcept
    {
        return nSmallStringBytes / sizeof(value_t);
    }

    static constexpr bool shrink_to_fit_when_small() noexcept
    {
        return bShrinkToFitWhenSmall;
    }
};



// -------------------------------------------------- test_char_traits -------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct test_char_traits;

template<class value_t>
struct base_test_char_traits
{
    static bool is_eng_alpha(value_t ch) noexcept
    {
        return (ch >= QX_CHAR_PREFIX(value_t, 'A') && ch <= QX_CHAR_PREFIX(value_t, 'Z'))
               || (ch >= QX_CHAR_PREFIX(value_t, 'a') && ch <= QX_CHAR_PREFIX(value_t, 'z'));
    }
};

template<class usings_char_traits_t>
struct test_char_traits<char, usings_char_traits_t> : base_test_char_traits<char>
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
struct test_char_traits<wchar_t, usings_char_traits_t> : base_test_char_traits<wchar_t>
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
    using format_string = QX_FMT_NS::basic_format_string<value_t, args_t...>;
};



// --------------------------------------------------- format_traits ---------------------------------------------------

template<class value_t, class usings_char_traits_t>
struct format_traits;

template<class usings_char_traits_t>
struct format_traits<char, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type nMemoryBufferSize = 1024;

    template<class... args_t>
    static auto make_format_args(args_t&... args)
    {
        return QX_FMT_NS::make_format_args(args...);
    }

    template<class... args_t>
    static int sscanf(
        typename usings_char_traits_t::const_pointer pszString,
        typename usings_char_traits_t::const_pointer pszFormat,
        args_t&&... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();
        return std::sscanf(pszString, pszFormat, std::forward<args_t>(args)...);
        QX_POP_SUPPRESS_WARNINGS();
    }
};

template<class usings_char_traits_t>
struct format_traits<wchar_t, usings_char_traits_t>
{
    static constexpr typename usings_char_traits_t::size_type nMemoryBufferSize =
#if QX_WIN
        512;
#else
        256;
#endif

    template<class... args_t>
    static auto make_format_args(args_t&... args)
    {
        return QX_FMT_NS::make_wformat_args(args...);
    }

    template<class... args_t>
    static int sscanf(
        typename usings_char_traits_t::const_pointer pszString,
        typename usings_char_traits_t::const_pointer pszFormat,
        args_t&&... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS();
        return std::swscanf(pszString, pszFormat, std::forward<args_t>(args)...);
        QX_POP_SUPPRESS_WARNINGS();
    }
};

namespace details
{

template<
    class value_t,
    class usings_traits_t         = usings_traits<value_t>,
    class hash_traits_t           = hash_traits<value_t, usings_traits_t>,
    class allocation_traits_t     = allocation_traits<value_t, usings_traits_t, 64, false>,
    class test_char_traits_t      = test_char_traits<value_t, usings_traits_t>,
    class transform_char_traits_t = transform_char_traits<value_t, usings_traits_t>,
    class length_traits_t         = length_traits<value_t, usings_traits_t>,
    class compare_traits_t        = compare_traits<value_t, usings_traits_t>,
    class format_string_traits_t  = format_string_traits<value_t, usings_traits_t>,
    class format_traits_t         = format_traits<value_t, usings_traits_t>>
struct builder
{
    template<class... args_t>
    struct constructor : public args_t...
    {
    };

    struct type
        : constructor<
              usings_traits_t,
              hash_traits_t,
              allocation_traits_t,
              test_char_traits_t,
              transform_char_traits_t,
              length_traits_t,
              compare_traits_t,
              format_string_traits_t,
              format_traits_t>
    {
        using builder_type = builder;
    };

    template<class trait_override_t>
    using with_usings = builder<
        value_t,
        trait_override_t,
        hash_traits_t,
        allocation_traits_t,
        test_char_traits_t,
        transform_char_traits_t,
        length_traits_t,
        compare_traits_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_hash = builder<
        value_t,
        usings_traits_t,
        trait_override_t,
        allocation_traits_t,
        test_char_traits_t,
        transform_char_traits_t,
        length_traits_t,
        compare_traits_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_allocation = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        trait_override_t,
        test_char_traits_t,
        transform_char_traits_t,
        length_traits_t,
        compare_traits_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_test_char = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        allocation_traits_t,
        trait_override_t,
        transform_char_traits_t,
        length_traits_t,
        compare_traits_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_transform_char = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        allocation_traits_t,
        test_char_traits_t,
        trait_override_t,
        length_traits_t,
        compare_traits_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_length = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        allocation_traits_t,
        test_char_traits_t,
        transform_char_traits_t,
        trait_override_t,
        compare_traits_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_compare = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        allocation_traits_t,
        test_char_traits_t,
        transform_char_traits_t,
        length_traits_t,
        trait_override_t,
        format_string_traits_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_format_string = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        allocation_traits_t,
        test_char_traits_t,
        transform_char_traits_t,
        length_traits_t,
        compare_traits_t,
        trait_override_t,
        format_traits_t>;

    template<class trait_override_t>
    using with_format = builder<
        value_t,
        usings_traits_t,
        hash_traits_t,
        allocation_traits_t,
        test_char_traits_t,
        transform_char_traits_t,
        length_traits_t,
        compare_traits_t,
        format_string_traits_t,
        trait_override_t>;
};

} // namespace details

template<class value_t>
using default_traits = typename details::builder<value_t>::type;

template<class traits_t>
struct traits_builder : traits_t::builder_type
{
};

template<class value_t>
using small_traits = typename traits_builder<default_traits<value_t>>::template with_allocation<
    allocation_traits<value_t, usings_traits<value_t>, 32, false>>::type;

template<class value_t>
using big_traits = typename traits_builder<default_traits<value_t>>::template with_allocation<
    allocation_traits<value_t, usings_traits<value_t>, 128, false>>::type;

template<class value_t>
using huge_traits = typename traits_builder<default_traits<value_t>>::template with_allocation<
    allocation_traits<value_t, usings_traits<value_t>, 256, false>>::type;

} // namespace qx::string_traits
