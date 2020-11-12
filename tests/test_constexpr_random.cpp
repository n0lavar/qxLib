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
using random_check_duplicate = qx::constexpr_random<class TagA, CONST_SEED, 0u, 100u>;
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 45u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 66u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 31u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 20u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 65u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 86u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 3u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u); // duplicate value
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 91u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 32u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 17u);
QX_STATIC_ASSERT_EQ(random_check_duplicate::next(), 26u);

constexpr u32 left  = 4294967200u;
constexpr u32 right = 200u;
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
