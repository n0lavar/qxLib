/**

    @file      test_constexpr_sequence.cpp
    @author    Khrapov
    @date      25.08.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_constexpr_sequence.cpp

#if QX_TEST_CONSTEXPR_SEQUENCE

    #include <qx/meta/constexpr_sequence.h>

    #if QX_CONSTEXPR_SEQUENCE_SUPPORTED

        #include <qx/useful_macros.h>


//---------------------------- qx::detail::increase ----------------------------

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 0>(1)), 1);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 0>(2)), 2);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 0>(3)), 3);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 0>(4)), 4);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 0>(5)), 5);

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 1>(1)), 2);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 1>(2)), 3);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 1>(3)), 4);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 1>(4)), 5);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 1>(5)), 6);

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 2>(1)), 3);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 2>(2)), 4);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 2>(3)), 5);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 2>(4)), 6);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 2>(5)), 7);

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 3>(1)), 4);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 3>(2)), 5);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 3>(3)), 6);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 3>(4)), 7);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::increase<int, 3>(5)), 8);



//---------------------------- qx::detail::multiply ----------------------------

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 1>(1)), 1);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 1>(2)), 2);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 1>(3)), 3);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 1>(4)), 4);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 1>(5)), 5);

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 2>(1)), 2);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 2>(2)), 4);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 2>(3)), 6);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 2>(4)), 8);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 2>(5)), 10);

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 3>(1)), 3);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 3>(2)), 6);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 3>(3)), 9);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 3>(4)), 12);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 3>(5)), 15);

QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 0>(1)), 0);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 0>(2)), 0);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 0>(3)), 0);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 0>(4)), 0);
QX_STATIC_ASSERT_EQ(GTEST_SINGLE_ARGUMENT(qx::detail::multiply<int, 0>(5)), 0);



//---------------------------- qx::constexpr_counter ---------------------------

using counter_A_0_1 = qx::constexpr_counter<struct TagA, int, 0, 1>;
QX_STATIC_ASSERT_EQ(counter_A_0_1::value(), 0);
QX_STATIC_ASSERT_EQ(counter_A_0_1::next(), 1);
QX_STATIC_ASSERT_EQ(counter_A_0_1::value(), 1);
QX_STATIC_ASSERT_EQ(counter_A_0_1::value(), 1);
QX_STATIC_ASSERT_EQ(counter_A_0_1::next(), 2);
QX_STATIC_ASSERT_EQ(counter_A_0_1::value(), 2);
QX_STATIC_ASSERT_EQ(counter_A_0_1::next(), 3);
QX_STATIC_ASSERT_EQ(counter_A_0_1::value(), 3);

using counter_B_0_1 = qx::constexpr_counter<struct TagB, int, 0, 1>;
QX_STATIC_ASSERT_EQ(counter_B_0_1::value(), 0);
QX_STATIC_ASSERT_EQ(counter_B_0_1::next(), 1);
QX_STATIC_ASSERT_EQ(counter_B_0_1::value(), 1);
QX_STATIC_ASSERT_EQ(counter_B_0_1::value(), 1);
QX_STATIC_ASSERT_EQ(counter_B_0_1::value(), 1);
QX_STATIC_ASSERT_EQ(counter_B_0_1::next(), 2);
QX_STATIC_ASSERT_EQ(counter_B_0_1::value(), 2);

using counter_C_2_1 = qx::constexpr_counter<struct TagC, int, 2, 1>;
QX_STATIC_ASSERT_EQ(counter_C_2_1::value(), 2);
QX_STATIC_ASSERT_EQ(counter_C_2_1::next(), 3);
QX_STATIC_ASSERT_EQ(counter_C_2_1::value(), 3);
QX_STATIC_ASSERT_EQ(counter_C_2_1::next(), 4);
QX_STATIC_ASSERT_EQ(counter_C_2_1::value(), 4);
QX_STATIC_ASSERT_EQ(counter_C_2_1::value(), 4);
QX_STATIC_ASSERT_EQ(counter_C_2_1::value(), 4);

using counter_D_4_1 = qx::constexpr_counter<struct TagD, int, 4, 1>;
QX_STATIC_ASSERT_EQ(counter_D_4_1::value(), 4);
QX_STATIC_ASSERT_EQ(counter_D_4_1::value(), 4);
QX_STATIC_ASSERT_EQ(counter_D_4_1::value(), 4);
QX_STATIC_ASSERT_EQ(counter_D_4_1::next(), 5);
QX_STATIC_ASSERT_EQ(counter_D_4_1::value(), 5);
QX_STATIC_ASSERT_EQ(counter_D_4_1::next(), 6);
QX_STATIC_ASSERT_EQ(counter_D_4_1::value(), 6);

using counter_E_5_3 = qx::constexpr_counter<struct TagE, int, 5, 3>;
QX_STATIC_ASSERT_EQ(counter_E_5_3::value(), 5);
QX_STATIC_ASSERT_EQ(counter_E_5_3::next(), 8);
QX_STATIC_ASSERT_EQ(counter_E_5_3::value(), 8);
QX_STATIC_ASSERT_EQ(counter_E_5_3::value(), 8);
QX_STATIC_ASSERT_EQ(counter_E_5_3::next(), 11);
QX_STATIC_ASSERT_EQ(counter_E_5_3::value(), 11);

using counter_F_2_m3 = qx::constexpr_counter<struct TagF, int, 2, -3>;
QX_STATIC_ASSERT_EQ(counter_F_2_m3::value(), 2);
QX_STATIC_ASSERT_EQ(counter_F_2_m3::next(), -1);
QX_STATIC_ASSERT_EQ(counter_F_2_m3::value(), -1);
QX_STATIC_ASSERT_EQ(counter_F_2_m3::next(), -4);
QX_STATIC_ASSERT_EQ(counter_F_2_m3::value(), -4);
QX_STATIC_ASSERT_EQ(counter_F_2_m3::value(), -4);
QX_STATIC_ASSERT_EQ(counter_F_2_m3::value(), -4);

using counter_G_0_0 = qx::constexpr_counter<struct TagG, int, 0, 0>;
QX_STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
QX_STATIC_ASSERT_EQ(counter_G_0_0::next(), 0);
QX_STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
QX_STATIC_ASSERT_EQ(counter_G_0_0::next(), 0);
QX_STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
QX_STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);
QX_STATIC_ASSERT_EQ(counter_G_0_0::value(), 0);

    #endif

#endif
