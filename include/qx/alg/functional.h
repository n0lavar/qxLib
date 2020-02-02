//============================================================================
//
//!\file                         functional.h
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        2.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <glm.hpp>
#include <gtc/epsilon.hpp>

#include <qx/other/asserter.h>

namespace qx::alg
{

//============================================================================
//!\fn                       linear_interpolation
//
//!\brief  Linear interpolation algorithm
//!\param  p0 - point 0 (x - coord, y - f(x))
//!\param  p1 - point 1 (x - coord, y - f(x))
//!\param  x  - point
//!\retval    - ~f(x)
//!\author Khrapov
//!\date   10.11.2019
//============================================================================
inline double linear_interpolation(glm::dvec2 p0, glm::dvec2 p1, double x)
{
    return p0.y + (p1.y - p0.y) * (x - p0.x) / (p1.x - p0.x);
}

//============================================================================
//!\fn                      bilinear_inletpolation
//
//!\brief  Bilinear interpolation algorithm. Points are clockwise or counterclock-wise
//!\param  p0 - point 0 (x, y - coords, z - f(x, y))
//!\param  p1 - point 1 (x, y - coords, z - f(x, y))
//!\param  p2 - point 2 (x, y - coords, z - f(x, y))
//!\param  p3 - point 3 (x, y - coords, z - f(x, y))
//!\param  p  - point (x, y - coords).
//              It can be out of points square, in this case algorithm called extrapolation
//!\retval    - ~f(p.x, p.y)
//!\author Khrapov
//!\date   10.11.2019
//============================================================================
inline double bilinear_inletpolation(glm::dvec3 p0, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec2 p)
{
    // points must be as square
    ASSERT(glm::epsilonEqual(p0.y, p1.y, DBL_EPSILON));
    ASSERT(glm::epsilonEqual(p2.y, p3.y, DBL_EPSILON));
    ASSERT(glm::epsilonEqual(p0.x, p3.x, DBL_EPSILON));
    ASSERT(glm::epsilonEqual(p1.x, p2.x, DBL_EPSILON));

    glm::dvec2 temp0 = { p0.y, linear_interpolation({ p0.x, p0.z }, { p1.x, p1.z }, p.x) };
    glm::dvec2 temp1 = { p2.y, linear_interpolation({ p2.x, p2.z }, { p3.x, p3.z }, p.x) };
    return linear_interpolation(temp0, temp1, p.y);
}

}