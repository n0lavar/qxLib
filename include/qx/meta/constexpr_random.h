/**

    @file      constexpr_random.h
    @brief     Contains qx::constexpr_random and the corresponding functions
    @author    Khrapov
    @date      11.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string_utils.h>
#include <qx/meta/constexpr_sequence.h>

#if QX_CONSTEXPR_SEQUENCE_SUPPORTED

    #include <qx/typedefs.h>

namespace qx
{

/**
    @brief  An algorithm that yields a sequence of pseudo-randomized numbers
            calculated with a discontinuous piecewise linear equation
    @tparam MOD   - the "modulus" value
    @tparam MULT  - the "multiplier" value
    @tparam INC   - the "increment" value
    @param  nPrev - prev value of sequence
    @retval       - next value of sequence
**/
template<u32 MOD, u32 MULT, u32 INC>
constexpr u32 linear_congruential_generator(u32 nPrev)
{
    return (MULT * nPrev + INC) % MOD;
}

/**
    @brief  Linear_congruential_generator limited to MIN and MAX
    @tparam MIN   - min distribution value (including)
    @tparam MAX   - man distribution value (excluding)
    @tparam MOD   - the "modulus" value
    @tparam MULT  - the "multiplier" value
    @tparam INC   - the "increment" value
    @param  nPrev - prev value of sequence 
    @retval       - next value of sequence 
**/
template<u32 MIN, u32 MAX, u32 MOD, u32 MULT, u32 INC>
constexpr u32 uniform_distribution(u32 nPrev)
{
    return MIN + linear_congruential_generator<MOD, MULT, INC>(nPrev) % MAX;
}

// returns preudo random number of uniform distribution with each next() call
template<
    typename Tag,
    u32 SEED = 0u,
    u32 MIN  = std::numeric_limits<u32>::min(),
    u32 MAX  = std::numeric_limits<u32>::max(),
    u32 MOD  = 2147483648u,
    u32 MULT = 1103515245u,
    u32 INC  = 12345u>
using constexpr_random = constexpr_sequence<
    Tag,
    u32,
    SEED,
    uniform_distribution<MIN, MAX, MOD, MULT, INC> >;

} // namespace qx

#endif

/**
    @def   QX_UNIQUE_SEED
    @brief Creates unique u32 seed for current: file, date, time (seconds) and line number
**/
#define QX_UNIQUE_SEED                               \
    static_cast<u32>(                                \
        (qx::murmur_32_hash(                         \
             __FILE__ __DATE__ __TIME__,             \
             42u,                                    \
             qx::strlen(__FILE__ __DATE__ __TIME__)) \
         + __LINE__))
