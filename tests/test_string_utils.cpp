/**

    @file      test_string_utils.cpp
    @author    Khrapov
    @date      10.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_string_utils.cpp

#include <qx/containers/string/string_utils.h>
#include <qx/macros/static_assert.h>

//--------------------------------- qx::strlen ---------------------------------

QX_STATIC_ASSERT_EQ(qx::strlen(""), 0u);
QX_STATIC_ASSERT_EQ(qx::strlen("1"), 1u);
QX_STATIC_ASSERT_EQ(qx::strlen("12"), 2u);
QX_STATIC_ASSERT_EQ(qx::strlen("123"), 3u);
QX_STATIC_ASSERT_EQ(qx::strlen("1234"), 4u);
QX_STATIC_ASSERT_EQ(qx::strlen("12345"), 5u);
QX_STATIC_ASSERT_EQ(qx::strlen("123456"), 6u);
QX_STATIC_ASSERT_EQ(qx::strlen("1234567"), 7u);
QX_STATIC_ASSERT_EQ(qx::strlen("12345678"), 8u);
QX_STATIC_ASSERT_EQ(qx::strlen("123456789"), 9u);

//--------------------------------- qx::strcmp ---------------------------------

QX_STATIC_ASSERT_EQ(qx::strcmp("", ""), 0);
QX_STATIC_ASSERT_EQ(qx::strcmp("string", "string"), 0);
QX_STATIC_ASSERT_EQ(qx::strcmp("0", "0"), 0);
QX_STATIC_ASSERT_EQ(qx::strcmp(",,,", ",,,"), 0);
QX_STATIC_ASSERT_EQ(qx::strcmp("\"\"\"", "\"\"\""), 0);

QX_STATIC_ASSERT_LT(qx::strcmp("0", "1"), 0);
QX_STATIC_ASSERT_LT(qx::strcmp("00", "11"), 0);
QX_STATIC_ASSERT_LT(qx::strcmp("000", "1"), 0);
QX_STATIC_ASSERT_LT(qx::strcmp("0", "111"), 0);

QX_STATIC_ASSERT_GT(qx::strcmp("1", "0"), 0);
QX_STATIC_ASSERT_GT(qx::strcmp("11", "00"), 0);
QX_STATIC_ASSERT_GT(qx::strcmp("111", "0"), 0);
QX_STATIC_ASSERT_GT(qx::strcmp("1", "000"), 0);
