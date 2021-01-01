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
        : m_nHash(murmur_32_hash(pszString, nSize, Traits::hash_seed()))
    {
    }

    constexpr basic_string_hash(const_pointer pszString) noexcept
        : m_nHash(murmur_32_hash(pszString, Traits::length(pszString), Traits::hash_seed()))
    {
    }

    template <class String, class = std::enable_if_t<std::is_class_v<String>>>
    constexpr basic_string_hash(const String& sString) noexcept
        : m_nHash(murmur_32_hash(sString.data(), sString.size(), Traits::hash_seed()))
    {
    }

    constexpr operator u32() const noexcept
    {
        return m_nHash;
    }

private:

    u32 m_nHash = 0;
};

using string_hash  = basic_string_hash<char_traits<char>>;
using wstring_hash = basic_string_hash<char_traits<wchar_t>>;

}

namespace std
{
    template<>
    struct hash<qx::string_hash>
    {
        u32 operator()(const qx::string_hash& hash) const
        {
            return hash;
        }
    };

    template<>
    struct hash<qx::wstring_hash>
    {
        u32 operator()(const qx::wstring_hash& hash) const
        {
            return hash;
        }
    };
}
