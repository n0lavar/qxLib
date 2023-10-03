/**

    @file      string_data.inl
    @author    Khrapov
    @date      8.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class traits_t>
typename string_data<traits_t>::pointer string_data<traits_t>::data() noexcept
{
    if (is_small())
        return m_Buffer.data();
    else
        return m_pData;
}

template<class traits_t>
void string_data<traits_t>::free() noexcept
{
    if (!is_small())
    {
        std::free(m_pData);
        m_pData = nullptr;
    }

    m_nSize          = 0;
    m_nAllocatedSize = 0;
}

template<class traits_t>
bool string_data<traits_t>::resize(size_type nSymbols, size_type nAlign, string_resize_type eType) noexcept
{
    bool bRet = true;

    typename traits_t::size_type nSymbolsToAllocate =
        nAlign > 0 ? nAlign * ((nSymbols + 1) / nAlign + 1) : nSymbols + 1;

    if (eType == string_resize_type::shrink_to_fit // need to decrease size
        || size() == 0                             // string is empty
        || nSymbolsToAllocate > capacity())        // need to increase size
    {
        const bool      bSmallAtStart = is_small();
        const size_type nNewSize      = nSymbolsToAllocate * sizeof(value_type);

        buffer buff;

        if (nSymbolsToAllocate <= m_Buffer.size())
        {
            if (!bSmallAtStart && (traits_t::shrink_to_fit_when_small() || eType == string_resize_type::shrink_to_fit))
            {
                // free allocated memory and move string to buffer
                std::memmove(buff.data(), m_pData, nNewSize);
                free();
                m_Buffer = buff;
            }

            m_nSize = nSymbolsToAllocate - 1;
        }
        else
        {
            size_type nStartSize = 0;
            if (bSmallAtStart)
            {
                buff       = m_Buffer;
                nStartSize = size() * sizeof(value_type);
            }

            if (void* pNewBlock = std::realloc(bSmallAtStart ? nullptr : m_pData, nNewSize))
            {
                m_nAllocatedSize = nSymbolsToAllocate;
                m_pData          = static_cast<typename traits_t::value_type*>(pNewBlock);

                if (bSmallAtStart)
                    std::memmove(m_pData, buff.data(), nStartSize);
            }
            else
            {
                bRet = false;
            }
        }
    }

    if (bRet && eType == string_resize_type::common)
        m_nSize = nSymbols;

    return bRet;
}

template<class traits_t>
typename string_data<traits_t>::size_type string_data<traits_t>::size() const noexcept
{
    return m_nSize;
}

template<class traits_t>
typename string_data<traits_t>::size_type string_data<traits_t>::capacity() const noexcept
{
    if (is_small())
        return m_Buffer.size();
    else
        return m_nAllocatedSize;
}

template<class traits_t>
bool string_data<traits_t>::is_small() const noexcept
{
    return m_nAllocatedSize == 0;
}

} // namespace qx
