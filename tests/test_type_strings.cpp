/**

    @file      test_type_strings.cpp
    @author    Khrapov
    @date      12.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#define QX_CONF_USE_CHAR

#include <common.h>

#include <qx/containers/string/string_converters.h>
#include <qx/meta/type_strings.h>

#include <array>

//V_EXCLUDE_PATH *test_type_strings.cpp

TEST(type_strings, main)
{
    {
        using type_strings = qx::type_strings<int>;
        EXPECT_EQ(type_strings::get_name(), QX_TEXT("int")) << qx::to_cstring(type_strings::get_name()).c_str();
        EXPECT_EQ(type_strings::get_signature(), QX_TEXT("int"))
            << qx::to_cstring(type_strings::get_signature()).c_str();
        EXPECT_EQ(type_strings::get_template_parameters().size(), 0);
    }

    {
        using type_strings = qx::type_strings<std::array<int, 5>>;
        EXPECT_EQ(type_strings::get_name(), QX_TEXT("std::array")) << qx::to_cstring(type_strings::get_name()).c_str();

#if QX_MSVC
        EXPECT_EQ(type_strings::get_signature(), QX_TEXT("std::array<int,5> "))
            << qx::to_cstring(type_strings::get_signature()).c_str();
#else
        EXPECT_EQ(type_strings::get_signature(), QX_TEXT("std::array<int, 5>"))
            << qx::to_cstring(type_strings::get_signature()).c_str();
#endif

        constexpr auto templateParameters = type_strings::get_template_parameters();
        static_assert(templateParameters.size() == 2);
        if constexpr (templateParameters.size() == 2)
        {
            EXPECT_EQ(templateParameters[0], QX_TEXT("int")) << qx::to_cstring(templateParameters[0]).c_str();
            EXPECT_EQ(templateParameters[1], QX_TEXT("5")) << qx::to_cstring(templateParameters[1]).c_str();
        }
    }
}
