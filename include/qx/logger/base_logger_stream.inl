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
    string_view     svFormat,
    const category& category,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    va_list         args)
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
                formatFunc = format_line;

            va_list argsCopy;
            va_copy(argsCopy, args);

            formatFunc(buffers, eLogLevel, category, svFormat, svFile, svFunction, nLine, argsCopy);

            va_end(argsCopy);

            if (!buffers.sMessage.empty())
                do_log(buffers.sMessage, *optLogUnit, buffers.colors, eLogLevel);

            if (m_bAlwaysFlush)
                flush();
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

inline void base_logger_stream::format_time_string(
    string&   sTime,
    char_type chDateDelimiter,
    char_type chTimeDelimiter) noexcept
{
    std::time_t t = std::time(nullptr);
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4996);
    std::tm* now = std::localtime(&t);
    QX_POP_SUPPRESS_WARNINGS();

    sTime.sprintf(
        QX_TEXT("%02d%c%02d%c%04d_%02d%c%02d%c%02d"),
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

inline void base_logger_stream::format_line(
    logger_buffer&  buffers,
    log_level       eLogLevel,
    const category& category,
    string_view     svFormat,
    string_view     svFile,
    string_view     svFunction,
    int             nLine,
    va_list         args) noexcept
{
    buffers.sMessage.vsprintf(qx::string(svFormat).c_str(), args);

    format_time_string(buffers.sFormat, QX_TEXT('.'), QX_TEXT(':'));

    switch (eLogLevel)
    {
    case log_level::very_verbose:
        buffers.sFormat = QX_TEXT("[VV][") + buffers.sFormat;
        break;

    case log_level::verbose:
        buffers.sFormat = QX_TEXT("[V][") + buffers.sFormat;
        break;

    case log_level::important:
        buffers.sFormat = QX_TEXT("[I][") + buffers.sFormat;
        break;

    case log_level::warning:
        buffers.sFormat = QX_TEXT("[W][") + buffers.sFormat;
        break;

    case log_level::error:
        buffers.sFormat = QX_TEXT("[E][") + buffers.sFormat;
        break;

    case log_level::critical:
        buffers.sFormat = QX_TEXT("[C][") + buffers.sFormat;
        break;

    default:
        buffers.sFormat = QX_TEXT("   [") + buffers.sFormat;
        break;
    }

    const char_type* pszCategory = category.get_name();

    constexpr auto pszStringFormatSpecifier = get_format_specifier<char_type, const char_type*>();
    buffers.sFormat += QX_TEXT("][");
    buffers.sFormat += pszStringFormatSpecifier;
    if (pszCategory)
        buffers.sFormat += QX_TEXT("][");
    buffers.sFormat += pszStringFormatSpecifier;
    buffers.sFormat += QX_TEXT("::");
    buffers.sFormat += pszStringFormatSpecifier;
    buffers.sFormat += QX_TEXT("::%d] ");
    buffers.sFormat += buffers.sMessage;
    buffers.sMessage.sprintf(
        buffers.sFormat.c_str(),
        pszCategory ? pszCategory : QX_TEXT(""),
        qx::string(svFile).c_str(),
        qx::string(svFunction).c_str(),
        nLine);
    buffers.sMessage += QX_TEXT('\n');

    if (pszCategory)
        if (auto nPos = buffers.sMessage.find(pszCategory); nPos != string::npos)
            buffers.colors.push_back({ { nPos, nPos + qx::strlen(pszCategory) }, category.get_color() });
}

} // namespace qx
