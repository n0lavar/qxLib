/**

    @file      between.h
    @author    Khrapov
    @date      25.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/macros/suppress_warnings.h>
#include <qx/math/float_compare.h>

namespace qx
{

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

} // namespace qx

#include <qx/math/between.inl>
