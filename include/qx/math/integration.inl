/**

    @file      integration.inl
    @author    Khrapov
    @date      29.04.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class function_2d_t>
inline double integrate_rectangle_rule(const function_2d_t& func, double x0, double x1, size_t nIntervalsPer1)
{
    const size_t nIntervals = static_cast<size_t>(std::ceil((x1 - x0) * static_cast<double>(nIntervalsPer1)));

    const double dx         = (x1 - x0) / static_cast<double>(nIntervals);
    double       fTotalArea = 0.0;
    double       x          = x0;

    for (size_t i = 0; i < nIntervals; ++i)
    {
        fTotalArea += dx * func(x);
        x += dx;
    }

    return fTotalArea;
}

template<class function_2d_t>
double integrate_trapezoid_rule(const function_2d_t& func, double x0, double x1, size_t nIntervalsPer1)
{
    const size_t nIntervals = static_cast<size_t>(std::ceil(static_cast<double>(nIntervalsPer1) * (x1 - x0)));

    const double dx         = (x1 - x0) / static_cast<double>(nIntervals);
    double       fTotalArea = 0.0;
    double       x          = x0;

    for (size_t i = 0; i < nIntervals; ++i)
    {
        fTotalArea += dx * (func(x) + func(x + dx)) / 2;
        x += dx;
    }

    return fTotalArea;
}

template<class function_2d_t>
double integrate_adaptive_midpoint(
    const function_2d_t& func,
    double               x0,
    double               x1,
    double               fMaxSliceError,
    size_t               nIntervalsPer1,
    size_t               nMaxRecursion)
{
    const size_t nIntervals = static_cast<size_t>(std::ceil(static_cast<double>(nIntervalsPer1) * (x1 - x0)));

    const double dx         = (x1 - x0) / static_cast<double>(nIntervals);
    double       fTotalArea = 0.0;
    double       x          = x0;

    auto slice_area = make_recursive_lambda(
        [nMaxRecursion](
            const auto&          slice_area,
            const function_2d_t& func,
            double               x0,
            double               x1,
            double               max_slice_error,
            size_t               recursionLevel)
        {
            const double y0 = func(x0);
            const double y1 = func(x1);
            const double xm = (x0 + x1) / 2;
            const double ym = func(xm);

            const double fArea12  = (x1 - x0) * (y0 + y1) / 2.0;
            const double fArea1m  = (xm - x0) * (y0 + ym) / 2.0;
            const double fAream2  = (x1 - xm) * (ym + y1) / 2.0;
            const double fArea1m2 = fArea1m + fAream2;

            const double fError = (fArea1m2 - fArea12) / fArea12;

            ++recursionLevel;
            if (recursionLevel > nMaxRecursion || std::abs(fError) < max_slice_error)
            {
                return fArea1m2;
            }
            else
            {
                return slice_area(func, x0, xm, max_slice_error, recursionLevel)
                       + slice_area(func, xm, x1, max_slice_error, recursionLevel);
            }
        });

    for (size_t i = 0; i < nIntervals; ++i)
    {
        fTotalArea += slice_area(func, x, x + dx, fMaxSliceError, 0);
        x += dx;
    }

    return fTotalArea;
}

template<class function_2d_t>
double integrate_monte_carlo(
    const function_2d_t& funcIsInside,
    glm::dvec2           pos0,
    glm::dvec2           pos1,
    size_t               nPointsPerOneSquare)
{
    const double fArea        = std::abs(pos1.x - pos0.x) * std::abs(pos1.y - pos0.y);
    const int    nTotalPoints = static_cast<int>(std::ceil(fArea * static_cast<double>(nPointsPerOneSquare)));

    int points_inside = 0;

    std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_real_distribution<double> x_dist(pos0.x, pos1.x);
    std::uniform_real_distribution<double> y_dist(pos0.y, pos1.y);

    for (int i = 0; i < nTotalPoints; ++i)
    {
        int f = funcIsInside(x_dist(generator), y_dist(generator));
        if (f > 0)
            points_inside++;
        else if (f < 0)
            points_inside--;
    }

    return (static_cast<double>(points_inside) / nTotalPoints) * fArea;
}
} // namespace qx
