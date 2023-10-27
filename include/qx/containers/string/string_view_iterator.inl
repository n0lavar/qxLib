/**

    @file      string_view_iterator.inl
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class char_t>
constexpr string_view_iterator<char_t> string_view_iterator<char_t>::begin(
    value_type                       svFull,
    char_t                           chDelimiter,
    flags<delimiter_inclusion_flags> eDelimiterInclusionFlags)
{
    return ++string_view_iterator(svFull, chDelimiter, eDelimiterInclusionFlags);
}

template<class char_t>
constexpr string_view_iterator<char_t> string_view_iterator<char_t>::end()
{
    return string_view_iterator(value_type(nullptr, 0), QX_TEXT('\0'), delimiter_inclusion_flags::none);
}

template<class char_t>
constexpr typename string_view_iterator<char_t>::value_type string_view_iterator<char_t>::operator*() const noexcept
{
    return m_svCurrent;
}

template<class char_t>
constexpr string_view_iterator<char_t>& string_view_iterator<char_t>::operator++() noexcept
{
    next();
    return *this;
}

template<class char_t>
constexpr string_view_iterator<char_t> string_view_iterator<char_t>::operator++(int) const noexcept
{
    string_view_iterator itResult(*this);
    ++itResult;
    return itResult;
}

template<class char_t>
constexpr string_view_iterator<char_t>::string_view_iterator(
    value_type                       svFull,
    char_t                           chDelimiter,
    flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept
    : m_svFull(svFull)
    , m_svCurrent(value_type(m_svFull.data(), 0))
    , m_chDelimiter(chDelimiter)
    , m_eDelimiterInclusionFlags(eDelimiterInclusionFlags)
{
}

template<class char_t>
constexpr void string_view_iterator<char_t>::next() noexcept
{
    size_type nStart = m_svCurrent.data() - m_svFull.data() + m_svCurrent.size();
    size_type nEnd   = nStart;

    auto set_start = [this](size_type nStart)
    {
        m_svCurrent = value_type(
            m_svFull.data()
                + (m_eDelimiterInclusionFlags.contains(delimiter_inclusion_flags::begin) && nStart != 0 ? nStart - 1
                                                                                                        : nStart),
            0);
    };

    auto set_end = [this](size_type nEnd)
    {
        m_svCurrent = value_type(
            m_svCurrent.data(),
            (m_eDelimiterInclusionFlags.contains(delimiter_inclusion_flags::end) ? nEnd + 1 : nEnd)
                - (m_svCurrent.data() - m_svFull.data()));
    };

    while ((nEnd = m_svFull.find(m_chDelimiter, nStart)) != value_type::npos)
    {
        if (nStart != nEnd)
        {
            set_start(nStart);
            set_end(nEnd);
            return;
        }

        nStart = nEnd;
        while (nStart < m_svFull.size() && m_svFull[nStart] == m_chDelimiter)
            ++nStart;
    }

    if (nStart != m_svFull.size())
    {
        set_start(nStart);
        m_svCurrent = value_type(m_svCurrent.data(), m_svFull.size() - (m_svCurrent.data() - m_svFull.data()));
        return;
    }

    *this = end();
}

} // namespace qx
