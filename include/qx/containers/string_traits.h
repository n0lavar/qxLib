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

template<typename value_type>
struct char_traits;

//==============================================================================
//
//!\struct                   qx::char_traits<char>
//!\author  Khrapov
//!\date    30.10.2020
//==============================================================================
template<>
struct char_traits<char>
{
    using value_type        = char;
    using pointer           = char*;
    using const_pointer     = const char*;
    using reference         = char&;
    using const_reference   = const char&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    static constexpr size_type align(void)
    {
        return 16;
    }
    static constexpr size_type small_string_size(void)
    {
        return 48;
    }
    static bool is_space(value_type ch)
    {
        return std::isspace(static_cast<int>(ch));
    }
    static size_type length(const_pointer pszStr)
    {
        return static_cast<size_type>(std::strlen(pszStr));
    }
    static value_type to_lower(value_type ch)
    {
        return std::tolower(ch);
    }
    static value_type to_upper(value_type ch)
    {
        return std::toupper(ch);
    }
    static int compare(const_pointer pszFirst, const_pointer pszSecond)
    {
        return std::strcmp(pszFirst, pszSecond);
    }
    static int compare_n(const_pointer pszFirst, const_pointer pszSecond, size_type nCount)
    {
        return std::strncmp(pszFirst, pszSecond, nCount);
    }
    static int vsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, va_list args)
    {
        return std::vsnprintf(pszDest, nBuffer, pszFormat, args);
    }
    template<class ... Args>
    static int sscanf(const_pointer pszString, const_pointer pszFormat, Args ... args)
    {
        return std::sscanf(pszString, pszFormat, args...);
    }
};

//==============================================================================
//
//!\struct                  qx::char_traits<wchar_t>
//!\author  Khrapov
//!\date    24.03.2020
//==============================================================================
template<>
struct char_traits<wchar_t>
{
    using value_type        = wchar_t;
    using pointer           = wchar_t*;
    using const_pointer     = const wchar_t*;
    using reference         = wchar_t&;
    using const_reference   = const wchar_t&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    static constexpr size_type align(void)
    {
        return 8;
    }
    static constexpr size_type small_string_size(void)
    {
// MSVC:     sizeof(wchar_t) == 2
// GNU/Linux sizeof(wchar_t) == 4
#if QX_MSVC
        return 24;
#else
        return 12;
#endif
    }
    static bool is_space(value_type ch)
    {
        return std::iswspace(static_cast<wint_t>(ch));
    }
    static size_type length(const_pointer pszStr)
    {
        return static_cast<size_type>(std::wcslen(pszStr));
    }
    static value_type to_lower(value_type ch)
    {
        return std::towlower(ch);
    }
    static value_type to_upper(value_type ch)
    {
        return std::towupper(ch);
    }
    static int compare(const_pointer pszFirst, const_pointer pszSecond)
    {
        return std::wcscmp(pszFirst, pszSecond);
    }
    static int compare_n(const_pointer pszFirst, const_pointer pszSecond, size_type nCount)
    {
        return std::wcsncmp(pszFirst, pszSecond, nCount);
    }
    static int vsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, va_list args)
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
            FILE* pDummyFile = std::fopen("/dev/null", "w");
            if (pDummyFile)
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
    static int sscanf(const_pointer pszString, const_pointer pszFormat, Args ... args)
    {
        return std::swscanf(pszString, pszFormat, args...);
    }
};

}
