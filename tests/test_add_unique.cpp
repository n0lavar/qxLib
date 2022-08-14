/**

    @file      test_add_unique.cpp
    @author    Khrapov
    @date      14.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_add_unique.cpp

#include <qx/algo/add_unique.h>

#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>

template<class ContainerType>
void CheckContainer()
{
    ContainerType container { 'a', 'b', 'c', 'd', 'e', 'f', 'u' };
    EXPECT_FALSE(qx::add_unique(container, 'a'));
    EXPECT_FALSE(qx::add_unique(container, 'b'));
    EXPECT_FALSE(qx::add_unique(container, 'c'));
    EXPECT_FALSE(qx::add_unique(container, 'd'));
    EXPECT_FALSE(qx::add_unique(container, 'e'));
    EXPECT_FALSE(qx::add_unique(container, 'f'));
    EXPECT_FALSE(qx::add_unique(container, 'u'));
    EXPECT_TRUE(qx::add_unique(container, 'x'));
    EXPECT_TRUE(qx::add_unique(container, 'y'));
    EXPECT_TRUE(qx::add_unique(container, 't'));
    EXPECT_TRUE(qx::add_unique(container, 'n'));
}

TEST(add_unique, add_unique)
{
    CheckContainer<std::vector<char>>();
    CheckContainer<std::deque<char>>();
    CheckContainer<std::list<char>>();
    CheckContainer<std::set<char>>();
    CheckContainer<std::multiset<char>>();
    CheckContainer<std::unordered_set<char>>();
    CheckContainer<std::unordered_multiset<char>>();
    CheckContainer<std::basic_string<char>>();
}
