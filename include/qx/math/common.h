/**

    @file      common.h
    @brief     Contains common math functions
    @details   ~
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/macros/suppress_warnings.h>
#include <qx/typedefs.h>

#include <array>
#include <bitset>
#include <concepts>
#include <limits>

namespace qx
{

/**
    @brief  Constexpr absolute value
    @tparam T     - value type
    @param  value - value
    @retval       - absolute value
**/
template<typename T>
constexpr T abs(T value)
{
    return value < 0 ? -value : value;
}

/**
    @brief  Constexpr comparison function for a user defined epsilon values
    @tparam T     - value type
    @param  left  - left value
    @param  right - right value
    @param  eps   - epsilon value
    @retval       - true if |left - right| < eps
**/
template<typename T>
constexpr bool epsilon_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return abs(left - right) < eps;
}

/**
    @brief  Constexpr comparison with zero for a user defined epsilon values
    @tparam T     - value type
    @param  value - user value
    @param  eps   - epsilon value
    @retval       - true if |value| < eps
**/
template<typename T>
constexpr bool epsilon_zero(T value, T eps = std::numeric_limits<T>::epsilon())
{
    return abs(value) < eps;
}

/**
    @brief  Constexpr comparison function for a user defined epsilon values
    @tparam T     - value type
    @param  left  - left value
    @param  right - right value
    @param  eps   - epsilon value
    @retval       - true if left < right or |left - right| < eps
**/
template<typename T>
constexpr bool epsilon_less_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return left < right || epsilon_equal(left, right, eps);
}

/**
    @brief  Constexpr comparison function for a user defined epsilon values
    @tparam T     - value type
    @param  left  - left value
    @param  right - right value
    @param  eps   - epsilon value
    @retval       - true if left > right or |left - right| < eps
**/
template<typename T>
constexpr bool epsilon_greater_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return left > right || epsilon_equal(left, right, eps);
}

/**
    @brief  Check if value is odd
    @tparam T   - integral type
    @param  val - value
    @retval     - true if value is odd
**/
template<std::integral T>
constexpr bool is_odd(T val)
{
    return (val & 1) == 1;
}

/**
    @brief  Check if value is even
    @tparam T   - integral type
    @param  val - value
    @retval     - true if value is even
**/
template<std::integral T>
constexpr bool is_even(T val)
{
    return (val & 1) == 0;
}

/**
    @brief      Greatest common divisor
    @details    Euclid's algorithm
                based on fact gcd(A, B) == gcd(B, A mod B)
    @complexity O(log(second))
    @param      nFirst  - first num
    @param      nSecond - second num
    @retval             - greatest common divisor if first and second > 0, otherwise 0
**/
constexpr int gcd(int nFirst, int nSecond)
{
    if (nFirst == 0 || nSecond == 0)
        return 0;

    while (nSecond != 0)
    {
        const int nRemainder = nFirst % nSecond;
        nFirst               = nSecond;
        nSecond              = nRemainder;
    }

    return abs(nFirst);
}

/**
    @brief      Least common multiple
    @complexity O(log(second))
    @param      nFirst  - first num
    @param      nSecond - second num
    @retval             - least common multiple if first and second > 0, otherwise 0
**/
constexpr int lcm(int nFirst, int nSecond)
{
    if (nFirst == 0 || nSecond == 0)
        return 0;

    nFirst  = abs(nFirst);
    nSecond = abs(nSecond);

    return nFirst / gcd(nFirst, nSecond) * nSecond;
}

/**
    @brief      Power function for integer power
    @details    About 2.22 times (positive powers)
                      1.7  times (positive and negative powers)
                      2.33 times (negative powers)
                      faster then std::pow
    @complexity O(log(power))
    @tparam     T      - Integral or floating point type
    @param      number - integral of floating point value
    @param      nPower - integral power
    @retval            - number ^ power
**/
template<typename T>
inline double pow(T number, int nPower)
{
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Integral or floating point required");

    const bool   bNegativePower = nPower < 0;
    const size_t nPositivePower = static_cast<size_t>(std::abs(nPower));

    double fResult = 1.0;
    switch (nPositivePower)
    {
    case 0:
        break;

    case 1:
        fResult = static_cast<double>(number);
        break;

    case 2:
        fResult = static_cast<double>(number * number);
        break;

    default:
        const std::bitset<std::numeric_limits<int>::digits> powerBitSet(nPositivePower);

        std::array<double, std::numeric_limits<int>::digits> powers;

        powers[0] = static_cast<double>(number);

        size_t nCurPower = 1;
        size_t nCurIndex = 1;

        while (nCurPower < nPositivePower)
        {
            powers[nCurIndex] = powers[nCurIndex - 1] * powers[nCurIndex - 1];
            nCurPower *= 2;
            nCurIndex++;
        }

        for (size_t i = 0; i < nCurIndex; ++i)
            if (powerBitSet.test(i))
                fResult *= powers[i];

        break;
    }

    return bNegativePower ? 1.0 / fResult : fResult;
}

/**
    @brief  Max power of two in integer
    @tparam I      - Integral type
    @param  nValue - number
    @retval        - max power of two in number
**/
template<std::integral I>
inline I maxpot(I nValue)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    if (nValue == 0)
        return 0;

    std::bitset<std::numeric_limits<I>::digits> powers(static_cast<size_t>(abs(nValue)));

    I nPow = static_cast<I>(std::numeric_limits<I>::digits - 1);
    while (!powers.test(static_cast<size_t>(nPow)))
        --nPow;

    return nPow;
}

// trick to determine if an integer is between two integers (inclusive)
// with only one comparison/branch
// https://stackoverflow.com/a/17095534/8021662
QX_DISABLE_MSVC_WARNINGS(4018 4388)

/**
    @brief  Checks if value is between left and right
    @tparam T       - value type
    @tparam Compare - comparator type
    @param  left    - left value
    @param  value   - value
    @param  right   - right value
    @param  compare - comparator function
    @retval         - true, left <= value <= right
**/
template<typename T, typename Compare = std::less_equal<>>
constexpr bool between(T left, T value, T right, Compare compare)
{
    if constexpr (std::is_enum_v<T>)
    {
        i64 l = static_cast<i64>(left);
        i64 r = static_cast<i64>(right);
        i64 v = static_cast<i64>(value);
        return between(l, v, r, compare);
    }
    else if constexpr (std::is_integral_v<T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return compare(static_cast<size_t>(value - left), right - left);
    }
    else if constexpr (std::is_floating_point_v<T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return epsilon_less_equal(left, value) && epsilon_less_equal(value, right);
    }
    else
    {
        return compare(left, value) && compare(value, right);
    }
}

QX_RESTORE_MSVC_WARNINGS(4018 4388)

/**
    @brief   Checks if value is between left and right
    @details Overloading for disabling 4388 warning with Compare instantiation
    @tparam  T       - value type
    @tparam  Compare - comparator type
    @param   left    - left value
    @param   value   - value
    @param   right   - right value
    @retval          - true, left <= value <= right
**/
template<typename T, typename Compare = std::less_equal<>>
constexpr bool between(T left, T value, T right)
{
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4388)
    return between(left, value, right, Compare());
    QX_POP_SUPPRESS_WARNINGS
}

} // namespace qx
