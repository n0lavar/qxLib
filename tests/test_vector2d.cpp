//==============================================================================
//
//!\file                      test_vector2d.cpp
//
//!\brief       
//!\details     ~
//
//!\author      Khrapov
//!\date        25.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <config.h>

//V_EXCLUDE_PATH *test_vector2d.cpp

#if QX_TEST_VECTOR2D

#include <qx/containers/vector2d.h>
#include <gtest/gtest.h>
#include <array>

TEST(TestQxVector2d, constructing)
{
    auto check_empty = [] (const qx::vector2d<int>& v)
    {
        EXPECT_TRUE(v.empty());
        EXPECT_EQ(v.size(), 0);
        EXPECT_EQ(v.size_x(), 0);
        EXPECT_EQ(v.size_y(), 0);
        EXPECT_EQ(v.rows(), 0);
        EXPECT_EQ(v.cols(), 0);
    };

    auto check_full = [] (const qx::vector2d<int>& v)
    {
        EXPECT_FALSE(v.empty());
        EXPECT_EQ(v.size(), 20);
        EXPECT_EQ(v.size_x(), 5);
        EXPECT_EQ(v.size_y(), 4);
        EXPECT_EQ(v.rows(), 5);
        EXPECT_EQ(v.cols(), 4);
        EXPECT_TRUE(std::all_of(v.cbegin(), v.cend(), [] (auto val) { return val == 2; }));
    };

    {
        qx::vector2d<int> vec0;
        check_empty(vec0);

        qx::vector2d<int> vec1(5, 4, 2);
        check_full(vec1);

        qx::vector2d<int> vec2(vec1);
        check_full(vec1);
        check_full(vec2);

        qx::vector2d<int> vec3(std::move(vec1));
        check_empty(vec1);
        check_full(vec3);

        std::array<int, 20> arr;
        arr.fill(2);
        qx::vector2d<int> vec4(5, 4, arr.data());
        check_full(vec4);
    }

    {
        qx::vector2d<int> vec1;
        vec1.assign(5, 4, 2);
        check_full(vec1);

        qx::vector2d<int> vec2;
        vec2.assign(vec1);
        check_full(vec1);
        check_full(vec2);

        qx::vector2d<int> vec3;
        vec3.assign(std::move(vec1));
        check_empty(vec1);
        check_full(vec3);

        std::array<int, 20> arr;
        arr.fill(2);
        qx::vector2d<int> vec4;
        vec4.assign(5, 4, arr.data());
        check_full(vec4);
    }

    {
        qx::vector2d<int> vec1;
        vec1.assign(5, 4, 2);
        check_full(vec1);

        qx::vector2d<int> vec2 = vec1;
        check_full(vec1);
        check_full(vec2);

        qx::vector2d<int> vec3 = std::move(vec1);
        check_empty(vec1);
        check_full(vec3);
    }
}

TEST(TestQxVector2d, size)
{
    qx::vector2d<int> vec1;
    EXPECT_TRUE(vec1.empty());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_x(), 0);
    EXPECT_EQ(vec1.size_y(), 0);
    EXPECT_EQ(vec1.rows(), 0);
    EXPECT_EQ(vec1.cols(), 0);
    EXPECT_EQ(vec1.capacity(), 0);

    vec1.reserve(22);
    EXPECT_TRUE(vec1.empty());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_x(), 0);
    EXPECT_EQ(vec1.size_y(), 0);
    EXPECT_EQ(vec1.rows(), 0);
    EXPECT_EQ(vec1.cols(), 0);
    EXPECT_EQ(vec1.capacity(), 22);

    vec1.resize(5, 4);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 20);
    EXPECT_EQ(vec1.size_x(), 5);
    EXPECT_EQ(vec1.size_y(), 4);
    EXPECT_EQ(vec1.rows(), 5);
    EXPECT_EQ(vec1.cols(), 4);
    EXPECT_EQ(vec1.capacity(), 22);

    vec1.reserve(15);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 20);
    EXPECT_EQ(vec1.size_x(), 5);
    EXPECT_EQ(vec1.size_y(), 4);
    EXPECT_EQ(vec1.rows(), 5);
    EXPECT_EQ(vec1.cols(), 4);
    EXPECT_EQ(vec1.capacity(), 22);

    vec1.reserve(25);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 20);
    EXPECT_EQ(vec1.size_x(), 5);
    EXPECT_EQ(vec1.size_y(), 4);
    EXPECT_EQ(vec1.rows(), 5);
    EXPECT_EQ(vec1.cols(), 4);
    EXPECT_EQ(vec1.capacity(), 25);

    vec1.resize(3, 4);
    EXPECT_FALSE(vec1.empty());
    EXPECT_EQ(vec1.size(), 12);
    EXPECT_EQ(vec1.size_x(), 3);
    EXPECT_EQ(vec1.size_y(), 4);
    EXPECT_EQ(vec1.rows(), 3);
    EXPECT_EQ(vec1.cols(), 4);
    EXPECT_EQ(vec1.capacity(), 25);

    vec1.clear();
    EXPECT_TRUE(vec1.empty());
    EXPECT_TRUE(vec1.data());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_x(), 0);
    EXPECT_EQ(vec1.size_y(), 0);
    EXPECT_EQ(vec1.rows(), 0);
    EXPECT_EQ(vec1.cols(), 0);
    EXPECT_EQ(vec1.capacity(), 25);

    vec1.free();
    EXPECT_TRUE(vec1.empty());
    EXPECT_FALSE(vec1.data());
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.size_x(), 0);
    EXPECT_EQ(vec1.size_y(), 0);
    EXPECT_EQ(vec1.rows(), 0);
    EXPECT_EQ(vec1.cols(), 0);
    EXPECT_EQ(vec1.capacity(), 0);
}

TEST(TestQxVector2d, access)
{
    auto check = [] (const qx::vector2d<int>& v)
    {
        EXPECT_EQ(v[0][0], 0);
        EXPECT_EQ(v[0][1], 1);
        EXPECT_EQ(v[0][2], 2);
        EXPECT_EQ(v[1][0], 1);
        EXPECT_EQ(v[1][1], 2);
        EXPECT_EQ(v[1][2], 3);
        EXPECT_EQ(v[2][0], 2);
        EXPECT_EQ(v[2][1], 3);
        EXPECT_EQ(v[2][2], 4);
        EXPECT_EQ(v[3][0], 3);
        EXPECT_EQ(v[3][1], 4);
        EXPECT_EQ(v[3][2], 5);

        EXPECT_EQ(v.get(0, 0), 0);
        EXPECT_EQ(v.get(0, 1), 1);
        EXPECT_EQ(v.get(0, 2), 2);
        EXPECT_EQ(v.get(1, 0), 1);
        EXPECT_EQ(v.get(1, 1), 2);
        EXPECT_EQ(v.get(1, 2), 3);
        EXPECT_EQ(v.get(2, 0), 2);
        EXPECT_EQ(v.get(2, 1), 3);
        EXPECT_EQ(v.get(2, 2), 4);
        EXPECT_EQ(v.get(3, 0), 3);
        EXPECT_EQ(v.get(3, 1), 4);
        EXPECT_EQ(v.get(3, 2), 5);
    };

    qx::vector2d<int> vec1(4, 3);
    for (size_t i = 0; i < vec1.rows(); i++)
        for (size_t j = 0; j < vec1.cols(); j++)
            vec1[i][j] = static_cast<int>(i + j);

    check(vec1);

    vec1.resize(4, 3);
    for (size_t i = 0; i < vec1.rows(); i++)
        for (size_t j = 0; j < vec1.cols(); j++)
            vec1.set(i, j, static_cast<int>(i + j));

    check(vec1);
}

#endif