/**

    @file      test_string_literal.cpp
    @author    Khrapov
    @date      10.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_string_literal.cpp

#include <qx/containers/string/string_literal.h>
#include <qx/containers/string/string_utils.h>

template<qx::string_literal text>
class StringTemplateClass
{
public:
    static constexpr std::string_view as_view()
    {
        return text.view();
    }

    static constexpr const char* as_as_pointer()
    {
        return text.data();
    }

    static constexpr size_t size()
    {
        return text.size();
    }
};

constexpr StringTemplateClass<"Text"> stringTemplateClass;
constexpr std::string_view            svText = stringTemplateClass.as_view();
QX_STATIC_ASSERT_STR_EQ(svText.data(), "Text");
QX_STATIC_ASSERT_STR_EQ(stringTemplateClass.as_as_pointer(), "Text");
static_assert(stringTemplateClass.size() == 5);
