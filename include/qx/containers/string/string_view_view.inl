/**

    @file      string_view_view.inl
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class char_t>
constexpr string_view_view<char_t>::string_view_view(
    basic_string_view<char_t>        svFull,
    char_t                           chDelimiter,
    flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept
    : m_svFull(svFull)
    , m_chDelimiter(chDelimiter)
    , m_eDelimiterInclusionFlags(eDelimiterInclusionFlags)
{
}

template<class char_t>
string_view_iterator<char_t> string_view_view<char_t>::begin() const noexcept
{
    return string_view_iterator<char_t>::begin(m_svFull, m_chDelimiter, m_eDelimiterInclusionFlags);
}

template<class char_t>
string_view_iterator<char_t> string_view_view<char_t>::end() const noexcept
{
    return string_view_iterator<char_t>::end(m_svFull, m_chDelimiter, m_eDelimiterInclusionFlags);
}

} // namespace qx
