/**

    @file      test_integration.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_integration.cpp

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
