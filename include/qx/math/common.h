/**

    @file      common.h
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
template<class T>
constexpr T abs(T value);

/**
    @brief  Constexpr comparison function for a user defined epsilon values
    @tparam T     - value type
    @param  left  - left value
    @param  right - right value
    @param  eps   - epsilon value
    @retval       - true if |left - right| < eps
**/
template<class T>
constexpr bool epsilon_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon());

/**
    @brief  Constexpr comparison with zero for a user defined epsilon values
    @tparam T     - value type
    @param  value - user value
    @param  eps   - epsilon value
    @retval       - true if |value| < eps
**/
template<class T>
constexpr bool epsilon_zero(T value, T eps = std::numeric_limits<T>::epsilon());

/**
    @brief  Constexpr comparison function for a user defined epsilon values
    @tparam T     - value type
    @param  left  - left value
    @param  right - right value
    @param  eps   - epsilon value
    @retval       - true if left < right or |left - right| < eps
**/
template<class T>
constexpr bool epsilon_less_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon());

/**
    @brief  Constexpr comparison function for a user defined epsilon values
    @tparam T     - value type
    @param  left  - left value
    @param  right - right value
    @param  eps   - epsilon value
    @retval       - true if left > right or |left - right| < eps
**/
template<class T>
constexpr bool epsilon_greater_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon());

/**
    @brief  Check if value is odd
    @tparam T   - integral type
    @param  val - value
    @retval     - true if value is odd
**/
template<std::integral T>
constexpr bool is_odd(T val);

/**
    @brief  Check if value is even
    @tparam T   - integral type
    @param  val - value
    @retval     - true if value is even
**/
template<std::integral T>
constexpr bool is_even(T val);

/**
    @brief      Greatest common divisor
    @details    Euclid's algorithm
                based on fact gcd(A, B) == gcd(B, A mod B)
    @complexity O(log(second))
    @param      nFirst  - first num
    @param      nSecond - second num
    @retval             - greatest common divisor if first and second > 0, otherwise 0
**/
constexpr int gcd(int nFirst, int nSecond);

/**
    @brief      Least common multiple
    @complexity O(log(second))
    @param      nFirst  - first num
    @param      nSecond - second num
    @retval             - least common multiple if first and second > 0, otherwise 0
**/
constexpr int lcm(int nFirst, int nSecond);

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
template<class T>
inline double pow(T number, int nPower);

/**
    @brief  Max power of two in integer
    @tparam I      - Integral type
    @param  nValue - number
    @retval        - max power of two in number
**/
template<std::integral I>
inline I maxpot(I nValue);

/**
    @brief  Checks if value is between left and right
    @tparam T         - value type
    @tparam compare_t - comparator type
    @param  left      - left value
    @param  value     - value
    @param  right     - right value
    @param  compare   - comparator function
    @retval           - true, left <= value <= right
**/
template<class T, class compare_t = std::less_equal<>>
constexpr bool between(T left, T value, T right, compare_t compare);

/**
    @brief   Checks if value is between left and right
    @details Overloading for disabling 4388 warning with Compare instantiation
    @tparam  T         - value type
    @tparam  compare_t - comparator type
    @param   left      - left value
    @param   value     - value
    @param   right     - right value
    @retval            - true, left <= value <= right
**/
template<class T, class compare_t = std::less_equal<>>
constexpr bool between(T left, T value, T right);

} // namespace qx

#include <qx/math/common.inl>
