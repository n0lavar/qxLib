//==============================================================================
//
//!\file                   test_constexpr_random.cpp
//
//!\brief
//!\details     ~
//
//!\author      Khrapov
//!\date        11.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <qx/other/constexpr_random.h>
#include <qx/other/useful_macros.h>

struct A { };
struct B;

static_assert(qx::is_specialization_exist_v<A>, "!");
static_assert(!qx::is_specialization_exist_v<B>, "!");

template<auto L, auto R, auto V>
struct StaticAssert
{
    static_assert(qx::between(L, R, V), "Values are not equal");
};
#define STATIC_ASSERT_BETWEEN(l, r, v) StaticAssert<(l), (r), (v)> LINE_NAME(sa);

using random_check_duplicate = qx::constexpr_random<class TagA, 0, 0, 100>;
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next());
STATIC_ASSERT_BETWEEN(0, 100, random_check_duplicate::next()); // duplicate value
/*
using random_1 = qx::constexpr_random<class TagA, QX_UNIQUE_SEED, -100, 100>;
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next());
STATIC_ASSERT_BETWEEN(-100, 100, random_1::next()); // duplicate value
*/