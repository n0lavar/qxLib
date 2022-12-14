/**

    @file      interpolation.h
    @brief     Contains interpolation algorithms
    @details   ~
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/math/common.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS
#include <glm/glm.hpp>
QX_POP_SUPPRESS_WARNINGS

namespace qx
{

/**
    @brief  Linear interpolation algorithm
    @param  p0 - point 0 (x - coordinate, y - f(x))
    @param  p1 - point 1 (x - coordinate, y - f(x))
    @param  x  - point
    @retval    - ~f(x)
**/
inline double linear_interpolation(const glm::dvec2& p0, const glm::dvec2& p1, double x)
{
    if (epsilon_equal(p1.x, p0.x))
        return p0.y;

    return p0.y + (p1.y - p0.y) * (x - p0.x) / (p1.x - p0.x);
}

/**
    @brief   Bilinear interpolation algorithm
    @details po.z is returned on any error
    @param   p0  - point 0 (x, y - coordinates, z - f(x, y)) 
    @param   p1  - point 1 (x, y - coordinates, z - f(x, y)) 
    @param   p2  - point 2 (x, y - coordinates, z - f(x, y)) 
    @param   p3  - point 3 (x, y - coordinates, z - f(x, y))
    @param   p   - point (x, y - coordinates).
                   It can be out of points square, in this case algorithm called extrapolation
    @retval      - ~f(p.x, p.y) 
**/
inline double bilinear_interpolation(
    const glm::dvec3& p0,
    const glm::dvec3& p1,
    const glm::dvec3& p2,
    const glm::dvec3& p3,
    const glm::dvec2& p)
{
    const glm::dvec2 temp0 { p0.y, linear_interpolation({ p0.x, p0.z }, { p1.x, p1.z }, p.x) };
    const glm::dvec2 temp1 { p2.y, linear_interpolation({ p2.x, p2.z }, { p3.x, p3.z }, p.x) };
    const double     fRet = linear_interpolation(temp0, temp1, p.y);
    return fRet;
}

} // namespace qx
