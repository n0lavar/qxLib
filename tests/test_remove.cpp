/**

    @file      test_remove.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_remove.cpp

#include <qx/algo/remove.h>
#include <qx/math/common.h>

#include <vector>

TEST(remove, remove_if_i)
{
    std::vector<int> vector;
    auto             reset_vector = [&vector]()
    {
        vector = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
    };

    const auto predicate = [](size_t i)
    {
        return qx::is_even(i);
    };

    reset_vector();
    qx::remove_if_i(vector, predicate);
    EXPECT_EQ(vector[0], 2);
    EXPECT_EQ(vector[1], 6);
    EXPECT_EQ(vector[2], 10);
    EXPECT_EQ(vector[3], 14);
    EXPECT_EQ(vector[4], 18);
    EXPECT_EQ(vector.size(), 10);

    reset_vector();
    qx::remove_if_i(vector.begin() + 2, vector.end(), predicate, 2);
    EXPECT_EQ(vector[0], 0);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 6);
    EXPECT_EQ(vector[3], 10);
    EXPECT_EQ(vector[4], 14);
    EXPECT_EQ(vector[5], 18);
    EXPECT_EQ(vector.size(), 10);
}
