/**

    @file      test_threads_shared.cpp
    @author    Khrapov
    @date      4.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *threads_shared.cpp

#if QX_TEST_THREADS_SHARED

    #include <qx/thread/threads_shared.h>

    #include <chrono>
    #include <list>
    #include <random>
    #include <thread>

struct STestStruct
{
    int    intData      = 0;
    float  floatData    = 0.f;
    bool   boolData     = false;
    size_t unsignedData = 0u;

    constexpr STestStruct(void) = default;
    constexpr STestStruct(int _intData, float _floatData, bool _boolData, size_t _unsignedData)
        : intData(_intData)
        , floatData(_floatData)
        , boolData(_boolData)
        , unsignedData(_unsignedData)
    {
    }

    bool operator==(const STestStruct& other) const
    {
        return intData == other.intData && floatData == other.floatData && boolData == other.boolData
               && unsignedData == other.unsignedData;
    }
};

constexpr STestStruct TEST_DATA_0 { 0, 0.f, false, 0u };
constexpr STestStruct TEST_DATA_1 { 1, 1.f, true, 1u };
constexpr STestStruct TEST_DATA_2 { 2, 2.f, true, 2u };

constexpr size_t NUM_ITERATIONS = 20;
constexpr size_t MIN_MS_WAIT    = 100;
constexpr size_t MAX_MS_WAIT    = 500;

TEST(threads_shared, main)
{
    qx::threads_shared<STestStruct> sharedData(2, 2.f, true, 2u);

    {
        auto data = sharedData.lock();
        ASSERT_EQ(*data, TEST_DATA_2);
    }

    // clang-format off
    std::thread thread_setting_0 { [&sharedData]()
                                   {
                                       std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
                                       std::uniform_int_distribution distribution(MIN_MS_WAIT, MAX_MS_WAIT);

                                       for (size_t i = 0; i < NUM_ITERATIONS; ++i)
                                       {
                                           auto data = sharedData.lock();
                                           std::cout << "thread_setting_0: locked\n";
                                           *data = TEST_DATA_0;
                                           ASSERT_EQ(*data, TEST_DATA_0);
                                           std::this_thread::sleep_for(
                                               std::chrono::microseconds(distribution(generator)));
                                           ASSERT_EQ(*data, TEST_DATA_0);
                                       }
                                   } };
    // clang-format on

    std::thread thread_setting_1 {
        [&sharedData]()
        {
            std::default_random_engine            generator(static_cast<unsigned>(std::time(nullptr) + 1));
            std::uniform_int_distribution<size_t> distribution(MIN_MS_WAIT, MAX_MS_WAIT);

            for (size_t i = 0; i < NUM_ITERATIONS; ++i)
            {
                auto data = sharedData.lock();
                std::cout << "thread_setting_1: locked\n";
                *data = TEST_DATA_1;
                ASSERT_EQ(*data, TEST_DATA_1);
                std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
                ASSERT_EQ(*data, TEST_DATA_1);
            }
        }
    };

    std::thread thread_setting_2 {
        [&sharedData]()
        {
            std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr) + 2));

            std::uniform_int_distribution<size_t> distribution(MIN_MS_WAIT, MAX_MS_WAIT);

            for (size_t i = 0; i < NUM_ITERATIONS; ++i)
            {
                auto optionalProxy = sharedData.try_lock();
                if (optionalProxy.has_value())
                {
                    auto& proxy = optionalProxy.value();

                    std::cout << "thread_setting_2: locked\n";
                    *proxy = TEST_DATA_2;
                    ASSERT_EQ(*proxy, TEST_DATA_2);
                    std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
                    ASSERT_EQ(*proxy, TEST_DATA_2);
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

TEST(threads_shared, list)
{
    // check compilation
    std::list<qx::threads_shared<STestStruct>> list;
    list.emplace_back(2, 2.f, true, 2u);

    {
        auto data = list.back().lock();
        ASSERT_EQ(*data, TEST_DATA_2);
    }
}

TEST(threads_shared, recursive_mutex)
{
    // check compilation
    qx::threads_shared<STestStruct, std::recursive_mutex> sharedData(2, 2.f, true, 2u);

    {
        auto data = sharedData.lock();
        ASSERT_EQ(*data, TEST_DATA_2);
    }
}

#endif
