/**

    @file      test_moving_average.cpp
    @author    Khrapov
    @date      1.06.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_moving_average.cpp

#if QX_TEST_MOVING_AVERAGE

#include <qx/stat/moving_average.h>

#include <qx/math.h>

#include <array>
#include <iomanip>
#include <limits>
#include <numeric>

template<
    typename T,
    size_t         ENTRIES,
    size_t         START_VALUE,
    std::vector<T> FUNC(size_t nEntries)>
class MovingAverageTraits
{
public:
    using type                        = T;
    static constexpr auto nEntries    = ENTRIES;
    static constexpr auto fStartValue = START_VALUE;
    static constexpr auto func        = FUNC;
};

template<typename Traits>
class TestMovingAverageClass : public ::testing::Test
{
protected:
    /* init protected members here */
    TestMovingAverageClass()
        : m_MovingAverage(Traits::nEntries, Traits::fStartValue, Traits::func)
    {
    }

    /* called before every test */
    void SetUp() override
    {
    }

    /* called after every test */
    void TearDown() override
    {
    }

protected:
    qx::moving_average<typename Traits::type> m_MovingAverage;
};

using Implementations = ::testing::Types<
    MovingAverageTraits<
        float,
        10,
        0,
        qx::get_moving_average_simple_weights<float>>,
    MovingAverageTraits<
        float,
        10,
        0,
        qx::get_moving_average_linear_weights<float>>,
    MovingAverageTraits<
        float,
        10,
        0,
        qx::get_moving_average_exp_weights<float>>,

    MovingAverageTraits<
        float,
        15,
        0,
        qx::get_moving_average_simple_weights<float>>,
    MovingAverageTraits<
        float,
        15,
        0,
        qx::get_moving_average_linear_weights<float>>,
    MovingAverageTraits<
        float,
        15,
        0,
        qx::get_moving_average_exp_weights<float>>,

    MovingAverageTraits<
        double,
        10,
        0,
        qx::get_moving_average_simple_weights<double>>,
    MovingAverageTraits<
        double,
        10,
        0,
        qx::get_moving_average_linear_weights<double>>,
    MovingAverageTraits<
        double,
        10,
        0,
        qx::get_moving_average_exp_weights<double>>,

    MovingAverageTraits<
        double,
        15,
        0,
        qx::get_moving_average_simple_weights<double>>,
    MovingAverageTraits<
        double,
        15,
        0,
        qx::get_moving_average_linear_weights<double>>,
    MovingAverageTraits<
        double,
        15,
        0,
        qx::get_moving_average_exp_weights<double>>>;

TYPED_TEST_SUITE(TestMovingAverageClass, Implementations);

TYPED_TEST(TestMovingAverageClass, weights_sum)
{
    const auto weights = TypeParam::func(TypeParam::nEntries);
    const auto fSumm   = std::accumulate(
        weights.cbegin(),
        weights.cend(),
        typename TypeParam::type(0.f));
    EXPECT_TRUE(qx::epsilon_equal(
        typename TypeParam::type(1.f),
        fSumm,
        typename TypeParam::type(0.000001f)));
}

TYPED_TEST(TestMovingAverageClass, values)
{
    constexpr float fLowerBound = -5.f;
    constexpr float fUpperBound = 5.f;

    // generated by qx::random(fLowerBound, fUpperBound)
    constexpr std::array values {
        -0.246858119964599609375f,  -3.8619120121002197265625f,
        -1.9051692485809326171875f, 0.807511806488037109375f,
        -4.016750812530517578125f,  4.8727092742919921875f,
        1.9572658538818359375f,     -3.2410314083099365234375f,
        1.3986148834228515625f,     0.652375698089599609375f,
        1.061019420623779296875f,   4.963634490966796875f,
        3.29406642913818359375f,    -3.274301052093505859375f,
        -3.18559932708740234375f,   1.38341045379638671875f,
        1.851825714111328125f,      -4.91829395294189453125f,
        -4.24566650390625f,         4.6774921417236328125f
    };

    for (size_t i = 0; i < values.size(); ++i)
    {
        const typename TypeParam::type fValue = values[i];
        const typename TypeParam::type fAverage =
            TestFixture::m_MovingAverage.update(fValue);

        EXPECT_TRUE(
            qx::epsilon_equal(fAverage, TestFixture::m_MovingAverage.get()));

        EXPECT_GE(fAverage, fLowerBound);
        EXPECT_LE(fAverage, fUpperBound);

#if 0
        std::cout
            << std::setw(30) << std::setprecision(std::numeric_limits<typename TypeParam::type>::digits) << fValue
            << std::setw(30) << std::setprecision(std::numeric_limits<typename TypeParam::type>::digits) << fAverage
            << std::endl;
#endif
    }
}

#endif