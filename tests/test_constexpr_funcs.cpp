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
#include <test_config.h>

//V_EXCLUDE_PATH *test_constexpr_funcs.cpp

#if QX_TEST_CONSTEXPR_FUNCS

#include <qx/meta/constexpr_funcs.h>
#include <qx/useful_macros.h>


//------------------------------ qx::meta::strlen ------------------------------

QX_STATIC_ASSERT_EQ(qx::meta::strlen(""),           0u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("1"),          1u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("12"),         2u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("123"),        3u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("1234"),       4u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("12345"),      5u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("123456"),     6u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("1234567"),    7u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("12345678"),   8u);
QX_STATIC_ASSERT_EQ(qx::meta::strlen("123456789"),  9u);



//------------------------------ qx::meta::strcmp ------------------------------

QX_STATIC_ASSERT_EQ(qx::meta::strcmp("", ""),               0);
QX_STATIC_ASSERT_EQ(qx::meta::strcmp("string", "string"),   0);
QX_STATIC_ASSERT_EQ(qx::meta::strcmp("0", "0"),             0);
QX_STATIC_ASSERT_EQ(qx::meta::strcmp(",,,", ",,,"),         0);
QX_STATIC_ASSERT_EQ(qx::meta::strcmp("\"\"\"", "\"\"\""),   0);

QX_STATIC_ASSERT_LT(qx::meta::strcmp("0", "1"),             0);
QX_STATIC_ASSERT_LT(qx::meta::strcmp("00", "11"),           0);
QX_STATIC_ASSERT_LT(qx::meta::strcmp("000", "1"),           0);
QX_STATIC_ASSERT_LT(qx::meta::strcmp("0", "111"),           0);

QX_STATIC_ASSERT_GT(qx::meta::strcmp("1", "0"),             0);
QX_STATIC_ASSERT_GT(qx::meta::strcmp("11", "00"),           0);
QX_STATIC_ASSERT_GT(qx::meta::strcmp("111", "0"),           0);
QX_STATIC_ASSERT_GT(qx::meta::strcmp("1", "000"),           0);



//-------------------------------- qx::meta::abs -------------------------------

QX_STATIC_ASSERT_EQ(qx::meta::abs(1),   1);
QX_STATIC_ASSERT_EQ(qx::meta::abs(2),   2);
QX_STATIC_ASSERT_EQ(qx::meta::abs(3),   3);
QX_STATIC_ASSERT_EQ(qx::meta::abs(4),   4);
QX_STATIC_ASSERT_EQ(qx::meta::abs(-1),  1);
QX_STATIC_ASSERT_EQ(qx::meta::abs(-2),  2);
QX_STATIC_ASSERT_EQ(qx::meta::abs(-3),  3);
QX_STATIC_ASSERT_EQ(qx::meta::abs(-4),  4);



//--------------------------- qx::meta::epsilon_equal --------------------------

static_assert( qx::meta::epsilon_equal(0.5, 0.41, 0.1));
static_assert( qx::meta::epsilon_equal(0.5, 0.45, 0.1));
static_assert( qx::meta::epsilon_equal(0.5, 0.48, 0.1));
static_assert( qx::meta::epsilon_equal(0.5, 0.49, 0.1));
static_assert(!qx::meta::epsilon_equal(0.5, 0.39, 0.1));

#endif
