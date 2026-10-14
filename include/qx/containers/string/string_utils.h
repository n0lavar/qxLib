/**

    @file      string_utils.h
    @author    Khrapov
    @date      17.10.2020
    @copyright (c) Nick Khrapov, 2021. All right reserved.

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
constexpr size_t djb2a_hash(const value_t* pszStr, size_t nSeed, size_t nLen);

/**
    @brief  djb2a hash
    @tparam value_t - char type
    @param  pszStr  - string for hashing (zero terminated)
    @param  nSeed   - seed for hashing
    @retval         - 32bit unsigned value
**/
template<class value_t>
constexpr size_t djb2a_hash(const value_t* pszStr, size_t nSeed = 0);

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
constexpr size_t murmur_32_hash(const value_t* pStr, size_t nSeed, size_t nLen) noexcept;

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
constexpr int iter_strcmp(fwd_it_1_t itBegin1, fwd_it_1_t itEnd1, fwd_it_2_t itBegin2, fwd_it_2_t itEnd2) noexcept;

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
constexpr int strcmp(const value_t* pszLeft, const value_t* pszRight);

namespace details
{

template<class value_t, size_t N>
constexpr const auto& choose_str_prefix(const char (&c)[N], const wchar_t (&w)[N]) noexcept;

template<class value_t>
constexpr value_t choose_char_prefix(char, wchar_t) noexcept;

template<>
constexpr char choose_char_prefix<char>(char c, wchar_t) noexcept;

template<>
constexpr wchar_t choose_char_prefix<wchar_t>(char, wchar_t w) noexcept;

} // namespace details

} // namespace qx

//==============================================================================

#define _QX_TO_WCHAR(x) L##x

#if QX_MSVC
    #define _QX_TO_WSTRING(x) __LPREFIX(x)
#else
    #define _QX_TO_WSTRING(x) _QX_TO_WCHAR(x)
#endif

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
#define QX_CHAR_PREFIX(value_t, ch) qx::details::choose_char_prefix<value_t>(ch, _QX_TO_WCHAR(ch))

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
constexpr const value_t* get_format_specifier() noexcept;

/**
    @brief  Naive but constexpr string length algorithm,
            for runtime prefer std::strlen as there are may be a lot of optimizations
    @tparam value_t - char type
    @param  psz     - pointer to string zero terminated
    @retval         - string length
**/
template<class value_t>
constexpr std::size_t strlen(const value_t* psz);

} // namespace qx

#include <qx/containers/string/string_utils.inl>
