/**

    @file      sbo_bytes.inl
    @author    Khrapov
    @date      20.12.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class traits_t>
sbo_bytes<traits_t>::sbo_bytes(sbo_bytes&& other) noexcept
{
    std::swap(m_Data, other.m_Data);
    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
}

template<class traits_t>
sbo_bytes<traits_t>::~sbo_bytes() noexcept
{
    QX_STATIC_ASSERT_EQ(sizeof(sbo_bytes), nSBOSize);
    free();
    m_nSize = 0;
}

template<class traits_t>
sbo_bytes<traits_t>& sbo_bytes<traits_t>::operator=(sbo_bytes&& other) noexcept
{
    std::swap(m_Data, other.m_Data);
    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
    return *this;
}

template<class traits_t>
bool sbo_bytes<traits_t>::resize(size_type nRequestedSize) noexcept
{
    bool bRet = true;
    if (nRequestedSize > capacity())
    {
        bRet = reallocate_to_big(get_new_size(nRequestedSize));
    }
    else
    {
        if constexpr (bShrinkToFitWhenSmall)
            if (!is_small() && nRequestedSize <= nBufferSize)
                reallocate_to_small(nRequestedSize);
    }

    if (bRet) [[likely]]
        m_nSize = nRequestedSize;

    return bRet;
}

template<class traits_t>
bool sbo_bytes<traits_t>::reserve(size_type nRequestedSize) noexcept
{
    if (nRequestedSize <= capacity())
        return true;

    return reallocate_to_big(get_new_size(nRequestedSize));
}

template<class traits_t>
bool sbo_bytes<traits_t>::shrink_to_fit() noexcept
{
    if (m_nSize <= nBufferSize)
    {
        if (!is_small())
            reallocate_to_small(m_nSize);

        return true;
    }
    else
    {
        return reallocate_to_big(m_nSize);
    }
}

template<class traits_t>
void sbo_bytes<traits_t>::free() noexcept
{
    if (!is_small())
    {
        std::free(m_Data.pData);
        m_Data.buffer = buffer_type();
    }

    m_nAllocatedSize = 0;
}

template<class traits_t>
QX_FORCE_INLINE std::byte* sbo_bytes<traits_t>::data() noexcept
{
    if (is_small())
        return m_Data.buffer.data();
    else
        return m_Data.pData;
}

template<class traits_t>
QX_FORCE_INLINE const std::byte* sbo_bytes<traits_t>::data() const noexcept
{
    return QX_CONST_CAST_THIS()->data();
}

template<class traits_t>
QX_FORCE_INLINE typename sbo_bytes<traits_t>::size_type sbo_bytes<traits_t>::size() const noexcept
{
    return m_nSize;
}

template<class traits_t>
QX_FORCE_INLINE typename sbo_bytes<traits_t>::size_type sbo_bytes<traits_t>::capacity() const noexcept
{
    return is_small() ? nBufferSize : m_nAllocatedSize;
}

template<class traits_t>
QX_FORCE_INLINE bool sbo_bytes<traits_t>::is_small() const noexcept
{
    return m_nAllocatedSize == 0;
}

template<class traits_t>
bool sbo_bytes<traits_t>::reallocate_to_big(size_type nNewSize) noexcept
{
    const bool bSmallAtStart = is_small();

    if (void* pNewBlock = std::realloc(bSmallAtStart ? nullptr : m_Data.pData, nNewSize)) [[likely]]
    {
        if constexpr (bPreserveContents)
            if (bSmallAtStart)
                std::memcpy(pNewBlock, m_Data.buffer.data(), std::min(nNewSize, capacity()));

        m_Data.pData     = static_cast<std::byte*>(pNewBlock);
        m_nAllocatedSize = nNewSize;
        return true;
    }
    else
    {
        return false;
    }
}

template<class traits_t>
void sbo_bytes<traits_t>::reallocate_to_small(size_type nNewSize) noexcept
{
    if constexpr (bPreserveContents)
    {
        buffer_type buff;
        std::memcpy(buff.data(), m_Data.pData, std::min(nNewSize, capacity()));
        free();
        m_Data.buffer = buff;
    }
    else
    {
        free();
    }
}

template<class traits_t>
QX_FORCE_INLINE sbo_bytes<traits_t>::size_type sbo_bytes<traits_t>::get_new_size(
    size_type nRequestedSize) const noexcept
{
    const size_t nCapacity       = capacity();
    const size_t nAdvancedGrowth = traits_type::growth_strategy(nCapacity);
    size_t       nNewSize        = nRequestedSize;
    if (nCapacity < nRequestedSize && nRequestedSize < nAdvancedGrowth)
        nNewSize = nAdvancedGrowth;

    return nNewSize;
}

} // namespace qx
