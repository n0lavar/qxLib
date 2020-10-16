//==============================================================================
//
//!\file                       constexpr_random.h
//
//!\brief       contains constexpr_random and the corresponding functions
//!\details     ~
//
//!\author      Khrapov
//!\date        11.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/string_utils.h>
#include <qx/meta/constexpr_sequence.h>
#include <qx/typedefs.h>

namespace qx
{

//==============================================================================
//!\fn         qx::linear_congruential_generator<MOD, MULT, INC>
//
//!\brief  an algorithm that yields a sequence of pseudo-randomized numbers
//         calculated with a discontinuous piecewise linear equation
//!\param  nPrev - prev value of secuence
//!\retval       - next value of secuence
//!\author Khrapov
//!\date   21.09.2020
//==============================================================================
template<u32 MOD, u32 MULT, u32 INC>
constexpr u32 linear_congruential_generator(u32 nPrev)
{
    return (MULT * nPrev + INC) % MOD;
}

//==============================================================================
//!\fn         qx::uniform_distribution<MIN, MAX, MOD, MULT, INC>
//
//!\brief  linear_congruential_generator limited to MIN and MAX
//!\param  nPrev - prev value of secuence
//!\retval       - next value of secuence
//!\author Khrapov
//!\date   21.09.2020
//==============================================================================
template<u32 MIN, u32 MAX, u32 MOD, u32 MULT, u32 INC>
constexpr u32 uniform_distribution(u32 nPrev)
{
    return MIN + linear_congruential_generator<MOD, MULT, INC>(nPrev) % MAX;
}

// returns preudo random number of uniform distrubution with each next() call
template<
    typename Tag,
    u32 SEED    = 0u,
    u32 MIN     = std::numeric_limits<u32>::min(),
    u32 MAX     = std::numeric_limits<u32>::max(),
    u32 MOD     = 2147483648u,
    u32 MULT    = 1103515245u,
    u32 INC     = 12345u
>
using constexpr_random = constexpr_sequence<
    Tag,
    u32,
    SEED,
    uniform_distribution<MIN, MAX, MOD, MULT, INC>
>;

}

// creates unique u32 seed for current: file, date, time (seconds) and line number
#define QX_UNIQUE_SEED (qx::murmur_32_hash(__FILE__ __DATE__ __TIME__,                      \
                                           qx::meta::strlen(__FILE__ __DATE__ __TIME__),    \
                                           42)                                              \
                                            + __LINE__)
