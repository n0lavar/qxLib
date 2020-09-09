//==============================================================================
//
//!\file                         functional.h
//
//!\brief       Algorithms for math functions
//!\details     ~
//
//!\author      Khrapov
//!\date        2.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <functional>
#include <random>
#include <ctime>

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

#include <qx/other/useful_macros.h>

namespace qx
{

using function2d = std::function<double(double)>;

//==============================================================================
//!\fn                     qx::linear_interpolation
//
//!\brief  Linear interpolation algorithm
//!\param  p0 - point 0 (x - coord, y - f(x))
//!\param  p1 - point 1 (x - coord, y - f(x))
//!\param  x  - point
//!\retval    - ~f(x)
//!\author Khrapov
//!\date   10.11.2019
//==============================================================================
inline double linear_interpolation(glm::dvec2 p0, glm::dvec2 p1, double x)
{
    ASSERT_MSG(glm::epsilonNotEqual(p1.x, p0.x, DBL_EPSILON), "two x are equal, result is nan");
    return p0.y + (p1.y - p0.y) * (x - p0.x) / (p1.x - p0.x);
}

//==============================================================================
//!\fn                    qx::bilinear_inletpolation
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
//==============================================================================
inline double bilinear_inletpolation(glm::dvec3 p0, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec2 p)
{
    ASSERT_MSG(glm::epsilonEqual(p0.y, p1.y, DBL_EPSILON), "points must be as square");
    ASSERT_MSG(glm::epsilonEqual(p2.y, p3.y, DBL_EPSILON), "points must be as square");
    ASSERT_MSG(glm::epsilonEqual(p0.x, p3.x, DBL_EPSILON), "points must be as square");
    ASSERT_MSG(glm::epsilonEqual(p1.x, p2.x, DBL_EPSILON), "points must be as square");

    glm::dvec2 temp0 = { p0.y, linear_interpolation({ p0.x, p0.z }, { p1.x, p1.z }, p.x) };
    glm::dvec2 temp1 = { p2.y, linear_interpolation({ p2.x, p2.z }, { p3.x, p3.z }, p.x) };
    return linear_interpolation(temp0, temp1, p.y);
}

//==============================================================================
//!\fn                   qx::integrate_rectangle_rule
//
//!\brief  Interate using rectangle rule
//!\param  func                - target function
//!\param  x0                  - left border
//!\param  x1                  - right border
//!\param  num_intervals_per_1 - number of intervals per dx = 1
//!\retval                     - approximate integral
//!\author Khrapov
//!\date   2.02.2020
//==============================================================================
inline double integrate_rectangle_rule(const function2d&    func,
                                       double               x0,
                                       double               x1,
                                       size_t               num_intervals_per_1 = 10)
{
    size_t num_intervals = static_cast<size_t>(std::ceil((x1 - x0) * static_cast<double>(num_intervals_per_1)));
    double dx = (x1 - x0) / static_cast<double>(num_intervals);
    double total_area = 0.0;
    double x = x0;

    for (size_t i = 0; i < num_intervals; i++)
    {
        total_area += dx * func(x);
        x += dx;
    }

    return total_area;
}

//==============================================================================
//!\fn                   qx::integrate_trapezoid_rule
//
//!\brief  Interate using trapezoid rule
//!\param  func                - target function
//!\param  x0                  - left border
//!\param  x1                  - right border
//!\param  num_intervals_per_1 - number of intervals per dx = 1
//!\retval                     - approximate integral
//!\author Khrapov
//!\date   2.02.2020
//==============================================================================
inline double integrate_trapezoid_rule(const function2d& func,
                                       double            x0,
                                       double            x1,
                                       size_t            num_intervals_per_1 = 10)
{
    size_t num_intervals = static_cast<size_t>(std::ceil(static_cast<double>(num_intervals_per_1) * (x1 - x0)));
    double dx = (x1 - x0) / static_cast<double>(num_intervals);
    double total_area = 0.0;
    double x = x0;

    for (size_t i = 0; i < num_intervals; i++)
    {
        total_area += dx * (func(x) + func(x + dx)) / 2;
        x += dx;
    }

    return total_area;
}

//==============================================================================
//!\fn                 qx::integrate_adaptive_midpoint
//
//!\brief  Interate using adaptive midpoint
//!\param  func                - target function
//!\param  x0                  - left border
//!\param  x1                  - right border
//!\param  max_slice_error     - max error per one slice
//!\param  num_intervals_per_1 - number of intervals per dx = 1
//!\param  max_recursion       - max recursion depth
//!\retval                     - approximate integral
//!\author Khrapov
//!\date   2.02.2020
//==============================================================================
inline double integrate_adaptive_midpoint(const function2d& func,
                                          double            x0,
                                          double            x1,
                                          double            max_slice_error,
                                          size_t            num_intervals_per_1 = 10,
                                          size_t            max_recursion       = 300)
{
    size_t num_intervals = static_cast<size_t>(std::ceil(static_cast<double>(num_intervals_per_1) * (x1 - x0)));
    double dx = (x1 - x0) / static_cast<double>(num_intervals);
    double total = 0.0;
    double total_area = 0.0;
    double x = x0;

    std::function<double(const function2d&, double, double, double, size_t)> slice_area
        = [&slice_area, &max_recursion]
        (const function2d& func,
         double x0,
         double x1,
         double max_slice_error,
         size_t recursionLevel) -> double
    {
        recursionLevel++;
        double y0 = func(x0);
        double y1 = func(x1);
        double xm = (x0 + x1) / 2;
        double ym = func(xm);

        double area12 = (x1 - x0) * (y0 + y1) / 2.0;
        double area1m = (xm - x0) * (y0 + ym) / 2.0;
        double aream2 = (x1 - xm) * (ym + y1) / 2.0;
        double area1m2 = area1m + aream2;

        double error = (area1m2 - area12) / area12;

        if (recursionLevel > max_recursion || std::abs(error) < max_slice_error)
            return area1m2;
        else
            return slice_area(func, x0, xm, max_slice_error, recursionLevel) + slice_area(func, xm, x1, max_slice_error, recursionLevel);
    };

    for (size_t i = 0; i < num_intervals; i++)
    {
        size_t recursionLevel = 0;
        total_area += slice_area(func, x, x + dx, max_slice_error, recursionLevel);
        x += dx;
    }

    return total_area;
}

//==============================================================================
//!\fn                    qx::integrate_monte_carlo
//
//!\brief  Interate using probabilistic algorithm Monte Carlo
//!\param  funcIsInside   - func that returns
//                          1 if point is inside shape with positive value
//                          0 if point is not inside shape
//                          -1 if point is inside shape with negative value
//!\param  pos0           - left down corner coords
//!\param  pos1           - right up corner coords
//!\param  points_per_1sq - points per 1 sqare (more is better)
//!\retval                - approximate integral
//!\author Khrapov
//!\date   2.02.2020
//==============================================================================
inline double integrate_monte_carlo(const std::function<int(double, double)>&  funcIsInside,
                                    glm::dvec2                                 pos0,
                                    glm::dvec2                                 pos1,
                                    size_t                                     points_per_1sq = 1000)
{
    double area = std::abs(pos1.x - pos0.x) * std::abs(pos1.y - pos0.y);
    int total_points = static_cast<int>(std::ceil(area * static_cast<double>(points_per_1sq)));
    int points_inside = 0;

    std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
    std::uniform_real_distribution<double> x_dist(pos0.x, pos1.x);
    std::uniform_real_distribution<double> y_dist(pos0.y, pos1.y);

    for (int i = 0; i < total_points; i++)
    {
        int f = funcIsInside(x_dist(generator), y_dist(generator));
        if (f > 0)
            points_inside++;
        else if (f < 0)
            points_inside--;
    }

    return (static_cast<double>(points_inside) / total_points) * area;
}

//==============================================================================
//!\fn                   qx::find_zero_newtons_method
//
//!\brief  Find root of the equation using Newtons method
//!\param  f              - function
//!\param  dfdx           - derivative
//!\param  initial_guess  - initial root guess
//!\param  max_error      - max error to stop searching
//!\param  max_iterations - max iterations number (sometimes alg breaks)
//!\retval                - approximate root
//!\author Khrapov
//!\date   4.02.2020
//==============================================================================
inline double find_zero_newtons_method(const function2d&    f,
                                       const function2d&    dfdx,
                                       double               initial_guess,
                                       double               max_error       = 0.0001,
                                       size_t               max_iterations  = 10000)
{
    double x = initial_guess;

    for (size_t i = 0; i < max_iterations; i++)
    {
        double y = f(x);

        if (std::abs(y) < max_error)
            break;

        x -= y / dfdx(x);
    }

    return x;
}

}
