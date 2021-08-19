/**

    @file      benchmark.inl
    @brief     Contains qx::benchmark class implementation
    @author    Khrapov
    @date      20.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void benchmark::start(void)
{
    m_Start = clock::now();
}

inline double benchmark::end(void)
{
    m_LastDuration = clock::now() - m_Start;
    return last();
}

inline double benchmark::last(void) const
{
    return static_cast<double>(m_LastDuration.count()) / 1e9;
}

} // namespace qx
