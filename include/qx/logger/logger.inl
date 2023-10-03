/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void logger::log(
    verbosity       eVerbosity,
    string_view     svFormat,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine)
{
    for (const auto& stream : m_Streams)
        stream->log(eVerbosity, category, svFile, svFunction, nLine, svFormat);
}

template<class... args_t>
    requires(log_acceptable_args<args_t...>)
inline void logger::log(
    verbosity                eVerbosity,
    format_string<args_t...> sFormat,
    const category&          category,
    string_view              svFile,
    string_view              svFunction,
    int                      nLine,
    const args_t&... args)
{
    const auto sLogMessage = qx::string::static_format(sFormat, args...);
    for (const auto& stream : m_Streams)
        stream->log(eVerbosity, category, svFile, svFunction, nLine, sLogMessage);
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

inline bool logger::will_any_stream_accept(
    const category& category,
    verbosity       eVerbosity,
    string_view     svFile,
    string_view     svFunction) const noexcept
{
    for (const auto& stream : m_Streams)
        if (stream->get_unit_info(category, eVerbosity, svFile, svFunction))
            return true;

    return false;
}

} // namespace qx
