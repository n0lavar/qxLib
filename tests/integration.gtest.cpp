/**

    @file      integration.gtest.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

#include <qx/math/integration.h>

const auto func_x = [](double x) -> double
{
    return x;
};
const auto func_x2 = [](double x) -> double
{
    return x * x;
};

TEST(integration, integrate_rectangle_rule)
{
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x, 0.0, 1.0), 0.5, 0.3);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x, 0.0, 0.5), 0.25, 0.3);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x, -1.0, 1.0), 0.0, 0.3);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x, -0.5, 1.0), 0.25, 0.3);

    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2, 0.0, 1.0), 0.33333, 0.05);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2, 0.0, 0.5), 0.04166, 0.05);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2, -1.0, 1.0), 0.66666, 0.05);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2, -0.5, 1.0), 0.375, 0.05);
}

TEST(integration, integrate_trapezoid_rule)
{
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x, 0.0, 1.0), 0.5, 0.13);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x, 0.0, 0.5), 0.25, 0.13);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x, -1.0, 1.0), 0.0, 0.13);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x, -0.5, 1.0), 0.25, 0.13);

    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2, 0.0, 1.0), 0.33333, 0.005);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2, 0.0, 0.5), 0.04166, 0.005);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2, -1.0, 1.0), 0.66666, 0.005);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2, -0.5, 1.0), 0.375, 0.005);
}

TEST(integration, integrate_adaptive_midpoint)
{
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x, 0.0, 1.0, 0.001), 0.5, 0.13);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x, 0.0, 0.5, 0.001), 0.25, 0.13);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x, -1.0, 1.0, 0.001), 0.0, 0.13);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x, -0.5, 1.0, 0.001), 0.25, 0.13);

    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2, 0.0, 1.0, 0.001), 0.33333, 0.0002);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2, 0.0, 0.5, 0.001), 0.04166, 0.0002);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2, -1.0, 1.0, 0.001), 0.66666, 0.0002);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2, -0.5, 1.0, 0.001), 0.375, 0.0002);
}

const auto b_func_x = [](double x, double y) -> int
{
    if (y > 0 && y <= x)
        return 1;
    else if (y <= 0 && y >= x)
        return -1;
    else
        return 0;
};
const auto b_func_x2 = [](double x, double y) -> int
{
    return y > 0 && y < x * x;
};

TEST(integration, bounds_and_sample_count)
{
    const auto check = [](const auto& integrate)
    {
        EXPECT_DOUBLE_EQ(integrate(1.0, 1.0, 10), 0.0);
        EXPECT_NEAR(integrate(1.0, 0.0, 100), -0.5, 0.01);
        EXPECT_TRUE(std::isnan(integrate(0.0, 1.0, 0)));
        EXPECT_TRUE(std::isnan(integrate(0.0, std::numeric_limits<double>::quiet_NaN(), 10)));
        EXPECT_TRUE(std::isnan(integrate(0.0, std::numeric_limits<double>::infinity(), 10)));
        EXPECT_TRUE(std::isnan(integrate(0.0, 2.0, std::numeric_limits<size_t>::max())));
    };

    check(
        [](double x0, double x1, size_t nDensity)
        {
            return qx::integrate_rectangle_rule(func_x, x0, x1, nDensity);
        });
    check(
        [](double x0, double x1, size_t nDensity)
        {
            return qx::integrate_trapezoid_rule(func_x, x0, x1, nDensity);
        });
    check(
        [](double x0, double x1, size_t nDensity)
        {
            return qx::integrate_adaptive_midpoint(func_x, x0, x1, 0.001, nDensity);
        });
}

TEST(integration, monte_carlo_bounds_and_sample_count)
{
    const auto inside = [](double, double)
    {
        return 1;
    };
    EXPECT_DOUBLE_EQ(qx::integrate_monte_carlo(inside, { 1.0, 1.0 }, { 1.0, 2.0 }), 0.0);
    EXPECT_DOUBLE_EQ(qx::integrate_monte_carlo(inside, { 2.0, 3.0 }, { 0.0, 0.0 }, 1), 6.0);
    EXPECT_TRUE(std::isnan(qx::integrate_monte_carlo(inside, { 0.0, 0.0 }, { 1.0, 1.0 }, 0)));
    EXPECT_TRUE(
        std::isnan(qx::integrate_monte_carlo(inside, { 0.0, 0.0 }, { std::numeric_limits<double>::infinity(), 1.0 })));
    EXPECT_TRUE(
        std::isnan(qx::integrate_monte_carlo(inside, { 0.0, 0.0 }, { 2.0, 2.0 }, std::numeric_limits<int>::max())));
}

TEST(integration, noexcept_callback_contract)
{
    const auto func = [](double x) noexcept
    {
        return x;
    };
    const auto inside = [](double, double) noexcept
    {
        return 1;
    };
    static_assert(noexcept(qx::integrate_rectangle_rule(func, 0.0, 1.0)));
    static_assert(noexcept(qx::integrate_trapezoid_rule(func, 0.0, 1.0)));
    static_assert(noexcept(qx::integrate_adaptive_midpoint(func, 0.0, 1.0, 0.001)));
    using monte_carlo_type = double (*)(const decltype(inside)&, glm::dvec2, glm::dvec2, size_t) noexcept;
    static_assert(std::is_same_v<decltype(&qx::integrate_monte_carlo<decltype(inside)>), monte_carlo_type>);
    static_assert(!noexcept(qx::integrate_rectangle_rule(func_x, 0.0, 1.0)));
    EXPECT_TRUE(std::isnan(qx::integrate_rectangle_rule(func, 0.0, 1.0, 0)));
}

TEST(functional, integrate_monte_carlo)
{
#if 0
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  {  0.0, -1.0 }, { 1.0, 1.0 }),  0.5, 0.3);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  {  0.0, -1.0 }, { 0.5, 1.0 }), 0.25, 0.3);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  { -1.0, -1.0 }, { 1.0, 1.0 }),  0.0, 0.3);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  { -0.5, -1.0 }, { 1.0, 1.0 }), 0.25, 0.3);

    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, {  0.0, -1.0 }, { 1.0, 1.0 }), 0.33333, 0.05);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, {  0.0, -1.0 }, { 0.5, 1.0 }), 0.04166, 0.05);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, { -1.0, -1.0 }, { 1.0, 1.0 }), 0.66666, 0.05);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, { -0.5, -1.0 }, { 1.0, 1.0 }), 0.375,   0.05);
#endif
}
