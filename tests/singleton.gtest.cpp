/**

    @file      singleton.gtest.cpp
    @author    Khrapov
    @date      26.09.2020
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

#include <qx/patterns/singleton.h>

//V_EXCLUDE_PATH *.gtest.cpp

static std::vector<int>* g_pTestNumbers = nullptr;

class test_singleton_1 final : public qx::singleton<test_singleton_1>
{
public:
    virtual void init() override;
    virtual ~test_singleton_1() override;
};

inline void test_singleton_1::init()
{
    g_pTestNumbers->push_back(1);
}

inline test_singleton_1::~test_singleton_1()
{
    g_pTestNumbers->push_back(8);
}

class test_singleton_2 final : public qx::singleton<test_singleton_2, test_singleton_1>
{
public:
    virtual void init() override;
    virtual ~test_singleton_2() override;
};

inline void test_singleton_2::init()
{
    g_pTestNumbers->push_back(2);
}

inline test_singleton_2::~test_singleton_2()
{
    g_pTestNumbers->push_back(7);
}

class test_singleton_3 final : public qx::singleton<test_singleton_3, test_singleton_2>
{
public:
    virtual void init() override;
    virtual ~test_singleton_3() override;
};

inline void test_singleton_3::init()
{
    g_pTestNumbers->push_back(3);
}

inline test_singleton_3::~test_singleton_3()
{
    g_pTestNumbers->push_back(6);
}

class test_singleton_4 final
    : public qx::singleton<test_singleton_4, test_singleton_1, test_singleton_3, test_singleton_2>
{
public:
    virtual void init() override;
    virtual ~test_singleton_4() override;
};

inline void test_singleton_4::init()
{
    g_pTestNumbers->push_back(4);
}

inline test_singleton_4::~test_singleton_4()
{
    g_pTestNumbers->push_back(5);
}

TEST(singleton, main)
{
    std::atexit(
        []() noexcept
        {
            EXPECT_EQ(*g_pTestNumbers, QX_GTEST_SINGLE_ARGUMENT(std::vector { 1, 2, 3, 4, 5, 6, 7, 8 }));
            delete g_pTestNumbers;
        });

    g_pTestNumbers = new std::vector<int>();
    test_singleton_4::get_instance();
}
