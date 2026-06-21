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
