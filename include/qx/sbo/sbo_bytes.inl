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
    QX_STATIC_ASSERT_EQ(sizeof(sbo_bytes), nSBOSize);
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

QX_PUSH_SUPPRESS_MSVC_WARNINGS(4701);
template<class traits_t>
bool sbo_bytes<traits_t>::resize(
    size_type       nNewSize,
    size_type       nAlignment,
    sbo_resize_type eSboResizeType,
    bool            bMemmove) noexcept
{
    bool bRet = true;

    const size_type nSizeToAllocate =
        eSboResizeType != sbo_resize_type::shrink_to_fit ? (nNewSize + nAlignment - 1) & ~(nAlignment - 1) : nNewSize;

    const bool bSmallAtStart = is_small();

    if (eSboResizeType == sbo_resize_type::shrink_to_fit // need to decrease a size
        || eSboResizeType == sbo_resize_type::common && !bSmallAtStart && bShrinkToFitWhenSmall
        || m_nSize == 0                  // SBO is empty
        || nSizeToAllocate > capacity()) // need to increase a size
    {
        buffer buff;

        if (nSizeToAllocate <= m_Buffer.size())
        {
            if (!bSmallAtStart && (bShrinkToFitWhenSmall || eSboResizeType == sbo_resize_type::shrink_to_fit))
            {
                // free allocated memory and move SBO to buffer

                if (bMemmove)
                    std::memmove(buff.data(), m_pData, nSizeToAllocate);

                free();

                m_Buffer = buff;
            }

            m_nSize = nSizeToAllocate;
        }
        else
        {
            size_type nStartSize = 0;
            if (bSmallAtStart)
            {
                buff       = m_Buffer;
                nStartSize = m_nSize;
            }

            if (void* pNewBlock = std::realloc(bSmallAtStart ? nullptr : m_pData, nSizeToAllocate))
            {
                m_nAllocatedSize = nSizeToAllocate;
                m_pData          = static_cast<std::byte*>(pNewBlock);

                if (bMemmove && bSmallAtStart && m_nSize > 0)
                    std::memmove(m_pData, buff.data(), nStartSize);
            }
            else
            {
                bRet = false;
            }
        }
    }

    if (bRet && eSboResizeType == sbo_resize_type::common)
        m_nSize = nNewSize;

    return bRet;
}
QX_POP_SUPPRESS_WARNINGS();

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
std::byte* sbo_bytes<traits_t>::data() noexcept
{
    if (is_small())
        return m_Buffer.data();
    else
        return m_pData;
}

template<class traits_t>
const std::byte* sbo_bytes<traits_t>::data() const noexcept
{
    return QX_CONST_CAST_THIS()->data();
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
