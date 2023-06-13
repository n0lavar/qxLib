/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void logger::log(
    log_level       eLogLevel,
    string_view     svFormat,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    ...)
{
    va_list args;
    va_start(args, nLine);

    for (const auto& stream : m_Streams)
        stream->log(eLogLevel, svFormat, category, svFile, svFunction, nLine, args);

    va_end(args);
}

inline void logger::flush()
{
    for (const auto& stream : m_Streams)
        stream->flush();
}

inline void logger::add_stream(std::unique_ptr<base_logger_stream> pStream) noexcept
{
    m_Streams.push_back(std::move(pStream));
}

inline void logger::reset() noexcept
{
    m_Streams.clear();
}

} // namespace qx
