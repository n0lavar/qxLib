/**

    @file      all_of_equal.gtest.cpp
    @author    Khrapov
    @date      7.02.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *all_of_equal.gtest.cpp

#include <qx/algo/all_of_equal.h>

TEST(all_of_equal, main)
{
    std::vector v0 { true, true, true };
    std::vector v1 { true, true, false };
    std::vector v2 { true, false, false };
    std::vector v3 { false, false, false };
    std::vector v4 { false, true, true };
    std::vector v5 { false, false, true };
    std::vector v6 { false, true, false };
    std::vector v7 { true, false, true };

    auto simple_predicate = [](bool bValue)
    {
        return bValue;
    };

    EXPECT_TRUE(qx::all_of_equal(v0, simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v1, simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v2, simple_predicate));
    EXPECT_TRUE(qx::all_of_equal(v3, simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v4, simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v5, simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v6, simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v7, simple_predicate));

    EXPECT_TRUE(qx::all_of_equal(v0.begin(), v0.end(), simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v1.begin(), v1.end(), simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v2.begin(), v2.end(), simple_predicate));
    EXPECT_TRUE(qx::all_of_equal(v3.begin(), v3.end(), simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v4.begin(), v4.end(), simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v5.begin(), v5.end(), simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v6.begin(), v6.end(), simple_predicate));
    EXPECT_FALSE(qx::all_of_equal(v7.begin(), v7.end(), simple_predicate));
}
