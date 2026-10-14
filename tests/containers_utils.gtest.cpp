/**

    @file      containers_utils.gtest.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

#include <qx/containers/utils.h>

#include <list>

//V_EXCLUDE_PATH *.gtest.cpp

//-------------------------------- qx::destruct --------------------------------

struct DestructChecker
{
    DestructChecker()
    {
        s_nCounter++;
    }
    ~DestructChecker()
    {
        s_nCounter--;
    }

    static int s_nCounter;
};

int DestructChecker::s_nCounter = 0;

TEST(containers_utils, destruct)
{
    std::vector<DestructChecker> v(3);
    ASSERT_EQ(DestructChecker::s_nCounter, 3);

    qx::destruct(v.begin(), v.end() - 1);
    ASSERT_EQ(DestructChecker::s_nCounter, 1);
}

//------------------------------- qx::make_array -------------------------------

constexpr auto k_TestArray1 = qx::make_array<5>(1);
static_assert(std::all_of(
    k_TestArray1.cbegin(),
    k_TestArray1.cend(),
    [](int val)
    {
        return val == 1;
    }));
static_assert(k_TestArray1.size() == 5);

// ------------------------------ qx::join_arrays ------------------------------

constexpr std::array k_First { 0, 1, 2, 3 };
constexpr std::array k_Second { 4, 5, 6, 7 };
constexpr auto       k_Result = qx::join_arrays(k_First, k_Second);
static_assert(k_Result == std::array<int, 8> { 0, 1, 2, 3, 4, 5, 6, 7 });

TEST(containers_utils, create_container)
{
    constexpr std::array   array { 0, 1, 2, 3, 4 };
    const std::vector<int> vector = qx::make_container<std::vector<int>>(array);

    EXPECT_EQ(vector.size(), array.size());
    for (size_t i = 0; i < array.size(); ++i)
        EXPECT_EQ(vector[i], array[i]);
}

TEST(containers_utils, bytes_size)
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
