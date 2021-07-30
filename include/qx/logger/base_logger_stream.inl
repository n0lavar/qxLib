//==============================================================================
//
//!\file                     base_logger_stream.inl
//
//!\brief       Contains qx::base_logger_stream class
//!\details     ~
//
//!\author      Khrapov
//!\date        30.07.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn             qx::base_logger_stream::on_logger_created
//
//!\brief  base_logger_stream object constructor
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline base_logger_stream::base_logger_stream(void)
{
    register_unit(
        DEFAULT_UNIT,
        { log_level::info });
}

//==============================================================================
//!\fn                   qx::base_logger_stream::output
//
//!\brief  Output to stream
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  svTag                - tracing tag
//!\param  svFile               - file name string
//!\param  svFunction           - function name string
//!\param  nLine                - code line number
//!\param  args                 - additional args for format
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void base_logger_stream::output(
    log_level           eLogLevel,
    const char        * pszFormat,
    const char        * pszAssertExpression,
    std::string_view    svTag,
    std::string_view    svFile,
    std::string_view    svFunction,
    int                 nLine,
    va_list             args)
{
    if (const auto optLogUnit = get_unit_info(svTag, svFile, svFunction))
    {
        auto& logUnit = optLogUnit.value();

        if (eLogLevel >= logUnit.pUnitInfo->eUnitLevel)
        {
            m_sBufferMessage.clear();

            auto formatFunc = logUnit.pUnitInfo->formatFunc;
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
                svTag,
                svFile,
                svFunction,
                nLine,
                argsCopy);

            va_end(argsCopy);

            if (!m_sBufferMessage.empty())
                process_output(m_sBufferMessage, logUnit);
        }
    }
}

//==============================================================================
//!\fn               qx::base_logger_stream::get_unit_info
//
//!\brief  Try to find log unit info based on trace location info
//!\param  svTag      - tag string
//!\param  svFile     - file string
//!\param  svFunction - function string
//!\retval            - log unit info if found
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline std::optional<log_unit> base_logger_stream::get_unit_info(
    std::string_view    svTag,
    std::string_view    svFile,
    std::string_view    svFunction) noexcept
{
    auto find_unit = [this](std::string_view svUnit)
    {
        return m_Units.find(string_hash(svUnit));
    };

    std::optional<log_unit> logUnit = std::nullopt;

    auto it = m_Units.end();
    if (it = find_unit(svTag); it != m_Units.end())
        logUnit = { &it->second, svTag };
    else if (it = find_unit(svFile); it != m_Units.end())
        logUnit = { &it->second, svFile };
    else if (it = find_unit(svFunction); it != m_Units.end())
        logUnit = { &it->second, svFunction };
    else if (it = find_unit(DEFAULT_UNIT); it != m_Units.end())
        logUnit = { &it->second, DEFAULT_UNIT };

    return logUnit;
}

//==============================================================================
//!\fn               qx::base_logger_stream::register_unit
//
//!\brief  Register logger unit
//!\param  svUnitName - unit name (tag, file or function)
//!\param  unit       - unit info
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void base_logger_stream::register_unit(
    std::string_view        svUnitName,
    const log_unit_info   & unit)
{
    if (!svUnitName.empty())
        m_Units.emplace(string_hash(svUnitName), unit);
}

//==============================================================================
//!\fn              qx::base_logger_stream::deregister_unit
//
//!\brief  Deregister logger unit
//!\param  svUnitName - unit name (tag, file or function)
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void base_logger_stream::deregister_unit(
    std::string_view        svUnitName)
{
    m_Units.erase(string_hash(svUnitName));
}

//==============================================================================
//!\fn                qx::base_logger_stream::format_line
//
//!\brief  Format logger line
//!\param  sMsg                 - output msg
//!\param  sFormat              - buffer for formatting
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  svTag                - tracing tag or nullptr
//!\param  svFile               - file name string
//!\param  svFunction           - function name string
//!\param  nLine                - code line number
//!\param  args                 - additional args for format
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
inline void base_logger_stream::format_line(
    string            & sMsg,
    string            & sFormat,
    log_level           eLogLevel,
    const char        * pszFormat,
    const char        * pszAssertExpression,
    std::string_view    svTag,
    std::string_view    svFile,
    std::string_view    svFunction,
    int                 nLine,
    va_list             args) noexcept
{
    sMsg.vsprintf(pszFormat, args);

    format_time_string(sFormat);

    switch (eLogLevel)
    {
    case log_level::info:
        sFormat = "[I][" + sFormat + "][%s::%s(%d)] ";
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
        sMsg.sprintf(
            sFormat.data(),
            svFile.data(),
            svFunction.data(),
            nLine);
    }
    else
    {
        sMsg.sprintf(
            sFormat.data(),
            svFile.data(),
            svFunction.data(),
            nLine,
            pszAssertExpression);
    }

    sMsg += '\n';
}

//==============================================================================
//!\fn   qx::base_logger_stream::base_logger_stream::format_time_string
//
//!\brief  Format time string to the buffer
//!\param  sTime - output time buffer
//!\author Khrapov
//!\date   30.07.2021
//==============================================================================
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

}