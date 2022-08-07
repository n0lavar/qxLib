/**

    @file      test_interpolation.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_interpolation.cpp

#include <qx/math/interpolation.h>

TEST(interpolation, linear_interpolation)
{
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ 0.0, 0.0 }, { 1.0, 0.0 }, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ 0.0, 0.0 }, { 1.0, 0.0 }, 0.5), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ 0.0, 0.0 }, { 1.0, 0.0 }, 1.0), 0.0);

    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ 0.0, 0.0 }, { 1.0, 1.0 }, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ 0.0, 0.0 }, { 1.0, 1.0 }, 0.5), 0.5);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ 0.0, 0.0 }, { 1.0, 1.0 }, 1.0), 1.0);

    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -1.0, 0.0 }, { 1.0, 1.0 }, -0.5), 0.25);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -1.0, 0.0 }, { 1.0, 1.0 }, 0.0), 0.5);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -1.0, 0.0 }, { 1.0, 1.0 }, 0.5), 0.75);

    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 }, -2.0), -1.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 }, -1.0), 0.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 }, 0.0), 1.0);
    EXPECT_DOUBLE_EQ(qx::linear_interpolation({ -2.0, -1.0 }, { 1.0, 2.0 }, 1.0), 2.0);
}

TEST(interpolation, bilinear_inletpolation)
{
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, 0.0 },
            { 1.0, -1.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { -1.0, 1.0, 0.0 },
            { 0.0, 0.0 }),
        0.0);
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, 0.0 },
            { 1.0, -1.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { -1.0, 1.0, 0.0 },
            { 1.0, 1.0 }),
        0.0);
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, 0.0 },
            { 1.0, -1.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { -1.0, 1.0, 0.0 },
            { -1.0, 1.0 }),
        0.0);
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, 0.0 },
            { 1.0, -1.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { -1.0, 1.0, 0.0 },
            { 0.0, 0.0 }),
        0.0);

    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, -1.0 },
            { 1.0, -1.0, -1.0 },
            { 1.0, 1.0, 1.0 },
            { -1.0, 1.0, 1.0 },
            { 0.0, 0.0 }),
        0.0);
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, -1.0 },
            { 1.0, -1.0, -1.0 },
            { 1.0, 1.0, 1.0 },
            { -1.0, 1.0, 1.0 },
            { 1.0, 1.0 }),
        1.0);
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, -1.0 },
            { 1.0, -1.0, -1.0 },
            { 1.0, 1.0, 1.0 },
            { -1.0, 1.0, 1.0 },
            { 0.5, 0.5 }),
        0.5);
    EXPECT_DOUBLE_EQ(
        qx::bilinear_interpolation(
            { -1.0, -1.0, -1.0 },
            { 1.0, -1.0, -1.0 },
            { 1.0, 1.0, 1.0 },
            { -1.0, 1.0, 1.0 },
            { -0.5, -0.5 }),
        -0.5);
}
