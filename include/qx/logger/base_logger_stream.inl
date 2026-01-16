/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

QX_SET_FILE_CATEGORY(CatLogger);

namespace qx
{

inline base_logger_stream::base_logger_stream(const config& streamConfig)
    : m_pMutex(std::make_unique<std::recursive_mutex>())
    , m_bProtectLog(streamConfig.bProtectLog)
    , m_eMinFlushVerbosity(streamConfig.eMinFlushVerbosity)
{
}

inline void base_logger_stream::log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    QX_PERF_SCOPE("Log");

    if (m_bProtectLog)
        m_pMutex->lock();

    do_log(category, eVerbosity, svMessage);

    if (eVerbosity >= m_eMinFlushVerbosity)
        flush();

    if (m_bProtectLog)
        m_pMutex->unlock();
}

inline void base_logger_stream::flush()
{
    QX_PERF_SCOPE("Flush");

    if (m_bProtectLog)
        m_pMutex->lock();

    do_flush();

    if (m_bProtectLog)
        m_pMutex->unlock();
}

} // namespace qx
