//============================================================================
//
//!\file                     test_smart_enum.cpp
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        26.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#include <config.h>

#if QX_TEST_SMART_ENUM

#include <qx/other/smart_enum.h>
#include <gtest/gtest.h>

SMART_ENUM(colors_header, -3,
    red,
    black,
    green,
    white,
    yellow
)

template <typename Enum>
class TestQxSmartEnum : public ::testing::Test
{
protected:
    using current_enum = Enum;
};


using Implementations = ::testing::Types
<
    colors_header
>;

TYPED_TEST_SUITE(TestQxSmartEnum, Implementations);


TYPED_TEST(TestQxSmartEnum, test)
{
    EXPECT_STREQ(current_enum::s_to_string(current_enum::red),     "red");
    EXPECT_STREQ(current_enum::s_to_string(current_enum::black),   "black");
    EXPECT_STREQ(current_enum::s_to_string(current_enum::green),   "green");
    EXPECT_STREQ(current_enum::s_to_string(current_enum::white),   "white");
    EXPECT_STREQ(current_enum::s_to_string(current_enum::yellow),  "yellow");

    {
        auto optional = current_enum::s_from_string("red");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), current_enum::red);
    }

    {
        auto optional = current_enum::s_from_string("black");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), current_enum::black);
    }

    {
        auto optional = current_enum::s_from_string("green");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), current_enum::green);
    }

    {
        auto optional = current_enum::s_from_string("white");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), current_enum::white);
    }

    {
        auto optional = current_enum::s_from_string("yellow");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), current_enum::yellow);
    }

    {
        auto optional = current_enum::s_from_string("trash");
        EXPECT_FALSE(optional.has_value());
    }

    current_enum color = current_enum::black;
    EXPECT_EQ(color++, current_enum::black);
    EXPECT_EQ(color, current_enum::green);
    EXPECT_EQ(++color, current_enum::white);
    EXPECT_EQ(color, current_enum::white);
}

#endif
