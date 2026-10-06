/**

    @file      integration.inl
    @author    Khrapov
    @date      29.04.2023
    @copyright (c) Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

namespace details
{

template<class count_t>
inline std::optional<count_t> integration_sample_count(double fExtent, size_t nSamplesPerUnit) noexcept
{
    if (!std::isfinite(fExtent) || nSamplesPerUnit == 0)
        return std::nullopt;

    const double fCount = std::ceil(std::abs(fExtent) * static_cast<double>(nSamplesPerUnit));

    // A power of two is exact in double, unlike the largest size_t value.
    const double fCountLimit = std::ldexp(1.0, std::numeric_limits<count_t>::digits);
    if (!std::isfinite(fCount) || fCount >= fCountLimit)
        return std::nullopt;

    return static_cast<count_t>(fCount);
}

} // namespace details

template<class function_2d_t>
inline double integrate_rectangle_rule(const function_2d_t& func, double x0, double x1, size_t nIntervalsPer1)
    noexcept(noexcept(static_cast<double>(func(0.0))))
{
    const auto optIntervals = details::integration_sample_count<size_t>(x1 - x0, nIntervalsPer1);
    if (!optIntervals)
        return std::numeric_limits<double>::quiet_NaN();

    const size_t nIntervals = *optIntervals;
    if (nIntervals == 0)
        return 0.0;

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
    noexcept(noexcept(static_cast<double>(func(0.0))))
{
    const auto optIntervals = details::integration_sample_count<size_t>(x1 - x0, nIntervalsPer1);
    if (!optIntervals)
        return std::numeric_limits<double>::quiet_NaN();

    const size_t nIntervals = *optIntervals;
    if (nIntervals == 0)
        return 0.0;

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
    size_t               nMaxRecursion) noexcept(noexcept(static_cast<double>(func(0.0))))
{
    const auto optIntervals = details::integration_sample_count<size_t>(x1 - x0, nIntervalsPer1);
    if (!optIntervals)
        return std::numeric_limits<double>::quiet_NaN();

    const size_t nIntervals = *optIntervals;
    if (nIntervals == 0)
        return 0.0;

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
    size_t               nPointsPerOneSquare) noexcept(noexcept(static_cast<int>(funcIsInside(0.0, 0.0))))
{
    const double fArea        = std::abs(pos1.x - pos0.x) * std::abs(pos1.y - pos0.y);

    const auto optTotalPoints = details::integration_sample_count<int>(fArea, nPointsPerOneSquare);
    if (!optTotalPoints)
        return std::numeric_limits<double>::quiet_NaN();

    const int nTotalPoints = *optTotalPoints;
    if (nTotalPoints == 0)
        return 0.0;

    int points_inside = 0;

    std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_real_distribution<double> x_dist(std::min(pos0.x, pos1.x), std::max(pos0.x, pos1.x));
    std::uniform_real_distribution<double> y_dist(std::min(pos0.y, pos1.y), std::max(pos0.y, pos1.y));

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
