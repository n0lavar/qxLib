/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

QX_SET_FILE_CATEGORY(CatLogger);

namespace qx
{

inline base_logger_stream::base_logger_stream(bool bProtectLog, bool bAlwaysFlush)
    : m_pMutex(std::make_unique<std::mutex>())
    , m_bProtectLog(bProtectLog)
    , m_bAlwaysFlush(bAlwaysFlush)
{
}

inline void base_logger_stream::log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    QX_PERF_SCOPE("Log");

    if (m_bProtectLog)
        m_pMutex->lock();

    do_log(category, eVerbosity, svMessage);
    if (m_bAlwaysFlush)
        flush();

    if (m_bProtectLog)
        m_pMutex->unlock();
}

} // namespace qx
