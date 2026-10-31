/**

    @file      string_converters.gtest.cpp
    @author    Khrapov
    @date      17.04.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/string_converters.h>

TEST(string_converters, to_wstring)
{
    {
        qx::string  str(QXT("Hello world"));
        qx::wstring wstr = qx::to_wstring(str);
        EXPECT_STREQ(wstr.data(), L"Hello world");
    }

    {
        qx::string  str(QXT("0123456789"));
        qx::wstring wstr = qx::to_wstring(str);
        EXPECT_STREQ(wstr.data(), L"0123456789");
    }

    {
        qx::string  str(QXT("!@#$%^&*()_+"));
        qx::wstring wstr = qx::to_wstring(str);
        EXPECT_STREQ(wstr.data(), L"!@#$%^&*()_+");
    }
}

TEST(string_converters, to_string)
{
    {
        qx::wstring wstr(L"Hello world");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), QXT("Hello world"));
    }

    {
        qx::wstring wstr(L"0123456789");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), QXT("0123456789"));
    }

    {
        qx::wstring wstr(L"!@#$%^&*()_+");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), QXT("!@#$%^&*()_+"));
    }

#if 0
    {
        qx::wstring wstr(L"Привет мир");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), QXT("?????? ???"));
    }
#endif
}

TEST(string_converters, string_to_uft8_preserves_unicode_and_embedded_nulls)
{
    const qx::cstring source("A\0\xD0\x96\xF0\x9F\x8C\x8D", 8);
    const qx::string  text = qx::utf8_to_string(source);
    EXPECT_EQ(qx::string_to_uft8(text), source);

    qx::cstring output("previous");
    qx::string_to_uft8(output, text);
    EXPECT_EQ(output, source);
    qx::string_to_uft8(output, {});
    EXPECT_TRUE(output.empty());
    EXPECT_TRUE(qx::string_to_uft8({}).empty());
}
