//==============================================================================
//
//!\file                       string_traits.h
//
//!\brief       Traits for qx::string
//!\details     ~
//
//!\author      Khrapov
//!\date        24.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/useful_macros.h>

#include <cwctype>
#include <sstream>
#include <cstring>
#include <cctype>
#include <cstdarg>

namespace qx
{

//==============================================================================
//
//!\struct                 qx::common_char_traits<T>
//!\author  Khrapov
//!\date    25.01.2021
//==============================================================================
template<typename T>
struct common_char_traits
{
    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    static size_type hash_function(const_pointer pszStr, size_t nSeed, size_type nLen) noexcept
    {
        return murmur_32_hash(pszStr, static_cast<u32>(nSeed), nLen);
    }
};

template<typename value_type>
struct char_traits;

//==============================================================================
//
//!\struct                   qx::char_traits<char>
//!\author  Khrapov
//!\date    30.10.2020
//==============================================================================
template<>
struct char_traits<char> : public common_char_traits<char>
{
    static constexpr size_type align(void) noexcept
    {
        return 16;
    }
    static constexpr size_type small_string_size(void) noexcept
    {
        return 48;
    }
    static constexpr u32 hash_seed(void) noexcept
    {
        return 5712564;
    }
    static bool is_space(value_type ch) noexcept
    {
        return std::isspace(static_cast<int>(ch)) != 0;
    }
    static size_type length(const_pointer pszStr) noexcept
    {
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
    static int vsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, va_list args) noexcept
    {
        return std::vsnprintf(pszDest, nBuffer, pszFormat, args);
    }
    template<class ... Args>
    static int sscanf(const_pointer pszString, const_pointer pszFormat, Args ... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS
        return std::sscanf(pszString, pszFormat, args...);
        QX_POP_SUPPRESS_WARNINGS
    }
};

//==============================================================================
//
//!\struct                  qx::char_traits<wchar_t>
//!\author  Khrapov
//!\date    24.03.2020
//==============================================================================
template<>
struct char_traits<wchar_t> : public common_char_traits<wchar_t>
{
    static constexpr size_type align(void) noexcept
    {
        return 8;
    }
    static constexpr size_type small_string_size(void) noexcept
    {
// MSVC:     sizeof(wchar_t) == 2
// GNU/Linux sizeof(wchar_t) == 4
#if QX_MSVC
        return 24;
#else
        return 12;
#endif
    }
    static constexpr u32 hash_seed(void) noexcept
    {
        return 985214;
    }
    static bool is_space(value_type ch) noexcept
    {
        return std::iswspace(static_cast<wint_t>(ch)) != 0;
    }
    static size_type length(const_pointer pszStr) noexcept
    {
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
    static int vsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, va_list args) noexcept
    {
// MVSC's std::swprintf returns required size if nullptr and 0 passed as pDest and nBuffer,
// while other compilers returns -1
#if QX_MSVC
        return std::vswprintf(pszDest, nBuffer, pszFormat, args);
#else
        int size = -1;

        if (nBuffer <= 0)
        {
            // opening a dummy file to /dev/null and printing to that file to retrieve the required size
            if (FILE* pDummyFile = std::fopen("/dev/null", "w"))
            {
                size = std::vfwprintf(pDummyFile, pszFormat, args);
                std::fclose(pDummyFile);
            }
        }
        else
        {
            size = std::vswprintf(pszDest, nBuffer, pszFormat, args);
        }

        return size;
#endif
    }
    template<class ... Args>
    static int sscanf(const_pointer pszString, const_pointer pszFormat, Args ... args) noexcept
    {
        QX_PUSH_SUPPRESS_ALL_WARNINGS
        return std::swscanf(pszString, pszFormat, args...);
        QX_POP_SUPPRESS_WARNINGS
    }
};

}
