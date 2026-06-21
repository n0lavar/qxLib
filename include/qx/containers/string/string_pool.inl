/**

    @file      string_pool.inl
    @author    Khrapov
    @date      17.01.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<size_t nSize>
string_pool<nSize>::string_pool()
{
    // Pre-create empty strings with reserved capacity 32
    for (string& s : m_Storage)
        normalize(s);

    for (auto& b : m_FreeMask)
        b.store(~0ull, std::memory_order_relaxed);

    // Disable unused bits in the last block if nSize is not a multiple of 64
    constexpr size_t nRemove = nSize % bTotalBits;
    if constexpr (nRemove != 0)
    {
        u64 nValid = (1ull << nRemove) - 1;
        m_FreeMask[m_FreeMask.size() - 1].store(nValid, std::memory_order_relaxed);
    }
}

template<size_t nSize>
typename string_pool<nSize>::item string_pool<nSize>::acquire()
{
    for (size_t nBlock = 0; nBlock < m_FreeMask.size(); ++nBlock)
    {
        u64 nMask = m_FreeMask[nBlock].load(std::memory_order_relaxed);

        while (nMask)
        {
            const u64 nBit     = nMask & (~nMask + 1); // lowest set bit
            const u64 nNewMask = nMask & ~nBit;        // mark as used

            if (m_FreeMask[nBlock]
                    .compare_exchange_weak(nMask, nNewMask, std::memory_order_acquire, std::memory_order_relaxed))
            {
                const size_t nIndex = nBlock * bTotalBits + ctz64(nBit);
                return item { std::move(m_Storage[nIndex]), static_cast<int>(nIndex) };
            }
        }
    }

    // Pool is empty
    return item { string(), nFreeString };
}

template<size_t nSize>
void string_pool<nSize>::release(string sValue, int nIndex)
{
    if (nIndex == nFreeString)
        return;

    const size_t nSizeIndex = static_cast<size_t>(nIndex);
    if (nSizeIndex >= nSize)
        return;

    normalize(sValue);

    // Exclusive access is guaranteed by the occupancy bit
    m_Storage[nSizeIndex] = std::move(sValue);

    const size_t nBlock  = nSizeIndex / bTotalBits;
    const size_t nOffset = nSizeIndex % bTotalBits;
    const u64    nBit    = 1ull << nOffset;

    // Make the slot visible as free
    m_FreeMask[nBlock].fetch_or(nBit, std::memory_order_release);
}

template<size_t nSize>
int string_pool<nSize>::ctz64(u64 nBit) noexcept
{
#if QX_GNU || QX_CLANG || QX_APPLE_CLANG
    return __builtin_ctzll(nBit);
#else
    int n = 0;
    while ((nBit & 1) == 0)
    {
        nBit >>= 1;
        ++n;
    }
    return n;
#endif
}

template<size_t nSize>
void string_pool<nSize>::normalize(string& string)
{
    string.clear();
    string.reserve(bStringStartCapacity);
}

} // namespace qx
