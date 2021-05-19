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

#include <qx/containers/string_utils.h>

#include <limits>

namespace qx::meta
{

//==============================================================================
//!\fn                         qx::meta::strlen
//
//!\brief  Constexpr string length
//!\param  psz - poiter to string zero terminated
//!\retval     - string length
//!\author Khrapov
//!\date   24.09.2020
//==============================================================================
template<typename TChar>
constexpr std::size_t strlen(const TChar* psz)
{
    std::size_t nLen = 0;
    while (psz && *psz != QX_CHAR_PREFIX(TChar, '\0'))
    {
        ++psz;
        nLen++;
    }

    return nLen;
}

//==============================================================================
//!\fn                      qx::meta::strcmp<TChar>
//
//!\brief  Compare two strings
//!\param  pszLeft  - first string
//!\param  pszRight - second string
//!\retval          -
//  < 0 the first character that does not match has a lower value in ptr1 than in ptr2
//    0 the contents of both strings are equal
//  > 0 the first character that does not match has a greater value in ptr1 than in ptr2
//!\author Khrapov
//!\date   25.09.2020
//==============================================================================
template<typename TChar>
constexpr int strcmp(const TChar* pszLeft, const TChar* pszRight)
{
    while (*pszLeft && (*pszLeft == *pszRight))
    {
        ++pszLeft;
        ++pszRight;
    }
    return *pszLeft - *pszRight;
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
constexpr T abs(T value)
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
constexpr bool epsilon_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return meta::abs(left - right) < eps;
}

//==============================================================================
//!\fn                  qx::meta::epsilon_less_equal<T>
//
//!\brief  Constexpr comparison function for a user defined epsilon values
//!\param  left  - left value
//!\param  right - right value
//!\param  eps   - epsilon value
//!\retval       - true if left < right or |left - right| < eps
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
constexpr bool epsilon_less_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return left < right || epsilon_equal(left, right, eps);
}

//==============================================================================
//!\fn                 qx::meta::epsilon_greater_equal<T>
//
//!\brief  Constexpr comparison function for a user defined epsilon values
//!\param  left  - left value
//!\param  right - right value
//!\param  eps   - epsilon value
//!\retval       - true if left > right or |left - right| < eps
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
constexpr bool epsilon_greater_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return left > right || epsilon_equal(left, right, eps);
}

}
