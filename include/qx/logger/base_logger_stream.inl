/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

QX_DEFINE_FILE_CATEGORY(CatLogger);

namespace qx
{

inline base_logger_stream::base_logger_stream(bool bAlwaysFlush) : m_bAlwaysFlush(bAlwaysFlush)
{
    register_unit(k_svDefaultUnit, { verbosity::log });
}

inline void base_logger_stream::log(
    verbosity       eVerbosity,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string_view     swLogMessage)
{
    QX_PERF_SCOPE("Log");

    const auto optLogUnit = get_unit_info(category, eVerbosity, svFile, svFunction);
    if (!optLogUnit)
        return;

    std::lock_guard lock(m_LoggerStreamMutex);

    auto& buffers = get_log_buffer();
    buffers.clear();

    auto formatFunc = optLogUnit->pUnitInfo->formatFunc;
    if (!formatFunc)
    {
        formatFunc = [this](
                         logger_buffer&      buffers,
                         verbosity           eVerbosity,
                         const qx::category& category,
                         string_view         svFile,
                         string_view         svFunction,
                         int                 nLine,
                         string_view         swLogMessage)
        {
            format_line(buffers, eVerbosity, category, svFile, svFunction, nLine, swLogMessage);
        };
    }

    {
        QX_PERF_SCOPE("Log formatting");
        formatFunc(buffers, eVerbosity, category, svFile, svFunction, nLine, swLogMessage);
    }

    if (!buffers.sMessage.empty())
    {
        do_log(buffers.sMessage, *optLogUnit, buffers.colors, eVerbosity);
        if (m_bAlwaysFlush)
            flush();
    }
}

inline void base_logger_stream::register_unit(string_view svUnitName, const log_unit_info& unit) noexcept
{
    if (!svUnitName.empty())
        m_Units.emplace(string_hash(svUnitName), unit);
}

inline void base_logger_stream::deregister_unit(string_view svUnitName) noexcept
{
    m_Units.erase(string_hash(svUnitName));
}

inline std::optional<log_unit> base_logger_stream::get_unit_info(
    const category& category,
    verbosity       eVerbosity,
    string_view     svFile,
    string_view     svFunction) const noexcept
{
    QX_PERF_SCOPE();

    auto find_unit = [this](string_view svUnit)
    {
        return !svUnit.empty() ? m_Units.find(string_hash(svUnit)) : m_Units.cend();
    };

    std::optional<log_unit> optLogUnit = std::nullopt;

    if (auto it = find_unit(category.get_name()); it != m_Units.cend())
        optLogUnit = { &it->second, category.get_name() };
    else if (it = find_unit(svFile); it != m_Units.cend())
        optLogUnit = { &it->second, svFile };
    else if (it = find_unit(svFunction); it != m_Units.cend())
        optLogUnit = { &it->second, svFunction };
    else if (it = find_unit(k_svDefaultUnit); it != m_Units.cend())
        optLogUnit = { &it->second, k_svDefaultUnit };

    if (optLogUnit && optLogUnit->pUnitInfo && eVerbosity >= optLogUnit->pUnitInfo->eMinVerbosity)
        return optLogUnit;
    else
        return std::nullopt;
}

inline void base_logger_stream::append_time_string(
    string&   sTime,
    char_type chDateDelimiter,
    char_type chTimeDelimiter) noexcept
{
    std::time_t t = std::time(nullptr);
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4996);
    std::tm* now = std::localtime(&t);
    QX_POP_SUPPRESS_WARNINGS();

    sTime.append_format(
        QX_TEXT("{:02}{}{:02}{}{:04}_{:02}{}{:02}{}{:02}"),
        now->tm_mday,
        chDateDelimiter,
        now->tm_mon,
        chDateDelimiter,
        now->tm_year + 1900,
        now->tm_hour,
        chTimeDelimiter,
        now->tm_min,
        chTimeDelimiter,
        now->tm_sec);
}

inline logger_buffer& base_logger_stream::get_log_buffer() noexcept
{
    return m_Buffer;
}

inline void base_logger_stream::format_line(
    logger_buffer&  buffers,
    verbosity       eVerbosity,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string_view     swLogMessage) noexcept
{
    switch (eVerbosity)
    {
    case verbosity::very_verbose:
        buffers.sMessage = QX_TEXT("[VV][");
        break;

    case verbosity::verbose:
        buffers.sMessage = QX_TEXT("[V][");
        break;

    case verbosity::important:
        buffers.sMessage = QX_TEXT("[I][");
        break;

    case verbosity::warning:
        buffers.sMessage = QX_TEXT("[W][");
        break;

    case verbosity::error:
        buffers.sMessage = QX_TEXT("[E][");
        break;

    case verbosity::critical:
        buffers.sMessage = QX_TEXT("[C][");
        break;

    default:
        buffers.sMessage = QX_TEXT("   [");
        break;
    }

    append_time_string(buffers.sMessage, QX_TEXT('.'), QX_TEXT(':'));
    buffers.sMessage += QX_TEXT("][");

    string_view svCategory = category.get_name();
    if (!svCategory.empty())
    {
        buffers.sMessage += svCategory;
        buffers.sMessage += QX_TEXT("][");
    }

    buffers.sMessage.append_format(QX_TEXT("{}::{}::{}] {}\n"), svFile, svFunction, nLine, swLogMessage);

    if (!svCategory.empty())
        if (auto nPos = buffers.sMessage.find(svCategory); nPos != string::npos)
            buffers.colors.push_back({ { nPos, nPos + svCategory.size() }, category.get_color() });
}

} // namespace qx
