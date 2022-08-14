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

template<class ContainerType>
void CheckAddUnique()
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

TEST(add, add_unique)
{
    CheckAddUnique<std::vector<char>>();
    CheckAddUnique<std::deque<char>>();
    CheckAddUnique<std::list<char>>();
    CheckAddUnique<std::set<char>>();
    CheckAddUnique<std::multiset<char>>();
    CheckAddUnique<std::unordered_set<char>>();
    CheckAddUnique<std::unordered_multiset<char>>();
    CheckAddUnique<std::basic_string<char>>();
}

template<class ContainerType>
void CheckAddIf()
{
    ContainerType container { 'a', 'b', 'c', 'd', 'e', 'f', 'u' };
    const auto    predicate = [](int existing, int value)
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
    CheckAddIf<std::vector<char>>();
    CheckAddIf<std::deque<char>>();
    CheckAddIf<std::list<char>>();
    CheckAddIf<std::set<char>>();
    CheckAddIf<std::multiset<char>>();
    CheckAddIf<std::unordered_set<char>>();
    CheckAddIf<std::unordered_multiset<char>>();
    CheckAddIf<std::basic_string<char>>();
}
