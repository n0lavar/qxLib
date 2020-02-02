//============================================================================
//
//!\file                        useful_funcs.h
//
//!\brief
//!\details     ~
//
//!\author      Khrapov
//!\date        1.11.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <qx/other/asserter.h>

#include <initializer_list>
#include <algorithm>
#include <glm.hpp>
#include <gtc/epsilon.hpp>

//============================================================================
//!\fn                          SAFE_DELETE<T>
//
//!\brief  safe pointer deleting
//!\param  ptr    - pointer to delete
//!\param  bArray - true if need to use delete[]
//!\author Khrapov
//!\date   17.06.2019
//============================================================================
template<typename T>
inline void SAFE_DELETE(T*& ptr, bool bArray = false)
{
    if (ptr)
    {
        if (!bArray)
            delete ptr;
        else
            delete[] ptr;

        ptr = nullptr;
    }
}

namespace qx
{

//============================================================================
//!\fn                         between<L, R, V>
//
//!\brief  Checks if value is between left and right
//!\param  left  - left value
//!\param  right - right value
//!\param  value - value
//!\retval       - true if so
//!\author Khrapov
//!\date   3.11.2019
//============================================================================
template<typename L, typename R, typename V>
inline bool between(L left, R right, V value)
{
    return (value - left) <= (right - left);
}

template<typename E>
inline bool between_enum(E left, E right, E value)
{
    i64 l = static_cast<i64>(left);
    i64 r = static_cast<i64>(right);
    i64 v = static_cast<i64>(value);
    return between(l, r, v);
}

//============================================================================
//!\fn                          step_to<V, T>
//
//!\brief  Do step to some value
//!\param  val - value
//!\param  to  - value to check
//!\author Khrapov
//!\date   3.11.2019
//============================================================================
template<typename V, typename T>
inline void step_to(V& val, const T& to)
{
    if (val < to)
        val++;
    else if (val > to)
        val--;
}

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
#if 0
    ASSERT(glm::epsilonEqual(p0.y, p1.y, DBL_EPSILON));
    ASSERT(glm::epsilonEqual(p2.y, p3.y, DBL_EPSILON));
    ASSERT(glm::epsilonEqual(p0.x, p3.x, DBL_EPSILON));
    ASSERT(glm::epsilonEqual(p1.x, p2.x, DBL_EPSILON));
#endif

    glm::dvec2 temp0 = { p0.y, linear_interpolation({ p0.x, p0.z }, { p1.x, p1.z }, p.x) };
    glm::dvec2 temp1 = { p2.y, linear_interpolation({ p2.x, p2.z }, { p3.x, p3.z }, p.x) };
    return linear_interpolation(temp0, temp1, p.y);
}

//============================================================================
//!\fn                                pi
//
//!\brief  Get pi
//!\author Khrapov
//!\date   16.11.2019
//============================================================================
template <typename T = float>
inline constexpr T pi()
{
    return static_cast<T>(3.14159265358979323846264338327950288);
}

}