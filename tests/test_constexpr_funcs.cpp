//==============================================================================
//
//!\file                    test_constexpr_funcs.cpp
//
//!\brief       Tests for constexpr functions
//!\details     ~
//
//!\author      Khrapov
//!\date        23.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <qx/meta/constexpr_funcs.h>
#include <qx/other/useful_macros.h>



//------------------------------ qx::meta::strlen ------------------------------

QX_STATIC_ASSERT_EQ(qx::meta::strlen(""),           0)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("1"),          1)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("12"),         2)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("123"),        3)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("1234"),       4)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("12345"),      5)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("123456"),     6)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("1234567"),    7)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("12345678"),   8)
QX_STATIC_ASSERT_EQ(qx::meta::strlen("123456789"),  9)



//-------------------------------- qx::meta::abs -------------------------------

QX_STATIC_ASSERT_EQ(qx::meta::abs(1),   1)
QX_STATIC_ASSERT_EQ(qx::meta::abs(2),   2)
QX_STATIC_ASSERT_EQ(qx::meta::abs(3),   3)
QX_STATIC_ASSERT_EQ(qx::meta::abs(4),   4)
QX_STATIC_ASSERT_EQ(qx::meta::abs(-1),  1)
QX_STATIC_ASSERT_EQ(qx::meta::abs(-2),  2)
QX_STATIC_ASSERT_EQ(qx::meta::abs(-3),  3)
QX_STATIC_ASSERT_EQ(qx::meta::abs(-4),  4)
