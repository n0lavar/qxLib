/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

QX_SET_FILE_CATEGORY(CatLogger);

namespace qx
{

inline base_logger_stream::base_logger_stream(bool bAlwaysFlush) : m_bAlwaysFlush(bAlwaysFlush)
{
}

inline void base_logger_stream::log(const category& category, verbosity eVerbosity, string_view svMessage)
{
    QX_PERF_SCOPE("Log");

    do_log(category, eVerbosity, svMessage);
    if (m_bAlwaysFlush)
        flush();
}

} // namespace qx
