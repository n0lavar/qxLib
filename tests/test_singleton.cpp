/**

    @file      test_singleton.cpp
    @author    Khrapov
    @date      26.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

//V_EXCLUDE_PATH *test_singleton.cpp

#include <qx/patterns/singleton.h>

template<>
struct qx::singleton_traits<class CTestSingleton>
{
    static void on_constructed(CTestSingleton& instance);
    static void on_getter(CTestSingleton& instance);
    static void on_destructed(CTestSingleton& instance);
};

class CTestSingleton
{
    QX_SINGLETON(CTestSingleton);

public:
    static int get_counter()
    {
        return m_nCounter;
    }
    static bool get_created()
    {
        return m_bCreated;
    }
    void do_stuff()
    {
    }

private:
    static bool m_bCreated;
    static int  m_nCounter;
};

void qx::singleton_traits<CTestSingleton>::on_constructed(CTestSingleton& instance)
{
    instance.m_bCreated = true;
}
void qx::singleton_traits<CTestSingleton>::on_getter(CTestSingleton& instance)
{
    instance.m_nCounter++;
}
void qx::singleton_traits<CTestSingleton>::on_destructed(CTestSingleton& instance)
{
    instance.m_bCreated = false;
}


bool CTestSingleton::m_bCreated = false;
int  CTestSingleton::m_nCounter = 0;

TEST(singleton, test)
{
    ASSERT_EQ(CTestSingleton::get_counter(), 0);
    ASSERT_EQ(CTestSingleton::get_created(), false);

    CTestSingleton::get_instance().do_stuff();

    ASSERT_EQ(CTestSingleton::get_counter(), 1);
    ASSERT_EQ(CTestSingleton::get_created(), true);

    CTestSingleton::get_instance().do_stuff();

    ASSERT_EQ(CTestSingleton::get_counter(), 2);
    ASSERT_EQ(CTestSingleton::get_created(), true);

    CTestSingleton::get_instance().do_stuff();

    ASSERT_EQ(CTestSingleton::get_counter(), 3);
    ASSERT_EQ(CTestSingleton::get_created(), true);
}
