/**

    @file      test_equal.cpp
    @author    Khrapov
    @date      20.08.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

#include <qx/algo/equal.h>

#include <deque>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

//V_EXCLUDE_PATH *test_equal.cpp

template<class T, template<class...> class original_container_t, template<class...> class rotated_container_t>
void TestContainerWithAdapter()
{
    original_container_t<T> original { 0, 1, 2, 3, 4 };

    rotated_container_t<T> rotated0 { 1, 2, 3, 4, 0 };
    rotated_container_t<T> rotated1 { 2, 3, 4, 0, 1 };
    rotated_container_t<T> rotated2 { 3, 4, 0, 1, 2 };
    rotated_container_t<T> rotated3 { 4, 0, 1, 2, 3 };

    EXPECT_TRUE(qx::equal_rotated(original, original));
    EXPECT_TRUE(qx::equal_rotated(original, rotated0));
    EXPECT_TRUE(qx::equal_rotated(original, rotated1));
    EXPECT_TRUE(qx::equal_rotated(original, rotated2));
    EXPECT_TRUE(qx::equal_rotated(original, rotated3));

    rotated_container_t<T> rotatedWrongSize0 { 0, 1, 2, 3 };
    rotated_container_t<T> rotatedWrongSize1 { 0, 1, 2 };
    rotated_container_t<T> rotatedWrongSize2 { 0, 1 };
    rotated_container_t<T> rotatedWrongSize3 { 0 };

    EXPECT_FALSE(qx::equal_rotated(original, rotatedWrongSize0));
    EXPECT_FALSE(qx::equal_rotated(original, rotatedWrongSize1));
    EXPECT_FALSE(qx::equal_rotated(original, rotatedWrongSize2));
    EXPECT_FALSE(qx::equal_rotated(original, rotatedWrongSize3));
}

TEST(equal, main)
{
    TestContainerWithAdapter<char, std::vector, std::vector>();
    TestContainerWithAdapter<char, std::vector, std::deque>();
    TestContainerWithAdapter<char, std::vector, std::list>();
    TestContainerWithAdapter<char, std::vector, std::basic_string>();

    TestContainerWithAdapter<char, std::deque, std::vector>();
    TestContainerWithAdapter<char, std::deque, std::deque>();
    TestContainerWithAdapter<char, std::deque, std::list>();
    TestContainerWithAdapter<char, std::deque, std::basic_string>();

    TestContainerWithAdapter<char, std::list, std::vector>();
    TestContainerWithAdapter<char, std::list, std::deque>();
    TestContainerWithAdapter<char, std::list, std::list>();
    TestContainerWithAdapter<char, std::list, std::basic_string>();

    TestContainerWithAdapter<char, std::basic_string, std::vector>();
    TestContainerWithAdapter<char, std::basic_string, std::deque>();
    TestContainerWithAdapter<char, std::basic_string, std::list>();
    TestContainerWithAdapter<char, std::basic_string, std::basic_string>();
}
