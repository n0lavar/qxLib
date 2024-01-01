/**

    @file      test_concepts.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_concepts.cpp

#include <qx/meta/concepts.h>

#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using vec_int   = std::vector<int>;
using vec_float = std::vector<float>;

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

// ------------------------------------------------------ iterator -----------------------------------------------------

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

// -------------------------------------------- is_random_access_iterator_v --------------------------------------------

static_assert(!qx::is_random_access_iterator<std::map<int, int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::unordered_map<int, int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::multimap<int, int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::unordered_multimap<int, int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::set<int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::unordered_set<int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::multiset<int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::unordered_multiset<int>::iterator>);
static_assert(qx::is_random_access_iterator<std::string::iterator>);
static_assert(!qx::is_random_access_iterator<std::list<int>::iterator>);
static_assert(!qx::is_random_access_iterator<std::forward_list<int>::iterator>);
static_assert(qx::is_random_access_iterator<std::deque<int>::iterator>);
static_assert(qx::is_random_access_iterator<std::vector<int>::iterator>);

static_assert(!qx::is_random_access_iterator<int>);
static_assert(!qx::is_random_access_iterator<void>);
static_assert(!qx::is_random_access_iterator<std::vector<int>>);

// ---------------------------------------------------- enumeration ----------------------------------------------------

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

static_assert(qx::is_enumeration<ETest1>);
static_assert(qx::is_enumeration<ETest2>);
static_assert(!qx::is_enumeration<int>);
static_assert(!qx::is_enumeration<vec_int>);
static_assert(!qx::is_enumeration<vec_float>);
static_assert(!qx::is_enumeration<C<int>>);
static_assert(!qx::is_enumeration<S>);

// ------------------------------------------------------ callable -----------------------------------------------------

struct test1
{
};
struct test2
{
};

// clang-format off
static_assert(qx::callable_c<std::function<void()>, void>);
static_assert(!qx::callable_c<std::function<void(test1)>, void>);
static_assert(qx::callable_c<std::function<void(test1)>, void, test1>);
static_assert(!qx::callable_c<std::function<test2(test1)>, void, test1>);
static_assert(qx::callable_c<std::function<test2(test1)>, test2, test1>);

static_assert(qx::callable_c<void(), void>);
static_assert(!qx::callable_c<void(test1), void>);
static_assert(qx::callable_c<void(test1), void, test1>);
static_assert(!qx::callable_c<test2(test1), void, test1>);
static_assert(qx::callable_c<test2(test1), test2, test1>);

static_assert(qx::callable_c<decltype([](){}), void>);
static_assert(!qx::callable_c<decltype([](test1){}), void>);
static_assert(qx::callable_c<decltype([](test1){}), void, test1>);
static_assert(!qx::callable_c<decltype([](test1){ return test2(); }), void, test1>);
static_assert(qx::callable_c<decltype([](test1){ return test2(); }), test2, test1>);
// clang-format on

// ---------------------------------------------- derived_from_template_c ----------------------------------------------

template<class T>
class C1
{
};

class C2 : public C1<int>
{
};

class C3 : public C1<float>
{
};

static_assert(qx::derived_from_template_c<C2, C1>);
static_assert(qx::derived_from_template_c<C3, C1>);
static_assert(!qx::derived_from_template_c<C<int>, C1>);
