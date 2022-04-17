/**

    @file      test_rect.cpp
    @author    Khrapov
    @date      16.04.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_rect.cpp

#if QX_TEST_RECT

#include <qx/render/rect.h>

void CheckRect(
    const qx::rect& rect,
    float           fWidth,
    float           fHeight,
    float           fX1,
    float           fX2)
{
    EXPECT_FLOAT_EQ(rect.width(), fWidth);
    EXPECT_FLOAT_EQ(rect.height(), fHeight);
    EXPECT_FLOAT_EQ(rect.left(), fX1);
    EXPECT_FLOAT_EQ(rect.top(), fX2);
    EXPECT_FLOAT_EQ(rect.right(), fX1 + fWidth);
    EXPECT_FLOAT_EQ(rect.bottom(), fX2 + fHeight);
    EXPECT_EQ(rect.pos(), glm::vec2(fX1, fX2));
    EXPECT_EQ(rect.size(), glm::vec2(fWidth, fHeight));
    EXPECT_FLOAT_EQ(rect.area(), fWidth * fHeight);
    EXPECT_EQ(rect.min(), glm::vec2(fX1, fX2));
    EXPECT_EQ(rect.max(), glm::vec2(fX1 + fWidth, fX2 + fHeight));
    EXPECT_EQ(
        rect.center(),
        glm::vec2(fX1, fX2) + glm::vec2(fWidth, fHeight) / 2.f);
    EXPECT_EQ(!rect.empty(), fWidth * fHeight > 0.f);
}

TEST(rect, construct)
{
    {
        qx::rect rect;
        CheckRect(rect, 0.f, 0.f, 0.f, 0.f);
    }

    {
        qx::rect rect(glm::vec2 { 1.f, 1.f });
        CheckRect(rect, 1.f, 1.f, 0.f, 0.f);
    }

    {
        qx::rect rect(glm::vec2 { 1.f, 1.f }, glm::vec2 { 2.f, 2.f });
        CheckRect(rect, 1.f, 1.f, 2.f, 2.f);
    }

    {
        qx::rect rect(1.f, 1.f);
        CheckRect(rect, 1.f, 1.f, 0.f, 0.f);
    }

    {
        qx::rect rect(1.f, 1.f, 2.f, 2.f);
        CheckRect(rect, 1.f, 1.f, 2.f, 2.f);
    }
}

TEST(rect, resize)
{
    qx::rect rect(1.f, 1.f);
    CheckRect(rect, 1.f, 1.f, 0.f, 0.f);

    rect.expand({ 2.f, 3.f });
    CheckRect(rect, 3.f, 4.f, 0.f, 0.f);

    rect.contract({ 1.f, 3.f });
    CheckRect(rect, 2.f, 1.f, 0.f, 0.f);

    rect.set_size({ 5.f, 5.f });
    CheckRect(rect, 5.f, 5.f, 0.f, 0.f);

    rect.set_size({ -1.f, -1.f });
    CheckRect(rect, 0.f, 0.f, 0.f, 0.f);

    rect.set_size({ 1.f, 1.f });
    rect.expand({ -2.f, 3.f });
    CheckRect(rect, 0.f, 4.f, 0.f, 0.f);

    rect.set_size({ 1.f, 3.f });
    rect.contract({ 2.f, 2.f });
    CheckRect(rect, 0.f, 1.f, 0.f, 0.f);
}

TEST(rect, replace)
{
    qx::rect rect(1.f, 1.f);
    CheckRect(rect, 1.f, 1.f, 0.f, 0.f);

    rect.shift({ 1.f, 2.f });
    CheckRect(rect, 1.f, 1.f, 1.f, 2.f);

    rect.shift({ -2.f, -1.f });
    CheckRect(rect, 1.f, 1.f, -1.f, 1.f);

    rect.set_pos({ 5.f, 5.f });
    CheckRect(rect, 1.f, 1.f, 5.f, 5.f);
}

TEST(rect, contains)
{
    qx::rect rect(1.f, 2.f, 1.f, 2.f);

    EXPECT_TRUE(rect.contains(glm::vec2({ 1.f, 2.f })));
    EXPECT_TRUE(rect.contains(glm::vec2({ 1.f, 4.f })));
    EXPECT_TRUE(rect.contains(glm::vec2({ 2.f, 3.f })));
    EXPECT_TRUE(rect.contains(glm::vec2({ 2.f, 2.f })));
    EXPECT_FALSE(rect.contains(glm::vec2({ 0.f, 0.f })));
    EXPECT_FALSE(rect.contains(glm::vec2({ 10.f, 0.f })));
    EXPECT_FALSE(rect.contains(glm::vec2({ 0.f, 10.f })));
    EXPECT_FALSE(rect.contains(glm::vec2({ 10.f, 10.f })));

    EXPECT_TRUE(rect.contains(rect));
    EXPECT_TRUE(rect.contains(qx::rect(1.f, 1.f, 1.f, 2.f)));
    EXPECT_TRUE(rect.contains(qx::rect(1.f, 1.f, 1.f, 3.f)));

    EXPECT_FALSE(rect.contains(qx::rect(1.f, 2.f)));
    EXPECT_FALSE(rect.contains(qx::rect(1.f, 10.f)));
    EXPECT_FALSE(rect.contains(qx::rect(1.f, 1.f, 1.f, 4.f)));
    EXPECT_FALSE(rect.contains(qx::rect(1.f, 1.f, 2.f, 1.f)));
}

TEST(rect, overlaps)
{
    qx::rect rect(1.f, 2.f, 1.f, 2.f);

    EXPECT_TRUE(rect.overlaps(qx::rect(1.f, 2.f)));
    EXPECT_TRUE(rect.overlaps(qx::rect(1.f, 4.f)));
    EXPECT_TRUE(rect.overlaps(qx::rect(2.f, 3.f)));
    EXPECT_TRUE(rect.overlaps(qx::rect(2.f, 2.f)));
    EXPECT_TRUE(rect.overlaps(qx::rect(10.f, 10.f)));

    EXPECT_FALSE(rect.overlaps(qx::rect(0.f, 0.f)));
    EXPECT_FALSE(rect.overlaps(qx::rect(10.f, 0.f)));
    EXPECT_FALSE(rect.overlaps(qx::rect(0.f, 10.f)));
    EXPECT_FALSE(rect.overlaps(qx::rect(1.f, 0.5f)));
    EXPECT_FALSE(rect.overlaps(qx::rect(0.5f, 1.f)));
}

TEST(rect, overlap)
{
    qx::rect rect(1.f, 2.f, 1.f, 2.f);

    EXPECT_EQ(rect.overlap(qx::rect()), std::nullopt);
    EXPECT_EQ(rect.overlap(qx::rect(1.f, 1.f)), std::nullopt);
    EXPECT_EQ(rect.overlap(qx::rect(1.f, 2.f, 3.f, 5.f)), std::nullopt);

    EXPECT_EQ(rect.overlap(qx::rect(1.f, 2.f)), qx::rect(0.f, 0.f, 1.f, 2.f));
    EXPECT_EQ(
        rect.overlap(qx::rect(1.f, 2.f, 1.f, 2.f)),
        qx::rect(1.f, 2.f, 1.f, 2.f));
    EXPECT_EQ(
        rect.overlap(qx::rect(2.f, 1.f, 0.f, 2.f)),
        qx::rect(1.f, 1.f, 1.f, 2.f));
    EXPECT_EQ(
        rect.overlap(qx::rect(2.f, 1.f, 0.f, 2.f)),
        qx::rect(1.f, 1.f, 1.f, 2.f));
}

TEST(rect, equal)
{
    qx::rect rec0(1.f, 2.f, 1.f, 2.f);
    qx::rect rec1(1.f, 2.f, 1.f, 3.f);
    qx::rect rec2(1.f, 3.f, 1.f, 2.f);

    EXPECT_EQ(rec0, qx::rect(1.f, 2.f, 1.f, 2.f));
    EXPECT_EQ(rec1, qx::rect(1.f, 2.f, 1.f, 3.f));
    EXPECT_EQ(rec2, qx::rect(1.f, 3.f, 1.f, 2.f));

    EXPECT_NE(rec0, rec1);
    EXPECT_NE(rec0, rec2);
    EXPECT_NE(rec1, rec0);
    EXPECT_NE(rec1, rec2);
    EXPECT_NE(rec2, rec0);
    EXPECT_NE(rec2, rec1);
}

#endif
