/**

    @file      test_triangular_vector.cpp
    @author    Khrapov
    @date      26.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_triangular_vector.cpp

#if QX_TEST_TRIANGULAR_VECTOR

    #include <qx/containers/triangular_vector.h>
    #include <algorithm>


TEST(TestQxTriangularVector, constructing)
{
    auto check_empty = [](const qx::triangular_vector<int>& v)
    {
        EXPECT_TRUE(v.empty());
        EXPECT_EQ(v.size(), 0);
        EXPECT_EQ(v.size_side(), 0);
    };

    auto check_full = [](const qx::triangular_vector<int>& v)
    {
        EXPECT_FALSE(v.empty());
        EXPECT_EQ(v.size(), 15);
        EXPECT_EQ(v.size_side(), 5);
        EXPECT_TRUE(std::all_of(
            v.cbegin(),
            v.cend(),
            [](auto val)
            {
                return val == 2;
            }));
    };

    {
        qx::triangular_vector<int> vec0;
        check_empty(vec0);

        qx::triangular_vector<int> vec1(5, 2);
        check_full(vec1);

        qx::triangular_vector<int> vec2(vec1);
        check_full(vec1);
        check_full(vec2);

        qx::triangular_vector<int> vec3(std::move(vec1));
        check_empty(vec1);
        check_full(vec3);
    }

    {
        qx::triangular_vector<int> vec1;
        vec1.assign(5, 2);
        check_full(vec1);

        qx::triangular_vector<int> vec2;
        vec2.assign(vec1);
        check_full(vec1);
        check_full(vec2);

        qx::triangular_vector<int> vec3;
        vec3.assign(std::move(vec1));
        check_empty(vec1);
        check_full(vec3);
    }

    {
        qx::triangular_vector<int> vec1;
        vec1.assign(5, 2);
        check_full(vec1);

        qx::triangular_vector<int> vec2 = vec1;
        check_full(vec1);
        check_full(vec2);

        qx::triangular_vector<int> vec3 = std::move(vec1);
        check_empty(vec1);
        check_full(vec3);
    }
}

TEST(TestQxTriangularVector, size)
{
    qx::triangular_vector<int> vec1;
    EXPECT_TRUE(vec1.empty());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_side(), 0);
    EXPECT_EQ(vec1.capacity(), 0);

    vec1.reserve(5);
    EXPECT_TRUE(vec1.empty());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_side(), 0);
    EXPECT_EQ(vec1.capacity(), 15);

    vec1.resize(5);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1.size_side(), 5);
    EXPECT_EQ(vec1.capacity(), 15);

    vec1.reserve(6);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1.size_side(), 5);
    EXPECT_EQ(vec1.capacity(), 21);

    vec1.reserve(3);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1.size_side(), 5);
    EXPECT_EQ(vec1.capacity(), 21);

    vec1.resize(7);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 28);
    EXPECT_EQ(vec1.size_side(), 7);
    EXPECT_EQ(vec1.capacity(), 28);

    vec1.clear();
    EXPECT_TRUE(vec1.empty());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_side(), 0);
    EXPECT_EQ(vec1.capacity(), 28);
    EXPECT_TRUE(vec1.data());

    vec1.free();
    EXPECT_TRUE(vec1.empty());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_side(), 0);
    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_FALSE(vec1.data());
}

TEST(TestQxTriangularVector, access)
{
    qx::triangular_vector<int> vec1(4);
    for (size_t i = 0; i < vec1.size_side(); i++)
        for (size_t j = 0; j <= i; j++)
            vec1.set(i, j, static_cast<int>(i + j));

    EXPECT_EQ(vec1.get(0, 0), 0);
    EXPECT_EQ(vec1.get(0, 1), 1);
    EXPECT_EQ(vec1.get(0, 2), 2);
    EXPECT_EQ(vec1.get(0, 3), 3);
    EXPECT_EQ(vec1.get(1, 0), 1);
    EXPECT_EQ(vec1.get(1, 1), 2);
    EXPECT_EQ(vec1.get(1, 2), 3);
    EXPECT_EQ(vec1.get(1, 3), 4);
    EXPECT_EQ(vec1.get(2, 0), 2);
    EXPECT_EQ(vec1.get(2, 1), 3);
    EXPECT_EQ(vec1.get(2, 2), 4);
    EXPECT_EQ(vec1.get(2, 3), 5);
    EXPECT_EQ(vec1.get(3, 0), 3);
    EXPECT_EQ(vec1.get(3, 1), 4);
    EXPECT_EQ(vec1.get(3, 2), 5);
    EXPECT_EQ(vec1.get(3, 3), 6);
}

#endif
