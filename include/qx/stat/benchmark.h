/**

    @file      benchmark.h
    @author    Khrapov
    @date      2.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <chrono>

namespace qx
{

/**

    @class   benchmark
    @brief   Benchmark class
    @details ~
    @author  Khrapov
    @date    2.02.2020

**/
class benchmark
{
public:
    using clock      = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration   = std::chrono::nanoseconds;

    /**
        @brief Start benchmark
    **/
    void start();

    /**
        @brief  End benchmark
        @retval - number of seconds since start time
    **/
    double end();

    /**
        @brief  Get last benchmark time
        @retval - last number of seconds since start time
    **/
    double last() const;

private:
    time_point m_Start;
    duration   m_LastDuration = duration(0);
};

} // namespace qx

#include <qx/stat/benchmark.inl>
