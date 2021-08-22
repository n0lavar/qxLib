/**

    @file      string_hash.h
    @brief     Contains qx::basic_string_hash class
    @author    Khrapov
    @date      13.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string_traits.h>

namespace qx
{

namespace detail
{

template<typename T>
concept has_zero_termonated_hash_func_overload =
    requires(typename T::const_pointer pszString, size_t nSeed)
{
    T::hash_function(pszString, nSeed);
};

} // namespace detail


template<typename T>
concept string_convertable = requires(T t)
{
    t.cbegin();
    t.cend();
};

/**

    @class   basic_string_hash
    @brief   String hash object
    @details ~
    @tparam  Traits - char traits. \see string_traits.h
    @author  Khrapov
    @date    13.11.2020

**/
template<class Traits>
class basic_string_hash
{
public:
    using const_pointer = typename Traits::const_pointer;
    using size_type     = typename Traits::size_type;

    constexpr basic_string_hash(void) noexcept = default;

    /**
        @brief basic_string_hash object constructor
        @param pString - string first char pointer
        @param nSize   - string size
    **/
    constexpr basic_string_hash(
        const_pointer pString,
        size_type     nSize) noexcept;

    /**
        @brief basic_string_hash object constructor
        @param pszString - pointer to string zero terminated
    **/
    constexpr basic_string_hash(const_pointer pszString) noexcept;

    /**
        @brief  basic_string_hash object constructor
        @tparam String  - string-ish type, satisfying the "string_convertable" concept
        @param  sString - string-ish container
    **/
    template<string_convertable String>
    constexpr basic_string_hash(const String& sString) noexcept;

    /**
        @brief  operator size_t
        @retval - hash number
    **/
    constexpr operator size_t() const noexcept;

private:
    size_t m_nHash = 0;
};

using string_hash  = basic_string_hash<char_traits<char>>;
using wstring_hash = basic_string_hash<char_traits<wchar_t>>;

/**
    @struct fast_hash_string_traits
    @tparam value_type - char type
    @date   25.01.2021
**/
template<typename value_type>
struct fast_hash_string_traits : public char_traits<value_type>
{
    /**
        @brief  Hash function realization
        @param  sStr  - string first char pointer
        @param  nSeed - hash seed
        @param  nLen  - string size
        @retval       - hash 
    **/
    static constexpr typename char_traits<value_type>::size_type hash_function(
        typename char_traits<value_type>::const_pointer sStr,
        size_t                                          nSeed,
        typename char_traits<value_type>::size_type     nLen) noexcept;

    /**
        @brief  Hash function realization
        @param  pszStr - pointer to string zero terminated
        @param  nSeed  - hash seed
        @retval        - hash
    **/
    static constexpr typename char_traits<value_type>::size_type hash_function(
        typename char_traits<value_type>::const_pointer pszStr,
        size_t                                          nSeed) noexcept;
};

using fast_string_hash  = basic_string_hash<fast_hash_string_traits<char>>;
using fast_wstring_hash = basic_string_hash<fast_hash_string_traits<wchar_t>>;

} // namespace qx

#include <qx/containers/string_hash.inl>
