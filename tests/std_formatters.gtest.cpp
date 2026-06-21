/**

    @file      std_formatters.gtest.cpp
    @author    Khrapov
    @date      27.03.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/format.h>
#include <qx/containers/string/std_formatters.h>

//V_EXCLUDE_PATH *.gtest.cpp

TEST(std_formatters, variant)
{
    using variant_t = std::variant<int, float, qx::string>;

    qx::string sResult = qx::format(QXT("{}"), variant_t(1));
    EXPECT_STREQ(sResult.c_str(), QXT("1"));

    sResult = qx::format(QXT("{}"), variant_t(2.f));
    EXPECT_STREQ(sResult.c_str(), QXT("2"));

    sResult = qx::format(QXT("{}"), variant_t(qx::string(QXT("3"))));
    EXPECT_STREQ(sResult.c_str(), QXT("3"));
}
