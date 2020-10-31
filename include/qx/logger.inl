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
//!\fn                    qx::logger::process_output<...Args>
//
//!\brief  Process tracings
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\param  nLine                - code line number
//!\param  svColor              - ascii color string
//!\param  ...args              - additional args for format
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
template<class ... Args>
inline void logger::process_output(
    level               eLogLevel,
    const char        * pszFormat,
    const char        * pszAssertExpression,
    const char        * pszFile,
    const char        * pszFunction,
    int                 nLine,
    std::string_view    svColor,
    Args...             args)
{
    if (auto pUnitInfo = get_unit_info(eLogLevel, pszFormat, pszAssertExpression, pszFile, pszFunction))
    {
        format_line(
            m_sMsg,
            m_sFormat,
            eLogLevel,
            pszFormat,
            pszAssertExpression,
            pszFile, pszFunction,
            nLine,
            args...);

        if (eLogLevel >= pUnitInfo->GetTraceUnitInfo().eFileLevel
            && output_to_file(m_sMsg, pUnitInfo->GetTraceUnitInfo().sLogFileName))
        {
            pUnitInfo->SetWroteToFile();
        }

        if (eLogLevel >= pUnitInfo->GetTraceUnitInfo().eConsoleLevel)
        {
            output_to_cout(m_sMsg, svColor);
        }
    }
}

//================================================================================
//!\fn                     qx::logger::register_unit
//
//!\brief  Register file or function for tracing
//         Register unit with name "default" to update default tracing settings
//!\param  svUnitName - file or function name of "default"
//!\param  unit       - unit info
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::register_unit(std::string_view svUnitName, const unit_info& unit)
{
    if (!unit.sLogFileName.empty())
    {
        if (m_eLogPolicy == policy::clear_then_uppend)
            std::ofstream ofs(unit.sLogFileName.data(), std::ofstream::out | std::ofstream::trunc); //-V808
                                                                                                    // clear file
        m_RegisteredUnits.emplace(svUnitName, unit);
    }
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
//!\fn                    logger::format_line<...Args>
//
//!\brief  Format logger line
//!\param  sMsg                 - output msg
//!\param  sFormat              - buffer for formatting
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\param  nLine                - code line number
//!\param  ...args              - additional args for format
//!\author Khrapov
//!\date   22.10.2020
//==============================================================================
template<class ...Args>
inline void logger::format_line(
    string        & sMsg,
    string        & sFormat,
    level           eLogLevel,
    const char    * pszFormat,
    const char    * pszAssertExpression,
    const char    * pszFile,
    const char    * pszFunction,
    int             nLine,
    Args...         args)
{
    switch (eLogLevel)
    {
    case qx::logger::level::info:
        sFormat = "[I][%s][%s::%s(%d)] ";
        break;

    case qx::logger::level::errors:
        sFormat = "[E][%s][%s::%s(%d)] ";
        break;

    case qx::logger::level::asserts:
        sFormat = "[A][%s][%s::%s(%d)][%s] ";
        break;

    default:
        sFormat = "";
        break;
    }

    sFormat += pszFormat;

    // assume all psz != nullptr as method must be used in macros only
    if (eLogLevel != qx::logger::level::asserts)
    {
        sMsg.format(
            sFormat.data(),
            get_time_str(),
            pszFile,
            pszFunction,
            nLine,
            args...);
    }
    else
    {
        sMsg.format(
            sFormat.data(),
            get_time_str(),
            pszFile,
            pszFunction,
            nLine,
            pszAssertExpression,
            args...);
    }

    sMsg += '\n';
}

//==============================================================================
//!\fn                       logger::get_unit_info
//
//!\brief  Get unit info
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\retval                      - unit info pointer
//                                if exists and file or console level is matches
//!\author Khrapov
//!\date   23.10.2020
//==============================================================================
inline logger::runtime_unit_info* logger::get_unit_info(
    level       eLogLevel,
    const char* pszFormat,
    const char* pszAssertExpression,
    const char* pszFile,
    const char* pszFunction)
{
    runtime_unit_info* pUnitInfo = nullptr;
    if (auto it = m_RegisteredUnits.find(pszFunction); it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);
    else if (auto it = m_RegisteredUnits.find(pszFile); it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);
    else if (auto it = m_RegisteredUnits.find(DEFAULT_UNIT); it != m_RegisteredUnits.end())
        pUnitInfo = &(it->second);

    if (pUnitInfo && (eLogLevel >= pUnitInfo->GetTraceUnitInfo().eFileLevel || eLogLevel >= pUnitInfo->GetTraceUnitInfo().eConsoleLevel))
        return pUnitInfo;
    else
        return nullptr;
}

//==============================================================================
//!\fn                     qx::logger::get_time_str
//
//!\brief  Get time c string
//!\author Khrapov
//!\date   4.09.2019
//==============================================================================
inline const char* logger::get_time_str(void)
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    m_sTime.format(
        "%02d-%02d-%04d_%02d-%02d-%02d",
        now->tm_mday,
        now->tm_mon,
        now->tm_year + 1900,
        now->tm_hour,
        now->tm_min,
        now->tm_sec);

    return m_sTime.data();
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
        if (u.second.GetWroteToFile())
        {
            std::ofstream ofs(u.second.GetTraceUnitInfo().sLogFileName.data(), std::ofstream::app);
            ofs << std::endl << std::endl << std::endl;
            u.second.SetWroteToFile(false);
        }
    }
}

}
