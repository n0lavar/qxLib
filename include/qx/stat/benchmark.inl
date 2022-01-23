/**

    @file      benchmark.inl
    @author    Khrapov
    @date      20.08.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void benchmark::start()
{
    m_Start = clock::now();
}

inline double benchmark::end()
{
    m_LastDuration = clock::now() - m_Start;
    return last();
}

inline double benchmark::last() const
{
    return static_cast<double>(m_LastDuration.count()) / 1e9;
}

} // namespace qx
