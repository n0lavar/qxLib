/**

    @file      string_hash.inl
    @author    Khrapov
    @date      18.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

// ----------------------------- basic_string_hash -----------------------------

template<class Traits>
constexpr basic_string_hash<Traits>::basic_string_hash(
    const_pointer pString,
    size_type     nSize) noexcept
    : m_nHash(Traits::hash_function(pString, Traits::hash_seed(), nSize))
{
}

template<class Traits>
constexpr basic_string_hash<Traits>::basic_string_hash(
    const_pointer pszString) noexcept
{
    if constexpr (detail::has_zero_termonated_hash_func_overload<Traits>)
    {
        m_nHash = Traits::hash_function(pszString, Traits::hash_seed());
    }
    else
    {
        m_nHash = Traits::hash_function(
            pszString,
            Traits::hash_seed(),
            Traits::length(pszString));
    }
}

template<class Traits>
template<string_convertable String>
constexpr basic_string_hash<Traits>::basic_string_hash(
    const String& sString) noexcept
    : m_nHash(Traits::hash_function(
        sString.data(),
        Traits::hash_seed(),
        sString.size()))
{
}

template<class Traits>
constexpr basic_string_hash<Traits>::operator size_t() const noexcept
{
    return m_nHash;
}



// -------------------------- fast_hash_string_traits --------------------------

template<typename value_type>
constexpr typename char_traits<value_type>::size_type fast_hash_string_traits<
    value_type>::
    hash_function(
        typename char_traits<value_type>::const_pointer sStr,
        size_t                                          nSeed,
        typename char_traits<value_type>::size_type     nLen) noexcept
{
    return djb2a_hash(sStr, nSeed, nLen);
}

template<typename value_type>
constexpr typename char_traits<value_type>::size_type fast_hash_string_traits<
    value_type>::
    hash_function(
        typename char_traits<value_type>::const_pointer pszStr,
        size_t                                          nSeed) noexcept
{
    return djb2a_hash(pszStr, nSeed);
}

} // namespace qx



// --------------------------------- std::hash ---------------------------------

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

} // namespace std
