/**

    @file      test_type_strings.cpp
    @author    Khrapov
    @date      12.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

#include <qx/containers/string/string_converters.h>
#include <qx/meta/type_strings.h>

#include <array>

//V_EXCLUDE_PATH *test_type_strings.cpp

TEST(type_strings, main)
{
    {
        using type_strings = qx::type_strings<int, char>;
        EXPECT_EQ(type_strings::get_name(), "int") << type_strings::get_name();
        EXPECT_EQ(type_strings::get_signature(), "int") << type_strings::get_signature();
        EXPECT_EQ(type_strings::get_template_parameters().size(), 0);
    }

    {
        using type_strings = qx::type_strings<std::array<int, 5>, char>;
        EXPECT_EQ(type_strings::get_name(), "std::array") << type_strings::get_name();
#if QX_MSVC
        EXPECT_EQ(type_strings::get_signature(), "std::array<int,5>") << type_strings::get_signature();
#else
        EXPECT_EQ(type_strings::get_signature(), "std::array<int, 5>") << type_strings::get_signature();
#endif

        constexpr auto templateParameters = type_strings::get_template_parameters();
        static_assert(templateParameters.size() == 2);
        if constexpr (templateParameters.size() == 2)
        {
            EXPECT_EQ(templateParameters[0], "int") << templateParameters[0];
            EXPECT_EQ(templateParameters[1], "5") << templateParameters[1];
        }
    }
}
