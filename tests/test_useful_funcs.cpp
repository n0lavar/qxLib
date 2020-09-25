//==============================================================================
//
//!\file                     test_useful_funcs.cpp
//
//!\brief       Tests for functions from useful_funcs.h
//!\details     ~
//
//!\author      Khrapov
//!\date        23.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <qx/other/useful_macros.h>
#include <qx/containers/container.h>
#include <gtest/gtest.h>

 //V_EXCLUDE_PATH *test_useful_funcs.cpp


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
static_assert( qx::between(E_1, E_1, E_5));
static_assert( qx::between(E_1, E_2, E_5));
static_assert( qx::between(E_1, E_3, E_5));
static_assert( qx::between(E_1, E_4, E_5));
static_assert( qx::between(E_1, E_5, E_5));
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
static_assert( qx::between(EnumClass::e1, EnumClass::e1, EnumClass::e5));
static_assert( qx::between(EnumClass::e1, EnumClass::e2, EnumClass::e5));
static_assert( qx::between(EnumClass::e1, EnumClass::e3, EnumClass::e5));
static_assert( qx::between(EnumClass::e1, EnumClass::e4, EnumClass::e5));
static_assert( qx::between(EnumClass::e1, EnumClass::e5, EnumClass::e5));
static_assert(!qx::between(EnumClass::e1, EnumClass::e6, EnumClass::e5));


// integral
static_assert(!qx::between(0, -1, 5));
static_assert( qx::between(0, 0, 5));
static_assert( qx::between(0, 1, 5));
static_assert( qx::between(0, 2, 5));
static_assert( qx::between(0, 3, 5));
static_assert( qx::between(0, 4, 5));
static_assert( qx::between(0, 5, 5));
static_assert(!qx::between(0, 6, 5));


// floating point
static_assert(!qx::between(0.0, -0.2, 1.0));
static_assert( qx::between(0.0,  0.0, 1.0));
static_assert( qx::between(0.0,  0.2, 1.0));
static_assert( qx::between(0.0,  0.4, 1.0));
static_assert( qx::between(0.0,  0.6, 1.0));
static_assert( qx::between(0.0,  0.8, 1.0));
static_assert( qx::between(0.0,  1.0, 1.0));
static_assert(!qx::between(0.0,  1.2, 1.0));



//--------------------------------- qx::step_to --------------------------------

QX_STATIC_ASSERT_EQ(qx::step_to(0, 5), 1);
QX_STATIC_ASSERT_EQ(qx::step_to(1, 5), 2);
QX_STATIC_ASSERT_EQ(qx::step_to(2, 5), 3);
QX_STATIC_ASSERT_EQ(qx::step_to(3, 5), 4);
QX_STATIC_ASSERT_EQ(qx::step_to(4, 5), 5);
QX_STATIC_ASSERT_EQ(qx::step_to(5, 5), 5);
QX_STATIC_ASSERT_EQ(qx::step_to(6, 5), 5);
QX_STATIC_ASSERT_EQ(qx::step_to(7, 5), 6);
QX_STATIC_ASSERT_EQ(qx::step_to(8, 5), 7);
QX_STATIC_ASSERT_EQ(qx::step_to(9, 5), 8);



//-------------------------------- qx::destruct --------------------------------

struct DestructChecker
{
     DestructChecker() { counter++; }
    ~DestructChecker() { counter--; }

    static int counter;
};

int DestructChecker::counter = 0;

TEST(useful_funcs, destruct)
{
    std::vector<DestructChecker> v(3);
    ASSERT_EQ(DestructChecker::counter, 3);

    qx::destruct(v.begin(), v.end() - 1);
    ASSERT_EQ(DestructChecker::counter, 1);
}