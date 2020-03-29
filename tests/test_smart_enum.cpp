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

TEST(TestQxSmartEnum, test)
{
    EXPECT_STREQ(colors_header::s_to_string(colors_header::red),     "red");
    EXPECT_STREQ(colors_header::s_to_string(colors_header::black),   "black");
    EXPECT_STREQ(colors_header::s_to_string(colors_header::green),   "green");
    EXPECT_STREQ(colors_header::s_to_string(colors_header::white),   "white");
    EXPECT_STREQ(colors_header::s_to_string(colors_header::yellow),  "yellow");

    {
        auto optional = colors_header::s_from_string("red");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), colors_header::red);
    }

    {
        auto optional = colors_header::s_from_string("black");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), colors_header::black);
    }

    {
        auto optional = colors_header::s_from_string("green");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), colors_header::green);
    }

    {
        auto optional = colors_header::s_from_string("white");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), colors_header::white);
    }

    {
        auto optional = colors_header::s_from_string("yellow");
        EXPECT_TRUE(optional.has_value());
        EXPECT_EQ(optional.value(), colors_header::yellow);
    }

    {
        auto optional = colors_header::s_from_string("trash");
        EXPECT_FALSE(optional.has_value());
    }

    colors_header color = colors_header::black;
    EXPECT_EQ(color++, colors_header::black);
    EXPECT_EQ(color, colors_header::green);
    EXPECT_EQ(++color, colors_header::white);
    EXPECT_EQ(color, colors_header::white);
}

#endif
