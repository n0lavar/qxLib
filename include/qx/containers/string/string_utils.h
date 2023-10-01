/**

    @file      string_utils.h
    @author    Khrapov
    @date      17.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/config.h>
#include <qx/typedefs.h>

namespace qx
{

/**
    @brief  djb2a hash
    @tparam value_t - char type
    @param  pszStr  - string for hashing
    @param  nSeed   - seed for hashing
    @param  nLen    - string length
    @retval         - 32bit unsigned value
**/
template<class value_t>
constexpr size_t djb2a_hash(const value_t* pszStr, size_t nSeed, size_t nLen)
{
    size_t nHash = nSeed;

    for (size_t i = 0; i < nLen; ++i)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

/**
    @brief  djb2a hash
    @tparam value_t - char type
    @param  pszStr  - string for hashing (zero terminated)
    @param  nSeed   - seed for hashing
    @retval         - 32bit unsigned value
**/
template<class value_t>
constexpr size_t djb2a_hash(const value_t* pszStr, size_t nSeed)
{
    size_t nHash = nSeed;

    for (size_t i = 0; pszStr[i]; ++i)
        nHash = nHash * 33 ^ pszStr[i];

    return nHash;
}

/**
    @brief   Murmur nHash
    @details https://en.wikipedia.org/wiki/MurmurHash
             https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
    @tparam  value_t - char type
    @param   pStr    - string for hashing
    @param   nSeed   - seed for hashing
    @param   nLen    - string length
    @retval          - 32bit unsigned value
**/
template<class value_t>
constexpr size_t murmur_32_hash(const value_t* pStr, size_t nSeed, size_t nLen) noexcept
{
    size_t nHash = nSeed;

    if (nLen > 3)
    {
        size_t i = nLen >> 2;
        do
        {
            size_t k = 0;

            // constexpr version of std::memcpy(&k, pszStr, sizeof(u32));
            static_assert(sizeof(value_t) == 1 || sizeof(value_t) == 2 || sizeof(value_t) == 4);

            if constexpr (sizeof(value_t) == sizeof(u32))
            {
                k += *(pStr + 0);
            }
            else if constexpr (sizeof(value_t) == sizeof(u16))
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

    nHash ^= nLen;       //-V103
    nHash ^= nHash >> 16;
    nHash *= 0x85ebca6b; //-V101
    nHash ^= nHash >> 13;
    nHash *= 0xc2b2ae35; //-V101
    nHash ^= nHash >> 16;

    return nHash;
}

/**
    @brief  Compares string 1 with string 2
    @tparam fwd_it_1_t - string 1 iterator type
    @tparam fwd_it_2_t - string 2 iterator type
    @param  itBegin1   - string 1 begin iterator 
    @param  itEnd1     - string 1 end iterator 
    @param  itBegin2   - string 2 begin iterator 
    @param  itEnd2     - string 2 end iterator 
    @retval            - < 0 the first character that does not match has a lower value in str 1 than in str 2
                           0 the contents of both strings are equal
                         > 0 the first character that does not match has a greater value in str 1 than in str 2
**/
template<class fwd_it_1_t, class fwd_it_2_t>
constexpr int iter_strcmp(fwd_it_1_t itBegin1, fwd_it_1_t itEnd1, fwd_it_2_t itBegin2, fwd_it_2_t itEnd2) noexcept
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
    @tparam value_t  - char type
    @param  pszLeft  - first string (zero terminated)
    @param  pszRight - second string (zero terminated)
    @retval          -  < 0 the first character that does not match has a lower value in ptr1 than in ptr2
                          0 the contents of both strings are equal
                        > 0 the first character that does not match has a greater value in ptr1 than in ptr2
**/
template<class value_t>
constexpr int strcmp(const value_t* pszLeft, const value_t* pszRight)
{
    while (*pszLeft && (*pszLeft == *pszRight))
    {
        ++pszLeft;
        ++pszRight;
    }
    return *pszLeft - *pszRight;
}

namespace details
{

template<class value_t>
constexpr const value_t* choose_str_prefix(const char*, const wchar_t*) noexcept;

template<>
constexpr const char* choose_str_prefix<char>(const char* c, const wchar_t*) noexcept
{
    return c;
}

template<>
constexpr const wchar_t* choose_str_prefix<wchar_t>(const char*, const wchar_t* w) noexcept
{
    return w;
}

template<class value_t>
constexpr value_t choose_char_prefix(char, wchar_t) noexcept;

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

} // namespace details

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
    @param value_t - char type
    @param str        - string to apply
**/
#define QX_STR_PREFIX(value_t, str) qx::details::choose_str_prefix<value_t>(str, QX_TO_WSTRING(str))

/**
    @def   QX_CHAR_PREFIX
    @brief Chose witch of prefixes add to char : L or none
    @param value_t - char type
    @param ch         - string to apply
**/
#define QX_CHAR_PREFIX(value_t, ch) qx::details::choose_char_prefix<value_t>(ch, QX_TO_WSTRING(ch))

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
    @tparam value_t - char type
    @tparam T       - target type
    @retval         - format specifier or nullptr
**/
template<class value_t, class T>
constexpr auto get_format_specifier() noexcept
{
    const value_t* pszFormat = nullptr;

    using test_type = std::remove_cvref_t<T>;

    if constexpr (std::is_same_v<test_type, char>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hhd");
    }
    else if constexpr (std::is_same_v<test_type, unsigned char>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hhu");
    }
    else if constexpr (std::is_same_v<test_type, short>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hd");
    }
    else if constexpr (std::is_same_v<test_type, unsigned short>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%hu");
    }
    else if constexpr (std::is_same_v<test_type, int>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%d");
    }
    else if constexpr (std::is_same_v<test_type, unsigned int>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%u");
    }
    else if constexpr (std::is_same_v<test_type, long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%ld");
    }
    else if constexpr (std::is_same_v<test_type, unsigned long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%lu");
    }
    else if constexpr (std::is_same_v<test_type, long long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%lld");
    }
    else if constexpr (std::is_same_v<test_type, unsigned long long>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%llu");
    }
    else if constexpr (std::is_same_v<test_type, float>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%f");
    }
    else if constexpr (std::is_same_v<test_type, double>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%lf");
    }
    else if constexpr (std::is_same_v<test_type, long double>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%Lf");
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<std::remove_pointer_t<test_type>>, char>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%s");
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<std::remove_pointer_t<test_type>>, wchar_t>)
    {
        pszFormat = QX_STR_PREFIX(value_t, "%ls");
    }
    else if constexpr (std::is_pointer_v<test_type>)
    {
#if QX_MSVC
        pszFormat = QX_STR_PREFIX(value_t, "0x%p");
#else
        pszFormat = QX_STR_PREFIX(value_t, "%p");
#endif
    }

    return pszFormat;
}

/**
    @brief  Constexpr string length
    @tparam value_t - char type
    @param  psz     - pointer to string zero terminated
    @retval         - string length
**/
template<class value_t>
constexpr std::size_t strlen(const value_t* psz)
{
    std::size_t nLen = 0;
    while (psz && *psz != QX_CHAR_PREFIX(value_t, '\0'))
    {
        ++psz;
        nLen++;
    }

    return nLen;
}

} // namespace qx
