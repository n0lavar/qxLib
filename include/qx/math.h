/**

    @file      math.h
    @brief     Math functions
    @author    Khrapov
    @date      22.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <concepts>
#include <ctime>
#include <limits>
#include <random>

namespace qx
{

/**
    @brief  Get random generated integral value [min, max]
    @tparam T   - integral type
    @param  min - min uniform distribution value (including)
    @param  max - max uniform distribution value (including)
    @retval     - random generated integral value
**/
template<std::integral T>
T random(T min, T max)
{
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(generator);
}

/**
    @brief  Get random generated real value [min, max]
    @tparam T   - floating point type
    @param  min - min uniform distribution value (including)
    @param  max - max uniform distribution value (including)
    @retval     - random generated integral value
**/
template<std::floating_point T>
T random(T min, T max)
{
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(generator);
}

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

} // namespace qx
