//==============================================================================
//
//!\file                         string_utils.h
//
//!\brief       String functions
//!\details     ~
//
//!\author      Khrapov
//!\date        17.10.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/typedefs.h>

namespace qx
{

//==============================================================================
//!\fn                        qx::djb2a_hash<Char>
//
//!\brief djb2a hash
//!\param  pszStr - string for hashing
//!\param  nSeed  - seed for hashing
//!\param  nLen   - string length
//!\retval        - 32bit unsigned value
//!\author Khrapov
//!\date   25.01.2021
//==============================================================================
template<typename Char>
constexpr u32 djb2a_hash(const Char* pszStr, u32 nSeed, size_t nLen)
{
    u32 nHash = nSeed;

    for (size_t i = 0; i < nLen; i++)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

//==============================================================================
//!\fn                        qx::djb2a_hash<Char>
//
//!\brief djb2a hash
//!\param  pszStr - string for hashing
//!\param  nSeed  - seed for hashing
//!\retval        - 32bit unsigned value
//!\author Khrapov
//!\date   25.01.2021
//==============================================================================
template<typename Char>
constexpr u32 djb2a_hash(const Char* pszStr, u32 nSeed)
{
    u32 nHash = nSeed;
    Char ch;

    while (ch = *pszStr++) //-V559
        nHash = ((nHash << 5) + nHash) + ch;

    return nHash;
}

//==============================================================================
//!\fn                      qx::murmur_32_hash<Char>
//
//!\brief   Murmur nHash
//!\details https://en.wikipedia.org/wiki/MurmurHash
//          https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
//
//!\param   pszStr - string for hashing (char must be 1, 2 or 4 bytes long)
//!\param   nSeed  - seed for hashing
//!\param   nLen   - string length
//!\retval         - 32bit unsigned value
//!\author  Khrapov
//!\date    10.09.2020
//==============================================================================
template<typename Char>
constexpr u32 murmur_32_hash(const Char* pszStr, u32 nSeed, size_t nLen) noexcept
{
    u32 nHash = nSeed;

    if (nLen > 3)
    {
        size_t i = nLen >> 2;
        do
        {
            u32 k = 0;

            // constexpr version of std::memcpy(&k, pszStr, sizeof(u32));
            if constexpr (sizeof(Char) == sizeof(u32))
            {
                k += *(pszStr + 0);
            }
            else if constexpr (sizeof(Char) == sizeof(u16))
            {
                k += *(pszStr + 0);
                k <<= sizeof(u16);
                k += *(pszStr + 1);
            }
            else
            {
                k += *(pszStr + 0);
                k <<= sizeof(u8);
                k += *(pszStr + 1);
                k <<= sizeof(u8);
                k += *(pszStr + 2);
                k <<= sizeof(u8);
                k += *(pszStr + 3);
            }

            pszStr += sizeof(u32);

            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;

            nHash ^= k;
            nHash = (nHash << 13) | (nHash >> 19);
            nHash = nHash * 5 + 0xe6546b64;
        } while (--i);
    }

    if (nLen & 3)
    {
        size_t i = nLen & 3;
        u32 k = 0;
        do
        {
            k <<= 8;
            k |= pszStr[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        nHash ^= k;
    }

    nHash ^= nLen; //-V103
    nHash ^= nHash >> 16;
    nHash *= 0x85ebca6b;
    nHash ^= nHash >> 13;
    nHash *= 0xc2b2ae35;
    nHash ^= nHash >> 16;

    return nHash;
}

//==============================================================================
//!\fn                  qx::iter_strcmp<FwdIt1, FwdIt2>
//
//!\brief  Compares string 1 with string 2
//!\param  itBegin1 - string 1 begin iterator
//!\param  itEnd1   - string 1 end iterator
//!\param  itBegin2 - string 2 begin iterator
//!\param  itEnd2   - string 2 end iterator
//!\retval          - < 0 the first character that does not match has a lower value in str 1 than in str 2
//                      0 the contents of both strings are equal
//                    > 0 the first character that does not match has a greater value in str 1 than in str 2
//!\date   23.10.2020
//==============================================================================
template<class FwdIt1, class FwdIt2>
constexpr int iter_strcmp(
    FwdIt1 itBegin1,
    FwdIt1 itEnd1,
    FwdIt2 itBegin2,
    FwdIt2 itEnd2) noexcept
{
    int nRet = 0;

    if (itBegin1 != itEnd1 && itBegin2 != itEnd2)
    {
        auto it1 = itBegin1;
        auto it2 = itBegin2;
        while (it2 != itEnd2 && (*it1 == *it2))
        {
            ++it2;
            ++it1;
        }
        nRet = *it1 - (it2 == itEnd2 ? *it1 : *it2);
    }

    return nRet;
}

namespace detail
{
    template<typename value_type>
    constexpr const value_type* const choose_str_prefix(const char* const, const wchar_t* const) noexcept;

    template<>
    constexpr const char* const choose_str_prefix<char>(const char* const c, const wchar_t* const) noexcept
    {
        return c;
    }

    template<>
    constexpr const wchar_t* const choose_str_prefix<wchar_t>(const char* const, const wchar_t* const w) noexcept
    {
        return w;
    }

    template<typename value_type>
    constexpr value_type choose_char_prefix(char, wchar_t) noexcept;

    template<>
    constexpr char choose_char_prefix<char>(char c, wchar_t) noexcept
    {
        return c;
    }

    template<>
    constexpr wchar_t choose_char_prefix<wchar_t>(char, wchar_t w) noexcept
    {
        return w;
    }
}

}

//==============================================================================

#define _QX_TO_WSTRING(x) L##x
#define QX_TO_WSTRING(x) _QX_TO_WSTRING(x)

/*
    chose witch of prefixes add to string : L or none
*/
#define QX_STR_PREFIX(value_type, str) qx::detail::choose_str_prefix<value_type>(str, QX_TO_WSTRING(str))

/*
    chose witch of prefixes add to char : L or none
*/
#define QX_CHAR_PREFIX(value_type, ch) qx::detail::choose_char_prefix<value_type>(ch, QX_TO_WSTRING(ch))

//==============================================================================

/*
    Static string comparisons
*/
#define QX_STATIC_ASSERT_STR_EQ(a, b) static_assert(qx::meta::strcmp((a), (b)) == 0)
#define QX_STATIC_ASSERT_STR_NE(a, b) static_assert(qx::meta::strcmp((a), (b)) != 0)
#define QX_STATIC_ASSERT_STR_LT(a, b) static_assert(qx::meta::strcmp((a), (b)) <  0)
#define QX_STATIC_ASSERT_STR_LE(a, b) static_assert(qx::meta::strcmp((a), (b)) <= 0)
#define QX_STATIC_ASSERT_STR_GT(a, b) static_assert(qx::meta::strcmp((a), (b)) >  0)
#define QX_STATIC_ASSERT_STR_GE(a, b) static_assert(qx::meta::strcmp((a), (b)) >= 0)

//==============================================================================

namespace qx
{

//==============================================================================
//!\fn                qx::get_format_specifier<value_type, T>
//
//!\brief  Get format specifier for type
//!\retval  - format specifier or nullptr if type is not supported
//!\author Khrapov
//!\date   11.09.2020
//==============================================================================
template<typename value_type, typename T>
constexpr auto get_format_specifier(void) noexcept
{
    const value_type* pszFormat = nullptr;

    if constexpr (std::is_same_v<T, char>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%hhd");
    }
    else if constexpr (std::is_same_v<T, unsigned char>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%hhu");
    }
    else if constexpr (std::is_same_v<T, short>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%hd");
    }
    else if constexpr (std::is_same_v<T, unsigned short>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%hu");
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%d");
    }
    else if constexpr (std::is_same_v<T, unsigned int>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%u");
    }
    else if constexpr (std::is_same_v<T, long>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%ld");
    }
    else if constexpr (std::is_same_v<T, unsigned long>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%lu");
    }
    else if constexpr (std::is_same_v<T, long long>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%lld");
    }
    else if constexpr (std::is_same_v<T, unsigned long long>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%llu");
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%f");
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%lf");
    }
    else if constexpr (std::is_same_v<T, long double>)
    {
        pszFormat = QX_STR_PREFIX(value_type, "%Lf");
    }
    else if constexpr (std::is_pointer_v<T>)
    {
#if QX_MSVC
        pszFormat = QX_STR_PREFIX(value_type, "0x%p");
#else
        pszFormat = QX_STR_PREFIX(value_type, "%p");
#endif
    }

    return pszFormat;
}

}