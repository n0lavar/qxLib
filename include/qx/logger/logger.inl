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
    cstring_view    svFunction,
    int             nLine,
    string          sMessage)
{
    string sFunction         = to_string(svFunction);
    string sFormattedMessage = format_line(eVerbosity, category, svFile, sFunction, nLine, sMessage);
    for (auto& stream : m_Streams)
        stream->log(category, eVerbosity, sFormattedMessage);
}

template<class... args_t>
    requires(log_acceptable_args_c<args_t...>)
inline void logger::log(
    const category&                        category,
    verbosity                              eVerbosity,
    string_view                            svFile,
    cstring_view                           svFunction,
    int                                    nLine,
    format_string_strong_checks<args_t...> sFormat,
    args_t&&... args)
{
    const auto sMessage = qx::string::static_format(sFormat, std::forward<args_t>(args)...);
    log(category, eVerbosity, svFile, svFunction, nLine, std::move(sMessage));
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
    cstring_view    svFunction) const noexcept
{
#if 0
    string sFunction = to_string(svFunction);
    for (const auto& stream : m_Streams)
        if (stream->get_unit_info(category, eVerbosity, svFile, sFunction))
            return true;

    return false;
#endif
    return true;
}

inline string logger::format_line(
    verbosity       eVerbosity,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string_view     swLogMessage) noexcept
{
    string sResult;
    switch (eVerbosity)
    {
    case verbosity::very_verbose:
        sResult = QXT("[W][");
        break;

    case verbosity::verbose:
        sResult = QXT("[V][");
        break;

    case verbosity::important:
        sResult = QXT("[I][");
        break;

    case verbosity::warning:
        sResult = QXT("[W][");
        break;

    case verbosity::error:
        sResult = QXT("[E][");
        break;

    case verbosity::critical:
        sResult = QXT("[C][");
        break;

    default:
        sResult = QXT("   [");
        break;
    }

    append_time_string(sResult, QXT('.'), QXT(':'));
    sResult += QXT("][");

    string_view svCategory = category.get_name();
    if (!svCategory.empty())
    {
        sResult += svCategory;
        sResult += QXT("][");
    }

    sResult.append_format(QXT("{}::{}::{}] {}\n"), svFile, svFunction, nLine, swLogMessage);

    return sResult;
}

} // namespace qx
