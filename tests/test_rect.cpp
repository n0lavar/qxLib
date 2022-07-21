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

template<typename VectorType>
class TestRect : public ::testing::Test
{
};

using Implementations = ::testing::Types<glm::vec2, glm::dvec2>;

TYPED_TEST_SUITE(TestRect, Implementations);

template<class Rect>
void CheckRect(
    const Rect&               rect,
    typename Rect::value_type fWidth,
    typename Rect::value_type fHeight,
    typename Rect::value_type fX1,
    typename Rect::value_type fX2)
{
    using VectorType = typename Rect::vector_type;

    EXPECT_DOUBLE_EQ(rect.width(), fWidth);
    EXPECT_DOUBLE_EQ(rect.height(), fHeight);
    EXPECT_DOUBLE_EQ(rect.left(), fX1);
    EXPECT_DOUBLE_EQ(rect.top(), fX2);
    EXPECT_DOUBLE_EQ(rect.right(), fX1 + fWidth);
    EXPECT_DOUBLE_EQ(rect.bottom(), fX2 + fHeight);
    EXPECT_EQ(rect.pos(), VectorType(fX1, fX2));
    EXPECT_EQ(rect.size(), VectorType(fWidth, fHeight));
    EXPECT_DOUBLE_EQ(rect.area(), fWidth * fHeight);
    EXPECT_EQ(rect.min(), VectorType(fX1, fX2));
    EXPECT_EQ(rect.max(), VectorType(fX1 + fWidth, fX2 + fHeight));
    EXPECT_EQ(
        rect.center(),
        VectorType(fX1, fX2) + VectorType(fWidth, fHeight) / static_cast<typename Rect::value_type>(2.0));
    EXPECT_EQ(!rect.empty(), fWidth * fHeight > 0.0);
}

    #define Rect       qx::basic_rect<TypeParam>
    #define VectorType TypeParam

TYPED_TEST(TestRect, construct)
{
    {
        Rect rect;
        CheckRect(rect, 0.0, 0.0, 0.0, 0.0);
    }

    {
        Rect rect(VectorType { 1.0, 1.0 });
        CheckRect(rect, 1.0, 1.0, 0.0, 0.0);
    }

    {
        Rect rect(VectorType { 1.0, 1.0 }, VectorType { 2.0, 2.0 });
        CheckRect(rect, 1.0, 1.0, 2.0, 2.0);
    }

    {
        Rect rect(1.0, 1.0);
        CheckRect(rect, 1.0, 1.0, 0.0, 0.0);
    }

    {
        Rect rect(1.0, 1.0, 2.0, 2.0);
        CheckRect(rect, 1.0, 1.0, 2.0, 2.0);
    }
}

TYPED_TEST(TestRect, resize)
{
    Rect rect(1.0, 1.0);
    CheckRect(rect, 1.0, 1.0, 0.0, 0.0);

    rect.expand({ 2.0, 3.0 });
    CheckRect(rect, 3.0, 4.0, 0.0, 0.0);

    rect.contract({ 1.0, 3.0 });
    CheckRect(rect, 2.0, 1.0, 0.0, 0.0);

    rect.set_size({ 5.0, 5.0 });
    CheckRect(rect, 5.0, 5.0, 0.0, 0.0);

    rect.set_size({ -1.0, -1.0 });
    CheckRect(rect, 0.0, 0.0, 0.0, 0.0);

    rect.set_size({ 1.0, 1.0 });
    rect.expand({ -2.0, 3.0 });
    CheckRect(rect, 0.0, 4.0, 0.0, 0.0);

    rect.set_size({ 1.0, 3.0 });
    rect.contract({ 2.0, 2.0 });
    CheckRect(rect, 0.0, 1.0, 0.0, 0.0);
}

TYPED_TEST(TestRect, replace)
{
    Rect rect(1.0, 1.0);
    CheckRect(rect, 1.0, 1.0, 0.0, 0.0);

    rect.shift({ 1.0, 2.0 });
    CheckRect(rect, 1.0, 1.0, 1.0, 2.0);

    rect.shift({ -2.0, -1.0 });
    CheckRect(rect, 1.0, 1.0, -1.0, 1.0);

    rect.set_pos({ 5.0, 5.0 });
    CheckRect(rect, 1.0, 1.0, 5.0, 5.0);
}

TYPED_TEST(TestRect, contains)
{
    Rect rect(1.0, 2.0, 1.0, 2.0);

    EXPECT_TRUE(rect.contains(VectorType({ 1.0, 2.0 })));
    EXPECT_TRUE(rect.contains(VectorType({ 1.0, 4.0 })));
    EXPECT_TRUE(rect.contains(VectorType({ 2.0, 3.0 })));
    EXPECT_TRUE(rect.contains(VectorType({ 2.0, 2.0 })));
    EXPECT_FALSE(rect.contains(VectorType({ 0.0, 0.0 })));
    EXPECT_FALSE(rect.contains(VectorType({ 10.0, 0.0 })));
    EXPECT_FALSE(rect.contains(VectorType({ 0.0, 10.0 })));
    EXPECT_FALSE(rect.contains(VectorType({ 10.0, 10.0 })));

    EXPECT_TRUE(rect.contains(rect));
    EXPECT_TRUE(rect.contains(Rect(1.0, 1.0, 1.0, 2.0)));
    EXPECT_TRUE(rect.contains(Rect(1.0, 1.0, 1.0, 3.0)));

    EXPECT_FALSE(rect.contains(Rect(1.0, 2.0)));
    EXPECT_FALSE(rect.contains(Rect(1.0, 10.0)));
    EXPECT_FALSE(rect.contains(Rect(1.0, 1.0, 1.0, 4.0)));
    EXPECT_FALSE(rect.contains(Rect(1.0, 1.0, 2.0, 1.0)));
}

TYPED_TEST(TestRect, overlaps)
{
    Rect rect(1.0, 2.0, 1.0, 2.0);

    EXPECT_TRUE(rect.overlaps(Rect(1.0, 2.0)));
    EXPECT_TRUE(rect.overlaps(Rect(1.0, 4.0)));
    EXPECT_TRUE(rect.overlaps(Rect(2.0, 3.0)));
    EXPECT_TRUE(rect.overlaps(Rect(2.0, 2.0)));
    EXPECT_TRUE(rect.overlaps(Rect(10.0, 10.0)));

    EXPECT_FALSE(rect.overlaps(Rect(0.0, 0.0)));
    EXPECT_FALSE(rect.overlaps(Rect(10.0, 0.0)));
    EXPECT_FALSE(rect.overlaps(Rect(0.0, 10.0)));
    EXPECT_FALSE(rect.overlaps(Rect(1.0, 0.5f)));
    EXPECT_FALSE(rect.overlaps(Rect(0.5f, 1.0)));
}

TYPED_TEST(TestRect, overlap)
{
    Rect rect(1.0, 2.0, 1.0, 2.0);

    EXPECT_EQ(rect.overlap(Rect()), std::nullopt);
    EXPECT_EQ(rect.overlap(Rect(1.0, 1.0)), std::nullopt);
    EXPECT_EQ(rect.overlap(Rect(1.0, 2.0, 3.0, 5.0)), std::nullopt);

    EXPECT_EQ(rect.overlap(Rect(1.0, 2.0)), Rect(0.0, 0.0, 1.0, 2.0));
    EXPECT_EQ(rect.overlap(Rect(1.0, 2.0, 1.0, 2.0)), Rect(1.0, 2.0, 1.0, 2.0));
    EXPECT_EQ(rect.overlap(Rect(2.0, 1.0, 0.0, 2.0)), Rect(1.0, 1.0, 1.0, 2.0));
    EXPECT_EQ(rect.overlap(Rect(2.0, 1.0, 0.0, 2.0)), Rect(1.0, 1.0, 1.0, 2.0));
}

TYPED_TEST(TestRect, equal)
{
    Rect rec0(1.0, 2.0, 1.0, 2.0);
    Rect rec1(1.0, 2.0, 1.0, 3.0);
    Rect rec2(1.0, 3.0, 1.0, 2.0);

    EXPECT_EQ(rec0, Rect(1.0, 2.0, 1.0, 2.0));
    EXPECT_EQ(rec1, Rect(1.0, 2.0, 1.0, 3.0));
    EXPECT_EQ(rec2, Rect(1.0, 3.0, 1.0, 2.0));

    EXPECT_NE(rec0, rec1);
    EXPECT_NE(rec0, rec2);
    EXPECT_NE(rec1, rec0);
    EXPECT_NE(rec1, rec2);
    EXPECT_NE(rec2, rec0);
    EXPECT_NE(rec2, rec1);
}

#endif
