//==============================================================================
//
//!\file                   test_constexpr_counter.cpp
//
//!\brief       Tests for constexpr_counter class
//!\details     ~
//
//!\author      Khrapov
//!\date        25.08.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <qx/other/constexpr_conter.h>
#include <qx/other/useful_macros.h>

 //V_EXCLUDE_PATH *test_constexpr_counter.cpp

// shows constexpr A and B in error msg
template<int A, int B>
struct StaticAssert
{
    static_assert(A == B, "Values are not equal");
};
#define STATIC_ASSERT_EQ(a, b) StaticAssert<(a), (b)> LINE_NAME(sa);

using counter_A_0_1 = qx::constexpr_counter<struct TagA, 0, 1>;
constexpr int a0 = counter_A_0_1::next();
constexpr int a1 = counter_A_0_1::next();
constexpr int a2 = counter_A_0_1::next();
STATIC_ASSERT_EQ(a0, 0);
STATIC_ASSERT_EQ(a1, 1);
STATIC_ASSERT_EQ(a2, 2);

using counter_B_0_1 = qx::constexpr_counter<struct TagB, 0, 1>;
constexpr int b0 = counter_B_0_1::next();
constexpr int b1 = counter_B_0_1::next();
constexpr int b2 = counter_B_0_1::next();
STATIC_ASSERT_EQ(b0, 0);
STATIC_ASSERT_EQ(b1, 1);
STATIC_ASSERT_EQ(b2, 2);

using counter_C_2_1 = qx::constexpr_counter<struct TagC, 2, 1>;
constexpr int c0 = counter_C_2_1::next();
constexpr int c1 = counter_C_2_1::next();
constexpr int c2 = counter_C_2_1::next();
STATIC_ASSERT_EQ(c0, 2);
STATIC_ASSERT_EQ(c1, 3);
STATIC_ASSERT_EQ(c2, 4);

using counter_D_4_1 = qx::constexpr_counter<struct TagD, 4, 1>;
constexpr int d0 = counter_D_4_1::next();
constexpr int d1 = counter_D_4_1::next();
constexpr int d2 = counter_D_4_1::next();
STATIC_ASSERT_EQ(d0, 4);
STATIC_ASSERT_EQ(d1, 5);
STATIC_ASSERT_EQ(d2, 6);

using counter_E_5_3 = qx::constexpr_counter<struct TagE, 5, 3>;
constexpr int e0 = counter_E_5_3::next();
constexpr int e1 = counter_E_5_3::next();
constexpr int e2 = counter_E_5_3::next();
STATIC_ASSERT_EQ(e0, 5);
STATIC_ASSERT_EQ(e1, 8);
STATIC_ASSERT_EQ(e2, 11);

using counter_F_2_m3 = qx::constexpr_counter<struct TagF, 2, -3>;
constexpr int f0 = counter_F_2_m3::next();
constexpr int f1 = counter_F_2_m3::next();
constexpr int f2 = counter_F_2_m3::next();
STATIC_ASSERT_EQ(f0, 2);
STATIC_ASSERT_EQ(f1, -1);
STATIC_ASSERT_EQ(f2, -4);
