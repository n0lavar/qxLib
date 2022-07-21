/**

    @file      test_benchmark.cpp
    @author    Khrapov
    @date      27.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_benchmark.cpp

#if QX_TEST_BENCHMARK

    #include <cmath>
    #include <thread>

    #include <qx/stat/benchmark.h>

TEST(benchmark, benchmark)
{
    constexpr size_t NUM_ITERATIONS = 300;
    constexpr double WAIT_INTERVAL  = 0.01;

    qx::benchmark bench;

    for (size_t i = 0; i < NUM_ITERATIONS; i++)
    {
        bench.start();
        std::this_thread::sleep_for(std::chrono::duration<double>(WAIT_INTERVAL));
        double duration = bench.end();
        EXPECT_GE(duration, WAIT_INTERVAL);
    }
}

#endif
