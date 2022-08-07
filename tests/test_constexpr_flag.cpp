/**

    @file      test_constexpr_flag.cpp
    @author    Khrapov
    @date      16.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_constexpr_flag.cpp

#include <qx/macros/static_assert.h>
#include <qx/meta/constexpr_flag.h>

using Flag1 = qx::constexpr_flag<class FtagTag1>;
QX_STATIC_ASSERT_EQ(Flag1::test(), false);
QX_STATIC_ASSERT_EQ(Flag1::test_and_set(), false);
QX_STATIC_ASSERT_EQ(Flag1::test(), true);

using Flag2 = qx::constexpr_flag<class FtagTag2>;
QX_STATIC_ASSERT_EQ(Flag2::test(), false);
QX_STATIC_ASSERT_EQ(Flag2::test_and_set(), false);
QX_STATIC_ASSERT_EQ(Flag2::test(), true);

using Flag3 = qx::constexpr_flag<class FtagTag3>;
QX_STATIC_ASSERT_EQ(Flag3::test(), false);
QX_STATIC_ASSERT_EQ(Flag3::test(), false);
QX_STATIC_ASSERT_EQ(Flag3::test(), false);
QX_STATIC_ASSERT_EQ(Flag3::test_and_set(), false);
QX_STATIC_ASSERT_EQ(Flag3::test(), true);
QX_STATIC_ASSERT_EQ(Flag3::test(), true);
QX_STATIC_ASSERT_EQ(Flag3::test(), true);

using Flag4 = qx::constexpr_flag<class FtagTag4, int, 50, 100>;
QX_STATIC_ASSERT_EQ(Flag4::test(), 50);
QX_STATIC_ASSERT_EQ(Flag4::test_and_set(), 50);
QX_STATIC_ASSERT_EQ(Flag4::test(), 100);

using Flag5 = qx::constexpr_flag<class FtagTag5, int, 33, -11>;
QX_STATIC_ASSERT_EQ(Flag5::test(), 33);
QX_STATIC_ASSERT_EQ(Flag5::test_and_set(), 33);
QX_STATIC_ASSERT_EQ(Flag5::test(), -11);
