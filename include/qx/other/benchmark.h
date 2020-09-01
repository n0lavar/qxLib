//==============================================================================
//
//!\file                         benchmark.h
//
//!\brief       Contains benchmark class
//!\details     ~
//
//!\author      Khrapov
//!\date        2.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <chrono>

namespace qx
{

//==============================================================================
//
//!\class                         benchmark
//
//!\brief   Benchmark class
//!\details ~
//
//!\author  Khrapov
//!\date    2.02.2020
//
//==============================================================================
class benchmark
{
    using clock         = std::chrono::steady_clock;
    using time_point    = clock::time_point;
    using time_duration = std::chrono::nanoseconds;

public:

    benchmark(void)
    {
        Start();
    }

    void Start(void)
    {
        m_Start = clock::now();
    }

    double End(void)
    {
        m_LastDuration = clock::now() - m_Start;
        return Last();
    }

    double Last(void)
    {
        return m_LastDuration.count() / 1e9;
    }

private:

    time_point      m_Start;
    time_duration   m_LastDuration;
};

}
