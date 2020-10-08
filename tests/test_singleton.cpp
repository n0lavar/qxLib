//==============================================================================
//
//!\file                       test_singleton.cpp
//
//!\brief       Tests for singleton macro
//!\details     ~
//
//!\author      Khrapov
//!\date        26.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_singleton.cpp

#if QX_TEST_SINGLETON

#include <qx/other/singleton.h>
#include <gtest/gtest.h>

class CTestSingleton
{
    QX_SINGLETON_CDP(CTestSingleton, on_create();, on_terminate();, ProcessGetter();)

    void on_create(void)
    {
        m_bCreated = true;
    }

    void on_terminate(void)
    {
        m_bCreated = false;
    }

    static void ProcessGetter(void)
    {
        m_nCounter++;
    }

public:

    static int  get_counter(void) { return m_nCounter; }
    static bool get_created(void) { return m_bCreated; }
           void do_stuff   (void) { }

private:

    static bool m_bCreated;
    static int  m_nCounter;
};

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

#endif