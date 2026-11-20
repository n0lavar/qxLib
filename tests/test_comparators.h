/**

    @file      test_comparators.h
    @brief     Tests comparison helpers
    @author    Khrapov
    @date      20.11.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <common.h>

#include <qx/containers/string/string.h>
#include <qx/math/float_compare.h>

#include <concepts>

void expect_equal(const qx::string& sLeft, const qx::string& sRight);

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
