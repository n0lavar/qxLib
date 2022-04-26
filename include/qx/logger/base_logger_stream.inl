/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

inline base_logger_stream::base_logger_stream()
{
    register_unit(k_svDefaultUnit, { log_level::info });
}

inline void base_logger_stream::output(
    log_level   eLogLevel,
    const char* pszFormat,
    const char* pszAssertExpression,
    const char* pszTag,
    const char* pszFile,
    const char* pszFunction,
    int         nLine,
    va_list     args)
{
    if (const auto optLogUnit = get_unit_info(pszTag, pszFile, pszFunction))
    {
        if (eLogLevel >= optLogUnit->pUnitInfo->eMinLogLevel)
        {
            m_sBufferMessage.clear();

            auto formatFunc = optLogUnit->pUnitInfo->formatFunc;
            if (!formatFunc)
                formatFunc = format_line;

            va_list argsCopy;
            va_copy(argsCopy, args);

            formatFunc(
                m_sBufferMessage,
                m_sBufferFormat,
                eLogLevel,
                pszFormat,
                pszAssertExpression,
                pszTag,
                pszFile,
                pszFunction,
                nLine,
                argsCopy);

            va_end(argsCopy);

            if (!m_sBufferMessage.empty())
                process_output(m_sBufferMessage, *optLogUnit, eLogLevel);
        }
    }
}

inline std::optional<log_unit> base_logger_stream::get_unit_info(
    const char* pszTag,
    const char* pszFile,
    const char* pszFunction) noexcept
{
    auto find_unit = [this](const char* pszUnit)
    {
        return pszUnit ? m_Units.find(string_hash(pszUnit)) : m_Units.end();
    };

    std::optional<log_unit> logUnit = std::nullopt;

    auto it = m_Units.end();
    if (it = find_unit(pszTag); it != m_Units.end())
        logUnit = { &it->second, pszTag };
    else if (it = find_unit(pszFile); it != m_Units.end())
        logUnit = { &it->second, pszFile };
    else if (it = find_unit(pszFunction); it != m_Units.end())
        logUnit = { &it->second, pszFunction };
    else if (it = find_unit(k_svDefaultUnit); it != m_Units.end())
        logUnit = { &it->second, k_svDefaultUnit };

    return logUnit;
}

inline void base_logger_stream::register_unit(
    std::string_view     svUnitName,
    const log_unit_info& unit)
{
    if (!svUnitName.empty())
        m_Units.emplace(string_hash(svUnitName), unit);
}

inline void base_logger_stream::deregister_unit(std::string_view svUnitName)
{
    m_Units.erase(string_hash(svUnitName));
}

inline void base_logger_stream::format_line(
    string&     sMsg,
    string&     sFormat,
    log_level   eLogLevel,
    const char* pszFormat,
    const char* pszAssertExpression,
    const char* pszTag,
    const char* pszFile,
    const char* pszFunction,
    int         nLine,
    va_list     args) noexcept
{
    sMsg.vsprintf(pszFormat, args);

    format_time_string(sFormat);

    switch (eLogLevel)
    {
    case log_level::info:
        sFormat = "   [" + sFormat + "][%s::%s(%d)] ";
        break;

    case log_level::warnings:
        sFormat = "[W][" + sFormat + "][%s::%s(%d)] ";
        break;

    case log_level::errors:
        sFormat = "[E][" + sFormat + "][%s::%s(%d)] ";
        break;

    case log_level::asserts:
        sFormat = "[A][" + sFormat + "][%s::%s(%d)][%s] ";
        break;

    default:
        sFormat = "";
        break;
    }

    sFormat += sMsg;

    if (eLogLevel != log_level::asserts)
    {
        sMsg.sprintf(sFormat.data(), pszFile, pszFunction, nLine);
    }
    else
    {
        sMsg.sprintf(
            sFormat.data(),
            pszFile,
            pszFunction,
            nLine,
            pszAssertExpression);
    }

    sMsg += '\n';
}

inline void base_logger_stream::format_time_string(string& sTime) noexcept
{
    std::time_t t = std::time(nullptr);
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4996)
    std::tm* now = std::localtime(&t);
    QX_POP_SUPPRESS_WARNINGS

    sTime.sprintf(
        "%02d-%02d-%04d_%02d-%02d-%02d",
        now->tm_mday,
        now->tm_mon,
        now->tm_year + 1900,
        now->tm_hour,
        now->tm_min,
        now->tm_sec);
}

inline string& base_logger_stream::get_time_buffer() noexcept
{
    return m_sBufferTime;
}

} // namespace qx
