//==============================================================================
//
//!\file                     test_object_pool.cpp
//
//!\brief       test qx::object_pool
//!\details     ~
//
//!\author      Khrapov
//!\date        15.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <config.h>

//V_EXCLUDE_PATH *test_object_pool.cpp

#if QX_TEST_OBJECT_POOL

#include <qx/containers/object_pool.h>
#include <gtest/gtest.h>

TEST(object_pool, testing)
{
    struct TestStruct
    {
        TestStruct() { };
        TestStruct(int n1, int n2, long l1, long l2)
            : m_n1(n1), m_n2(n2), m_l1(l1), m_l2(l2) 
        { 
        }

        bool operator==(const TestStruct& other) const
        {
            return m_n1 == other.m_n1
                && m_n2 == other.m_n2
                && m_l1 == other.m_l1
                && m_l2 == other.m_l2;
        }

        int  m_n1 = 0;
        int  m_n2 = 1;
        long m_l1 = 2;
        long m_l2 = 3;
    };

    qx::object_pool<TestStruct> pool_empty;
    EXPECT_EQ(pool_empty.size(), 0);
    EXPECT_TRUE(pool_empty.empty());

    qx::object_pool<TestStruct> pool(5, 3);
    EXPECT_EQ(pool.size(), 0);
    EXPECT_TRUE(pool.empty());

//------------------------------- emplace_back -------------------------------

    size_t ind1 = pool.emplace_back(1, 1, 1, 1);
    EXPECT_EQ(pool.size(), 1);
    EXPECT_EQ(pool[ind1], TestStruct(1, 1, 1, 1));
    EXPECT_FALSE(pool.empty());

    size_t ind2 = pool.emplace_back(2, 2, 2, 1);
    EXPECT_EQ(pool.size(), 2);
    EXPECT_EQ(pool[ind2], TestStruct(2, 2, 2, 1));
    EXPECT_FALSE(pool.empty());

    size_t ind3 = pool.emplace_back(3, 3, 3, 1);
    EXPECT_EQ(pool.size(), 3);
    EXPECT_EQ(pool[ind3], TestStruct(3, 3, 3, 1));
    EXPECT_FALSE(pool.empty());

    size_t ind4 = pool.emplace_back(4, 4, 4, 1);
    EXPECT_EQ(pool.size(), 4);
    EXPECT_EQ(pool[ind4], TestStruct(4, 4, 4, 1));
    EXPECT_FALSE(pool.empty());

//--------------------------------- push_pack --------------------------------

    size_t ind5 = pool.push_back({ 5, 5, 5, 1 });
    EXPECT_EQ(pool.size(), 5);
    EXPECT_EQ(pool[ind5], TestStruct(5, 5, 5, 1));
    EXPECT_FALSE(pool.empty());

    size_t ind6 = pool.push_back({ 6, 6, 6, 1 });
    EXPECT_EQ(pool.size(), 6);
    EXPECT_EQ(pool[ind6], TestStruct(6, 6, 6, 1));
    EXPECT_FALSE(pool.empty());

    size_t ind7 = pool.push_back({ 7, 7, 7, 1 });
    EXPECT_EQ(pool.size(), 7);
    EXPECT_EQ(pool[ind7], TestStruct(7, 7, 7, 1));
    EXPECT_FALSE(pool.empty());

    size_t ind8 = pool.push_back({ 8, 8, 8, 1 });
    EXPECT_EQ(pool.size(), 8);
    EXPECT_EQ(pool[ind8], TestStruct(8, 8, 8, 1));
    EXPECT_FALSE(pool.empty());

//----------------------------------- erase ----------------------------------

    pool.erase(ind4);
    EXPECT_EQ(pool.size(), 7);
    EXPECT_FALSE(pool.empty());

    size_t ind9 = pool.push_back({ 8, 8, 8, 1 });
    EXPECT_EQ(pool.size(), 8);
    EXPECT_FALSE(pool.empty());
    EXPECT_EQ(ind9, ind4);

//-------------------------------- operator[] --------------------------------

    EXPECT_EQ(pool[ind9], TestStruct(8, 8, 8, 1));
    pool[ind9] = TestStruct(9, 9, 9, 1);
    EXPECT_EQ(pool[ind9], TestStruct(9, 9, 9, 1));

//----------------------------------- clear ----------------------------------

    pool.clear();
    EXPECT_EQ(pool_empty.size(), 0);
    EXPECT_TRUE(pool_empty.empty());
}

#endif