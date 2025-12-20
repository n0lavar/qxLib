/**

    @file      bytes_sbo.inl
    @author    Khrapov
    @date      20.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class traits_t>
bytes_sbo<traits_t>::bytes_sbo(bytes_sbo&& other) noexcept
{
    std::swap(m_Data, other.m_Data);
    std::swap(m_nSize, other.m_nSize);
    std::swap(m_nAllocatedSize, other.m_nAllocatedSize);
}

template<class traits_t>
bytes_sbo<traits_t>::~bytes_sbo() noexcept
{
    free();
}

template<class traits_t>
std::byte* bytes_sbo<traits_t>::data() noexcept
{
    static_assert(
        sizeof(bytes_sbo) == 32 || sizeof(bytes_sbo) == 64 || sizeof(bytes_sbo) == 128 || sizeof(bytes_sbo) == 256
            || sizeof(bytes_sbo) > 256,
        "The buffer size should be such that the final size of the structure is aligned");

    return std::visit(
        visit_overload { [](std::byte* pData)
                         {
                             return pData;
                         },
                         [](buffer& data)
                         {
                             return data.data();
                         } },
        m_Data);
}

template<class traits_t>
void bytes_sbo<traits_t>::free() noexcept
{
    if (auto pData = std::get_if<std::byte*>(m_Data))
    {
        std::free(*pData);
        m_Data = buffer();
    }

    m_nSize          = 0;
    m_nAllocatedSize = 0;
}

template<class traits_t>
bool bytes_sbo<traits_t>::resize(size_type nNewSize, size_type nAlign, sbo_resize_type eType) noexcept
{
    bool bRet = true;

    const size_type nSizeToAllocate = nAlign > 0 ? nAlign * ((nNewSize + 1) / nAlign + 1) : nNewSize + 1;

    if (eType == sbo_resize_type::shrink_to_fit // need to decrease size
        || size() == 0                          // SBO is empty
        || nSizeToAllocate > capacity())        // need to increase size
    {
        std::byte** pData   = std::get_if<std::byte*>(m_Data);
        buffer*     pBuffer = std::get_if<buffer>(m_Data);

        buffer buff;

        if (nSizeToAllocate <= nSBOSize)
        {
            if (pData && (bShrinkToFitWhenSmall || eType == sbo_resize_type::shrink_to_fit))
            {
                // free allocated memory and move SBO to buffer
                std::memmove(buff.data(), *pData, nSizeToAllocate);
                free();
                m_Data = buff;
            }

            m_nSize = nSizeToAllocate - 1;
        }
        else
        {
            size_type nStartSize = 0;
            if (pBuffer)
            {
                buff       = *pBuffer;
                nStartSize = size();
            }

            if (void* pNewBlock = std::realloc(pData ? *pData : nullptr, nSizeToAllocate))
            {
                m_nAllocatedSize = nSizeToAllocate;
                m_Data           = static_cast<std::byte*>(pNewBlock);

                if (pBuffer)
                    std::memmove(pNewBlock, buff.data(), nStartSize);
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
typename bytes_sbo<traits_t>::size_type bytes_sbo<traits_t>::size() const noexcept
{
    return m_nSize;
}

template<class traits_t>
typename bytes_sbo<traits_t>::size_type bytes_sbo<traits_t>::capacity() const noexcept
{
    return std::visit(visit_overload { [this](std::byte* pData)
                                       {
                                           return m_nAllocatedSize;
                                       },
                                       [](buffer& data)
                                       {
                                           return data.size();
                                       } });
}

template<class traits_t>
bool bytes_sbo<traits_t>::is_small() const noexcept
{
    return std::holds_alternative<buffer>(m_Data);
}

} // namespace qx
