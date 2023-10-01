/**

    @file      string_hash.h
    @author    Khrapov
    @date      13.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_setup.h>
#include <qx/containers/string/string_traits.h>
#include <qx/meta/concepts.h>

namespace qx
{

namespace details
{

template<class T>
concept has_zero_termonated_hash_func_overload =
    requires(typename T::const_pointer pszStr, size_t nSeed) { T::hash_function(pszStr, nSeed); };

};

/**

    @class   basic_string_hash
    @brief   String hash object
    @tparam  traits_t - char traits. \see string_traits.h
    @author  Khrapov
    @date    13.11.2020

**/
template<class traits_t>
class basic_string_hash
{
public:
    using const_pointer = typename traits_t::const_pointer;
    using size_type     = typename traits_t::size_type;

    constexpr basic_string_hash() noexcept = default;

    /**
        @brief basic_string_hash object constructor
        @param pszString - string first char pointer
        @param nSize     - string size
    **/
    constexpr basic_string_hash(const_pointer pszString, size_type nSize) noexcept;

    /**
        @brief basic_string_hash object constructor
        @param pszString - pointer to string zero terminated
    **/
    constexpr basic_string_hash(const_pointer pszString) noexcept;

    /**
        @brief  basic_string_hash object constructor
        @tparam string_t - string-ish type, satisfying the "range_of_t_c" concept
        @param  sString  - string-ish container
    **/
    template<range_of_t_c<typename traits_t::value_type> string_t>
    constexpr basic_string_hash(const string_t& sString) noexcept;

    /**
        @brief  operator size_t
        @retval - hash number
    **/
    constexpr operator size_t() const noexcept;

private:
    size_t m_nHash = 0;
};

using cstring_hash = basic_string_hash<char_traits<char>>;
using wstring_hash = basic_string_hash<char_traits<wchar_t>>;
using string_hash  = basic_string_hash<char_traits<char_type>>;

#define QX_STRING_HASH(quote) qx::string_hash(QX_TEXT(quote))

namespace literals
{

/**
    @brief  String hash literal for constexpr converting. Can be used with switch-case
    @param  pszStr - literal text pointer
    @param  nSize  - literal text size
    @retval        - text hash value
**/
constexpr basic_string_hash<char_traits<char>> operator"" _sh(const char* pszStr, size_t nSize);

/**
    @brief  String hash literal for constexpr converting. Can be used with switch-case
    @param  pszStr - literal text pointer
    @param  nSize  - literal text size
    @retval        - text hash value
**/
constexpr basic_string_hash<char_traits<wchar_t>> operator"" _sh(const wchar_t* pszStr, size_t nSize);

} // namespace literals

} // namespace qx

#include <qx/containers/string/string_hash.inl>
