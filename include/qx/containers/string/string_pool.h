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
    @tparam  nSize - pool size
    @author  Khrapov
    @date    18.01.2026

**/
template<size_t nSize = 32>
class string_pool
{
    static constexpr size_t bTotalBits           = 64; // bits in u64
    static constexpr size_t nBlocks              = (nSize + bTotalBits - 1) / bTotalBits;
    static constexpr size_t bStringStartCapacity = 128;

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
        @retval - If a free slot exists, returns it (moved) and its index,
                  otherwise returns a fresh string with nIndex = nFreeString.
    **/
    item acquire();

    /**
        @brief   Return a string back to the pool.
        @details If nIndex == nFreeString, it is ignored.
        @param   sValue - a string that does not necessarily have to be from this pool
        @param   nIndex - an index of previously acquired string
    **/
    void release(string sValue, int nIndex);

private:
    /**
        @brief  Count trailing zeros for a non-zero 64-bit value
        @param  nBit - 64-bit value
        @retval      - number of trailing zeros
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
    std::array<std::atomic<u64>, nBlocks> m_FreeMask;
};

} // namespace qx

#include <qx/containers/string/string_pool.inl>
