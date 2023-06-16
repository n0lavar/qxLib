/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_logger_stream::base_logger_stream(bool bAlwaysFlush) : m_bAlwaysFlush(bAlwaysFlush)
{
    register_unit(k_svDefaultUnit, { log_level::log });
}

inline void base_logger_stream::log(
    log_level       eLogLevel,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string_view     swLogMessage)
{
    const char_type* pszCategory = category.get_name();

    if (const auto optLogUnit =
            get_unit_info(pszCategory ? qx::string_view(pszCategory) : qx::string_view(), svFile, svFunction);
        optLogUnit && optLogUnit->pUnitInfo)
    {
        if (eLogLevel >= optLogUnit->pUnitInfo->eMinLogLevel)
        {
            QX_PERF_SCOPE(CatLogger, "Log");

            std::lock_guard lock(m_Mutex);

            auto& buffers = get_log_buffer();
            buffers.clear();

            auto formatFunc = optLogUnit->pUnitInfo->formatFunc;
            if (!formatFunc)
            {
                formatFunc = [this](
                                 logger_buffer&      buffers,
                                 log_level           eLogLevel,
                                 const qx::category& category,
                                 string_view         svFile,
                                 string_view         svFunction,
                                 int                 nLine,
                                 string_view         swLogMessage)
                {
                    format_line(buffers, eLogLevel, category, svFile, svFunction, nLine, swLogMessage);
                };
            }

            formatFunc(buffers, eLogLevel, category, svFile, svFunction, nLine, swLogMessage);

            if (!buffers.sMessage.empty())
            {
                do_log(buffers.sMessage, *optLogUnit, buffers.colors, eLogLevel);
                if (m_bAlwaysFlush)
                    flush();
            }
        }
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
    log_level       eLogLevel,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    string_view     swLogMessage) noexcept
{
    switch (eLogLevel)
    {
    case log_level::very_verbose:
        buffers.sMessage = QX_TEXT("[VV][");
        break;

    case log_level::verbose:
        buffers.sMessage = QX_TEXT("[V][");
        break;

    case log_level::important:
        buffers.sMessage = QX_TEXT("[I][");
        break;

    case log_level::warning:
        buffers.sMessage = QX_TEXT("[W][");
        break;

    case log_level::error:
        buffers.sMessage = QX_TEXT("[E][");
        break;

    case log_level::critical:
        buffers.sMessage = QX_TEXT("[C][");
        break;

    default:
        buffers.sMessage = QX_TEXT("   [");
        break;
    }

    append_time_string(buffers.sMessage, QX_TEXT('.'), QX_TEXT(':'));
    buffers.sMessage += QX_TEXT("][");

    const char_type* pszCategory = category.get_name();
    if (pszCategory)
    {
        buffers.sMessage += pszCategory;
        buffers.sMessage += QX_TEXT("][");
    }

    buffers.sMessage.append_format(QX_TEXT("{}::{}::{}] {}\n"), svFile, svFunction, nLine, swLogMessage);

    if (pszCategory)
        if (auto nPos = buffers.sMessage.find(pszCategory); nPos != string::npos)
            buffers.colors.push_back({ { nPos, nPos + qx::strlen(pszCategory) }, category.get_color() });
}

inline std::optional<log_unit> base_logger_stream::get_unit_info(
    string_view svCategory,
    string_view svFile,
    string_view svFunction) noexcept
{
    auto find_unit = [this](string_view svUnit)
    {
        return !svUnit.empty() ? m_Units.find(string_hash(svUnit)) : m_Units.end();
    };

    std::optional<log_unit> logUnit = std::nullopt;

    auto it = m_Units.end();
    if (it = find_unit(svCategory); it != m_Units.end())
        logUnit = { &it->second, svCategory };
    else if (it = find_unit(svFile); it != m_Units.end())
        logUnit = { &it->second, svFile };
    else if (it = find_unit(svFunction); it != m_Units.end())
        logUnit = { &it->second, svFunction };
    else if (it = find_unit(k_svDefaultUnit); it != m_Units.end())
        logUnit = { &it->second, k_svDefaultUnit };

    return logUnit;
}

} // namespace qx
