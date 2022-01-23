/**

    @file      string_data.inl
    @author    Khrapov
    @date      8.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class Traits>
typename string_data<Traits>::pointer string_data<Traits>::data() noexcept
{
    if (is_small())
        return m_Buffer.data();
    else
        return m_pData;
}

template<class Traits>
void string_data<Traits>::free() noexcept
{
    if (!is_small())
    {
        std::free(m_pData);
        m_pData = nullptr;
    }

    m_nSize          = 0;
    m_nAllocatedSize = 0;
}

template<class Traits>
bool string_data<Traits>::resize(
    size_type          nSymbols,
    size_type          nAlign,
    string_resize_type eType) noexcept
{
    bool bRet = true;

    typename Traits::size_type nSymbolsToAllocate =
        nAlign > 0 ? nAlign * ((nSymbols + 1) / nAlign + 1) : nSymbols + 1;

    if (eType == string_resize_type::shrink_to_fit // need to decrease size
        || size() == 0                             // string is empty
        || nSymbolsToAllocate > capacity())        // need to increase size
    {
        buffer    buff;
        bool      bSmallAtStart = is_small();
        size_type nNewSize      = nSymbolsToAllocate * sizeof(value_type);

        if (nSymbolsToAllocate <= m_Buffer.size())
        {
            if (!bSmallAtStart)
            {
                // free allocated memory and move string to buffer
                std::memmove(buff.data(), m_pData, nNewSize);
                free();
                m_Buffer = buff;
                m_nSize  = nSymbolsToAllocate - 1;
            }
        }
        else
        {
            size_type nStartSize = 0;
            if (bSmallAtStart)
            {
                buff       = m_Buffer;
                nStartSize = size() * sizeof(value_type);
            }

            if (void* pNewBlock =
                    std::realloc(bSmallAtStart ? nullptr : m_pData, nNewSize))
            {
                m_nAllocatedSize = nSymbolsToAllocate;
                m_pData = static_cast<typename Traits::value_type*>(pNewBlock);

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

template<class Traits>
typename string_data<Traits>::size_type string_data<Traits>::size(
    void) const noexcept
{
    return m_nSize;
}

template<class Traits>
typename string_data<Traits>::size_type string_data<Traits>::capacity(
    void) const noexcept
{
    if (is_small())
        return m_Buffer.size();
    else
        return m_nAllocatedSize;
}

template<class Traits>
bool string_data<Traits>::is_small() const noexcept
{
    return m_nAllocatedSize == 0;
}

} // namespace qx
