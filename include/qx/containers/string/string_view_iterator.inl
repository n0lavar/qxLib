/**

    @file      string_view_iterator.inl
    @author    Khrapov
    @date      24.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator>::base_string_view_iterator(
    value_type                       svFull,
    char_t                           chDelimiter,
    flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept
    : m_svFull(svFull)
    , m_nCurrentBegin(bForwardIterator ? (!m_svFull.empty() ? 0 : -1) : (!m_svFull.empty() ? m_svFull.size() - 1 : -1))
    , m_nCurrentEnd(m_nCurrentBegin)
    , m_chDelimiter(chDelimiter)
    , m_eDelimiterInclusionFlags(eDelimiterInclusionFlags)
{
    next(true);
}

template<class char_t, bool bForwardIterator>
base_string_view_iterator<char_t, bForwardIterator>::operator bool() const noexcept
{
    return m_nCurrentBegin != m_nCurrentEnd;
}

template<class char_t, bool bForwardIterator>
constexpr typename base_string_view_iterator<char_t, bForwardIterator>::value_type base_string_view_iterator<
    char_t,
    bForwardIterator>::operator*() const noexcept
{
    auto itBegin = m_svFull.cbegin() + (bForwardIterator ? m_nCurrentBegin : m_nCurrentEnd + 1);
    if (m_eDelimiterInclusionFlags.contains(delimiter_inclusion_flags::begin))
        while (itBegin != m_svFull.cbegin() && *(itBegin - 1) == m_chDelimiter)
            --itBegin;

    auto itEnd = m_svFull.cbegin() + (bForwardIterator ? m_nCurrentEnd : m_nCurrentBegin + 1);
    if (m_eDelimiterInclusionFlags.contains(delimiter_inclusion_flags::end))
        while (itEnd != m_svFull.cend() && *(itEnd) == m_chDelimiter)
            ++itEnd;

    return value_type(itBegin, itEnd);
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator>& base_string_view_iterator<char_t, bForwardIterator>::
    operator++() noexcept
{
    next(true);
    return *this;
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator> base_string_view_iterator<char_t, bForwardIterator>::
    operator++(int) const noexcept
{
    base_string_view_iterator it(*this);
    ++it;
    return it;
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator>& base_string_view_iterator<char_t, bForwardIterator>::
    operator--() noexcept
{
    next(false);
    return *this;
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator> base_string_view_iterator<char_t, bForwardIterator>::
    operator--(int) const noexcept
{
    base_string_view_iterator it(*this);
    --it;
    return it;
}

template<class char_t, bool bForwardIterator>
constexpr void base_string_view_iterator<char_t, bForwardIterator>::next(bool bForwardDirection) noexcept
{
    const bool   bRealDirectionIsForward = bForwardIterator == bForwardDirection;
    const size_t nEnd                    = bRealDirectionIsForward ? (!m_svFull.empty() ? m_svFull.size() : -1) : -1;

    size_t nNewStart = m_nCurrentEnd;
    while (nNewStart != nEnd && m_svFull[nNewStart] == m_chDelimiter)
    {
        nNewStart = bRealDirectionIsForward ? nNewStart + 1 : nNewStart - 1;
    }

    size_t nNewEnd = nEnd;
    if (nNewStart != nEnd)
    {
        if (const size_t nDelimiterPos = bRealDirectionIsForward ? m_svFull.find(m_chDelimiter, nNewStart)
                                                                 : m_svFull.rfind(m_chDelimiter, nNewStart);
            nDelimiterPos != value_type::npos)
        {
            nNewEnd = nDelimiterPos;
        }
    }

    m_nCurrentBegin = nNewStart;
    m_nCurrentEnd   = nNewEnd;
}

} // namespace qx
