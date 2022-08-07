/**

    @file      test_color.cpp
    @author    Khrapov
    @date      16.07.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

//V_EXCLUDE_PATH *test_color.cpp

#include <qx/math/common.h>
#include <qx/render/color.h>

void TestColor(const qx::color& color)
{
    EXPECT_TRUE(qx::between(0.f, color.r(), 1.f));
    EXPECT_TRUE(qx::between(0.f, color.g(), 1.f));
    EXPECT_TRUE(qx::between(0.f, color.b(), 1.f));
    EXPECT_TRUE(qx::between(0.f, color.a(), 1.f));

    EXPECT_TRUE(qx::between(0, color.r_dec(), 255));
    EXPECT_TRUE(qx::between(0, color.g_dec(), 255));
    EXPECT_TRUE(qx::between(0, color.b_dec(), 255));
    EXPECT_TRUE(qx::between(0, color.a_dec(), 255));

    ASSERT_TRUE(color.data());
    EXPECT_EQ(color.size(), 4);
    EXPECT_EQ(color.data()[0], color.r());
    EXPECT_EQ(color.data()[1], color.g());
    EXPECT_EQ(color.data()[2], color.b());
    EXPECT_EQ(color.data()[3], color.a());

    glm::vec4 vec4color = color;
    EXPECT_EQ(vec4color[0], color.r());
    EXPECT_EQ(vec4color[1], color.g());
    EXPECT_EQ(vec4color[2], color.b());
    EXPECT_EQ(vec4color[3], color.a());

    glm::vec3 vec3color = color;
    EXPECT_EQ(vec3color[0], color.r());
    EXPECT_EQ(vec3color[1], color.g());
    EXPECT_EQ(vec3color[2], color.b());

    // unsigned int hex = color.hex();
    // EXPECT_EQ(qx::color(hex), color);
}

TEST(color, colors)
{
    TestColor(qx::color());
    TestColor(qx::color::aqua());
    TestColor(qx::color::black());
    TestColor(qx::color::blue());
    TestColor(qx::color::fuchsia());
    TestColor(qx::color::gray());
    TestColor(qx::color::green());
    TestColor(qx::color::lime());
    TestColor(qx::color::maroon());
    TestColor(qx::color::navy());
    TestColor(qx::color::olive());
    TestColor(qx::color::purple());
    TestColor(qx::color::red());
    TestColor(qx::color::silver());
    TestColor(qx::color::teal());
    TestColor(qx::color::white());
    TestColor(qx::color::yellow());
    TestColor(qx::color::empty());
}

TEST(color, set)
{
    qx::color color(1.f, 1.f, 1.f, 1.f);
    TestColor(color);

    color.set_r(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_g(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_b(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 1.f);

    color.set_a(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_r(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_g(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_b(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 0.5f);

    color.set_a(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_r(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_g(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_b(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 1.f);

    color.set_a(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);
}

TEST(color, set_dec)
{
    qx::color color(255, 255, 255, 255);
    TestColor(color);

    color.set_r_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_g_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_b_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_a_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_r_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_g_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_b_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 127);

    color.set_a_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_r_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_g_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_b_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 255);

    color.set_a_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);
}

TEST(color, update)
{
    qx::color color(0.f, 0.f, 0.f, 0.f);
    TestColor(color);

    color.update_r(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);

    color.update_g(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);

    color.update_b(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.f);

    color.update_a(0.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.5f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_r(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 0.5f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_g(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 0.5f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_b(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 0.5f);

    color.update_a(1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 1.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_r(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 1.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_g(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 1.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_b(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 1.f);

    color.update_a(-1.5f);
    TestColor(color);
    EXPECT_EQ(color[0], 0.f);
    EXPECT_EQ(color[1], 0.f);
    EXPECT_EQ(color[2], 0.f);
    EXPECT_EQ(color[3], 0.f);
}

TEST(color, update_dec)
{
    qx::color color(0, 0, 0, 0);
    TestColor(color);

    color.update_r_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);

    color.update_g_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);

    color.update_b_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 0);

    color.update_a_dec(127);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 127);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_r_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 127);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_g_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 127);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_b_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 127);

    color.update_a_dec(500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 255);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_r_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 255);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_g_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 255);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_b_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 255);

    color.update_a_dec(-500);
    TestColor(color);
    EXPECT_EQ(color.r_dec(), 0);
    EXPECT_EQ(color.g_dec(), 0);
    EXPECT_EQ(color.b_dec(), 0);
    EXPECT_EQ(color.a_dec(), 0);
}
