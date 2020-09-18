//==============================================================================
//
//!\file                  test_constexpr_sequence.cpp
//
//!\brief       Tests for constexpr_counter class
//!\details     ~
//
//!\author      Khrapov
//!\date        25.08.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <qx/other/constexpr_sequence.h>
#include <qx/other/useful_macros.h>

 //V_EXCLUDE_PATH *test_constexpr_counter.cpp

// shows constexpr A and B in error msg
template<int A, int B>
struct StaticAssert
{
    static_assert(A == B, "Values are not equal");
};
#define STATIC_ASSERT_EQ(a, b) StaticAssert<(a), (b)> LINE_NAME(sa);

using counter_A_0_1 = qx::constexpr_counter<struct TagA, int, 0, 1>;
STATIC_ASSERT_EQ(counter_A_0_1::value(), 0);
STATIC_ASSERT_EQ(counter_A_0_1::next(),  1);
STATIC_ASSERT_EQ(counter_A_0_1::value(), 1);
STATIC_ASSERT_EQ(counter_A_0_1::value(), 1);
STATIC_ASSERT_EQ(counter_A_0_1::next(),  2);
STATIC_ASSERT_EQ(counter_A_0_1::value(), 2);
STATIC_ASSERT_EQ(counter_A_0_1::next(),  3);
STATIC_ASSERT_EQ(counter_A_0_1::value(), 3);

using counter_B_0_1 = qx::constexpr_counter<struct TagB, int, 0, 1>;
STATIC_ASSERT_EQ(counter_B_0_1::value(), 0);
STATIC_ASSERT_EQ(counter_B_0_1::next(),  1);
STATIC_ASSERT_EQ(counter_B_0_1::value(), 1);
STATIC_ASSERT_EQ(counter_B_0_1::value(), 1);
STATIC_ASSERT_EQ(counter_B_0_1::value(), 1);
STATIC_ASSERT_EQ(counter_B_0_1::next(),  2);
STATIC_ASSERT_EQ(counter_B_0_1::value(), 2);

using counter_C_2_1 = qx::constexpr_counter<struct TagC, int, 2, 1>;
STATIC_ASSERT_EQ(counter_C_2_1::value(), 2);
STATIC_ASSERT_EQ(counter_C_2_1::next(),  3);
STATIC_ASSERT_EQ(counter_C_2_1::value(), 3);
STATIC_ASSERT_EQ(counter_C_2_1::next(),  4);
STATIC_ASSERT_EQ(counter_C_2_1::value(), 4);
STATIC_ASSERT_EQ(counter_C_2_1::value(), 4);
STATIC_ASSERT_EQ(counter_C_2_1::value(), 4);

using counter_D_4_1 = qx::constexpr_counter<struct TagD, int, 4, 1>;
STATIC_ASSERT_EQ(counter_D_4_1::value(), 4);
STATIC_ASSERT_EQ(counter_D_4_1::value(), 4);
STATIC_ASSERT_EQ(counter_D_4_1::value(), 4);
STATIC_ASSERT_EQ(counter_D_4_1::next(),  5);
STATIC_ASSERT_EQ(counter_D_4_1::value(), 5);
STATIC_ASSERT_EQ(counter_D_4_1::next(),  6);
STATIC_ASSERT_EQ(counter_D_4_1::value(), 6);

using counter_E_5_3 = qx::constexpr_counter<struct TagE, int, 5, 3>;
STATIC_ASSERT_EQ(counter_E_5_3::value(), 5);
STATIC_ASSERT_EQ(counter_E_5_3::next(),  8);
STATIC_ASSERT_EQ(counter_E_5_3::value(), 8);
STATIC_ASSERT_EQ(counter_E_5_3::value(), 8);
STATIC_ASSERT_EQ(counter_E_5_3::next(),  11);
STATIC_ASSERT_EQ(counter_E_5_3::value(), 11);

using counter_F_2_m3 = qx::constexpr_counter<struct TagF, int, 2, -3>;
STATIC_ASSERT_EQ(counter_F_2_m3::value(),  2);
STATIC_ASSERT_EQ(counter_F_2_m3::next(),  -1);
STATIC_ASSERT_EQ(counter_F_2_m3::value(), -1);
STATIC_ASSERT_EQ(counter_F_2_m3::next(),  -4);
STATIC_ASSERT_EQ(counter_F_2_m3::value(), -4);
STATIC_ASSERT_EQ(counter_F_2_m3::value(), -4);
STATIC_ASSERT_EQ(counter_F_2_m3::value(), -4);

using counter_G_0_0 = qx::constexpr_counter<struct TagG, int, 0, 0>;
STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
STATIC_ASSERT_EQ(counter_G_0_0::next(),  0);
STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
STATIC_ASSERT_EQ(counter_G_0_0::next(),  0);
STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
