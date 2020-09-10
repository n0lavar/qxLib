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

#include <qx/other/useful_funcs.h>

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
    using std_string_type   = std::string;
    using sstream_type      = std::stringstream;

    static constexpr value_type teol(void)
    {
        return '\0';
    }
    static constexpr size_type talign(void)
    {
        return static_cast<size_type>(Align);
    }
    static size_type tstrlen(const_pointer pStr)
    {
        return static_cast<size_type>(std::strlen(pStr));
    }
    static value_type ttolower(value_type ch)
    {
        return std::tolower(ch);
    }
    static value_type ttoupper(value_type ch)
    {
        return std::toupper(ch);
    }
    static i64 ttolli(const_pointer pStr, pointer* pEnd, int base)
    {
        return std::strtoll(pStr, pEnd, base);
    }
    static u64 ttoull(const_pointer pStr, pointer* pEnd, int base)
    {
        return std::strtoull(pStr, pEnd, base);
    }
    static long double ttold(const_pointer pStr, pointer* pEnd)
    {
        return std::strtold (pStr, pEnd);
    }
    static int tstrcmp(const_pointer pFirst, const_pointer pSecond)
    {
        return std::strcmp(pFirst, pSecond);
    }
    static int tstrncmp(const_pointer  pFirst, const_pointer  pSecond, size_type nCount)
    {
        return std::strncmp(pFirst, pSecond, nCount);
    }
    template<class ... Args>
    static int tsnprintf(pointer pDest, size_type nBuffer, const_pointer pFormat, Args ... args)
    {
        return std::snprintf(pDest, nBuffer, pFormat, args...);
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
    using std_string_type   = std::wstring;
    using sstream_type      = std::wstringstream;

    static constexpr value_type teol(void)
    {
        return L'\0';
    }
    static constexpr size_type talign(void)
    {
        return static_cast<size_type>(Align);
    }
    static size_type tstrlen (const_pointer pStr)
    {
        return static_cast<size_type>(std::wcslen(pStr));
    }
    static value_type ttolower (value_type ch)
    {
        return std::towlower(ch);
    }
    static value_type ttoupper(value_type ch)
    {
        return std::towupper(ch);
    }
    static i64 ttolli(const_pointer pStr, pointer* pEnd, int base)
    {
        return std::wcstoll(pStr, pEnd, base);
    }
    static u64 ttoull(const_pointer pStr, pointer* pEnd, int base)
    {
        return std::wcstoull(pStr, pEnd, base);
    }
    static long double ttold(const_pointer pStr, pointer* pEnd)
    {
        return std::wcstod(pStr, pEnd);
    }
    static int tstrcmp(const_pointer pFirst, const_pointer pSecond)
    {
        return std::wcscmp(pFirst, pSecond);
    }
    static int tstrncmp(const_pointer  pFirst, const_pointer  pSecond, size_type nCount)
    {
        return std::wcsncmp(pFirst, pSecond, nCount);
    }

    // MVSC's std::swprintf returns required size if nullptr and 0 passed as pDest and nBuffer,
    // while other compilers returns -1
#ifdef _MSC_VER
    template<class ... Args>
    static int tsnprintf(pointer pDest, size_type nBuffer, const_pointer pFormat, Args ... args)
    {
        return std::swprintf(pDest, nBuffer, pFormat, args...);
    }
#else
    static int tsnprintf(pointer pDest, size_type nBuffer, const_pointer pFormat, ...)
    {
        int size = -1;

        va_list va;
        va_start(va, pFormat);
        if (nBuffer <= 0)
        {
            // opening a dummy file to /dev/null and printing to that file to retrieve the required size
            FILE* pDummyFile = std::fopen("/dev/null", "w");
            if (pDummyFile)
            {
                size = std::vfwprintf(pDummyFile, pFormat, va);
                std::fclose(pDummyFile);
            }
        }
        else
        {
            size = std::vswprintf(pDest, nBuffer, pFormat, va);
        }
        va_end(va);

        return size;
    }
#endif
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
//!\param   key  - key value, string for hashing
//!\param   len  - string length
//!\param   seed - seed for hashing
//!\retval       - 32bit unsigned value
//!\author  Khrapov
//!\date    10.09.2020
//==============================================================================
template<typename Char>
inline u32 murmur_32_hash(const Char* key, size_t len, u32 seed)
{
    u32 h = seed;
    if (len > 3)
    {
        size_t i = len >> 2;
        do
        {
            u32 k;
            memcpy(&k, key, sizeof(u32));
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

template<typename value_type>
constexpr const value_type * const ChooseStrPrefix(const char * const, const wchar_t * const);

template<>
constexpr const char * const ChooseStrPrefix<char>(const char * const c, const wchar_t * const)
{
    return c;
}

template<>
constexpr const wchar_t * const ChooseStrPrefix<wchar_t>(const char * const, const wchar_t * const w)
{
    return w;
}

template<typename value_type>
constexpr value_type ChooseCharPrefix(char, wchar_t);

template<>
constexpr char ChooseCharPrefix<char>(char c, wchar_t)
{
    return c;
}

template<>
constexpr wchar_t ChooseCharPrefix<wchar_t>(char, wchar_t w)
{
    return w;
}

}

#define _QX_TO_WSTRING(x) L##x
#define QX_TO_WSTRING(x) _QX_TO_WSTRING(x)

// chose witch of prefixes add to string : L or none
#define STR_PREFIX(value_type, str) qx::detail::ChooseStrPrefix<value_type>(str, QX_TO_WSTRING(str))

// chose witch of prefixes add to char : L or none
#define CHAR_PREFIX(value_type, ch) qx::detail::ChooseCharPrefix<value_type>(ch, QX_TO_WSTRING(ch))
