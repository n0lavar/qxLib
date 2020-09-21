//==============================================================================
//
//!\file                       constexpr_funcs.h
//
//!\brief       Constexpr functions implementations
//!\details     ~
//
//!\author      Khrapov
//!\date        12.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/containers/string_traits.h>

namespace qx
{

template<typename T, T INC>
constexpr T increase(T val)
{
    return val + INC;
}

template<typename T, T MULT>
constexpr T multiply(T val)
{
    return val * MULT;
}

template<typename TChar>
constexpr std::size_t strlen(const TChar* psz)
{
    std::size_t nLen = 0;
    while (psz && *psz != CHAR_PREFIX(TChar, '\0'))
    {
        psz++;
        nLen++;
    }

    return nLen;
}

}
