//==============================================================================
//
//!\file                     test_functional.cpp
//
//!\brief       Tests for functional algorithms
//!\details     ~
//
//!\author      Khrapov
//!\date        14.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_functional.cpp

#if QX_TEST_FUNCTIONAL

#include <qx/alg/functional.h>


TEST(functional, linear_interpolation)
{
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({  0.0,  0.0 }, { 1.0, 0.0 },  0.0), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({  0.0,  0.0 }, { 1.0, 0.0 },  0.5), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({  0.0,  0.0 }, { 1.0, 0.0 },  1.0), 0.0);

    EXPECT_DOUBLE_EQ(qx::linear_interpolation({  0.0,  0.0 }, { 1.0, 1.0 },  0.0), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({  0.0,  0.0 }, { 1.0, 1.0 },  0.5), 0.5);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({  0.0,  0.0 }, { 1.0, 1.0 },  1.0), 1.0);

    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -1.0,  0.0 }, { 1.0, 1.0 }, -0.5), 0.25);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -1.0,  0.0 }, { 1.0, 1.0 },  0.0), 0.5);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -1.0,  0.0 }, { 1.0, 1.0 },  0.5), 0.75);

    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 }, -2.0), -1.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 }, -1.0),  0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 },  0.0),  1.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 },  1.0),  2.0);
}

TEST(functional, bilinear_inletpolation)
{
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0,  0.0 },
                                                {  1.0, -1.0,  0.0 },
                                                {  1.0,  1.0,  0.0 },
                                                { -1.0,  1.0,  0.0 },
                                                {  0.0,  0.0 }),
                     0.0);
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0,  0.0 },
                                                {  1.0, -1.0,  0.0 },
                                                {  1.0,  1.0,  0.0 },
                                                { -1.0,  1.0,  0.0 },
                                                {  1.0,  1.0 }),
                     0.0);
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0,  0.0 },
                                                {  1.0, -1.0,  0.0 },
                                                {  1.0,  1.0,  0.0 },
                                                { -1.0,  1.0,  0.0 },
                                                { -1.0,  1.0 }),
                     0.0);
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0,  0.0 },
                                                {  1.0, -1.0,  0.0 },
                                                {  1.0,  1.0,  0.0 },
                                                { -1.0,  1.0,  0.0 },
                                                {  0.0,  0.0 }),
                     0.0);

    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0, -1.0 },
                                                {  1.0, -1.0, -1.0 },
                                                {  1.0,  1.0,  1.0 },
                                                { -1.0,  1.0,  1.0 },
                                                {  0.0,  0.0 }),
                     0.0);
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0, -1.0 },
                                                {  1.0, -1.0, -1.0 },
                                                {  1.0,  1.0,  1.0 },
                                                { -1.0,  1.0,  1.0 },
                                                {  1.0,  1.0 }),
                     1.0);
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0, -1.0 },
                                                {  1.0, -1.0, -1.0 },
                                                {  1.0,  1.0,  1.0 },
                                                { -1.0,  1.0,  1.0 },
                                                {  0.5,  0.5 }),
                     0.5);
    EXPECT_DOUBLE_EQ(qx::bilinear_interpolation({ -1.0, -1.0, -1.0 },
                                                {  1.0, -1.0, -1.0 },
                                                {  1.0,  1.0,  1.0 },
                                                { -1.0,  1.0,  1.0 },
                                                { -0.5, -0.5 }),
                     -0.5);
}

const qx::function2d func_x  = [] (double x) -> double { return x; };
const qx::function2d func_x2 = [] (double x) -> double { return x * x; };

TEST(functional, integrate_rectangle_rule)
{
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x,   0.0, 1.0),  0.5, 0.3);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x,   0.0, 0.5), 0.25, 0.3);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x,  -1.0, 1.0),  0.0, 0.3);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x,  -0.5, 1.0), 0.25, 0.3);

    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2,  0.0, 1.0), 0.33333, 0.05);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2,  0.0, 0.5), 0.04166, 0.05);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2, -1.0, 1.0), 0.66666, 0.05);
    EXPECT_NEAR(qx::integrate_rectangle_rule(func_x2, -0.5, 1.0), 0.375,   0.05);
}

TEST(functional, integrate_trapezoid_rule)
{
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x,   0.0, 1.0),  0.5, 0.13);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x,   0.0, 0.5), 0.25, 0.13);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x,  -1.0, 1.0),  0.0, 0.13);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x,  -0.5, 1.0), 0.25, 0.13);

    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2,  0.0, 1.0), 0.33333, 0.005);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2,  0.0, 0.5), 0.04166, 0.005);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2, -1.0, 1.0), 0.66666, 0.005);
    EXPECT_NEAR(qx::integrate_trapezoid_rule(func_x2, -0.5, 1.0), 0.375,   0.005);
}

TEST(functional, integrate_adaptive_midpoint)
{
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x,   0.0, 1.0, 0.001),  0.5, 0.13);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x,   0.0, 0.5, 0.001), 0.25, 0.13);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x,  -1.0, 1.0, 0.001),  0.0, 0.13);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x,  -0.5, 1.0, 0.001), 0.25, 0.13);

    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2,  0.0, 1.0, 0.001), 0.33333, 0.0002);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2,  0.0, 0.5, 0.001), 0.04166, 0.0002);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2, -1.0, 1.0, 0.001), 0.66666, 0.0002);
    EXPECT_NEAR(qx::integrate_adaptive_midpoint(func_x2, -0.5, 1.0, 0.001), 0.375,   0.0002);
}

const auto b_func_x  = [] (double x, double y) -> int
{
    if (y > 0 && y <= x)
        return 1;
    else if (y <= 0 && y >= x)
        return -1;
    else
        return 0;
};
const auto b_func_x2 = [] (double x, double y) -> int { return y > 0 && y < x * x; };

TEST(functional, integrate_monte_carlo)
{
    /*
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  {  0.0, -1.0 }, { 1.0, 1.0 }),  0.5, 0.3);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  {  0.0, -1.0 }, { 0.5, 1.0 }), 0.25, 0.3);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  { -1.0, -1.0 }, { 1.0, 1.0 }),  0.0, 0.3);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x,  { -0.5, -1.0 }, { 1.0, 1.0 }), 0.25, 0.3);

    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, {  0.0, -1.0 }, { 1.0, 1.0 }), 0.33333, 0.05);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, {  0.0, -1.0 }, { 0.5, 1.0 }), 0.04166, 0.05);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, { -1.0, -1.0 }, { 1.0, 1.0 }), 0.66666, 0.05);
    EXPECT_NEAR(qx::integrate_monte_carlo(b_func_x2, { -0.5, -1.0 }, { 1.0, 1.0 }), 0.375,   0.05);
    */
}

const qx::function2d func_x2_dx = [] (double x) -> double { return 2 * x; };

TEST(functional, find_zero_newtons_method)
{
    EXPECT_NEAR(qx::find_zero_newtons_method(func_x2, func_x2_dx, 1.0), 0.0, 0.01);
    EXPECT_NEAR(qx::find_zero_newtons_method(func_x2, func_x2_dx, 10.0), 0.0, 0.01);
    EXPECT_NEAR(qx::find_zero_newtons_method(func_x2, func_x2_dx, 100.0), 0.0, 0.01);
}

#endif