//============================================================================
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
//============================================================================

namespace qx
{

//==============================================================================
//!\fn                        Log::ProcessOutput<...Args>
//
//!\brief  Process tracings
//!\param  eLogLevel            - log level
//!\param  pszFormat            - format string
//!\param  pszAssertExpression  - assert expr or nullptr
//!\param  pszFile              - file name string
//!\param  pszFunction          - function name string
//!\param  nLine                - code line number
//!\param  ...args              - additional args for format
//!\author Khrapov
//!\date   10.01.2020
//==============================================================================
template<class ... Args>
inline void logger::ProcessOutput(level         eLogLevel,
                                  const char  * pszFormat, 
                                  const char  * pszAssertExpression,
                                  const char  * pszFile, 
                                  const char  * pszFunction,
                                  int           nLine, 
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
        static qx::string sFormat;
        static qx::string sMsg;

        switch (eLogLevel)
        {
        case qx::logger::level::all:
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

#if ENABLE_DETAIL_TRACE_INFO

        static qx::string sFunction;
        sFunction = "";
        // delete long and ugly lambda name from debug
        if (const char* pLambdaStr = std::strstr(pszFunction, "{ctor}::<lambda_"); pLambdaStr != nullptr)
        {
            constexpr int LAMBDA_NAME_SIZE = 62;

            sFunction = pszFunction;
            sFunction.erase(pLambdaStr - pszFunction, LAMBDA_NAME_SIZE);
            sFunction.insert(pLambdaStr - pszFunction, "lambda");
        }

        // assume pszAssertExpression != nullptr as method must be used in macros only
        if (eLogLevel != qx::logger::level::asserts)
        {
            sMsg.format(sFormat.data(),
                        GetTimeStr(),
                        pszFile,
                        sFunction.empty() ? pszFunction : sFunction.data(),
                        nLine,
                        args...);
        }
        else
        {
            sMsg.format(sFormat.data(),
                        GetTimeStr(),
                        pszFile,
                        sFunction.empty() ? pszFunction : sFunction.data(),
                        nLine,
                        pszAssertExpression,
                        args...);
        }

#else

        sMsg.format(sFormat.data(),
                    GetTimeStr(),
                    pszFile,
                    pszFunction,
                    nLine,
                    pszAssertExpression,
                    args...);

        if (auto it = sMsg.find("[::(0)]"); it != qx::string::npos)
            sMsg.erase(it, 7);

#endif

        sMsg += '\n';

        if (eLogLevel >= pUnitInfo->eFileLevel)
            OutputToFile(sMsg, pUnitInfo->sLogFileName);

        if (eLogLevel >= pUnitInfo->eConsoleLevel)
        {
            const char* pszColor = nullptr;
            switch (eLogLevel)
            {
            case level::all:     pszColor = ANSI_COLOR_RESET;    break;
            case level::errors:  pszColor = ANSI_COLOR_YELLOW;   break;
            case level::asserts: pszColor = ANSI_COLOR_RED;      break;
            }

            OutputToConsole(sMsg, pszColor);
        }
    }
}

//==============================================================================
//!\fn                       logger::RegisterUnit
//
//!\brief  Register file or function for tracing
//         Register unit with name "default" to update default tracing settings
//!\param  pszUnitName - file or function name of "default"
//!\param  unit        - unit info
//!\author Khrapov
//!\date   10.01.2020
//==============================================================================
inline void logger::RegisterUnit(const char* pszUnitName, const TraceUnitInfo& unit)
{
    if (m_eLogPolicy == policy::clear_then_uppend)
        std::ofstream ofs(unit.sLogFileName.data(), std::ofstream::out | std::ofstream::trunc); //-V808
                                                                                                // clear file
    if(!unit.sLogFileName.empty())
        m_RegisteredUnits[pszUnitName] = unit;
}

//==============================================================================
//!\fn                      logger::DeregisterUnit
//
//!\brief  Deregister unit
//!\param  pszUnitName - unit name
//!\author Khrapov
//!\date   11.01.2020
//==============================================================================
inline void logger::DeregisterUnit(const char* pszUnitName)
{
    m_RegisteredUnits.erase(pszUnitName);
}

//==============================================================================
//!\fn                       logger::SetLogPolicy
//
//!\brief  Set log policy
//!\author Khrapov
//!\date   11.01.2020
//==============================================================================
inline void logger::SetLogPolicy(policy eLogPolicy)
{
    m_eLogPolicy = eLogPolicy;
}

//============================================================================
//!\fn                       logger::GetTimeStr
//
//!\brief  Get time c string
//!\author Khrapov
//!\date   4.09.2019
//============================================================================
inline const char* logger::GetTimeStr(void)
{
    static qx::string ret(19, '\0');

    std::time_t t = time(0);
    std::tm now;
    localtime_s(&now, &t);
    ret.format("%02d-%02d-%04d_%02d-%02d-%02d", 
               now.tm_mday, 
               now.tm_mon, 
               now.tm_year + 1900,
               now.tm_hour, 
               now.tm_min, 
               now.tm_sec);

    return ret.data();
}

//==============================================================================
//!\fn                       logger::OutputToFile
//
//!\brief  Output log string to file
//!\param  sText     - log string text
//!\param  sFileName - file name string
//!\author Khrapov
//!\date   10.01.2020
//==============================================================================
inline void logger::OutputToFile(const qx::string& sText, const qx::string& sFileName)
{
    std::ofstream ofs;
    ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    try
    {
        qx::string sPath;

        switch (m_eLogPolicy)
        {
        case policy::folder_time:
            sPath = "logs/" + m_sSessionTime;
            break;

        case policy::append:
        case policy::clear_then_uppend:
        default:
            sPath = "logs/";
            break;
        }

        std::filesystem::create_directories(sPath.data());
        ofs.open((sPath + sFileName).data(), std::ios::out | std::ios::app);
        ofs << sText.data();
        ofs.close();
    }
    catch (const std::system_error& e)
    {
        std::cerr 
            << "OutputToFile error: file " << sFileName.data() 
            << ", error " << e.code().value()
            << ", msg " << e.what() << std::endl;
    }
}

//==============================================================================
//!\fn                      logger::OutputToConsole
//
//!\brief  Output log string to console
//!\param  sText         - log string text
//!\param  pszAnsiiColor - text color
//!\author Khrapov
//!\date   10.01.2020
//==============================================================================
inline void logger::OutputToConsole(const qx::string& sText, const char* pszAnsiiColor)
{
    SAutoPrintfColor apc(pszAnsiiColor);
    printf("%s", sText.data());
}

//==============================================================================
//!\fn                         logger::OnCreate
//
//!\brief  On create singleton
//!\author Khrapov
//!\date   11.01.2020
//==============================================================================
inline void logger::OnCreate(void)
{
    RegisterUnit("default", { "log.txt", level::all, level::all });
}

//==============================================================================
//!\fn                        logger::OnTerminate
//
//!\brief  On terminate singleton
//!\author Khrapov
//!\date   11.01.2020
//==============================================================================
inline void logger::OnTerminate(void)
{
    for (const auto& u : m_RegisteredUnits)
    {
        std::ofstream ofs(u.second.sLogFileName.data(), std::ios::out | std::ios::app);
        ofs << std::endl << std::endl << std::endl;
    }
}

}