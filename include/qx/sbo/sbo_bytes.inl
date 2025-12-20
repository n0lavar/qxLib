/**

    @file      sbo_bytes.inl
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class traits_t>
sbo_bytes<traits_t>::sbo_bytes(sbo_bytes&& other) noexcept
{
    *this = std::move(other);
}

template<class traits_t>
sbo_bytes<traits_t>::~sbo_bytes() noexcept
{
    free();
}

template<class traits_t>
sbo_bytes<traits_t>& sbo_bytes<traits_t>::operator=(sbo_bytes&& other) noexcept
{
    if (!is_small() && !other.is_small())
    {
        std::swap(m_pData, other.m_pData);
    }
    else if (is_small() && other.is_small())
    {
        std::swap(m_Buffer, other.m_Buffer);
    }
    else if (is_small() && !other.is_small())
    {
        buffer thisBuffer = std::move(m_Buffer);
        m_pData           = other.m_pData;
        other.m_Buffer    = std::move(thisBuffer);
    }
    else if (!is_small() && other.is_small())
    {
        std::byte* thisAllocated = m_pData;
        m_Buffer                 = std::move(other.m_Buffer);
        other.m_pData            = thisAllocated;
    }

    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);

    return *this;
}

template<class traits_t>
std::byte* sbo_bytes<traits_t>::data() noexcept
{
    static_assert(
        sizeof(sbo_bytes) == 32 || sizeof(sbo_bytes) == 64 || sizeof(sbo_bytes) == 128 || sizeof(sbo_bytes) == 256
            || sizeof(sbo_bytes) > 256,
        "The buffer size should be such that the final size of the structure is aligned");

    if (is_small())
        return m_Buffer.data();
    else
        return m_pData;
}

template<class traits_t>
void sbo_bytes<traits_t>::free() noexcept
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
bool sbo_bytes<traits_t>::resize(
    size_type       nNewSize,
    size_type       nAlign,
    sbo_resize_type eType,
    void* (*moveObject)(void* pDest, const void* pSource, std::size_t nSize)) noexcept
{
    bool bRet = true;

    const size_type nSizeToAllocate = nAlign > 0 ? nAlign * ((nNewSize + 1) / nAlign + 1) : nNewSize + 1;

    if (eType == sbo_resize_type::shrink_to_fit // need to decrease size
        || size() == 0                          // SBO is empty
        || nSizeToAllocate > capacity())        // need to increase size
    {
        const bool bSmallAtStart = is_small();

        buffer buff;

        if (nSizeToAllocate <= m_Buffer.size())
        {
            if (!bSmallAtStart && (bShrinkToFitWhenSmall || eType == sbo_resize_type::shrink_to_fit))
            {
                // free allocated memory and move SBO to buffer
                moveObject(buff.data(), m_pData, nSizeToAllocate);
                free();
                m_Buffer = buff;
            }

            m_nSize = nSizeToAllocate - 1;
        }
        else
        {
            size_type nStartSize = 0;
            if (bSmallAtStart)
            {
                buff       = m_Buffer;
                nStartSize = size();
            }

            if (void* pNewBlock = std::realloc(bSmallAtStart ? nullptr : m_pData, nSizeToAllocate))
            {
                m_nAllocatedSize = nSizeToAllocate;
                m_pData          = static_cast<std::byte*>(pNewBlock);

                if (bSmallAtStart)
                    moveObject(m_pData, buff.data(), nStartSize);
            }
            else
            {
                bRet = false;
            }
        }
    }

    if (bRet && eType == sbo_resize_type::common)
        m_nSize = nNewSize;

    return bRet;
}

template<class traits_t>
typename sbo_bytes<traits_t>::size_type sbo_bytes<traits_t>::size() const noexcept
{
    return m_nSize;
}

template<class traits_t>
typename sbo_bytes<traits_t>::size_type sbo_bytes<traits_t>::capacity() const noexcept
{
    if (is_small())
        return m_Buffer.size();
    else
        return m_nAllocatedSize;
}

template<class traits_t>
bool sbo_bytes<traits_t>::is_small() const noexcept
{
    return m_nAllocatedSize == 0;
}

} // namespace qx
