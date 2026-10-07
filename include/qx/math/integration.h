/**

    @file      integration.h
    @author    Khrapov
    @date      6.08.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/recursive_lambda.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <optional>
#include <random>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <glm/glm.hpp>
QX_POP_SUPPRESS_WARNINGS();

namespace qx
{

/**
    @brief   Integrate using rectangle rule
    @details Supports reversed bounds; noexcept depends on the callback.
    @param   func           - target function
    @param   x0             - left border
    @param   x1             - right border
    @param   nIntervalsPer1 - number of intervals per dx = 1
    @tpara m function_2d_t  - function that takes double and returns double
    @retval                 - approximate integral; 0 for zero extent;
                              NaN for invalid bounds, zero density or sample count overflow
**/
template<class function_2d_t>
inline double integrate_rectangle_rule(
    const function_2d_t& func,
    double               x0,
    double               x1,
    size_t               nIntervalsPer1 = 10) noexcept(noexcept(static_cast<double>(func(0.0))));

/**
    @brief   Integrate using trapezoid rule
    @details Supports reversed bounds; noexcept depends on the callback.
    @param   func           - target function 
    @param   x0             - left border 
    @param   x1             - right border 
    @param   nIntervalsPer1 - number of intervals per dx = 1 
    @tparam  function_2d_t  - function that takes double and returns double
    @retval                 - approximate integral; 0 for zero extent;
                              NaN for invalid bounds, zero density or sample count overflow
**/
template<class function_2d_t>
inline double integrate_trapezoid_rule(
    const function_2d_t& func,
    double               x0,
    double               x1,
    size_t               nIntervalsPer1 = 10) noexcept(noexcept(static_cast<double>(func(0.0))));

/**
    @brief  Integrate using adaptive midpoint
    @details Supports reversed bounds; noexcept depends on the callback.
    @param   func           - target function 
    @param   x0             - left border 
    @param   x1             - right border 
    @param   fMaxSliceError - max error per one slice 
    @param   nIntervalsPer1 - number of intervals per dx = 1 
    @param   nMaxRecursion  - max recursion depth 
    @tpara m function_2d_t  - function that takes double and returns double
    @retval                 - approximate integral; 0 for zero extent;
                              NaN for invalid bounds, zero density or sample count overflow
**/
template<class function_2d_t>
inline double integrate_adaptive_midpoint(
    const function_2d_t& func,
    double               x0,
    double               x1,
    double               fMaxSliceError,
    size_t               nIntervalsPer1 = 10,
    size_t               nMaxRecursion  = 300) noexcept(noexcept(static_cast<double>(func(0.0))));

/**
    @brief   Integrate using probabilistic algorithm Monte Carlo
    @details Supports reversed bounds; noexcept depends on the callback.
    @param   funcIsInside        - func that returns
                                   1 if point is inside shape with positive value
                                   0 if point is not inside shape
                                   -1 if point is inside shape with negative value
    @param   pos0                - left down corner coordinates
    @param   pos1                - right up corner coordinates
    @param   nPointsPerOneSquare - points per 1 square (more is better)
    @tparam  function_2d_t       - function that takes double and returns double
    @retval                      - approximate integral; 0 for zero area;
                                   NaN for invalid bounds, zero density or sample count overflow
**/
template<class function_2d_t>
inline double integrate_monte_carlo(
    const function_2d_t& funcIsInside,
    glm::dvec2           pos0,
    glm::dvec2           pos1,
    size_t               nPointsPerOneSquare = 1000) noexcept(noexcept(static_cast<int>(funcIsInside(0.0, 0.0))));

} // namespace qx

#include <qx/math/integration.inl>
