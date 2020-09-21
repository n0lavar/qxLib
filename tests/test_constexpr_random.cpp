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
#include <array>

 //V_EXCLUDE_PATH *test_constexpr_random.cpp

template<auto L, auto R, auto V>
struct StaticAssert
{
    static_assert(qx::between(L, R, V), "Values are not equal");
};
#define STATIC_ASSERT_BETWEEN(l, r, v) StaticAssert<(l), (r), (v)> LINE_NAME(sa);

using random_check_duplicate = qx::constexpr_random<class TagA, 0, 0, 100>;
constexpr std::array<u32, 50> ARR
{
    random_check_duplicate::next(), // 45
    random_check_duplicate::next(), // 66
    random_check_duplicate::next(), // 31
    random_check_duplicate::next(), // 20
    random_check_duplicate::next(), // 65
    random_check_duplicate::next(), // 86
    random_check_duplicate::next(), // 3
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17 duplicate value
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
    random_check_duplicate::next(), // 91
    random_check_duplicate::next(), // 32
    random_check_duplicate::next(), // 17
    random_check_duplicate::next(), // 26
};

static_assert(ARR[0]  == 45);
static_assert(ARR[1]  == 66);
static_assert(ARR[2]  == 31);
static_assert(ARR[3]  == 20);
static_assert(ARR[4]  == 65);
static_assert(ARR[5]  == 86);
static_assert(ARR[6]  == 3 );
static_assert(ARR[7]  == 32);
static_assert(ARR[8]  == 17);
static_assert(ARR[9]  == 26);
static_assert(ARR[10] == 91);
static_assert(ARR[11] == 32);
static_assert(ARR[12] == 17);
static_assert(ARR[13] == 26);
static_assert(ARR[14] == 91);
static_assert(ARR[15] == 32);
static_assert(ARR[16] == 17);
static_assert(ARR[17] == 26);
static_assert(ARR[18] == 91);
static_assert(ARR[19] == 32);
static_assert(ARR[20] == 17);
static_assert(ARR[21] == 26);
static_assert(ARR[22] == 91);
static_assert(ARR[23] == 32);
static_assert(ARR[24] == 17);
static_assert(ARR[25] == 26);
static_assert(ARR[26] == 91);
static_assert(ARR[27] == 32);
static_assert(ARR[28] == 17);
static_assert(ARR[29] == 26);
static_assert(ARR[30] == 91);
static_assert(ARR[31] == 32);
static_assert(ARR[32] == 17);
static_assert(ARR[33] == 26);
static_assert(ARR[34] == 91);
static_assert(ARR[35] == 32);
static_assert(ARR[36] == 17);
static_assert(ARR[37] == 26);
static_assert(ARR[38] == 91);
static_assert(ARR[39] == 32);
static_assert(ARR[40] == 17);
static_assert(ARR[41] == 26);
static_assert(ARR[42] == 91);
static_assert(ARR[43] == 32);
static_assert(ARR[44] == 17);
static_assert(ARR[45] == 26);
static_assert(ARR[46] == 91);
static_assert(ARR[47] == 32);
static_assert(ARR[48] == 17);
static_assert(ARR[49] == 26);

#if 0
#include <gtest/gtest.h>

TEST(constexpr_random, check)
{
    for (size_t i = 0; i < ARR.size(); i++)
        printf("%llu\n", ARR[i]);
}
#endif

constexpr u32 left  = -200;
constexpr u32 right =  200;
using random1 = qx::constexpr_random<class TagB, QX_UNIQUE_SEED, left, right>;
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
STATIC_ASSERT_BETWEEN(left, right, random1::next());
