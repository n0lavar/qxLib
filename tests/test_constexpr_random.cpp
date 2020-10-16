//==============================================================================
//
//!\file                   test_constexpr_random.cpp
//
//!\brief       Tests for qx::constexpr_random class
//!\details     ~
//
//!\author      Khrapov
//!\date        11.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_constexpr_random.cpp

#if QX_TEST_CONSTEXPR_RANDOM

#include <qx/meta/constexpr_random.h>
#include <qx/useful_macros.h>
#include <array>


constexpr u32 CONST_SEED = 0u;
using random_check_duplicate = qx::constexpr_random<class TagA, CONST_SEED, 0, 100>;
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 45);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 66);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 31);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 20);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 65);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 86);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 3);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17); // duplicate value
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26);

constexpr u32 left  = -200;
constexpr u32 right =  200;
using random1 = qx::constexpr_random<class TagB, QX_UNIQUE_SEED, left, right>;
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);
QX_STATIC_ASSERT_BETWEEN(left, random1::next(), right);

#endif
