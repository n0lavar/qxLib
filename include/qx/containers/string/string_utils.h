/**

    @file      string_utils.h
    @brief     String functions
    @author    Khrapov
    @date      17.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/config.h>
#include <qx/typedefs.h>

namespace qx
{

/**
    @brief  djb2a hash
    @tparam value_type - char type
    @param  pszStr     - string for hashing
    @param  nSeed      - seed for hashing
    @param  nLen       - string length
    @retval            - 32bit unsigned value
**/
template<typename value_type>
constexpr size_t djb2a_hash(const value_type* pszStr, size_t nSeed, size_t nLen)
{
    size_t nHash = nSeed;

    for (size_t i = 0; i < nLen; ++i)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

/**
    @brief  djb2a hash
    @tparam value_type - char type
    @param  pszStr     - string for hashing (zero terminated)
    @param  nSeed      - seed for hashing
    @retval            - 32bit unsigned value
**/
template<typename value_type>
constexpr size_t djb2a_hash(const value_type* pszStr, size_t nSeed)
{
    size_t     nHash = nSeed;
    value_type ch;

    for (size_t i = 0; pszStr[i]; ++i)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

/**
    @brief   Murmur nHash
    @details https://en.wikipedia.org/wiki/MurmurHash
             https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
    @tparam  value_type - char type
    @param   pStr       - string for hashing
    @param   nSeed      - seed for hashing
    @param   nLen       - string length
    @retval             - 32bit unsigned value
**/
template<typename value_type>
constexpr size_t murmur_32_hash(
    const value_type* pStr,
    size_t            nSeed,
    size_t            nLen) noexcept
{
    size_t nHash = nSeed;

    if (nLen > 3)
    {
        size_t i = nLen >> 2;
        do
        {
            size_t k = 0;

            // constexpr version of std::memcpy(&k, pszStr, sizeof(u32));
            static_assert(
                sizeof(value_type) == 1 || sizeof(value_type) == 2
                || sizeof(value_type) == 4);

            if constexpr (sizeof(value_type) == sizeof(u32))
            {
                k += *(pStr + 0);
            }
            else if constexpr (sizeof(value_type) == sizeof(u16))
            {
                k += *(pStr + 0);
                k <<= sizeof(u16);
                k += *(pStr + 1);
            }
            else
            {
                k += *(pStr + 0);
                k <<= sizeof(u8);
                k += *(pStr + 1);
                k <<= sizeof(u8);
                k += *(pStr + 2);
                k <<= sizeof(u8);
                k += *(pStr + 3);
            }

            pStr += sizeof(u32);

            k *= 0xcc9e2d51; //-V101
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;

            nHash ^= k;
            nHash = (nHash << 13) | (nHash >> 19);
            nHash = nHash * 5 + 0xe6546b64; //-V104
        } while (--i);
    }

    if (nLen & 3)
    {
        size_t i = nLen & 3;
        size_t k = 0;
        do
        {
            k <<= 8;
            k |= pStr[i - 1];
        } while (--i);
        k *= 0xcc9e2d51; //-V101
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        nHash ^= k;
    }

    nHash ^= nLen; //-V103
    nHash ^= nHash >> 16;
    nHash *= 0x85ebca6b; //-V101
    nHash ^= nHash >> 13;
    nHash *= 0xc2b2ae35; //-V101
    nHash ^= nHash >> 16;

    return nHash;
}

/**
    @brief  Compares string 1 with string 2
    @tparam FwdIt1   - string 1 iterator type
    @tparam FwdIt2   - string 2 iterator type
    @param  itBegin1 - string 1 begin iterator 
    @param  itEnd1   - string 1 end iterator 
    @param  itBegin2 - string 2 begin iterator 
    @param  itEnd2   - string 2 end iterator 
    @retval          - < 0 the first character that does not match has a lower value in str 1 than in str 2
                         0 the contents of both strings are equal
                       > 0 the first character that does not match has a greater value in str 1 than in str 2
**/
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

/**
    @brief  Constexpr compare two strings
    @tparam value_type - char type
    @param  pszLeft    - first string (zero terminated)
    @param  pszRight   - second string (zero terminated)
    @retval            -  < 0 the first character that does not match has a lower value in ptr1 than in ptr2
                            0 the contents of both strings are equal
                          > 0 the first character that does not match has a greater value in ptr1 than in ptr2
**/
template<typename value_type>
constexpr int strcmp(const value_type* pszLeft, const value_type* pszRight)
{
    while (*pszLeft && (*pszLeft == *pszRight))
    {
        ++pszLeft;
        ++pszRight;
    }
    return *pszLeft - *pszRight;
}

namespace detail
{

template<typename value_type>
constexpr const value_type* const choose_str_prefix(
    const char* const,
    const wchar_t* const) noexcept;

template<>
constexpr const char* const choose_str_prefix<char>(
    const char* const c,
    const wchar_t* const) noexcept
{
    return c;
}

template<>
constexpr const wchar_t* const choose_str_prefix<wchar_t>(
    const char* const,
    const wchar_t* const w) noexcept
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

} // namespace detail

} // namespace qx

//==============================================================================

#define _QX_TO_WSTRING(x) L##x

/**
    @def   QX_TO_WSTRING
    @brief Convert char* to wchar_t*
    @param str - string to apply
**/
#define QX_TO_WSTRING(str) _QX_TO_WSTRING(str)

/**
    @def   QX_STR_PREFIX
    @brief Chose witch of prefixes add to string : L or none
    @param value_type - char type
    @param str        - string to apply
**/
#define QX_STR_PREFIX(value_type, str) \
    qx::detail::choose_str_prefix<value_type>(str, QX_TO_WSTRING(str))

/**
    @def   QX_CHAR_PREFIX
    @brief Chose witch of prefixes add to char : L or none
    @param value_type - char type
    @param ch         - string to apply
**/
#define QX_CHAR_PREFIX(value_type, ch) \
    qx::detail::choose_char_prefix<value_type>(ch, QX_TO_WSTRING(ch))

//==============================================================================

/*
    Static string comparisons
*/
#define QX_STATIC_ASSERT_STR_EQ(a, b) static_assert(qx::strcmp((a), (b)) == 0)
#define QX_STATIC_ASSERT_STR_NE(a, b) static_assert(qx::strcmp((a), (b)) != 0)
#define QX_STATIC_ASSERT_STR_LT(a, b) static_assert(qx::strcmp((a), (b)) < 0)
#define QX_STATIC_ASSERT_STR_LE(a, b) static_assert(qx::strcmp((a), (b)) <= 0)
#define QX_STATIC_ASSERT_STR_GT(a, b) static_assert(qx::strcmp((a), (b)) > 0)
#define QX_STATIC_ASSERT_STR_GE(a, b) static_assert(qx::strcmp((a), (b)) >= 0)

//==============================================================================

namespace qx
{

/**
    @brief  Get format specifier for type
    @tparam value_type - char type
    @tparam T          - target type
    @retval            - format specifier or nullptr
**/
template<typename value_type, typename T>
constexpr auto get_format_specifier() noexcept
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

/**
    @brief  Constexpr string length
    @tparam value_type - char type
    @param  psz        - pointer to string zero terminated
    @retval            - string length
**/
template<typename value_type>
constexpr std::size_t strlen(const value_type* psz)
{
    std::size_t nLen = 0;
    while (psz && *psz != QX_CHAR_PREFIX(value_type, '\0'))
    {
        ++psz;
        nLen++;
    }

    return nLen;
}

} // namespace qx
