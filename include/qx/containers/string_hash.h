//==============================================================================
//
//!\file                         string_hash.h
//
//!\brief       Contains basic_string_hash class
//!\details     ~
//
//!\author      Khrapov
//!\date        13.11.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/string_traits.h>

namespace qx
{

namespace detail
{
    template<typename T>
    concept has_zero_termonated_hash_func_overload = requires(
        typename T::const_pointer pszString,
        size_t                    nSeed)
    {
        T::hash_function(pszString, nSeed);
    };

}

//==============================================================================
//
//!\class                qx::basic_string_hash<Traits>
//
//!\brief   String hash object
//!\details Use std::unordored_map<qx::string_hash, T> instead of
//          std::unordored_map<qx::string, T>, if you don't need string value
//
//!\author  Khrapov
//!\date    13.11.2020
//
//==============================================================================
template<class Traits>
class basic_string_hash
{
public:

    using const_pointer = typename Traits::const_pointer;
    using size_type     = typename Traits::size_type;

    constexpr basic_string_hash(void) noexcept = default;

    constexpr basic_string_hash(const_pointer pszString, size_type nSize) noexcept
        : m_nHash(Traits::hash_function(pszString, Traits::hash_seed(), nSize))
    {
    }

    constexpr basic_string_hash(const_pointer pszString) noexcept
    {
        if constexpr (detail::has_zero_termonated_hash_func_overload<Traits>)
            m_nHash = Traits::hash_function(pszString, Traits::hash_seed());
        else
            m_nHash = Traits::hash_function(pszString, Traits::hash_seed(), Traits::length(pszString));
    }

    template <class String, class = std::enable_if_t<std::is_class_v<String>>>
    constexpr basic_string_hash(const String& sString) noexcept
        : m_nHash(Traits::hash_function(sString.data(), Traits::hash_seed(), sString.size()))
    {
    }

    constexpr operator size_t() const noexcept
    {
        return m_nHash;
    }

private:

    size_t m_nHash = 0;
};

using string_hash  = basic_string_hash<char_traits<char>>;
using wstring_hash = basic_string_hash<char_traits<wchar_t>>;

//==============================================================================
//
//!\struct          qx::fast_hash_string_traits<value_type>
//!\author  Khrapov
//!\date    25.01.2021
//==============================================================================
template<typename value_type>
struct fast_hash_string_traits : public char_traits<value_type>
{
    static constexpr typename char_traits<value_type>::size_type hash_function(
        typename char_traits<value_type>::const_pointer pszStr,
        size_t nSeed,
        typename char_traits<value_type>::size_type nLen) noexcept
    {
        return djb2a_hash(pszStr, static_cast<u32>(nSeed), nLen);
    }

    static constexpr typename char_traits<value_type>::size_type hash_function(
        typename char_traits<value_type>::const_pointer pszStr,
        size_t nSeed) noexcept
    {
        return djb2a_hash(pszStr, static_cast<u32>(nSeed));
    }
};

using fast_string_hash  = basic_string_hash<fast_hash_string_traits<char>>;
using fast_wstring_hash = basic_string_hash<fast_hash_string_traits<wchar_t>>;

}

namespace std
{
    template<class Traits>
    struct hash<qx::basic_string_hash<Traits>>
    {
        size_t operator()(const qx::basic_string_hash<Traits>& hash) const
        {
            return hash;
        }
    };
}
