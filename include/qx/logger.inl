//==============================================================================
//
//!\file                          logger.inl
//
//!\brief       Console tracing and creating of logs
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================

namespace qx
{

//================================================================================
//!\fn                        qx::logger::process_output
//
//!\brief  Process tracings
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszTag               - trasing tag
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\param  nLine                - code line number
//!\param  svColor              - ascii color string
//!\param  ...                  - additional args for format
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::process_output(
    level               eLogLevel,
    const char        * pszFormat,
    const char        * pszAssertExpression,
    const char        * pszTag,
    const char        * pszFile,
    const char        * pszFunction,
    int                 nLine,
    std::string_view    svColor,
    ...)
{
    if (auto pUnitInfo = get_unit_info(eLogLevel, pszTag, pszFile, pszFunction))
    {
        auto& traceUnitInfo = pUnitInfo->get_trace_unit_info();
        m_sMsg.clear();

        if (auto formatFunc = traceUnitInfo.formatFunc; formatFunc)
        {
            va_list args;
            va_start(args, svColor);

            formatFunc(
                m_sMsg,
                m_sFormat,
                eLogLevel,
                pszFormat,
                pszAssertExpression,
                pszTag,
                pszFile,
                pszFunction,
                nLine,
                args);

            va_end(args);
        }

        if (!m_sMsg.empty())
        {
            if (eLogLevel >= traceUnitInfo.eFileLevel
                && output_to_file(m_sMsg, traceUnitInfo.sLogFileName))
            {
                pUnitInfo->set_wrote_to_file();
            }

            if (eLogLevel >= traceUnitInfo.eConsoleLevel)
            {
                output_to_cout(m_sMsg, svColor);
            }
        }
    }
}

//================================================================================
//!\fn                     qx::logger::register_unit
//
//!\brief  Register tag, file or function for tracing
//         Register unit with name "default" to update default tracing settings
//!\param  svUnitName - tag, file or function name
//!\param  unit       - unit info
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::register_unit(std::string_view svUnitName, const unit_info& unit)
{
    if (!unit.sLogFileName.empty() && !svUnitName.empty())
    {
        if (m_eLogPolicy == policy::clear_then_uppend)
            std::ofstream ofs(unit.sLogFileName.data(), std::ofstream::out | std::ofstream::trunc); //-V808
                                                                                                    // clear file

        m_RegisteredUnits.emplace(string_hash(svUnitName), unit);
    }
}

//==============================================================================
//!\fn                      logger::deregister_unit
//
//!\brief  Deregister tag, file or function for tracing
//!\param  svUnitName - tag, file or function name
//!\author Khrapov
//!\date   4.11.2020
//==============================================================================
inline void logger::deregister_unit(std::string_view svUnitName)
{
    m_RegisteredUnits.erase(svUnitName);
}

//================================================================================
//!\fn                     qx::logger::set_logs_folder
//
//!\brief  Set logs root folder
//!\param  pszFolder - log folder
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::set_logs_folder(const char* pszFolder)
{
    m_sFolder = pszFolder;
    if (!m_sFolder.empty() && !m_sFolder.ends_with('/'))
        m_sFolder += '/';
}

//==============================================================================
//!\fn                       qx::format_time_string
//
//!\brief  Get time c string
//!\param  sTime - output string with time
//!\author Khrapov
//!\date   5.11.2020
//==============================================================================
inline void logger::format_time_string(string& sTime)
{
    std::time_t t = std::time(nullptr);
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4996)
    std::tm* now = std::localtime(&t);
    QX_POP_SUPPRESS_WARNINGS

    sTime.printf(
        "%02d-%02d-%04d_%02d-%02d-%02d",
        now->tm_mday,
        now->tm_mon,
        now->tm_year + 1900,
        now->tm_hour,
        now->tm_min,
        now->tm_sec);
}

//==============================================================================
//!\fn                        logger::format_line
//
//!\brief  Format logger line
//!\param  sMsg                 - output msg
//!\param  sFormat              - buffer for formatting
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszTag               - trasing tag or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\param  nLine                - code line number
//!\param  args                 - additional args for format
//!\author Khrapov
//!\date   22.10.2020
//==============================================================================
inline void logger::format_line(
    string        & sMsg,
    string        & sFormat,
    level           eLogLevel,
    const char    * pszFormat,
    const char    * pszAssertExpression,
    const char    * /* pszTag */,
    const char    * pszFile,
    const char    * pszFunction,
    int             nLine,
    va_list         args)
{
    sMsg.vprintf(pszFormat, args);

    format_time_string(sFormat);

    switch (eLogLevel)
    {
    case qx::logger::level::info:
        sFormat = "[I][" + sFormat + "][%s::%s(%d)] ";
        break;

    case qx::logger::level::errors:
        sFormat = "[E][" + sFormat + "][%s::%s(%d)] ";
        break;

    case qx::logger::level::asserts:
        sFormat = "[A][" + sFormat + "][%s::%s(%d)][%s] ";
        break;

    default:
        sFormat = "";
        break;
    }

    sFormat += sMsg;

    // assume all psz != nullptr as method must be used in macros only
    if (eLogLevel != qx::logger::level::asserts)
    {
        sMsg.printf(
            sFormat.data(),
            pszFile,
            pszFunction,
            nLine);
    }
    else
    {
        sMsg.printf(
            sFormat.data(),
            pszFile,
            pszFunction,
            nLine,
            pszAssertExpression);
    }

    sMsg += '\n';
}

//==============================================================================
//!\fn                       logger::get_unit_info
//
//!\brief  Get unit info
//!\param  eLogLevel            - log level
//!\param  pszTag               - trasing tag or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\retval                      - unit info pointer
//                                if exists and file or console level is matches
//!\author Khrapov
//!\date   23.10.2020
//==============================================================================
inline logger::runtime_unit_info* logger::get_unit_info(
    level       eLogLevel,
    const char* pszTag,
    const char* pszFile,
    const char* pszFunction)
{
    auto find_unit = [this](std::string_view svUnit)
    {
        return m_RegisteredUnits.find(svUnit);
    };

    runtime_unit_info* pUnitInfo = nullptr;

    auto it = m_RegisteredUnits.end();

    if (pszTag)
        it = find_unit(pszTag);

    if (it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);
    else if (it = find_unit(pszFile); it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);
    else if (it = find_unit(pszFunction); it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);
    else if (it = find_unit(DEFAULT_UNIT); it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);

    if (pUnitInfo && (eLogLevel >= pUnitInfo->get_trace_unit_info().eFileLevel
                   || eLogLevel >= pUnitInfo->get_trace_unit_info().eConsoleLevel))
    {
        return pUnitInfo;
    }
    else
        return nullptr;
}

//================================================================================
//!\fn                     qx::logger::output_to_file
//
//!\brief  Output log string to file
//!\param  sText     - log string text
//!\param  sFileName - file name string
//!\retval           - true if successful
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline bool logger::output_to_file(const string& sText, const string& sFileName)
{
    bool bRet = true;

    switch (m_eLogPolicy)
    {
    case policy::folder_time:
        m_sPath = m_sFolder + m_sSessionTime;
        break;

    case policy::append:
    case policy::clear_then_uppend:
    default:
        m_sPath = m_sFolder;
        break;
    }

    if (!m_sFolder.empty())
        std::filesystem::create_directories(m_sPath.data());

    m_sPath += sFileName;
    std::ofstream ofs(m_sPath.data(), std::ofstream::app);

    if (ofs)
    {
        ofs << sText;
        ofs.close();
    }
    else
    {
        bRet = false;
        std::cerr << "output_to_file error: file " << sFileName;
    }

    return bRet;
}

//================================================================================
//!\fn                    qx::logger::output_to_cout
//
//!\brief  Output log string to console
//!\param  sText        - log string text
//!\param  svAsciiColor - text color
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::output_to_cout(const string& sText, std::string_view svAsciiColor)
{
    if (!svAsciiColor.empty() && m_bUsingColors)
    {
        auto_terminal_color atc(svAsciiColor);
        std::cout << sText;
    }
    else
        std::cout << sText;
}

//================================================================================
//!\fn                       qx::logger::on_create
//
//!\brief  On create logger
//!\author Khrapov
//!\date   11.01.2020
//================================================================================
inline void logger::on_create(void)
{
    format_time_string(m_sTime);
    m_sSessionTime = m_sTime + '/';
    register_unit(DEFAULT_UNIT, { DEFAULT_FILE, level::info, level::info });
}

//================================================================================
//!\fn                      qx::logger::on_terminate
//
//!\brief  On terminate logger
//!\author Khrapov
//!\date   11.01.2020
//================================================================================
inline void logger::on_terminate(void)
{
    for (auto& u : m_RegisteredUnits)
    {
        if (u.second.is_wrote_to_file())
        {
            std::ofstream ofs(u.second.get_trace_unit_info().sLogFileName.data(), std::ofstream::app);
            if (ofs)
            {
                ofs << std::endl << std::endl << std::endl;
                u.second.set_wrote_to_file(false);
            }
        }
    }
}

}
