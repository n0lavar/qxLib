//==============================================================================
//
//!\file                       constexpr_funcs.h
//
//!\brief       Constexpr functions implementations
//!\details     Prefer using functions from the standard library
//              if you don't need constexpr
//
//!\author      Khrapov
//!\date        12.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/useful_macros.h>
#include <limits>

namespace qx::meta
{

//==============================================================================
//!\fn                      qx::meta::strlen<TChar>
//
//!\brief  Constexpr string length
//!\param  psz - poiter to string zero terminated
//!\retval     - string length
//!\author Khrapov
//!\date   24.09.2020
//==============================================================================
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

//==============================================================================
//!\fn                          qx::meta::abs<T>
//
//!\brief  Constexpr absolute value
//!\param  value - value
//!\retval       - absolute value
//!\author Khrapov
//!\date   24.09.2020
//==============================================================================
template<typename T>
inline constexpr T abs(T value)
{
    return value < 0 ? -value : value;
}

//==============================================================================
//!\fn                     qx::meta::epsilon_equal<T>
//
//!\brief  Constexpr comparison function for a user defined epsilon values
//!\param  left  - left value
//!\param  right - right value
//!\param  eps   - epsilon value
//!\retval       - true if |left - right| < eps
//!\author Khrapov
//!\date   24.09.2020
//==============================================================================
template<typename T>
inline constexpr bool epsilon_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return qx::meta::abs(left - right) < eps;
};

}
