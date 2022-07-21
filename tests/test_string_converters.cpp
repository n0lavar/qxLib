/**

    @file      test_string_converters.cpp
    @author    Khrapov
    @date      17.04.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_string_converters.cpp

#if QX_TEST_STRING_CONVERTERS

    #include <qx/containers/string/string_converters.h>

TEST(string_converters, to_wstring)
{
    {
        qx::string  str("Hello world");
        qx::wstring wstr = qx::to_wstring(str);
        EXPECT_STREQ(wstr.data(), L"Hello world");
    }

    {
        qx::string  str("0123456789");
        qx::wstring wstr = qx::to_wstring(str);
        EXPECT_STREQ(wstr.data(), L"0123456789");
    }

    {
        qx::string  str("!@#$%^&*()_+");
        qx::wstring wstr = qx::to_wstring(str);
        EXPECT_STREQ(wstr.data(), L"!@#$%^&*()_+");
    }
}

TEST(string_converters, to_string)
{
    {
        qx::wstring wstr(L"Hello world");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), "Hello world");
    }

    {
        qx::wstring wstr(L"0123456789");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), "0123456789");
    }

    {
        qx::wstring wstr(L"!@#$%^&*()_+");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), "!@#$%^&*()_+");
    }

    #if 0
    {
        qx::wstring wstr(L"Привет мир");
        qx::string  str = qx::to_string(wstr);
        EXPECT_STREQ(str.data(), "?????? ???");
    }
    #endif
}

TEST(string_converters, to_char_pointer)
{
    {
        std::string_view svHelloWorld  = "Hello world";
        const char*      pszHelloWorld = qx::to_char_pointer(svHelloWorld);
        EXPECT_STREQ(pszHelloWorld, "Hello world");

        std::string_view svHelloWorld2  = "! Hello world !";
        const char*      pszHelloWorld2 = qx::to_char_pointer(svHelloWorld2);
        EXPECT_STREQ(pszHelloWorld2, "! Hello world !");
    }

    {
        std::wstring_view svHelloWorld  = L"Hello world";
        const wchar_t*    pszHelloWorld = qx::to_char_pointer(svHelloWorld);
        EXPECT_STREQ(pszHelloWorld, L"Hello world");

        std::wstring_view svHelloWorld2  = L"! Hello world !";
        const wchar_t*    pszHelloWorld2 = qx::to_char_pointer(svHelloWorld2);
        EXPECT_STREQ(pszHelloWorld2, L"! Hello world !");
    }
}

#endif
