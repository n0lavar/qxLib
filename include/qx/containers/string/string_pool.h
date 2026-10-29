/**

    @file      string_pool.h
    @author    Khrapov
    @date      17.01.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>

#include <array>
#include <atomic>
#include <cstdint>
#include <limits>
#include <string>
#include <utility>

namespace qx
{

/**

    @class   string_pool
    @brief   Fixed-size atomic string pool
    @tparam  nSize                - pool size
    @tparam  nStringStartCapacity - start string capacity for each string
    @author  Khrapov
    @date    18.01.2026

**/
template<size_t nSize = 32, size_t nStringStartCapacity = 128>
class string_pool
{
    static constexpr size_t k_nTotalBits = 64; // bits in u64
    static constexpr size_t k_nBlocks    = (nSize + k_nTotalBits - 1) / k_nTotalBits;

public:
    static constexpr int nFreeString = -1;

    struct item
    {
        string sValue;
        int    nIndex = nFreeString;
    };

public:
    string_pool();

    /**
        @brief  Acquire a string from the pool.
        @return - If a free slot exists, returns it (moved) and its index,
                  otherwise returns a fresh string with nIndex = nFreeString.
    **/
    item acquire();

    /**
        @brief Return a string back to the pool.
        @param item - an item object to release. 
               If nIndex == nFreeString, it is ignored. A string that isn't from this pool is acceptable.
    **/
    void release(item item);

private:
    /**
        @brief  Count trailing zeros for a non-zero 64-bit value
        @param  nBit - 64-bit value
        @return      - number of trailing zeros
    **/
    static int ctz64(u64 nBit) noexcept;

    /**
        @brief Prepare a string for pooling
        @param string - a string
    **/
    static void normalize(string& string);

private:
    std::array<string, nSize> m_Storage;

    // 1 = free, 0 = in use
    std::array<std::atomic<u64>, k_nBlocks> m_FreeMask;
};

} // namespace qx

#include <qx/containers/string/string_pool.inl>
