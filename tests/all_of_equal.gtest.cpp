/**

    @file      all_of_equal.gtest.cpp
    @author    Khrapov
    @date      7.02.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#include <qx/algo/all_of_equal.h>

TEST(all_of_equal, main)
{
    auto test_container = [](const auto& container, bool bExpectedValue)
    {
        auto simple_predicate = [](bool bValue)
        {
            return bValue;
        };

        EXPECT_EQ(qx::all_of_equal(container, simple_predicate), bExpectedValue);
        EXPECT_EQ(qx::all_of_equal(container.begin(), container.end(), simple_predicate), bExpectedValue);
    };

    test_container(std::vector { true, true, true }, true);
    test_container(std::vector { true, true, false }, false);
    test_container(std::vector { true, false, false }, false);
    test_container(std::vector { false, false, false }, true);
    test_container(std::vector { false, true, true }, false);
    test_container(std::vector { false, false, true }, false);
    test_container(std::vector { false, true, false }, false);
    test_container(std::vector { true, false, true }, false);
}
