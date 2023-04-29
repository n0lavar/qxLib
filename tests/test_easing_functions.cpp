/**

    @file      test_easing_functions.cpp
    @author    Khrapov
    @date      11.05.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_easing_functions.cpp

#include <qx/easing/easing_functions.h>

template<class T>
class TestEasingFunctions : public ::testing::Test
{
protected:
    template<T Func(T)>
    void TestFunc()
    {
        // x zero
        EXPECT_TRUE(qx::epsilon_equal(Func(T(0.f)), T(0.f), qx::easing::eps<T>()));

        // x one
        EXPECT_TRUE(qx::epsilon_equal(Func(T(1.f)), T(1.f), qx::easing::eps<T>()));

        // check there are no divides on zero and other calc errors
        constexpr T step(0.001f);

        volatile T sum_to_avoid_optimizing_out(0.f);
        for (T x = 0.0; qx::epsilon_less_equal(x, T(1.f)); x += step)
        {
            sum_to_avoid_optimizing_out = sum_to_avoid_optimizing_out + Func(x);
        }
    }
};

using Implementations = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(TestEasingFunctions, Implementations);

TYPED_TEST(TestEasingFunctions, common)
{
    TestFixture::template TestFunc<qx::easing::linear_func>();
    TestFixture::template TestFunc<qx::easing::step_func>();
    TestFixture::template TestFunc<qx::easing::smooth_step_func>();
    TestFixture::template TestFunc<qx::easing::smoother_step_func>();
    TestFixture::template TestFunc<qx::easing::quadratic_in_func>();
    TestFixture::template TestFunc<qx::easing::quadratic_out_func>();
    TestFixture::template TestFunc<qx::easing::quadratic_in_out_func>();
    TestFixture::template TestFunc<qx::easing::cubic_in_func>();
    TestFixture::template TestFunc<qx::easing::cubic_out_func>();
    TestFixture::template TestFunc<qx::easing::cubic_in_out_func>();
    TestFixture::template TestFunc<qx::easing::quartic_in_func>();
    TestFixture::template TestFunc<qx::easing::quartic_out_func>();
    TestFixture::template TestFunc<qx::easing::quartic_in_out_func>();
    TestFixture::template TestFunc<qx::easing::quintic_in_func>();
    TestFixture::template TestFunc<qx::easing::quintic_out_func>();
    TestFixture::template TestFunc<qx::easing::quintic_in_out_func>();
    TestFixture::template TestFunc<qx::easing::sine_in_func>();
    TestFixture::template TestFunc<qx::easing::sine_out_func>();
    TestFixture::template TestFunc<qx::easing::sine_in_out_func>();
    TestFixture::template TestFunc<qx::easing::circular_in_func>();
    TestFixture::template TestFunc<qx::easing::circular_out_func>();
    TestFixture::template TestFunc<qx::easing::circular_in_out_func>();
    TestFixture::template TestFunc<qx::easing::exponential_in_func>();
    TestFixture::template TestFunc<qx::easing::exponential_out_func>();
    TestFixture::template TestFunc<qx::easing::exponential_in_out_func>();
    TestFixture::template TestFunc<qx::easing::elastic_in_func>();
    TestFixture::template TestFunc<qx::easing::elastic_out_func>();
    TestFixture::template TestFunc<qx::easing::elastic_in_out_func>();
    TestFixture::template TestFunc<qx::easing::back_in_func>();
    TestFixture::template TestFunc<qx::easing::back_out_func>();
    TestFixture::template TestFunc<qx::easing::back_in_out_func>();
    TestFixture::template TestFunc<qx::easing::bounce_out_func>();
    TestFixture::template TestFunc<qx::easing::bounce_in_func>();
    TestFixture::template TestFunc<qx::easing::bounce_in_out_func>();
}
