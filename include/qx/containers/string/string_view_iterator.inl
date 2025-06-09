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
    , m_nCurrentBegin(bForwardIterator ? 0 : m_svFull.size())
    , m_nCurrentEnd(m_nCurrentBegin)
    , m_chDelimiter(chDelimiter)
    , m_eDelimiterInclusionFlags(eDelimiterInclusionFlags)
{
    next(true);
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator>::operator bool() const noexcept
{
    return m_nCurrentBegin != m_nCurrentEnd;
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator> base_string_view_iterator<char_t, bForwardIterator>::
    begin(value_type svFull, char_t chDelimiter, flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept
{
    return base_string_view_iterator(svFull, chDelimiter, eDelimiterInclusionFlags);
}

template<class char_t, bool bForwardIterator>
constexpr base_string_view_iterator<char_t, bForwardIterator> base_string_view_iterator<char_t, bForwardIterator>::end(
    value_type                       svFull,
    char_t                           chDelimiter,
    flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept
{
    size_t nEnd = bForwardIterator ? svFull.size() : 0;
    return base_string_view_iterator(svFull, nEnd, nEnd, chDelimiter, eDelimiterInclusionFlags);
}

template<class char_t, bool bForwardIterator>
constexpr typename base_string_view_iterator<char_t, bForwardIterator>::value_type base_string_view_iterator<
    char_t,
    bForwardIterator>::operator*() const noexcept
{
    auto itBegin = m_svFull.cbegin() + m_nCurrentBegin;
    if (m_eDelimiterInclusionFlags.contains(delimiter_inclusion_flags::begin))
        while (itBegin != m_svFull.cbegin() && *(itBegin - 1) == m_chDelimiter)
            --itBegin;

    auto itEnd = m_svFull.cbegin() + m_nCurrentEnd;
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
constexpr base_string_view_iterator<char_t, bForwardIterator>::base_string_view_iterator(
    value_type                       svFull,
    size_t                           nCurrentBegin,
    size_t                           nCurrentEnd,
    char_t                           chDelimiter,
    flags<delimiter_inclusion_flags> eDelimiterInclusionFlags) noexcept
    : m_svFull(svFull)
    , m_nCurrentBegin(nCurrentBegin)
    , m_nCurrentEnd(nCurrentEnd)
    , m_chDelimiter(chDelimiter)
    , m_eDelimiterInclusionFlags(eDelimiterInclusionFlags)
{
}

template<class char_t, bool bForwardIterator>
constexpr void base_string_view_iterator<char_t, bForwardIterator>::next(bool bForwardDirection) noexcept
{
    const bool       bRealDirectionIsForward = bForwardIterator == bForwardDirection;
    const size_t     nForwardEnd             = m_svFull.size();
    constexpr size_t nBackwardEnd            = static_cast<size_t>(-1);
    const size_t     nEnd                    = bRealDirectionIsForward ? nForwardEnd : nBackwardEnd;

    auto move_next = [bRealDirectionIsForward](size_t nPos) -> size_t
    {
        return bRealDirectionIsForward ? nPos + 1 : nPos - 1;
    };

    size_t nSearchStart = bRealDirectionIsForward ? m_nCurrentEnd : m_nCurrentBegin - 1;

    // if *this == end() and we move to begin(), shift from end()
    if (bRealDirectionIsForward && nSearchStart == nBackwardEnd
        || !bRealDirectionIsForward && nSearchStart == nForwardEnd)
    {
        nSearchStart = move_next(nSearchStart);
    }

    // skip all "start" delimiters
    while (nSearchStart != nEnd && m_svFull[nSearchStart] == m_chDelimiter)
    {
        nSearchStart = move_next(nSearchStart);
    }

    // find the "end" delimiter if any
    size_t nSearchPos = nEnd;
    if (nSearchStart != nEnd)
    {
        if (const size_t nDelimiterPos = bRealDirectionIsForward ? m_svFull.find(m_chDelimiter, nSearchStart)
                                                                 : m_svFull.rfind(m_chDelimiter, nSearchStart);
            nDelimiterPos != value_type::npos)
        {
            nSearchPos = nDelimiterPos;
        }
    }

    if (bRealDirectionIsForward)
    {
        m_nCurrentBegin = nSearchStart;
        m_nCurrentEnd   = nSearchPos;
    }
    else
    {
        m_nCurrentBegin = nSearchPos + 1;
        m_nCurrentEnd   = nSearchStart + 1;
    }
}

} // namespace qx
