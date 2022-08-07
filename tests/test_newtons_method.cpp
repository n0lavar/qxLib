/**

    @file      test_newtons_method.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_newtons_method.cpp

#include <qx/math/newtons_method.h>

TEST(newtons_method, newtons_method)
{
    const auto func_x2 = [](double x) -> double
    {
        return x * x;
    };

    const auto func_x2_dx = [](double x) -> double
    {
        return 2 * x;
    };

    EXPECT_NEAR(qx::newtons_method(func_x2, func_x2_dx, 1.0), 0.0, 0.01);
    EXPECT_NEAR(qx::newtons_method(func_x2, func_x2_dx, 10.0), 0.0, 0.01);
    EXPECT_NEAR(qx::newtons_method(func_x2, func_x2_dx, 100.0), 0.0, 0.01);
}
