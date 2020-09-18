//==============================================================================
//
//!\file                       constexpr_random.h
//
//!\brief
//!\details     ~
//
//!\author      Khrapov
//!\date        11.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/containers/string_traits.h>
#include <qx/other/constexpr_sequence.h>

namespace qx
{

template<u32 MOD, u32 MULT, u32 INC>
constexpr u32 linear_congruential_generator(u32 nPrev)
{
    return (MULT * nPrev + INC) % MOD;
}

template<u32 MIN, u32 MAX, u32 MOD, u32 MULT, u32 INC>
constexpr u32 uniform_distribution(u32 nPrev)
{
    return MIN + linear_congruential_generator<MOD, MULT, INC>(nPrev) % MAX;
}

template<typename Tag, u32 SEED, u32 MIN, u32 MAX, u32 MOD = 2147483648, u32 MULT = 1103515245, u32 INC = 12345>
using constexpr_random = constexpr_sequence<
    Tag,
    u32,
    SEED,
    uniform_distribution<MIN, MAX, MOD, MULT, INC>
>;

}

// creates unique u32 seed for current: file, date, time (seconds) and line number
#define QX_UNIQUE_SEED (qx::detail::murmur_32_hash(__FILE__ __DATE__ __TIME__, qx::strlen(__FILE__ __DATE__ __TIME__), 42) + __LINE__)
