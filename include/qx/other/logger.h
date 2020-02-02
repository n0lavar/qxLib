//============================================================================
//
//!\file                           trace.h
//
//!\brief       Tracing and logging
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include <qx/other/singleton.h>
#include <qx/containers/qxstring.h>
#include <qx/other/useful_macros.h>
#include <qx/other/typedefs.h>

namespace qx
{

constexpr cstr ANSI_COLOR_RESET            = "\033[0m";
constexpr cstr ANSI_COLOR_RED              = "\033[0;31m";
constexpr cstr ANSI_COLOR_RED_BOLD         = "\033[1;31m";
constexpr cstr ANSI_COLOR_GREEN            = "\033[0;32m";
constexpr cstr ANSI_COLOR_GREEN_BOLD       = "\033[1;32m";
constexpr cstr ANSI_COLOR_YELLOW           = "\033[0;33m";
constexpr cstr ANSI_COLOR_YELLOW_BOLD      = "\033[01;33m";
constexpr cstr ANSI_COLOR_BLUE             = "\033[0;34m";
constexpr cstr ANSI_COLOR_BLUE_BOLD        = "\033[1;34m";
constexpr cstr ANSI_COLOR_MAGENTA          = "\033[0;35m";
constexpr cstr ANSI_COLOR_MAGENTA_BOLD     = "\033[1;35m";
constexpr cstr ANSI_COLOR_CYAN             = "\033[0;36m";
constexpr cstr ANSI_COLOR_CYAN_BOLD        = "\033[1;36m";

#define TRACE(format, ...)            qx::logger::getInstance().ProcessOutput(qx::logger::level::all,     "[I][%s][%s::%s(%d)] "           format " \n", qx::logger::getInstance().GetTimeStr(), __SHORT_FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define TR_ERROR(format, ...)         qx::logger::getInstance().ProcessOutput(qx::logger::level::errors,  "[E][%s][%s::%s(%d)] "           format " \n", qx::logger::getInstance().GetTimeStr(), __SHORT_FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define _TR_ASSERT(expr, format, ...) qx::logger::getInstance().ProcessOutput(qx::logger::level::asserts, "[A][%s][%s::%s(%d)][" expr "] " format " \n", qx::logger::getInstance().GetTimeStr(), __SHORT_FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

//==============================================================================
//
//!\class                           logger
//
//!\brief   Logger singleton
//!\details ~
//
//!\author  Khrapov
//!\date    10.01.2020
//
//==============================================================================
class logger
{
    SINGLETON_CD(logger, OnCreate();, OnTerminate(););

    struct sAutoPrintfColor
    {
        sAutoPrintfColor(cstr color) { printf("%s", color);            }
        ~sAutoPrintfColor(void)      { printf("%s", ANSI_COLOR_RESET); }
    };

public:

    //!< Log files policy
    enum class policy
    {
        first = 0,
        append,             //!< append all
        clear_then_uppend,  //!< clear file at start, then append
        folder_time,        //!< create new folder with time name
        last
    };

    //!< Log level
    enum class level
    {
        first = 0,
        all,        // _TR_ASSERT + TR_ERROR + TRACE
        errors,     // _TR_ASSERT + TR_ERROR
        asserts,    // _TR_ASSERT
        none,       // disable
        last
    };

    //==============================================================================
    //
    //!\struct                       TraceUnitInfo
    //!\author  Khrapov
    //!\date    10.01.2020
    //==============================================================================
    struct TraceUnitInfo
    {
        string  sLogFileName;
        level   eConsoleLevel   = level::all;
        level   eFileLevel      = level::all;
    };

    using TraceUnitInfoMap = std::unordered_map<string, TraceUnitInfo>;

public:

    template<class ... Args>
    void ProcessOutput      (level                  eLogLevel,
                             cstr                   pszFormat,
                             cstr                   pszTime,
                             cstr                   pszFile,
                             cstr                   pszFunction,
                             int                    nLine,
                             Args...                args);

    void RegisterUnit       (cstr                   pszUnitName,
                             const TraceUnitInfo  & unit);
    void DeregisterUnit     (cstr                   pszUnitName);

    void SetLogPolicy       (policy                 eLogPolicy);

    cstr GetTimeStr         (void);

private:

    void OutputToFile       (const qx::string     & sText,
                             const qx::string     & sFileName);
    void OutputToConsole    (const qx::string     & sText,
                             cstr                   pszAnsiiColor);

    void OnCreate           (void);
    void OnTerminate        (void);

private:

    policy              m_eLogPolicy        = policy::append;
    string              m_sSessionTime      = string(GetTimeStr()) + "/";
    TraceUnitInfoMap    m_RegisteredUnits;
};

}

#include <qx/other/logger.inl>