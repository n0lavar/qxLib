//==============================================================================
//
//!\file                    test_threads_shared.cpp
//
//!\brief       Tests for qx::threads_shared
//!\details     ~
//
//!\author      Khrapov
//!\date        4.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *threads_shared.cpp

#if QX_TEST_THREADS_SHARED

#include <chrono>
#include <random>
#include <qx/threads_shared.h>

struct STestStruct
{
    int     _int    = 0;
    float   _float  = 0.f;
    bool    _bool   = false;
    size_t  _size   = 0u;

    bool operator==(const STestStruct& other) const
    {
        return _int == other._int
            && _float == other._float
            && _bool == other._bool
            && _size == other._size;
    }
};

constexpr STestStruct TEST_DATA_0
{
    0,
    0.f,
    false,
    0u
};

constexpr STestStruct TEST_DATA_1
{
    1,
    1.f,
    true,
    1u
};

constexpr STestStruct TEST_DATA_2
{
    2,
    2.f,
    true,
    2u
};

constexpr size_t NUM_ITERATIONS = 20;
constexpr size_t MIN_MS_WAIT    = 100;
constexpr size_t MAX_MS_WAIT    = 500;

TEST(threads_shared, construct)
{
    qx::threads_shared<STestStruct> sharedData;

    std::thread thread_setting_0
    {
        [&sharedData]()
        {
            std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
            std::uniform_int_distribution<size_t> distribution(MIN_MS_WAIT, MAX_MS_WAIT);

            for (size_t i = 0; i < NUM_ITERATIONS; ++i)
            {
                auto data = sharedData.lock();
                std::cout << "thread_setting_0: locked\n";
                data = TEST_DATA_0;
                ASSERT_EQ(static_cast<STestStruct>(data), TEST_DATA_0);
                std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
                ASSERT_EQ(static_cast<STestStruct>(data), TEST_DATA_0);
            }
        }
    };

    std::thread thread_setting_1
    {
        [&sharedData]()
        {
            std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr) + 1));
            std::uniform_int_distribution<size_t> distribution(MIN_MS_WAIT, MAX_MS_WAIT);

            for (size_t i = 0; i < NUM_ITERATIONS; ++i)
            {
                auto data = sharedData.lock();
                std::cout << "thread_setting_1: locked\n";
                data = TEST_DATA_1;
                ASSERT_EQ(static_cast<STestStruct>(data), TEST_DATA_1);
                std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
                ASSERT_EQ(static_cast<STestStruct>(data), TEST_DATA_1);
            }
        }
    };

    std::thread thread_setting_2
    {
        [&sharedData]()
        {
            std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr) + 2));
            std::uniform_int_distribution<size_t> distribution(MIN_MS_WAIT, MAX_MS_WAIT);

            for (size_t i = 0; i < NUM_ITERATIONS; ++i)
            {
                auto pair = sharedData.try_lock();
                if (pair.first)
                {
                    std::cout << "thread_setting_2: locked\n";
                    pair.second = TEST_DATA_2;
                    ASSERT_EQ(static_cast<STestStruct>(pair.second), TEST_DATA_2);
                    std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
                    ASSERT_EQ(static_cast<STestStruct>(pair.second), TEST_DATA_2);
                }
                else
                {
                    std::cout << "thread_setting_2: failed to lock\n";
                    --i;
                }
                std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
            }
        }
    };

    thread_setting_0.join();
    thread_setting_1.join();
    thread_setting_2.join();
}

#endif
