/**

    @file      test_iterate_several_containers.cpp
    @author    Khrapov
    @date      26.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_iterate_several_containers.cpp

#include <qx/algo/iterate_several_containers.h>

#include <array>
#include <list>
#include <vector>

TEST(iterate_several_containers, main)
{
    std::array  array { 0, 1, 2, 3, 4, 5, 6 };
    std::vector vector { 0, 2, 4, 6, 8 };
    std::list   list { 0, 3, 6, 9 };

    int nSum = 0;
    qx::iterate_several_containers(
        [&nSum](int num)
        {
            nSum += num;
        },
        array,
        vector,
        list);

    EXPECT_EQ(nSum, 59);
}