/**

    @file      format.gtest.cpp
    @author    Khrapov
    @date      28.03.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/format.h>

//V_EXCLUDE_PATH *.gtest.cpp

template<class char_t>
class test_format : public ::testing::Test
{
};

using implementations_type = ::testing::Types<QX_ALL_CHAR_TYPES>;

TYPED_TEST_SUITE(test_format, implementations_type);

TYPED_TEST(test_format, format_function)
{
    qx::basic_string<TypeParam> sResult = qx::format(QX_STR_PREFIX(TypeParam, "{}"), 42);
    EXPECT_STREQ(sResult.c_str(), QX_STR_PREFIX(TypeParam, "42"));
}

TYPED_TEST(test_format, convert_to_string)
{
    qx::basic_string<TypeParam> sResult = qx::convert_to_string<int, TypeParam>(42);
    EXPECT_STREQ(sResult.c_str(), QX_STR_PREFIX(TypeParam, "42"));
}
