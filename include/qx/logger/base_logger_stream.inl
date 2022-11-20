/**

    @file      base_logger_stream.inl
    @author    Khrapov
    @date      30.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class char_type>
const log_unit_info::format_func<char_type>& log_unit_info::get_format_func()
{
    if constexpr (std::is_same_v<char_type, char>)
        return formatFuncChar;
    else
        return formatFuncWChar;
}

inline base_logger_stream::base_logger_stream()
{
    register_unit(k_svDefaultUnit, { log_level::log });
}

template<class char_type>
inline void base_logger_stream::log(
    log_level        eLogLevel,
    const char_type* pszFormat,
    const char*      pszTag,
    const char*      pszFile,
    const char*      pszFunction,
    int              nLine,
    va_list          args)
{
    if (const auto optLogUnit = get_unit_info(pszTag, pszFile, pszFunction))
    {
        if (eLogLevel >= optLogUnit->pUnitInfo->eMinLogLevel)
        {
            auto& buffers = get_string_buffers<char_type>();
            buffers.sMessage.clear();

            auto formatFunc = optLogUnit->pUnitInfo->get_format_func<char_type>();
            if (!formatFunc)
                formatFunc = format_line<char_type>;

            va_list argsCopy;
            va_copy(argsCopy, args);

            if constexpr (std::is_same_v<char_type, char>)
            {
                formatFunc(buffers, eLogLevel, pszFormat, pszTag, pszFile, pszFunction, nLine, argsCopy);
            }
            else
            {
                if (pszTag)
                    buffers.sTag = to_wstring(pszTag);
                buffers.sFile     = to_wstring(pszFile);
                buffers.sFunction = to_wstring(pszFunction);

                formatFunc(
                    buffers,
                    eLogLevel,
                    pszFormat,
                    pszTag ? buffers.sTag.c_str() : nullptr,
                    buffers.sFile.c_str(),
                    buffers.sFunction.c_str(),
                    nLine,
                    argsCopy);
            }

            va_end(argsCopy);

            if (!buffers.sMessage.empty())
                do_log(buffers.sMessage, *optLogUnit, eLogLevel);
        }
    }
}

inline void base_logger_stream::register_unit(std::string_view svUnitName, const log_unit_info& unit) noexcept
{
    if (!svUnitName.empty())
        m_Units.emplace(string_hash(svUnitName), unit);
}

inline void base_logger_stream::deregister_unit(std::string_view svUnitName) noexcept
{
    m_Units.erase(string_hash(svUnitName));
}

template<class char_type>
inline void base_logger_stream::format_time_string(basic_string<char_type>& sTime) noexcept
{
    std::time_t t = std::time(nullptr);
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4996)
    std::tm* now = std::localtime(&t);
    QX_POP_SUPPRESS_WARNINGS

    sTime.sprintf(
        QX_STR_PREFIX(char_type, "%02d-%02d-%04d_%02d-%02d-%02d"),
        now->tm_mday,
        now->tm_mon,
        now->tm_year + 1900,
        now->tm_hour,
        now->tm_min,
        now->tm_sec);
}

template<class char_type>
inline logger_buffers<char_type>& base_logger_stream::get_string_buffers() noexcept
{
    if constexpr (std::is_same_v<char_type, char>)
        return m_BuffersChar;
    else
        return m_BuffersWChar;
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

template<class char_type>
inline void base_logger_stream::format_line(
    logger_buffers<char_type>& buffers,
    log_level                  eLogLevel,
    const char_type*           pszFormat,
    const char_type*           pszTag,
    const char_type*           pszFile,
    const char_type*           pszFunction,
    int                        nLine,
    va_list                    args) noexcept
{
    buffers.sMessage.vsprintf(pszFormat, args);

    format_time_string(buffers.sFormat);

    switch (eLogLevel)
    {
    case log_level::very_verbose:
        buffers.sFormat = QX_STR_PREFIX(char_type, "[VV][") + buffers.sFormat;
        break;

    case log_level::verbose:
        buffers.sFormat = QX_STR_PREFIX(char_type, "[V][") + buffers.sFormat;
        break;

    case log_level::important:
        buffers.sFormat = QX_STR_PREFIX(char_type, "[I][") + buffers.sFormat;
        break;

    case log_level::warning:
        buffers.sFormat = QX_STR_PREFIX(char_type, "[W][") + buffers.sFormat;
        break;

    case log_level::error:
        buffers.sFormat = QX_STR_PREFIX(char_type, "[E][") + buffers.sFormat;
        break;

    case log_level::critical:
        buffers.sFormat = QX_STR_PREFIX(char_type, "[C][") + buffers.sFormat;
        break;

    default:
        buffers.sFormat = QX_STR_PREFIX(char_type, "   [") + buffers.sFormat;
        break;
    }

    constexpr auto pszStringFormatSpecifier = get_format_specifier<char_type, const char_type*>();
    buffers.sFormat += QX_STR_PREFIX(char_type, "][");
    buffers.sFormat += pszStringFormatSpecifier;
    if (pszTag)
        buffers.sFormat += QX_STR_PREFIX(char_type, "][");
    buffers.sFormat += pszStringFormatSpecifier;
    buffers.sFormat += QX_STR_PREFIX(char_type, "::");
    buffers.sFormat += pszStringFormatSpecifier;
    buffers.sFormat += QX_STR_PREFIX(char_type, "::%d] ");
    buffers.sFormat += buffers.sMessage;
    buffers.sMessage.sprintf(buffers.sFormat.c_str(), pszTag ? pszTag : "", pszFile, pszFunction, nLine);
    buffers.sMessage += QX_CHAR_PREFIX(char_type, '\n');
}

} // namespace qx
