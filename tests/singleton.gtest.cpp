/**

    @file      singleton.gtest.cpp
    @author    Khrapov
    @date      26.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *singleton.gtest.cpp

#include <qx/patterns/singleton.h>

static std::vector<int>* g_pTestNumbers = nullptr;

class test_singleton_1 : public qx::singleton<test_singleton_1>
{
public:
    virtual void init() override
    {
        g_pTestNumbers->push_back(1);
    }
    virtual ~test_singleton_1() override
    {
        g_pTestNumbers->push_back(8);
    }
};

class test_singleton_2 : public qx::singleton<test_singleton_2, test_singleton_1>
{
public:
    virtual void init() override
    {
        g_pTestNumbers->push_back(2);
    }
    virtual ~test_singleton_2() override
    {
        g_pTestNumbers->push_back(7);
    }
};

class test_singleton_3 : public qx::singleton<test_singleton_3, test_singleton_2>
{
public:
    virtual void init() override
    {
        g_pTestNumbers->push_back(3);
    }
    virtual ~test_singleton_3() override
    {
        g_pTestNumbers->push_back(6);
    }
};

class test_singleton_4 : public qx::singleton<test_singleton_4, test_singleton_1, test_singleton_3, test_singleton_2>
{
public:
    virtual void init() override
    {
        g_pTestNumbers->push_back(4);
    }
    virtual ~test_singleton_4() override
    {
        g_pTestNumbers->push_back(5);
    }
};

TEST(singleton, main)
{
    std::atexit(
        []() noexcept
        {
            EXPECT_EQ(*g_pTestNumbers, GTEST_SINGLE_ARGUMENT(std::vector { 1, 2, 3, 4, 5, 6, 7, 8 }));
            delete g_pTestNumbers;
        });

    g_pTestNumbers = new std::vector<int>();
    test_singleton_4::get_instance();
}
