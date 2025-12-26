/**

    @file      logger.inl
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline void logger::log(
    const category& category,
    verbosity       eVerbosity,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string_view     svMessage)
{
    for (auto& stream : m_Streams)
        stream->log(category, eVerbosity, svFile, svFunction, nLine, svMessage);
}

template<class... args_t>
    requires(log_acceptable_args_c<args_t...>)
inline void logger::log(
    const category&                        category,
    verbosity                              eVerbosity,
    string_view                            svFile,
    string_view                            svFunction,
    int                                    nLine,
    format_string_strong_checks<args_t...> sFormat,
    args_t&&... args)
{
    const auto sLogMessage = qx::string::static_format(sFormat, std::forward<args_t>(args)...);
    for (auto& stream : m_Streams)
        stream->log(category, eVerbosity, svFile, svFunction, nLine, sLogMessage);
}

inline void logger::flush()
{
    for (auto& stream : m_Streams)
        stream->flush();
}

template<sbo_poly_assignable_c<base_logger_stream> stream_t>
inline void logger::add_stream(stream_t stream) noexcept
{
    m_Streams.emplace_back(std::move(stream));
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
