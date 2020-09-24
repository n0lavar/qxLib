//==============================================================================
//
//!\file                       constexpr_funcs.h
//
//!\brief       Constexpr functions implementations
//!\details     Use this methods only if you need constexpr, in other cases use std::
//
//!\author      Khrapov
//!\date        12.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/useful_macros.h>

namespace qx::meta
{

template<typename TChar>
inline constexpr std::size_t strlen(const TChar* psz)
{
    std::size_t nLen = 0;
    while (psz && *psz != QX_CHAR_PREFIX(TChar, '\0'))
    {
        psz++;
        nLen++;
    }

    return nLen;
}

template<typename T>
inline constexpr T abs(T value)
{
    return value < 0 ? -value : value;
}

template<typename T>
inline constexpr T epsilon_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return qx::meta::abs(left - right) < eps;
};

}
