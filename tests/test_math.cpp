/**

    @file      test_math.cpp
    @author    Khrapov
    @date      27.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_math.cpp

#if QX_TEST_MATH

#include <qx/math.h>
#include <qx/useful_funcs.h>
#include <qx/useful_macros.h>

//-------------------------------- qx::meta::abs -------------------------------

QX_STATIC_ASSERT_EQ(qx::abs(1), 1);
QX_STATIC_ASSERT_EQ(qx::abs(2), 2);
QX_STATIC_ASSERT_EQ(qx::abs(3), 3);
QX_STATIC_ASSERT_EQ(qx::abs(4), 4);
QX_STATIC_ASSERT_EQ(qx::abs(-1), 1);
QX_STATIC_ASSERT_EQ(qx::abs(-2), 2);
QX_STATIC_ASSERT_EQ(qx::abs(-3), 3);
QX_STATIC_ASSERT_EQ(qx::abs(-4), 4);



//--------------------------- qx::meta::epsilon_equal --------------------------

static_assert(qx::epsilon_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.45, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.48, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.49, 0.1));
static_assert(!qx::epsilon_equal(0.5, 0.39, 0.1));

//------------------------ qx::meta::epsilon_less_equal ------------------------

static_assert(qx::epsilon_less_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_less_equal(0.2, 0.45, 0.1));
static_assert(qx::epsilon_less_equal(0.0, 0.48, 0.1));
static_assert(!qx::epsilon_less_equal(0.5, 0.2, 0.1));
static_assert(!qx::epsilon_less_equal(0.5, 0.39, 0.1));

//----------------------- qx::meta::epsilon_greater_equal ----------------------

static_assert(qx::epsilon_greater_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_greater_equal(0.5, 0.45, 0.1));
static_assert(qx::epsilon_greater_equal(0.5, 0.3, 0.1));
static_assert(!qx::epsilon_greater_equal(0.2, 0.49, 0.1));
static_assert(!qx::epsilon_greater_equal(0.0, 0.39, 0.1));


template<typename T>
void TestRandom(T min, T max, size_t nIterations)
{
    for (size_t i = 0; i < nIterations; i++)
        ASSERT_TRUE(qx::between(min, qx::random(min, max), max));
}

TEST(random, random)
{
    constexpr size_t NUM_TESTS = 100000;

    TestRandom(0, 100, NUM_TESTS);
    TestRandom(-100, 100, NUM_TESTS);
    TestRandom(0u, 100u, NUM_TESTS);
    TestRandom(0.f, 100.f, NUM_TESTS);
    TestRandom(-100.f, 100.f, NUM_TESTS);
    TestRandom(0.0, 100.0, NUM_TESTS);
    TestRandom(-100.0, 100.0, NUM_TESTS);
}

#endif
