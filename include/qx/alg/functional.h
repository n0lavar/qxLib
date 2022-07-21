/**

    @file      functional.h
    @brief     Algorithms for math functions
    @author    Khrapov
    @date      2.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/assert/lib_asserts.h>
#include <qx/useful_macros.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
QX_POP_SUPPRESS_WARNINGS

#include <ctime>
#include <random>

namespace qx
{

using function2d = std::function<double(double)>;

/**
    @brief  Linear interpolation algorithm
    @param  p0 - point 0 (x - coordinate, y - f(x))
    @param  p1 - point 1 (x - coordinate, y - f(x))
    @param  x  - point
    @retval    - ~f(x)
**/
inline double linear_interpolation(const glm::dvec2& p0, const glm::dvec2& p1, double x)
{
    QX_LIB_EXPECT_RETURN(!epsilon_equal(p1.x, p0.x) && "Two x are equal, result is nan", p0.y);
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

/**
    @brief  Integrate using rectangle rule
    @param  func           - target function
    @param  x0             - left border
    @param  x1             - right border
    @param  nIntervalsPer1 - number of intervals per dx = 1
    @retval                - approximate integral
**/
inline double integrate_rectangle_rule(const function2d& func, double x0, double x1, size_t nIntervalsPer1 = 10)
{
    const size_t nIntervals = static_cast<size_t>(std::ceil((x1 - x0) * static_cast<double>(nIntervalsPer1)));

    const double dx         = (x1 - x0) / static_cast<double>(nIntervals);
    double       fTotalArea = 0.0;
    double       x          = x0;

    for (size_t i = 0; i < nIntervals; i++)
    {
        fTotalArea += dx * func(x);
        x += dx;
    }

    return fTotalArea;
}

/**
    @brief  Integrate using trapezoid rule
    @param  func           - target function 
    @param  x0             - left border 
    @param  x1             - right border 
    @param  nIntervalsPer1 - number of intervals per dx = 1 
    @retval                - approximate integral 
**/
inline double integrate_trapezoid_rule(const function2d& func, double x0, double x1, size_t nIntervalsPer1 = 10)
{
    const size_t nIntervals = static_cast<size_t>(std::ceil(static_cast<double>(nIntervalsPer1) * (x1 - x0)));

    const double dx         = (x1 - x0) / static_cast<double>(nIntervals);
    double       fTotalArea = 0.0;
    double       x          = x0;

    for (size_t i = 0; i < nIntervals; i++)
    {
        fTotalArea += dx * (func(x) + func(x + dx)) / 2;
        x += dx;
    }

    return fTotalArea;
}

/**
    @brief  Integrate using adaptive midpoint
    @param  func           - target function 
    @param  x0             - left border 
    @param  x1             - right border 
    @param  fMaxSliceError - max error per one slice 
    @param  nIntervalsPer1 - number of intervals per dx = 1 
    @param  nMaxRecursion  - max recursion depth 
    @retval                - approximate integral 
**/
inline double integrate_adaptive_midpoint(
    const function2d& func,
    double            x0,
    double            x1,
    double            fMaxSliceError,
    size_t            nIntervalsPer1 = 10,
    size_t            nMaxRecursion  = 300)
{
    const size_t nIntervals = static_cast<size_t>(std::ceil(static_cast<double>(nIntervalsPer1) * (x1 - x0)));

    const double dx         = (x1 - x0) / static_cast<double>(nIntervals);
    double       fTotalArea = 0.0;
    double       x          = x0;

    std::function<double(const function2d&, double, double, double, size_t)> slice_area =
        [&slice_area,
         &nMaxRecursion](const function2d& func, double x0, double x1, double max_slice_error, size_t recursionLevel)
        -> double
    {
        recursionLevel++;
        const double y0 = func(x0);
        const double y1 = func(x1);
        const double xm = (x0 + x1) / 2;
        const double ym = func(xm);

        const double fArea12  = (x1 - x0) * (y0 + y1) / 2.0;
        const double fArea1m  = (xm - x0) * (y0 + ym) / 2.0;
        const double fAream2  = (x1 - xm) * (ym + y1) / 2.0;
        const double fArea1m2 = fArea1m + fAream2;

        const double fError = (fArea1m2 - fArea12) / fArea12;

        if (recursionLevel > nMaxRecursion || std::abs(fError) < max_slice_error)
        {
            return fArea1m2;
        }
        else
        {
            return slice_area(func, x0, xm, max_slice_error, recursionLevel)
                   + slice_area(func, xm, x1, max_slice_error, recursionLevel);
        }
    };

    for (size_t i = 0; i < nIntervals; i++)
    {
        const size_t nRecursionLevel = 0;
        fTotalArea += slice_area(func, x, x + dx, fMaxSliceError, nRecursionLevel);

        x += dx;
    }

    return fTotalArea;
}

/**
    @brief  Integrate using probabilistic algorithm Monte Carlo
    @param  funcIsInside        - func that returns
                                  1 if point is inside shape with positive value
                                  0 if point is not inside shape
                                  -1 if point is inside shape with negative value
    @param  pos0                - left down corner coordinates
    @param  pos1                - right up corner coordinates
    @param  nPointsPerOneSquare - points per 1 square (more is better)
    @retval                     - approximate integral
**/
inline double integrate_monte_carlo(
    const std::function<int(double, double)>& funcIsInside,
    glm::dvec2                                pos0,
    glm::dvec2                                pos1,
    size_t                                    nPointsPerOneSquare = 1000)
{
    const double fArea        = std::abs(pos1.x - pos0.x) * std::abs(pos1.y - pos0.y);
    const int    nTotalPoints = static_cast<int>(std::ceil(fArea * static_cast<double>(nPointsPerOneSquare)));

    int points_inside = 0;

    std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_real_distribution<double> x_dist(pos0.x, pos1.x);
    std::uniform_real_distribution<double> y_dist(pos0.y, pos1.y);

    for (int i = 0; i < nTotalPoints; i++)
    {
        int f = funcIsInside(x_dist(generator), y_dist(generator));
        if (f > 0)
            points_inside++;
        else if (f < 0)
            points_inside--;
    }

    return (static_cast<double>(points_inside) / nTotalPoints) * fArea;
}

/**
    @brief  Find root of the equation using Newtons method
    @param  f              - function
    @param  dfdx           - derivative
    @param  fInitialGuess  - initial root guess
    @param  fMaxError      - max error to stop searching
    @param  nMaxIterations - max iterations number (sometimes alg breaks)
    @retval                - approximate root
**/
inline double find_zero_newtons_method(
    const function2d& f,
    const function2d& dfdx,
    double            fInitialGuess,
    double            fMaxError      = 0.0001,
    size_t            nMaxIterations = 10000)
{
    double x = fInitialGuess;

    for (size_t i = 0; i < nMaxIterations; i++)
    {
        const double y = f(x);

        if (std::abs(y) < fMaxError)
            break;

        x -= y / dfdx(x);
    }

    return x;
}

} // namespace qx
