/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void logger::output(
    log_level   eLogLevel,
    const char* pszFormat,
    const char* pszTag,
    const char* pszFile,
    const char* pszFunction,
    int         nLine,
    ...)
{
    if (eLogLevel == log_level::none)
        return;

    va_list args;
    va_start(args, nLine);

    for (const auto& stream : m_Streams)
    {
        stream->output(eLogLevel, pszFormat, pszTag, pszFile, pszFunction, nLine, args);
    }

    va_end(args);
}

inline void logger::add_stream(std::unique_ptr<base_logger_stream> pStream)
{
    m_Streams.push_back(std::move(pStream));
}

} // namespace qx
