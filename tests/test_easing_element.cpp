/**

    @file      test_easing_element.cpp
    @author    Khrapov
    @date      11.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_easing_element.cpp

#include <qx/easing/easing_element.h>

#define TYPE typename TypeParam::type

template<typename T>
class TestEasingElements : public ::testing::Test
{
protected:
    using type                = typename T::type;
    static constexpr type eps = type(1e-6);

    /* called before every test */
    virtual void SetUp() override
    {
        m_Element = T(qx::easing::linear_func<type>, type(-1), type(2));
    }

    void CheckNotStarted()
    {
        EXPECT_TRUE(m_Element.is_not_started());
        EXPECT_FALSE(m_Element.is_started());
        EXPECT_FALSE(m_Element.is_paused());
        EXPECT_FALSE(m_Element.is_finished());
        EXPECT_EQ(m_Element.get_status(), T::status::not_started);
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get(), type(-1.0)));
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get_fraction(), type(0)));
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get_speed(), type(1)));
    }

    void CheckStarted(type fExpectedValue, type fExpectedFraction, type fExpectedSpeed = type(1.f))
    {
        EXPECT_FALSE(m_Element.is_not_started());
        EXPECT_TRUE(m_Element.is_started());
        EXPECT_FALSE(m_Element.is_paused());
        EXPECT_FALSE(m_Element.is_finished());
        EXPECT_EQ(m_Element.get_status(), T::status::started);
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get(), fExpectedValue, eps));
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get_fraction(), fExpectedFraction, eps));
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get_speed(), fExpectedSpeed, eps));
    }

    void CheckFinished(type fExpectedValue)
    {
        EXPECT_FALSE(m_Element.is_not_started());
        EXPECT_FALSE(m_Element.is_started());
        EXPECT_FALSE(m_Element.is_paused());
        EXPECT_TRUE(m_Element.is_finished());
        EXPECT_EQ(m_Element.get_status(), T::status::finished);
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get(), fExpectedValue));
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get_fraction(), type(1.0)));
    }

    void CheckPaused(type fExpectedValue, type fExpectedFraction)
    {
        EXPECT_FALSE(m_Element.is_not_started());
        EXPECT_FALSE(m_Element.is_started());
        EXPECT_TRUE(m_Element.is_paused());
        EXPECT_FALSE(m_Element.is_finished());
        EXPECT_EQ(m_Element.get_status(), T::status::paused);
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get(), fExpectedValue, eps));
        EXPECT_TRUE(qx::epsilon_equal(m_Element.get_fraction(), fExpectedFraction, eps));
    }

protected:
    T m_Element = T(qx::easing::linear_func<typename T::type>);
};

using Implementations = ::testing::
    Types<qx::base_easing_element<float>, qx::base_easing_element<double>, qx::base_easing_element<long double> >;

TYPED_TEST_SUITE(TestEasingElements, Implementations);

TYPED_TEST(TestEasingElements, construct)
{
    TestFixture::CheckNotStarted();
}

TYPED_TEST(TestEasingElements, start)
{
    TestFixture::m_Element.start();
    TestFixture::CheckStarted(TYPE(-1.f), TYPE(0.f));
}

TYPED_TEST(TestEasingElements, update_speed)
{
    TestFixture::m_Element.start();

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.1)), TYPE(0.f)));
    TestFixture::CheckStarted(TYPE(-0.7l), TYPE(0.1l));

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.1)), TYPE(0.f)));
    TestFixture::CheckStarted(TYPE(-0.4l), TYPE(0.2l));

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.2)), TYPE(0.f)));
    TestFixture::CheckStarted(TYPE(0.2l), TYPE(0.4l));

    TestFixture::m_Element.set_speed(TYPE(2.0));
    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.2)), TYPE(0.f)));
    TestFixture::CheckStarted(TYPE(1.4l), TYPE(0.8l), TYPE(2.l));

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(1.0)), TYPE(0.9f), TYPE(1e-7)));
    TestFixture::CheckFinished(TYPE(2.l));

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(1.0)), TYPE(1.f)));
    TestFixture::CheckFinished(TYPE(2.l));
}

TYPED_TEST(TestEasingElements, pause_resume)
{
    TestFixture::m_Element.start();

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.1)), TYPE(0.f)));
    TestFixture::m_Element.pause();
    TestFixture::CheckPaused(TYPE(-0.7l), TYPE(0.1l));

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.1f)), TYPE(0.1f)));
    TestFixture::CheckPaused(TYPE(-0.7l), TYPE(0.1l));

    TestFixture::m_Element.resume();
    TestFixture::CheckStarted(TYPE(-0.7l), TYPE(0.1l));

    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.1)), TYPE(0.f)));
    TestFixture::CheckStarted(TYPE(-0.4l), TYPE(0.2l));
}

TYPED_TEST(TestEasingElements, finish)
{
    TestFixture::m_Element.start();
    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.2)), TYPE(0.f)));
    TestFixture::m_Element.finish();
    TestFixture::CheckFinished(TYPE(2.l));
}

TYPED_TEST(TestEasingElements, reset)
{
    TestFixture::m_Element.start();
    EXPECT_TRUE(qx::epsilon_equal(TestFixture::m_Element.update(TYPE(0.2)), TYPE(0.f)));
    TestFixture::m_Element.reset();
    TestFixture::CheckNotStarted();
}
