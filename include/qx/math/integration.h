/**

    @file      integration.h
    @brief     Contains integration algorithms
    @details   ~
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/recursive_lambda.h>

#include <random>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <glm/glm.hpp>
QX_POP_SUPPRESS_WARNINGS();

namespace qx
{

/**
    @brief  Integrate using rectangle rule
    @param  func           - target function
    @param  x0             - left border
    @param  x1             - right border
    @param  nIntervalsPer1 - number of intervals per dx = 1
    @tparam function_2d_t  - function that takes double and returns double
    @retval                - approximate integral
**/
template<class function_2d_t>
inline double integrate_rectangle_rule(const function_2d_t& func, double x0, double x1, size_t nIntervalsPer1 = 10);

/**
    @brief  Integrate using trapezoid rule
    @param  func           - target function 
    @param  x0             - left border 
    @param  x1             - right border 
    @param  nIntervalsPer1 - number of intervals per dx = 1 
    @tparam function_2d_t  - function that takes double and returns double
    @retval                - approximate integral 
**/
template<class function_2d_t>
inline double integrate_trapezoid_rule(const function_2d_t& func, double x0, double x1, size_t nIntervalsPer1 = 10);

/**
    @brief  Integrate using adaptive midpoint
    @param  func           - target function 
    @param  x0             - left border 
    @param  x1             - right border 
    @param  fMaxSliceError - max error per one slice 
    @param  nIntervalsPer1 - number of intervals per dx = 1 
    @param  nMaxRecursion  - max recursion depth 
    @tparam function_2d_t  - function that takes double and returns double
    @retval                - approximate integral 
**/
template<class function_2d_t>
inline double integrate_adaptive_midpoint(
    const function_2d_t& func,
    double               x0,
    double               x1,
    double               fMaxSliceError,
    size_t               nIntervalsPer1 = 10,
    size_t               nMaxRecursion  = 300);

/**
    @brief  Integrate using probabilistic algorithm Monte Carlo
    @param  funcIsInside        - func that returns
                                  1 if point is inside shape with positive value
                                  0 if point is not inside shape
                                  -1 if point is inside shape with negative value
    @param  pos0                - left down corner coordinates
    @param  pos1                - right up corner coordinates
    @param  nPointsPerOneSquare - points per 1 square (more is better)
    @tparam function_2d_t       - function that takes double and returns double
    @retval                     - approximate integral
**/
template<class function_2d_t>
inline double integrate_monte_carlo(
    const function_2d_t& funcIsInside,
    glm::dvec2           pos0,
    glm::dvec2           pos1,
    size_t               nPointsPerOneSquare = 1000);

} // namespace qx

#include <qx/math/integration.inl>
