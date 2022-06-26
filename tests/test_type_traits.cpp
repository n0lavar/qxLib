/**

    @file      test_type_traits.cpp
    @author    Khrapov
    @date      26.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_type_traits.cpp

#if QX_TEST_TYPE_TRAITS

#include <qx/concepts.h>
#include <qx/type_traits.h>

#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

//-------------------------------- is_iterator -------------------------------

static_assert(qx::is_iterator<std::map<int, int>::iterator>);
static_assert(qx::is_iterator<std::unordered_map<int, int>::iterator>);
static_assert(qx::is_iterator<std::multimap<int, int>::iterator>);
static_assert(qx::is_iterator<std::unordered_multimap<int, int>::iterator>);
static_assert(qx::is_iterator<std::set<int>::iterator>);
static_assert(qx::is_iterator<std::unordered_set<int>::iterator>);
static_assert(qx::is_iterator<std::multiset<int>::iterator>);
static_assert(qx::is_iterator<std::unordered_multiset<int>::iterator>);
static_assert(qx::is_iterator<std::string::iterator>);
static_assert(qx::is_iterator<std::list<int>::iterator>);
static_assert(qx::is_iterator<std::forward_list<int>::iterator>);
static_assert(qx::is_iterator<std::deque<int>::iterator>);
static_assert(qx::is_iterator<std::vector<int>::iterator>);

static_assert(!qx::is_iterator<int>);
static_assert(!qx::is_iterator<void>);
static_assert(!qx::is_iterator<std::vector<int>>);



//------------------------- is_random_access_iterator_v ------------------------

static_assert(!qx::is_random_access_iterator_v<std::map<int, int>::iterator>);
static_assert(
    !qx::is_random_access_iterator_v<std::unordered_map<int, int>::iterator>);
static_assert(
    !qx::is_random_access_iterator_v<std::multimap<int, int>::iterator>);
static_assert(!qx::is_random_access_iterator_v<
              std::unordered_multimap<int, int>::iterator>);
static_assert(!qx::is_random_access_iterator_v<std::set<int>::iterator>);
static_assert(
    !qx::is_random_access_iterator_v<std::unordered_set<int>::iterator>);
static_assert(!qx::is_random_access_iterator_v<std::multiset<int>::iterator>);
static_assert(
    !qx::is_random_access_iterator_v<std::unordered_multiset<int>::iterator>);
static_assert(qx::is_random_access_iterator_v<std::string::iterator>);
static_assert(!qx::is_random_access_iterator_v<std::list<int>::iterator>);
static_assert(
    !qx::is_random_access_iterator_v<std::forward_list<int>::iterator>);
static_assert(qx::is_random_access_iterator_v<std::deque<int>::iterator>);
static_assert(qx::is_random_access_iterator_v<std::vector<int>::iterator>);

static_assert(!qx::is_random_access_iterator_v<int>);
static_assert(!qx::is_random_access_iterator_v<void>);
static_assert(!qx::is_random_access_iterator_v<std::vector<int>>);



//--------------------------------- are_same ---------------------------------

static_assert(qx::are_same_v<int, int, int>);
static_assert(qx::are_same_v<char, char, char>);
static_assert(qx::are_same_v<long, long, long>);
static_assert(!qx::are_same_v<char, int, int>);
static_assert(!qx::are_same_v<char, int, char>);
static_assert(!qx::are_same_v<long, char, long>);



//------------------------------- iterator_value -------------------------------

static_assert(
    std::is_same_v<qx::iterator_value_t<std::set<int>::iterator>, int>);
static_assert(std::is_same_v<
              qx::iterator_value_t<std::unordered_set<int>::iterator>,
              int>);
static_assert(
    std::is_same_v<qx::iterator_value_t<std::multiset<int>::iterator>, int>);
static_assert(std::is_same_v<
              qx::iterator_value_t<std::unordered_multiset<int>::iterator>,
              int>);
static_assert(
    std::is_same_v<qx::iterator_value_t<std::string::iterator>, char>);
static_assert(
    std::is_same_v<qx::iterator_value_t<std::list<int>::iterator>, int>);
static_assert(std::is_same_v<
              qx::iterator_value_t<std::forward_list<int>::iterator>,
              int>);
static_assert(
    std::is_same_v<qx::iterator_value_t<std::deque<int>::iterator>, int>);
static_assert(
    std::is_same_v<qx::iterator_value_t<std::vector<int>::iterator>, int>);



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


// -------------------------------- enumeration --------------------------------

enum ETest1
{
    a,
    b
};

enum class ETest2
{
    a,
    b
};

struct S;

static_assert(qx::enumeration<ETest1>);
static_assert(qx::enumeration<ETest2>);
static_assert(!qx::enumeration<int>);
static_assert(!qx::enumeration<vec_int>);
static_assert(!qx::enumeration<vec_float>);
static_assert(!qx::enumeration<C<int>>);
static_assert(!qx::enumeration<S>);

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
                                                         result= 1;
                                                     },
                                                     [&result](const LightItem&)
                                                     {
                                                         result= 2;
                                                     },
                                                     [&result](const auto&)
                                                     {
                                                         result= 3;
                                                     } };

    std::variant<Fluid, LightItem, HeavyItem, FragileItem> package =
        HeavyItem();
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

#endif
