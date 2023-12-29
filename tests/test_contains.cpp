/**

    @file      test_contains.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_contains.cpp

#include <qx/algo/contains.h>

#include <array>

TEST(contains, contains)
{
    std::array ARRAY { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    EXPECT_FALSE(qx::contains(ARRAY.begin(), ARRAY.end(), -2));
    EXPECT_FALSE(qx::contains(ARRAY.begin(), ARRAY.end(), -1));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 0));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 1));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 2));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 3));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 4));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 5));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 6));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 7));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 8));
    EXPECT_TRUE(qx::contains(ARRAY.begin(), ARRAY.end(), 9));
    EXPECT_FALSE(qx::contains(ARRAY.begin(), ARRAY.end(), 10));
    EXPECT_FALSE(qx::contains(ARRAY.begin(), ARRAY.end(), 11));

    EXPECT_FALSE(qx::contains(ARRAY.begin(), ARRAY.end() - 2, 8));
    EXPECT_FALSE(qx::contains(ARRAY.begin(), ARRAY.end() - 2, 9));

    EXPECT_FALSE(qx::contains(ARRAY, -2));
    EXPECT_FALSE(qx::contains(ARRAY, -1));
    EXPECT_TRUE(qx::contains(ARRAY, 0));
    EXPECT_TRUE(qx::contains(ARRAY, 1));
    EXPECT_TRUE(qx::contains(ARRAY, 2));
    EXPECT_TRUE(qx::contains(ARRAY, 3));
    EXPECT_TRUE(qx::contains(ARRAY, 4));
    EXPECT_TRUE(qx::contains(ARRAY, 5));
    EXPECT_TRUE(qx::contains(ARRAY, 6));
    EXPECT_TRUE(qx::contains(ARRAY, 7));
    EXPECT_TRUE(qx::contains(ARRAY, 8));
    EXPECT_TRUE(qx::contains(ARRAY, 9));
    EXPECT_FALSE(qx::contains(ARRAY, 10));
    EXPECT_FALSE(qx::contains(ARRAY, 11));
}

TEST(contains, contains_if)
{
    std::array         ARRAY_0 { 0, 1, 2, 3, 4, 5 };
    std::array         ARRAY_1 { 5, 6, 7, 8, 9 };
    std::array         ARRAY_2 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::array<int, 0> ARRAY_3 {};

    const auto predicate = [](int num)
    {
        return num > 5;
    };

    EXPECT_FALSE(qx::contains_if(ARRAY_0, predicate));
    EXPECT_TRUE(qx::contains_if(ARRAY_1, predicate));
    EXPECT_TRUE(qx::contains_if(ARRAY_2, predicate));
    EXPECT_FALSE(qx::contains_if(ARRAY_3, predicate));

    EXPECT_FALSE(qx::contains_if(ARRAY_0.begin(), ARRAY_0.end(), predicate));
    EXPECT_TRUE(qx::contains_if(ARRAY_1.begin(), ARRAY_1.end(), predicate));
    EXPECT_TRUE(qx::contains_if(ARRAY_2.begin(), ARRAY_2.end(), predicate));
    EXPECT_FALSE(qx::contains_if(ARRAY_3.begin(), ARRAY_3.end(), predicate));

    EXPECT_FALSE(qx::contains_if(ARRAY_2.begin(), ARRAY_2.begin() + 4, predicate));
}

TEST(contains, contains_any)
{
    std::array         ARRAY_0 { 0, 1, 2, 3, 4 };
    std::array         ARRAY_1 { 0, 1, 2, 3, 4, 5 };
    std::array         ARRAY_2 { 5, 6, 7, 8, 9 };
    std::array<int, 0> ARRAY_3 {};

    EXPECT_TRUE(qx::contains_any(ARRAY_0, ARRAY_0));
    EXPECT_TRUE(qx::contains_any(ARRAY_0.begin(), ARRAY_0.end(), ARRAY_0.begin(), ARRAY_0.end()));

    EXPECT_TRUE(qx::contains_any(ARRAY_0, ARRAY_1));
    EXPECT_TRUE(qx::contains_any(ARRAY_0.begin(), ARRAY_0.end(), ARRAY_1.begin(), ARRAY_1.end()));

    EXPECT_FALSE(qx::contains_any(ARRAY_0, ARRAY_2));
    EXPECT_FALSE(qx::contains_any(ARRAY_0.begin(), ARRAY_0.end(), ARRAY_2.begin(), ARRAY_2.end()));

    EXPECT_FALSE(qx::contains_any(ARRAY_0, ARRAY_3));
    EXPECT_FALSE(qx::contains_any(ARRAY_0.begin(), ARRAY_0.end(), ARRAY_3.begin(), ARRAY_3.end()));

    EXPECT_TRUE(qx::contains_any(ARRAY_1, ARRAY_1));
    EXPECT_TRUE(qx::contains_any(ARRAY_1.begin(), ARRAY_1.end(), ARRAY_1.begin(), ARRAY_1.end()));

    EXPECT_TRUE(qx::contains_any(ARRAY_1, ARRAY_2));
    EXPECT_TRUE(qx::contains_any(ARRAY_1.begin(), ARRAY_1.end(), ARRAY_2.begin(), ARRAY_2.end()));

    EXPECT_FALSE(qx::contains_any(ARRAY_1, ARRAY_3));
    EXPECT_FALSE(qx::contains_any(ARRAY_1.begin(), ARRAY_1.end(), ARRAY_3.begin(), ARRAY_3.end()));

    EXPECT_TRUE(qx::contains_any(ARRAY_2, ARRAY_2));
    EXPECT_TRUE(qx::contains_any(ARRAY_2.begin(), ARRAY_2.end(), ARRAY_2.begin(), ARRAY_2.end()));

    EXPECT_FALSE(qx::contains_any(ARRAY_2, ARRAY_3));
    EXPECT_FALSE(qx::contains_any(ARRAY_2.begin(), ARRAY_2.end(), ARRAY_3.begin(), ARRAY_3.end()));
}
