//==============================================================================
//
//!\file                      test_type_traits.cpp
//
//!\brief
//!\details     ~
//
//!\author      Khrapov
//!\date        26.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_type_traits.cpp

#if QX_TEST_TYPE_TRAITS

#include <qx/type_traits.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <list>
#include <forward_list>
#include <deque>
#include <vector>



//-------------------------------- is_iterator -------------------------------

static_assert(qx::is_iterator_v<std::map<int, int>::iterator>);
static_assert(qx::is_iterator_v<std::unordered_map<int, int>::iterator>);
static_assert(qx::is_iterator_v<std::multimap<int, int>::iterator>);
static_assert(qx::is_iterator_v<std::unordered_multimap<int, int>::iterator>);
static_assert(qx::is_iterator_v<std::set<int>::iterator>);
static_assert(qx::is_iterator_v<std::unordered_set<int>::iterator>);
static_assert(qx::is_iterator_v<std::multiset<int>::iterator>);
static_assert(qx::is_iterator_v<std::unordered_multiset<int>::iterator>);
static_assert(qx::is_iterator_v<std::string::iterator>);
static_assert(qx::is_iterator_v<std::list<int>::iterator>);
static_assert(qx::is_iterator_v<std::forward_list<int>::iterator>);
static_assert(qx::is_iterator_v<std::deque<int>::iterator>);
static_assert(qx::is_iterator_v<std::vector<int>::iterator>);



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

struct B {};

template<typename T>
struct C;

template<>
struct C<int> {};

template<>
struct C<float> {};

static_assert(!qx::is_specialization_exist_v<A>);
static_assert(qx::is_specialization_exist_v<B>);
static_assert(qx::is_specialization_exist_v<C<int>>);
static_assert(qx::is_specialization_exist_v<C<float>>);
static_assert(!qx::is_specialization_exist_v<C<long>>);

#endif
