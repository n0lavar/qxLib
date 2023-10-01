/**

    @file      constexpr_random.h
    @author    Khrapov
    @date      11.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_utils.h>
#include <qx/meta/constexpr_sequence.h>

#if QX_CONSTEXPR_SEQUENCE_SUPPORTED

    #include <qx/typedefs.h>

namespace qx
{

/**
    @brief  An algorithm that yields a sequence of pseudo-randomized numbers
            calculated with a discontinuous piecewise linear equation
    @tparam nModulus    - the "modulus" value
    @tparam nMultiplier - the "multiplier" value
    @tparam nIncrement  - the "increment" value
    @param  nPrev       - prev value of sequence
    @retval             - next value of sequence
**/
template<u32 nModulus, u32 nMultiplier, u32 nIncrement>
constexpr u32 linear_congruential_generator(u32 nPrev)
{
    return (nMultiplier * nPrev + nIncrement) % nModulus;
}

/**
    @brief  Linear_congruential_generator limited to MIN and MAX
    @tparam nMin        - min distribution value (including)
    @tparam nMax        - man distribution value (excluding)
    @tparam nModulus    - the "modulus" value
    @tparam nMultiplier - the "multiplier" value
    @tparam nIncrement  - the "increment" value
    @param  nPrev      - prev value of sequence 
    @retval            - next value of sequence 
**/
template<u32 nMin, u32 nMax, u32 nModulus, u32 nMultiplier, u32 nIncrement>
constexpr u32 uniform_distribution(u32 nPrev)
{
    return nMin + linear_congruential_generator<nModulus, nMultiplier, nIncrement>(nPrev) % nMax;
}

// returns preudo random number of uniform distribution with each next() call
template<
    typename Tag,
    u32 nSeed       = 0u,
    u32 nMin        = std::numeric_limits<u32>::min(),
    u32 nMax        = std::numeric_limits<u32>::max(),
    u32 nModulus    = 2147483648u,
    u32 nMultiplier = 1103515245u,
    u32 nIncrement  = 12345u>
using constexpr_random =
    constexpr_sequence<Tag, u32, nSeed, uniform_distribution<nMin, nMax, nModulus, nMultiplier, nIncrement> >;

} // namespace qx

#endif

/**
    @def   QX_UNIQUE_SEED
    @brief Creates unique u32 seed for current: file, date, time (seconds) and line number
**/
#define QX_UNIQUE_SEED \
    static_cast<u32>(  \
        (qx::murmur_32_hash(__FILE__ __DATE__ __TIME__, 42u, qx::strlen(__FILE__ __DATE__ __TIME__)) + __LINE__))
