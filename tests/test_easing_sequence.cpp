/**

    @file      test_easing_sequence.cpp
    @author    Khrapov
    @date      11.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_easing_sequence.cpp

#if QX_TEST_EASING_SEQUENCE

#include <qx/easing/easing_sequence.h>

#define TYPE typename TypeParam::type

template<typename T>
class TestEasingSequence : public ::testing::Test
{
protected:
    using type                = typename T::type;
    static constexpr type eps = type(1e-7);

    /* called before every test */
    virtual void SetUp() override
    {
        m_Sequence = T();
    }

    void AddDefaultElements()
    {
        m_Sequence.emplace_back(
            qx::easing::linear_func<type>,
            type(0.f),
            type(1.f));

        m_Sequence.push_back(typename T::easing_element_type(
            qx::easing::linear_func<type>,
            type(1.f),
            type(0.5f),
            type(0.5f)));
    }

    void CheckNotStarted()
    {
        EXPECT_TRUE(m_Sequence.is_not_started());
        EXPECT_FALSE(m_Sequence.is_started());
        EXPECT_FALSE(m_Sequence.is_paused());
        EXPECT_FALSE(m_Sequence.is_finished());
        EXPECT_FALSE(m_Sequence.is_looped());
        EXPECT_TRUE(qx::epsilon_equal(m_Sequence.get(), type(0.f)));
        EXPECT_TRUE(qx::epsilon_equal(m_Sequence.get_fraction(), type(0.f)));
    }

    void CheckStarted(
        type fExpectedValue,
        type fExpectedFraction,
        bool bExpectedLooped = false)
    {
        EXPECT_FALSE(m_Sequence.is_not_started());
        EXPECT_TRUE(m_Sequence.is_started());
        EXPECT_FALSE(m_Sequence.is_paused());
        EXPECT_FALSE(m_Sequence.is_finished());
        EXPECT_EQ(m_Sequence.is_looped(), bExpectedLooped);
        EXPECT_TRUE(qx::epsilon_equal(m_Sequence.get(), fExpectedValue, eps));
        EXPECT_TRUE(qx::epsilon_equal(
            m_Sequence.get_fraction(),
            fExpectedFraction,
            eps));
    }

    void CheckPaused(type fExpectedValue, type fExpectedFraction)
    {
        EXPECT_FALSE(m_Sequence.is_not_started());
        EXPECT_FALSE(m_Sequence.is_started());
        EXPECT_TRUE(m_Sequence.is_paused());
        EXPECT_FALSE(m_Sequence.is_finished());
        EXPECT_FALSE(m_Sequence.is_looped());
        EXPECT_TRUE(qx::epsilon_equal(m_Sequence.get(), fExpectedValue, eps));
        EXPECT_TRUE(qx::epsilon_equal(
            m_Sequence.get_fraction(),
            fExpectedFraction,
            eps));
    }

    void CheckFinished(type fExpectedValue)
    {
        EXPECT_FALSE(m_Sequence.is_not_started());
        EXPECT_FALSE(m_Sequence.is_started());
        EXPECT_FALSE(m_Sequence.is_paused());
        EXPECT_TRUE(m_Sequence.is_finished());
        EXPECT_FALSE(m_Sequence.is_looped());
        EXPECT_TRUE(qx::epsilon_equal(m_Sequence.get(), fExpectedValue, eps));
        EXPECT_TRUE(qx::epsilon_equal(m_Sequence.get_fraction(), type(1.f)));
    }

protected:
    T m_Sequence;
};

using Implementations = ::testing::Types<
    qx::base_easing_sequence<float>,
    qx::base_easing_sequence<double>,
    qx::base_easing_sequence<long double> >;

TYPED_TEST_SUITE(TestEasingSequence, Implementations);

TYPED_TEST(TestEasingSequence, common)
{
    TestFixture::CheckNotStarted();

    TestFixture::AddDefaultElements();
    TestFixture::CheckNotStarted();

    TestFixture::m_Sequence.start();
    TestFixture::CheckStarted(TYPE(0.f), TYPE(0.f));

    // first element
    TestFixture::m_Sequence.update(TYPE(0.3f));
    TestFixture::CheckStarted(TYPE(0.3f), TYPE(0.1f));

    TestFixture::m_Sequence.update(TYPE(0.3f));
    TestFixture::CheckStarted(TYPE(0.6f), TYPE(0.2f));

    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckStarted(TYPE(1.f), TYPE(1.f / 3.f));

    // second element
    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckStarted(TYPE(0.9f), TYPE(1.f / 3.f + 2.f / 15.f));

    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckStarted(TYPE(0.8f), TYPE(1.f / 3.f + 4.f / 15.f));

    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckStarted(TYPE(0.7f), TYPE(1.f / 3.f + 6.f / 15.f));

    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckStarted(TYPE(0.6f), TYPE(1.f / 3.f + 8.f / 15.f));

    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckFinished(TYPE(0.5f));
}

TYPED_TEST(TestEasingSequence, update_overflow)
{
    TestFixture::AddDefaultElements();
    TestFixture::m_Sequence.start();

    // skip first element, update part of second element
    TestFixture::m_Sequence.update(TYPE(1.4f));
    TestFixture::CheckStarted(TYPE(0.9f), TYPE(1.f / 3.f + 2.f / 15.f));

    TestFixture::m_Sequence.update(TYPE(2.0f));
    TestFixture::CheckFinished(TYPE(0.5f));
}

TYPED_TEST(TestEasingSequence, update_speed)
{
    EXPECT_TRUE(
        qx::epsilon_equal(TestFixture::m_Sequence.get_speed(), TYPE(1.f)));

    TestFixture::AddDefaultElements();
    EXPECT_TRUE(
        qx::epsilon_equal(TestFixture::m_Sequence.get_speed(), TYPE(1.f)));

    TestFixture::m_Sequence.set_speed(TYPE(2.f));
    EXPECT_TRUE(
        qx::epsilon_equal(TestFixture::m_Sequence.get_speed(), TYPE(2.f)));

    TestFixture::m_Sequence.start();
    EXPECT_TRUE(
        qx::epsilon_equal(TestFixture::m_Sequence.get_speed(), TYPE(2.f)));

    TestFixture::m_Sequence.update(TYPE(0.7f));
    TestFixture::CheckStarted(TYPE(0.9f), TYPE(1.f / 3.f + 2.f / 15.f));
    EXPECT_TRUE(
        qx::epsilon_equal(TestFixture::m_Sequence.get_speed(), TYPE(2.f)));

    TestFixture::m_Sequence.update(TYPE(1.0f));
    TestFixture::CheckFinished(TYPE(0.5f));
    EXPECT_TRUE(
        qx::epsilon_equal(TestFixture::m_Sequence.get_speed(), TYPE(2.f)));
}

TYPED_TEST(TestEasingSequence, pause_resume)
{
    TestFixture::AddDefaultElements();
    TestFixture::m_Sequence.start();

    TestFixture::m_Sequence.update(TYPE(0.3f));
    TestFixture::CheckStarted(TYPE(0.3f), TYPE(0.1f));

    TestFixture::m_Sequence.pause();
    TestFixture::CheckPaused(TYPE(0.3f), TYPE(0.1f));

    TestFixture::m_Sequence.update(TYPE(0.3f));
    TestFixture::CheckPaused(TYPE(0.3f), TYPE(0.1f));

    TestFixture::m_Sequence.update(TYPE(10.f));
    TestFixture::CheckPaused(TYPE(0.3f), TYPE(0.1f));

    TestFixture::m_Sequence.resume();
    TestFixture::m_Sequence.update(TYPE(0.3f));
    TestFixture::CheckStarted(TYPE(0.6f), TYPE(0.2f));
}

TYPED_TEST(TestEasingSequence, skip)
{
    TestFixture::AddDefaultElements();
    TestFixture::m_Sequence.start();

    TestFixture::m_Sequence.update(TYPE(0.3f));
    TestFixture::CheckStarted(TYPE(0.3f), TYPE(0.1f));

    TestFixture::m_Sequence.skip();
    TestFixture::CheckStarted(TYPE(1.f), TYPE(1.f / 3.f));

    TestFixture::m_Sequence.update(TYPE(0.4f));
    TestFixture::CheckStarted(TYPE(0.9f), TYPE(1.f / 3.f + 2.f / 15.f));

    TestFixture::m_Sequence.skip();
    TestFixture::CheckFinished(TYPE(0.5f));
}

TYPED_TEST(TestEasingSequence, reset)
{
    TestFixture::AddDefaultElements();
    TestFixture::m_Sequence.start();
    TestFixture::m_Sequence.update(TYPE(0.3f));

    TestFixture::m_Sequence.reset();
    TestFixture::CheckNotStarted();
}

TYPED_TEST(TestEasingSequence, loop)
{
    EXPECT_FALSE(TestFixture::m_Sequence.is_looped());
    TestFixture::AddDefaultElements();
    EXPECT_FALSE(TestFixture::m_Sequence.is_looped());
    TestFixture::m_Sequence.start();
    EXPECT_FALSE(TestFixture::m_Sequence.is_looped());
    TestFixture::m_Sequence.set_looped(true);
    EXPECT_TRUE(TestFixture::m_Sequence.is_looped());

    TestFixture::m_Sequence.update(TYPE(1.f));
    TestFixture::CheckStarted(TYPE(1.f), TYPE(1.f / 3.f), true);
    TestFixture::m_Sequence.update(TYPE(2.f));
    TestFixture::CheckStarted(TYPE(0.f), TYPE(0.f), true);

    TestFixture::m_Sequence.update(TYPE(1.f));
    TestFixture::CheckStarted(TYPE(1.f), TYPE(1.f / 3.f), true);
    TestFixture::m_Sequence.update(TYPE(2.f));
    TestFixture::CheckStarted(TYPE(0.f), TYPE(0.f), true);

    TestFixture::m_Sequence.update(TYPE(1.f));
    TestFixture::CheckStarted(TYPE(1.f), TYPE(1.f / 3.f), true);
    TestFixture::m_Sequence.update(TYPE(2.f));
    TestFixture::CheckStarted(TYPE(0.f), TYPE(0.f), true);

    TestFixture::m_Sequence.set_looped(false);
    EXPECT_FALSE(TestFixture::m_Sequence.is_looped());

    TestFixture::m_Sequence.update(TYPE(1.f));
    TestFixture::CheckStarted(TYPE(1.f), TYPE(1.f / 3.f));
    TestFixture::m_Sequence.update(TYPE(2.f));
    TestFixture::CheckFinished(TYPE(0.5f));
}

#endif
