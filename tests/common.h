/**

    @file      test_config.h
    @brief     Tests configuring
    @author    Khrapov
    @date      8.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/macros/suppress_warnings.h>
#include <qx/math/float_compare.h>
#include <qx/pvs_config.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <gtest/gtest.h>
QX_POP_SUPPRESS_WARNINGS();

#define GTEST_SINGLE_ARGUMENT(...) (__VA_ARGS__)

template<std::floating_point T>
void expect_equal(T left, T right)
{
    EXPECT_TRUE(qx::float_compare(left, right));
}

template<std::integral T>
void expect_equal(T left, T right)
{
    EXPECT_EQ(left, right);
}

void expect_equal(const qx::string& sLeft, const qx::string& sRight)
{
    EXPECT_STREQ(sLeft.c_str(), sRight.c_str());
}

template<class T, class U>
void expect_equal(T left, U right)
{
    EXPECT_EQ(left, right);
}
