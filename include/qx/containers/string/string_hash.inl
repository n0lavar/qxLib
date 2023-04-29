/**

    @file      string_hash.inl
    @author    Khrapov
    @date      18.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

// ----------------------------- basic_string_hash -----------------------------

template<class traits_t>
constexpr basic_string_hash<traits_t>::basic_string_hash(const_pointer pString, size_type nSize) noexcept
    : m_nHash(traits_t::hash_function(pString, traits_t::hash_seed(), nSize))
{
}

template<class traits_t>
constexpr basic_string_hash<traits_t>::basic_string_hash(const_pointer pszString) noexcept
{
    if constexpr (detail::has_zero_termonated_hash_func_overload<traits_t>)
    {
        m_nHash = traits_t::hash_function(pszString, traits_t::hash_seed());
    }
    else
    {
        m_nHash = traits_t::hash_function(pszString, traits_t::hash_seed(), traits_t::length(pszString));
    }
}

template<class traits_t>
template<string_convertable string_t>
constexpr basic_string_hash<traits_t>::basic_string_hash(const string_t& sString) noexcept
    : m_nHash(traits_t::hash_function(sString.data(), traits_t::hash_seed(), sString.size()))
{
}

template<class traits_t>
constexpr basic_string_hash<traits_t>::operator size_t() const noexcept
{
    return m_nHash;
}



// -------------------------- fast_hash_string_traits --------------------------

template<class value_t>
constexpr typename char_traits<value_t>::size_type fast_hash_string_traits<value_t>::hash_function(
    typename char_traits<value_t>::const_pointer sStr,
    size_t                                       nSeed,
    typename char_traits<value_t>::size_type     nLen) noexcept
{
    return djb2a_hash(sStr, nSeed, nLen);
}

template<class value_t>
constexpr typename char_traits<value_t>::size_type fast_hash_string_traits<value_t>::hash_function(
    typename char_traits<value_t>::const_pointer pszStr,
    size_t                                       nSeed) noexcept
{
    return djb2a_hash(pszStr, nSeed);
}

// ------------------------------- operator"" _sh ------------------------------

namespace literals
{

constexpr basic_string_hash<fast_hash_string_traits<char>> operator"" _sh(const char* pszText, size_t nSize)
{
    return basic_string_hash<fast_hash_string_traits<char>>(pszText, nSize);
}

constexpr basic_string_hash<fast_hash_string_traits<wchar_t>> operator"" _sh(const wchar_t* pszText, size_t nSize)
{
    return basic_string_hash<fast_hash_string_traits<wchar_t>>(pszText, nSize);
}

} // namespace literals

} // namespace qx



// --------------------------------- std::hash ---------------------------------

namespace std
{

template<class traits_t>
struct hash<qx::basic_string_hash<traits_t>>
{
    size_t operator()(const qx::basic_string_hash<traits_t>& hash) const
    {
        return hash;
    }
};

} // namespace std
