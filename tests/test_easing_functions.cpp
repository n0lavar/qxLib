//==============================================================================
//
//!\file                   test_easing_functions.cpp
//
//!\brief       Tests for functions from qx::easing
//!\details     ~
//
//!\author      Khrapov
//!\date        11.05.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_easing_functions.cpp

#if QX_TEST_EASING_FUNCTIONS

#include <qx/easing/easing_functions.h>

template<typename T, T Func(T)>
class EasingFunctionTraits
{
public:

    using Type = T;

    static T CallEasingFunc(T x)
    {
        return Func(x);
    }
};

template<typename Traits>
class TestEasingFunctions : public ::testing::Test
{
};

using Implementations = ::testing::Types
<
    EasingFunctionTraits<float, qx::easing::linear_func>,
    EasingFunctionTraits<float, qx::easing::step_func>,
    EasingFunctionTraits<float, qx::easing::smooth_step_func>,
    EasingFunctionTraits<float, qx::easing::smoother_step_func>,
    EasingFunctionTraits<float, qx::easing::quadratic_in_func>,
    EasingFunctionTraits<float, qx::easing::quadratic_out_func>,
    EasingFunctionTraits<float, qx::easing::quadratic_in_out_func>,
    EasingFunctionTraits<float, qx::easing::cubic_in_func>,
    EasingFunctionTraits<float, qx::easing::cubic_out_func>,
    EasingFunctionTraits<float, qx::easing::cubic_in_out_func>,
    EasingFunctionTraits<float, qx::easing::quartic_in_func>,
    EasingFunctionTraits<float, qx::easing::quartic_out_func>,
    EasingFunctionTraits<float, qx::easing::quartic_in_out_func>,
    EasingFunctionTraits<float, qx::easing::quintic_in_func>,
    EasingFunctionTraits<float, qx::easing::quintic_out_func>,
    EasingFunctionTraits<float, qx::easing::quintic_in_out_func>,
    EasingFunctionTraits<float, qx::easing::sine_in_func>,
    EasingFunctionTraits<float, qx::easing::sine_out_func>,
    EasingFunctionTraits<float, qx::easing::sine_in_out_func>,
    EasingFunctionTraits<float, qx::easing::circular_in_func>,
    EasingFunctionTraits<float, qx::easing::circular_out_func>,
    EasingFunctionTraits<float, qx::easing::circular_in_out_func>,
    EasingFunctionTraits<float, qx::easing::exponential_in_func>,
    EasingFunctionTraits<float, qx::easing::exponential_out_func>,
    EasingFunctionTraits<float, qx::easing::exponential_in_out_func>,
    EasingFunctionTraits<float, qx::easing::elastic_in_func>,
    EasingFunctionTraits<float, qx::easing::elastic_out_func>,
    EasingFunctionTraits<float, qx::easing::elastic_in_out_func>,
    EasingFunctionTraits<float, qx::easing::back_in_func>,
    EasingFunctionTraits<float, qx::easing::back_out_func>,
    EasingFunctionTraits<float, qx::easing::back_in_out_func>,
    EasingFunctionTraits<float, qx::easing::bounce_out_func>,
    EasingFunctionTraits<float, qx::easing::bounce_in_func>,
    EasingFunctionTraits<float, qx::easing::bounce_in_out_func>,

    EasingFunctionTraits<double, qx::easing::linear_func>,
    EasingFunctionTraits<double, qx::easing::step_func>,
    EasingFunctionTraits<double, qx::easing::smooth_step_func>,
    EasingFunctionTraits<double, qx::easing::smoother_step_func>,
    EasingFunctionTraits<double, qx::easing::quadratic_in_func>,
    EasingFunctionTraits<double, qx::easing::quadratic_out_func>,
    EasingFunctionTraits<double, qx::easing::quadratic_in_out_func>,
    EasingFunctionTraits<double, qx::easing::cubic_in_func>,
    EasingFunctionTraits<double, qx::easing::cubic_out_func>,
    EasingFunctionTraits<double, qx::easing::cubic_in_out_func>,
    EasingFunctionTraits<double, qx::easing::quartic_in_func>,
    EasingFunctionTraits<double, qx::easing::quartic_out_func>,
    EasingFunctionTraits<double, qx::easing::quartic_in_out_func>,
    EasingFunctionTraits<double, qx::easing::quintic_in_func>,
    EasingFunctionTraits<double, qx::easing::quintic_out_func>,
    EasingFunctionTraits<double, qx::easing::quintic_in_out_func>,
    EasingFunctionTraits<double, qx::easing::sine_in_func>,
    EasingFunctionTraits<double, qx::easing::sine_out_func>,
    EasingFunctionTraits<double, qx::easing::sine_in_out_func>,
    EasingFunctionTraits<double, qx::easing::circular_in_func>,
    EasingFunctionTraits<double, qx::easing::circular_out_func>,
    EasingFunctionTraits<double, qx::easing::circular_in_out_func>,
    EasingFunctionTraits<double, qx::easing::exponential_in_func>,
    EasingFunctionTraits<double, qx::easing::exponential_out_func>,
    EasingFunctionTraits<double, qx::easing::exponential_in_out_func>,
    EasingFunctionTraits<double, qx::easing::elastic_in_func>,
    EasingFunctionTraits<double, qx::easing::elastic_out_func>,
    EasingFunctionTraits<double, qx::easing::elastic_in_out_func>,
    EasingFunctionTraits<double, qx::easing::back_in_func>,
    EasingFunctionTraits<double, qx::easing::back_out_func>,
    EasingFunctionTraits<double, qx::easing::back_in_out_func>,
    EasingFunctionTraits<double, qx::easing::bounce_out_func>,
    EasingFunctionTraits<double, qx::easing::bounce_in_func>,
    EasingFunctionTraits<double, qx::easing::bounce_in_out_func>,

    EasingFunctionTraits<long double, qx::easing::linear_func>,
    EasingFunctionTraits<long double, qx::easing::step_func>,
    EasingFunctionTraits<long double, qx::easing::smooth_step_func>,
    EasingFunctionTraits<long double, qx::easing::smoother_step_func>,
    EasingFunctionTraits<long double, qx::easing::quadratic_in_func>,
    EasingFunctionTraits<long double, qx::easing::quadratic_out_func>,
    EasingFunctionTraits<long double, qx::easing::quadratic_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::cubic_in_func>,
    EasingFunctionTraits<long double, qx::easing::cubic_out_func>,
    EasingFunctionTraits<long double, qx::easing::cubic_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::quartic_in_func>,
    EasingFunctionTraits<long double, qx::easing::quartic_out_func>,
    EasingFunctionTraits<long double, qx::easing::quartic_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::quintic_in_func>,
    EasingFunctionTraits<long double, qx::easing::quintic_out_func>,
    EasingFunctionTraits<long double, qx::easing::quintic_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::sine_in_func>,
    EasingFunctionTraits<long double, qx::easing::sine_out_func>,
    EasingFunctionTraits<long double, qx::easing::sine_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::circular_in_func>,
    EasingFunctionTraits<long double, qx::easing::circular_out_func>,
    EasingFunctionTraits<long double, qx::easing::circular_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::exponential_in_func>,
    EasingFunctionTraits<long double, qx::easing::exponential_out_func>,
    EasingFunctionTraits<long double, qx::easing::exponential_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::elastic_in_func>,
    EasingFunctionTraits<long double, qx::easing::elastic_out_func>,
    EasingFunctionTraits<long double, qx::easing::elastic_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::back_in_func>,
    EasingFunctionTraits<long double, qx::easing::back_out_func>,
    EasingFunctionTraits<long double, qx::easing::back_in_out_func>,
    EasingFunctionTraits<long double, qx::easing::bounce_out_func>,
    EasingFunctionTraits<long double, qx::easing::bounce_in_func>,
    EasingFunctionTraits<long double, qx::easing::bounce_in_out_func>
>;

TYPED_TEST_SUITE(TestEasingFunctions, Implementations);

TYPED_TEST(TestEasingFunctions, x_zero)
{
    EXPECT_TRUE(qx::meta::epsilon_equal(
        TypeParam::CallEasingFunc(TypeParam::Type(0.f)),
        TypeParam::Type(0.f),
        qx::easing::eps<typename TypeParam::Type>()));
}

TYPED_TEST(TestEasingFunctions, x_one)
{
    EXPECT_TRUE(qx::meta::epsilon_equal(
        TypeParam::CallEasingFunc(TypeParam::Type(1.f)),
        TypeParam::Type(1.f),
        qx::easing::eps<typename TypeParam::Type>()));
}

TYPED_TEST(TestEasingFunctions, try_calc)
{
    constexpr typename TypeParam::Type step(0.001f);

    volatile typename TypeParam::Type sum_to_avoid_optimizing_out(0.f);
    for (typename TypeParam::Type x = 0.0;
        qx::meta::epsilon_less_equal(x, TypeParam::Type(1.f));
        x += step)
    {
        // check there are no divides on zero and other calc errors
        sum_to_avoid_optimizing_out = sum_to_avoid_optimizing_out + TypeParam::CallEasingFunc(x);
    }
}

#endif
