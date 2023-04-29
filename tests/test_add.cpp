/**

    @file      test_add.cpp
    @author    Khrapov
    @date      14.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_add.cpp

#include <qx/algo/add.h>

#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>

template<class container_t>
void check_add_unique()
{
    container_t container { 'a', 'b', 'c', 'd', 'e', 'f', 'u' };
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

TEST(add, add_unique)
{
    check_add_unique<std::vector<char>>();
    check_add_unique<std::deque<char>>();
    check_add_unique<std::list<char>>();
    check_add_unique<std::set<char>>();
    check_add_unique<std::multiset<char>>();
    check_add_unique<std::unordered_set<char>>();
    check_add_unique<std::unordered_multiset<char>>();
    check_add_unique<std::basic_string<char>>();
}

template<class container_t>
void check_add_if()
{
    container_t container { 'a', 'b', 'c', 'd', 'e', 'f', 'u' };
    const auto  predicate = [](int existing, int value)
    {
        return existing == value;
    };

    EXPECT_FALSE(qx::add_unique_if(container, 'a', predicate));
    EXPECT_FALSE(qx::add_unique_if(container, 'b', predicate));
    EXPECT_FALSE(qx::add_unique_if(container, 'c', predicate));
    EXPECT_FALSE(qx::add_unique_if(container, 'd', predicate));
    EXPECT_FALSE(qx::add_unique_if(container, 'e', predicate));
    EXPECT_FALSE(qx::add_unique_if(container, 'f', predicate));
    EXPECT_FALSE(qx::add_unique_if(container, 'u', predicate));
    EXPECT_TRUE(qx::add_unique_if(container, 'x', predicate));
    EXPECT_TRUE(qx::add_unique_if(container, 'y', predicate));
    EXPECT_TRUE(qx::add_unique_if(container, 't', predicate));
    EXPECT_TRUE(qx::add_unique_if(container, 'n', predicate));
}

TEST(add, add_if)
{
    check_add_if<std::vector<char>>();
    check_add_if<std::deque<char>>();
    check_add_if<std::list<char>>();
    check_add_if<std::set<char>>();
    check_add_if<std::multiset<char>>();
    check_add_if<std::unordered_set<char>>();
    check_add_if<std::unordered_multiset<char>>();
    check_add_if<std::basic_string<char>>();
}
