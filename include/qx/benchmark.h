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
//!\class                       qx::benchmark
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
public:

    using clock      = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration   = std::chrono::nanoseconds;

    void start(void)
    {
        m_Start = clock::now();
    }

    double end(void)
    {
        m_LastDuration = clock::now() - m_Start;
        return last();
    }

    double last(void) const
    {
        return static_cast<double>(m_LastDuration.count()) / 1e9;
    }

private:

    time_point  m_Start;
    duration    m_LastDuration  = duration(0);
};

}
