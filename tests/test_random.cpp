//==============================================================================
//
//!\file                        test_random.cpp
//
//!\brief       Tests for random.h
//!\details     ~
//
//!\author      Khrapov
//!\date        27.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_random.cpp

#if QX_TEST_RANDOM

#include <qx/random.h>
#include <qx/useful_funcs.h>

template<typename T>
void TestRandom(T min, T max, size_t nIterations)
{
    for (size_t i = 0; i < nIterations; i++)
        ASSERT_TRUE(qx::between(min, qx::random(min, max), max));
}

TEST(random, random)
{
    constexpr size_t NUM_TESTS = 100000;

    TestRandom(0,       100,    NUM_TESTS);
    TestRandom(-100,    100,    NUM_TESTS);
    TestRandom(0u,      100u,   NUM_TESTS);
    TestRandom(0.f,     100.f,  NUM_TESTS);
    TestRandom(-100.f,  100.f,  NUM_TESTS);
    TestRandom(0.0,     100.0,  NUM_TESTS);
    TestRandom(-100.0,  100.0,  NUM_TESTS);
}

#endif
