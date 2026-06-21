/**

    @file      float_compare.h
    @author    Khrapov
    @date      25.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/math/common.h>

#include <limits>

namespace qx
{

/**
    @brief  Tolerance-based floating comparison
    @tparam T      - floating point type
    @param  fLeft  - left value
    @param  fRight - right value
    @param  fEps   - epsilon value
    @retval        - true if two values are nearly equal based on tolerance-based floating comparison
**/
template<std::floating_point T>
static constexpr bool float_compare(T fLeft, T fRight, T fEps = std::numeric_limits<T>::epsilon());

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

} // namespace qx

#include <qx/math/float_compare.inl>
