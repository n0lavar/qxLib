/**

    @file      test_math_common.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_math_common.cpp

#include <qx/macros/static_assert.h>
#include <qx/math/common.h>

// ---------------------------------- qx::abs ----------------------------------

QX_STATIC_ASSERT_EQ(qx::abs(1), 1);
QX_STATIC_ASSERT_EQ(qx::abs(2), 2);
QX_STATIC_ASSERT_EQ(qx::abs(3), 3);
QX_STATIC_ASSERT_EQ(qx::abs(4), 4);
QX_STATIC_ASSERT_EQ(qx::abs(-1), 1);
QX_STATIC_ASSERT_EQ(qx::abs(-2), 2);
QX_STATIC_ASSERT_EQ(qx::abs(-3), 3);
QX_STATIC_ASSERT_EQ(qx::abs(-4), 4);

// ----------------------------- qx::epsilon_equal -----------------------------

static_assert(qx::epsilon_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.45, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.48, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.49, 0.1));
static_assert(!qx::epsilon_equal(0.5, 0.39, 0.1));

// ------------------------------ qx::epsilon_zero -----------------------------

static_assert(qx::epsilon_zero(0.0));
static_assert(qx::epsilon_zero(0.f));
static_assert(!qx::epsilon_zero(0.1));
static_assert(!qx::epsilon_zero(1.0));

// --------------------------- qx::epsilon_less_equal --------------------------

static_assert(qx::epsilon_less_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_less_equal(0.2, 0.45, 0.1));
static_assert(qx::epsilon_less_equal(0.0, 0.48, 0.1));
static_assert(!qx::epsilon_less_equal(0.5, 0.2, 0.1));
static_assert(!qx::epsilon_less_equal(0.5, 0.39, 0.1));

// ------------------------- qx::epsilon_greater_equal -------------------------

static_assert(qx::epsilon_greater_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_greater_equal(0.5, 0.45, 0.1));
static_assert(qx::epsilon_greater_equal(0.5, 0.3, 0.1));
static_assert(!qx::epsilon_greater_equal(0.2, 0.49, 0.1));
static_assert(!qx::epsilon_greater_equal(0.0, 0.39, 0.1));

// --------------------------------- qx::is_odd --------------------------------

static_assert(qx::is_odd(-9));
static_assert(!qx::is_odd(-8));
static_assert(qx::is_odd(-7));
static_assert(!qx::is_odd(-6));
static_assert(qx::is_odd(-5));
static_assert(!qx::is_odd(-4));
static_assert(qx::is_odd(-3));
static_assert(!qx::is_odd(-2));
static_assert(qx::is_odd(-1));
static_assert(!qx::is_odd(0));
static_assert(qx::is_odd(1));
static_assert(!qx::is_odd(2));
static_assert(qx::is_odd(3));
static_assert(!qx::is_odd(4));
static_assert(qx::is_odd(5));
static_assert(!qx::is_odd(6));
static_assert(qx::is_odd(7));
static_assert(!qx::is_odd(8));
static_assert(qx::is_odd(9));

// -------------------------------- qx::is_even --------------------------------

static_assert(!qx::is_even(-9));
static_assert(qx::is_even(-8));
static_assert(!qx::is_even(-7));
static_assert(qx::is_even(-6));
static_assert(!qx::is_even(-5));
static_assert(qx::is_even(-4));
static_assert(!qx::is_even(-3));
static_assert(qx::is_even(-2));
static_assert(!qx::is_even(-1));
static_assert(qx::is_even(0));
static_assert(!qx::is_even(1));
static_assert(qx::is_even(2));
static_assert(!qx::is_even(3));
static_assert(qx::is_even(4));
static_assert(!qx::is_even(5));
static_assert(qx::is_even(6));
static_assert(!qx::is_even(7));
static_assert(qx::is_even(8));
static_assert(!qx::is_even(9));

//--------------------------------- qx::between --------------------------------

// unscoped enum
enum Enum
{
    E_0,
    E_1,
    E_2,
    E_3,
    E_4,
    E_5,
    E_6,
};

static_assert(!qx::between(E_1, E_0, E_5));
static_assert(qx::between(E_1, E_1, E_5));
static_assert(qx::between(E_1, E_2, E_5));
static_assert(qx::between(E_1, E_3, E_5));
static_assert(qx::between(E_1, E_4, E_5));
static_assert(qx::between(E_1, E_5, E_5));
static_assert(!qx::between(E_1, E_6, E_5));


// scoped enum
enum class EnumClass
{
    e0,
    e1,
    e2,
    e3,
    e4,
    e5,
    e6,
};

static_assert(!qx::between(EnumClass::e1, EnumClass::e0, EnumClass::e5));
static_assert(qx::between(EnumClass::e1, EnumClass::e1, EnumClass::e5));
static_assert(qx::between(EnumClass::e1, EnumClass::e2, EnumClass::e5));
static_assert(qx::between(EnumClass::e1, EnumClass::e3, EnumClass::e5));
static_assert(qx::between(EnumClass::e1, EnumClass::e4, EnumClass::e5));
static_assert(qx::between(EnumClass::e1, EnumClass::e5, EnumClass::e5));
static_assert(!qx::between(EnumClass::e1, EnumClass::e6, EnumClass::e5));


// integral
static_assert(!qx::between(0, -1, 5));
static_assert(qx::between(0, 0, 5));
static_assert(qx::between(0, 1, 5));
static_assert(qx::between(0, 2, 5));
static_assert(qx::between(0, 3, 5));
static_assert(qx::between(0, 4, 5));
static_assert(qx::between(0, 5, 5));
static_assert(!qx::between(0, 6, 5));


// floating point
static_assert(!qx::between(0.0, -0.2, 1.0));
static_assert(qx::between(0.0, 0.0, 1.0));
static_assert(qx::between(0.0, 0.2, 1.0));
static_assert(qx::between(0.0, 0.4, 1.0));
static_assert(qx::between(0.0, 0.6, 1.0));
static_assert(qx::between(0.0, 0.8, 1.0));
static_assert(qx::between(0.0, 1.0, 1.0));
static_assert(!qx::between(0.0, 1.2, 1.0));

TEST(math_common, gcd)
{
    ASSERT_EQ(qx::gcd(0, 0), 0);
    ASSERT_EQ(qx::gcd(0, 1), 0);
    ASSERT_EQ(qx::gcd(0, 10), 0);
    ASSERT_EQ(qx::gcd(1, 0), 0);
    ASSERT_EQ(qx::gcd(10, 0), 0);
    ASSERT_EQ(qx::gcd(10, 10), 10);
    ASSERT_EQ(qx::gcd(-10, 10), 10);
    ASSERT_EQ(qx::gcd(10, -10), 10);
    ASSERT_EQ(qx::gcd(-10, -10), 10);
    ASSERT_EQ(qx::gcd(15, 3), 3);
    ASSERT_EQ(qx::gcd(3, 15), 3);
    ASSERT_EQ(qx::gcd(-12, -10), 2);
    ASSERT_EQ(qx::gcd(-10, 12), 2);
    ASSERT_EQ(qx::gcd(17, 3), 1);
    ASSERT_EQ(qx::gcd(17, 1), 1);
    ASSERT_EQ(qx::gcd(-17, -16), 1);
    ASSERT_EQ(qx::gcd(-7, 1), 1);
}

TEST(math_common, lcm)
{
    ASSERT_EQ(qx::lcm(0, 0), 0);
    ASSERT_EQ(qx::lcm(0, 1), 0);
    ASSERT_EQ(qx::lcm(0, 10), 0);
    ASSERT_EQ(qx::lcm(1, 0), 0);
    ASSERT_EQ(qx::lcm(10, 0), 0);
    ASSERT_EQ(qx::lcm(10, 10), 10);
    ASSERT_EQ(qx::lcm(-10, 10), 10);
    ASSERT_EQ(qx::lcm(10, -10), 10);
    ASSERT_EQ(qx::lcm(-10, -10), 10);
    ASSERT_EQ(qx::lcm(15, 3), 15);
    ASSERT_EQ(qx::lcm(3, 15), 15);
    ASSERT_EQ(qx::lcm(-12, -10), 60);
    ASSERT_EQ(qx::lcm(-10, 12), 60);
    ASSERT_EQ(qx::lcm(17, 3), 51);
    ASSERT_EQ(qx::lcm(17, 1), 17);
    ASSERT_EQ(qx::lcm(-17, -16), 272);
    ASSERT_EQ(qx::lcm(-7, 1), 7);
}

TEST(math_common, pow)
{
    ASSERT_DOUBLE_EQ(qx::pow(0, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(-1, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(5, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, 1), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, 5), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, -5), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, -1), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(4, 5), 1024.0);
    ASSERT_DOUBLE_EQ(qx::pow(4, -5), 0.0009765625);
}

TEST(math_common, maxpot)
{
    ASSERT_EQ(qx::maxpot(0), 0);
    ASSERT_EQ(qx::maxpot(1), 0);
    ASSERT_EQ(qx::maxpot(-1), 0);
    ASSERT_EQ(qx::maxpot(2), 1);
    ASSERT_EQ(qx::maxpot(-2), 1);
    ASSERT_EQ(qx::maxpot(3), 1);
    ASSERT_EQ(qx::maxpot(4), 2);
    ASSERT_EQ(qx::maxpot(7), 2);
    ASSERT_EQ(qx::maxpot(8), 3);
    ASSERT_EQ(qx::maxpot(17), 4);
}
