/**

    @file      test_useful_funcs.cpp
    @author    Khrapov
    @date      23.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_useful_funcs.cpp

#if QX_TEST_USEFUL_FUNCS

    #include <qx/containers/container.h>
    #include <qx/useful_macros.h>

    #include <algorithm>
    #include <array>
    #include <list>
    #include <vector>

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



//-------------------------------- qx::destruct --------------------------------

struct DestructChecker
{
    DestructChecker()
    {
        counter++;
    }
    ~DestructChecker()
    {
        counter--;
    }

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

//------------------------------- qx::make_array -------------------------------

constexpr auto TEST_ARRAY_1 = qx::make_array<5>(1);
static_assert(std::all_of(
    TEST_ARRAY_1.cbegin(),
    TEST_ARRAY_1.cend(),
    [](int val)
    {
        return val == 1;
    }));
static_assert(TEST_ARRAY_1.size() == 5);

// ------------------------------ qx::join_arrays ------------------------------

constexpr std::array first { 0, 1, 2, 3 };
constexpr std::array second { 4, 5, 6, 7 };
constexpr auto       result = qx::join_arrays(first, second);
static_assert(result == std::array<int, 8> { 0, 1, 2, 3, 4, 5, 6, 7 });

TEST(useful_funcs, create_container)
{
    constexpr std::array   array { 0, 1, 2, 3, 4 };
    const std::vector<int> vector = qx::create_container<std::vector<int>>(array);

    EXPECT_EQ(vector.size(), array.size());
    for (size_t i = 0; i < array.size(); ++i)
        EXPECT_EQ(vector[i], array[i]);
}

TEST(useful_funcs, bytes_size)
{
    const std::array<int, 1000> array { 0 };
    EXPECT_EQ(qx::bytes_size(array), 4000);

    const std::vector<int> vector(2000);
    EXPECT_EQ(qx::bytes_size(vector), 8000);

    std::list<int> list;
    for (size_t i = 0; i < 500; ++i)
        list.push_back(0);
    EXPECT_EQ(qx::bytes_size(list), 2000);
}

#endif
