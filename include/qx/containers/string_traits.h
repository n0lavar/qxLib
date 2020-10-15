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

#include <cwctype>
#include <sstream>
#include <cstring>
#include <cctype>
#include <cstdarg>

#include <qx/other/useful_macros.h>

namespace qx
{

//==============================================================================
//
//!\struct                   qx::char_traits<Align>
//!\author  Khrapov
//!\date    30.10.2020
//==============================================================================
template <size_t Align>
struct char_traits
{
    using value_type        = char;
    using pointer           = char*;
    using const_pointer     = const char*;
    using reference         = char&;
    using const_reference   = const char&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    static constexpr value_type teol(void)
    {
        return '\0';
    }
    static constexpr bool tisspace(value_type ch)
    {
        return std::isspace(static_cast<int>(ch));
    }
    static constexpr size_type talign(void)
    {
        return static_cast<size_type>(Align);
    }
    static size_type tstrlen(const_pointer pszStr)
    {
        return static_cast<size_type>(std::strlen(pszStr));
    }
    static value_type ttolower(value_type ch)
    {
        return std::tolower(ch);
    }
    static value_type ttoupper(value_type ch)
    {
        return std::toupper(ch);
    }
    static int tstrcmp(const_pointer pszFirst, const_pointer pszSecond)
    {
        return std::strcmp(pszFirst, pszSecond);
    }
    static int tstrncmp(const_pointer pszFirst, const_pointer pszSecond, size_type nCount)
    {
        return std::strncmp(pszFirst, pszSecond, nCount);
    }
    template<class ... Args>
    static int tsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, Args ... args)
    {
        return std::snprintf(pszDest, nBuffer, pszFormat, args...);
    }
    template<class ... Args>
    static int tssscanf(const_pointer pszString, const_pointer pszFormat, Args ... args)
    {
        return std::sscanf(pszString, pszFormat, args...);
    }
};

//==============================================================================
//
//!\struct                  qx::wchar_traits<Align>
//!\author  Khrapov
//!\date    24.03.2020
//==============================================================================
template <size_t Align>
struct wchar_traits
{
    using value_type        = wchar_t;
    using pointer           = wchar_t*;
    using const_pointer     = const wchar_t*;
    using reference         = wchar_t&;
    using const_reference   = const wchar_t&;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;

    static constexpr value_type teol(void)
    {
        return L'\0';
    }
    static constexpr bool tisspace(value_type ch)
    {
        return std::iswspace(static_cast<wint_t>(ch));
    }
    static constexpr size_type talign(void)
    {
        return static_cast<size_type>(Align);
    }
    static size_type tstrlen(const_pointer pszStr)
    {
        return static_cast<size_type>(std::wcslen(pszStr));
    }
    static value_type ttolower(value_type ch)
    {
        return std::towlower(ch);
    }
    static value_type ttoupper(value_type ch)
    {
        return std::towupper(ch);
    }
    static int tstrcmp(const_pointer pszFirst, const_pointer pszSecond)
    {
        return std::wcscmp(pszFirst, pszSecond);
    }
    static int tstrncmp(const_pointer pszFirst, const_pointer pszSecond, size_type nCount)
    {
        return std::wcsncmp(pszFirst, pszSecond, nCount);
    }
    // MVSC's std::swprintf returns required size if nullptr and 0 passed as pDest and nBuffer,
    // while other compilers returns -1
#if QX_MSVC
    template<class ... Args>
    static int tsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, Args ... args)
    {
        return std::swprintf(pszDest, nBuffer, pszFormat, args...);
    }
#else
    static int tsnprintf(pointer pszDest, size_type nBuffer, const_pointer pszFormat, ...)
    {
        int size = -1;

        va_list va;
        va_start(va, pszFormat);
        if (nBuffer <= 0)
        {
            // opening a dummy file to /dev/null and printing to that file to retrieve the required size
            FILE* pDummyFile = std::fopen("/dev/null", "w");
            if (pDummyFile)
            {
                size = std::vfwprintf(pDummyFile, pszFormat, va);
                std::fclose(pDummyFile);
            }
        }
        else
        {
            size = std::vswprintf(pszDest, nBuffer, pszFormat, va);
        }
        va_end(va);

        return size;
    }
#endif
    template<class ... Args>
    static int tssscanf(const_pointer pszString, const_pointer pszFormat, Args ... args)
    {
        return std::swscanf(pszString, pszFormat, args...);
    }
};

}

namespace qx::detail
{

//==============================================================================
//!\fn                  qx::detail::murmur_32_hash<Char>
//
//!\brief   Murmur hash
//!\details https://en.wikipedia.org/wiki/MurmurHash
//          https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
//
//!\param   key  - key value, string for hashing (char must be 1, 2 or 4 bytes long)
//!\param   len  - string length
//!\param   seed - seed for hashing
//!\retval       - 32bit unsigned value
//!\author  Khrapov
//!\date    10.09.2020
//==============================================================================
template<typename Char>
inline constexpr u32 murmur_32_hash(const Char* key, size_t len, u32 seed)
{
    u32 h = seed;
    if (len > 3)
    {
        size_t i = len >> 2;
        do
        {
            u32 k = 0;

            // constexpr version of std::memcpy(&k, key, sizeof(u32));
            if constexpr (sizeof(Char) == sizeof(u32))
            {
                k += *(key + 0);
            }
            else if constexpr (sizeof(Char) == sizeof(u16))
            {
                k += *(key + 0);
                k <<= sizeof(u16);
                k += *(key + 1);
            }
            else
            {
                k += *(key + 0);
                k <<= sizeof(u8);
                k += *(key + 1);
                k <<= sizeof(u8);
                k += *(key + 2);
                k <<= sizeof(u8);
                k += *(key + 3);
            }

            key += sizeof(u32);
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = h * 5 + 0xe6546b64;
        } while (--i);
    }
    if (len & 3)
    {
        size_t i = len & 3;
        u32 k = 0;
        do
        {
            k <<= 8;
            k |= key[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len; //-V103
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

}