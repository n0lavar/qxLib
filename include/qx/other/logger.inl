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
//!\param  pszColor             - ansi color string
//!\param  ...args              - additional args for format
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
template<class ... Args>
inline void logger::process_output(
    level         eLogLevel,
    const char  * pszFormat,
    const char  * pszAssertExpression,
    const char  * pszFile,
    const char  * pszFunction,
    int           nLine,
    const char  * pszColor,
    Args...       args)
{
    TraceUnitInfo* pUnitInfo = nullptr;
    if (auto it = m_RegisteredUnits.find(pszFunction); it != m_RegisteredUnits.cend())
        pUnitInfo = &(it->second);
    else if (auto it = m_RegisteredUnits.find(pszFile); it != m_RegisteredUnits.cend())
        pUnitInfo = &(it->second);
    else if (auto it = m_RegisteredUnits.find("default"); it != m_RegisteredUnits.cend())
        pUnitInfo = &(it->second);

    if (pUnitInfo && (eLogLevel >= pUnitInfo->eFileLevel || eLogLevel >= pUnitInfo->eConsoleLevel))
    {
        m_sFormat.clear();

        switch (eLogLevel)
        {
        case qx::logger::level::info:
            m_sFormat = "[I][%s][%s::%s(%d)] ";
            break;

        case qx::logger::level::errors:
            m_sFormat = "[E][%s][%s::%s(%d)] ";
            break;

        case qx::logger::level::asserts:
            m_sFormat = "[A][%s][%s::%s(%d)][%s] ";
            break;

        default:
            m_sFormat = "";
            break;
        }

        m_sFormat += pszFormat;

        m_sFunction.clear();

#if _MSC_VER

        // delete long and ugly lambda name from debug
        if (const char* pLambdaStr = std::strstr(pszFunction, "{ctor}::<lambda_"); pLambdaStr != nullptr)
        {
            constexpr int LAMBDA_NAME_SIZE = 62;

            m_sFunction = pszFunction;
            m_sFunction.erase(pLambdaStr - pszFunction, LAMBDA_NAME_SIZE);
            m_sFunction.insert(pLambdaStr - pszFunction, "lambda");
        }

#endif

#if QX_ENABLE_DETAIL_TRACE_INFO

        // delete long and ugly lambda name from debug
        if (const char* pLambdaStr = std::strstr(pszFunction, "{ctor}::<lambda_"); pLambdaStr != nullptr)
        {
            constexpr int LAMBDA_NAME_SIZE = 62;

            m_sFunction = pszFunction;
            m_sFunction.erase(pLambdaStr - pszFunction, LAMBDA_NAME_SIZE);
            m_sFunction.insert(pLambdaStr - pszFunction, "lambda");
        }

#endif

#if 0

        if (auto it = m_sMsg.find("[::(0)]"); it != string::npos)
            m_sMsg.erase(it, 7);

#endif

        // assume pszAssertExpression != nullptr as method must be used in macros only
        if (eLogLevel != qx::logger::level::asserts)
        {
            m_sMsg.format(
                m_sFormat.data(),
                get_time_str(),
                pszFile,
                m_sFunction.empty() ? pszFunction : m_sFunction.data(),
                nLine,
                args...);
        }
        else
        {
            m_sMsg.format(
                m_sFormat.data(),
                get_time_str(),
                pszFile,
                m_sFunction.empty() ? pszFunction : m_sFunction.data(),
                nLine,
                pszAssertExpression,
                args...);
        }

        m_sMsg += '\n';

        if (eLogLevel >= pUnitInfo->eFileLevel)
            output_to_file(m_sMsg, pUnitInfo->sLogFileName);

        if (eLogLevel >= pUnitInfo->eConsoleLevel)
            output_to_cout(m_sMsg, pszColor);
    }
}

//================================================================================
//!\fn                     qx::logger::register_unit
//
//!\brief  Register file or function for tracing
//         Register unit with name "default" to update default tracing settings
//!\param  pszUnitName - file or function name of "default"
//!\param  unit        - unit info
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::register_unit(const char* pszUnitName, const TraceUnitInfo& unit)
{
    if (!unit.sLogFileName.empty())
    {
        if (m_eLogPolicy == policy::clear_then_uppend)
            std::ofstream ofs(unit.sLogFileName.data(), std::ofstream::out | std::ofstream::trunc); //-V808
                                                                                                    // clear file
        m_RegisteredUnits[pszUnitName] = unit;
    }
}

inline void logger::set_logs_folder(const char* pszFolder)
{
    m_sFolder = pszFolder;
    if (!m_sFolder.empty() && !m_sFolder.ends_with('/'))
        m_sFolder += '/';
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
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::output_to_file(const string& sText, const string& sFileName)
{
    std::ofstream ofs;
    ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    m_sPath.clear();

    try
    {
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
        ofs.open(m_sPath.data(), std::ofstream::app);
        ofs << sText;
        ofs.close();
    }
    catch (const std::system_error& e)
    {
        std::cerr
            << "output_to_file error: file " << sFileName
            << ", error " << e.code().value()
            << ", msg " << e.what() << std::endl;
    }
}

//================================================================================
//!\fn                    qx::logger::output_to_cout
//
//!\brief  Output log string to console
//!\param  sText         - log string text
//!\param  pszAnsiiColor - text color
//!\author Khrapov
//!\date   10.01.2020
//================================================================================
inline void logger::output_to_cout(const string& sText, const char* pszAnsiiColor)
{
    if (pszAnsiiColor && m_bUsingColors)
    {
        auto_terminal_color atc(pszAnsiiColor);
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
    register_unit("default", { "default.log", level::info, level::info });
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
    for (const auto& u : m_RegisteredUnits)
    {
        std::ofstream ofs(u.second.sLogFileName.data(), std::ofstream::app);
        ofs << std::endl << std::endl << std::endl;
    }
}

}
