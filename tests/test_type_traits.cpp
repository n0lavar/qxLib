/**

    @file      test_type_traits.cpp
    @author    Khrapov
    @date      26.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_type_traits.cpp

#include <qx/meta/type_traits.h>

#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

//--------------------------------- are_same ---------------------------------

static_assert(qx::are_same_v<int, int, int>);
static_assert(qx::are_same_v<char, char, char>);
static_assert(qx::are_same_v<long, long, long>);
static_assert(!qx::are_same_v<char, int, int>);
static_assert(!qx::are_same_v<char, int, char>);
static_assert(!qx::are_same_v<long, char, long>);



//------------------------------- iterator_value -------------------------------

static_assert(std::is_same_v<qx::iterator_value_t<std::set<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::unordered_set<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::multiset<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::unordered_multiset<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::string::iterator>, char>);
static_assert(std::is_same_v<qx::iterator_value_t<std::list<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::forward_list<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::deque<int>::iterator>, int>);
static_assert(std::is_same_v<qx::iterator_value_t<std::vector<int>::iterator>, int>);



//--------------------------- is_specialization_exist --------------------------

struct A;

struct B
{
};

template<typename T>
struct C;

template<>
struct C<int>
{
};

template<>
struct C<float>
{
};

static_assert(!qx::is_specialization_exist_v<A>);
static_assert(qx::is_specialization_exist_v<B>);
static_assert(qx::is_specialization_exist_v<C<int>>);
static_assert(qx::is_specialization_exist_v<C<float>>);
static_assert(!qx::is_specialization_exist_v<C<long>>);



//---------------------------- is_specialization_of ----------------------------

using vec_int   = std::vector<int>;
using vec_float = std::vector<float>;

static_assert(qx::is_specialization_of<vec_int, std::vector>::value);
static_assert(qx::is_specialization_of<vec_float, std::vector>::value);
static_assert(!qx::is_specialization_of<vec_int, std::list>::value);
static_assert(!qx::is_specialization_of<vec_int, std::list>::value);
static_assert(!qx::is_specialization_of<float, std::list>::value);


TEST(type_traits, visit_overload)
{
    struct Fluid
    {
    };
    struct LightItem
    {
    };
    struct HeavyItem
    {
    };
    struct FragileItem
    {
    };

    int        result         = 0;
    const auto visit_overload = qx::visit_overload { [&result](const Fluid&)
                                                     {
                                                         result = 1;
                                                     },
                                                     [&result](const LightItem&)
                                                     {
                                                         result = 2;
                                                     },
                                                     [&result](const auto&)
                                                     {
                                                         result = 3;
                                                     } };

    std::variant<Fluid, LightItem, HeavyItem, FragileItem> package = HeavyItem();
    std::visit(visit_overload, package);
    EXPECT_EQ(result, 3);

    package = Fluid();
    std::visit(visit_overload, package);
    EXPECT_EQ(result, 1);

    package = LightItem();
    std::visit(visit_overload, package);
    EXPECT_EQ(result, 2);

    package = FragileItem();
    std::visit(visit_overload, package);
    EXPECT_EQ(result, 3);
}
