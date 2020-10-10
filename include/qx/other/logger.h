//==============================================================================
//
//!\file                           logger.h
//
//!\brief       Tracing and logging
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

#include <qx/other/singleton.h>
#include <qx/containers/string.h>
#include <qx/other/config.h>

#ifndef QX_ENABLE_DETAIL_TRACE_INFO
    #define QX_ENABLE_DETAIL_TRACE_INFO QX_DEBUG
#endif

#define QX_TRACE_FROM(loggerInstanse, format, ...)              \
    loggerInstanse.process_output(                              \
        qx::logger::level::info,                                \
        format,                                                 \
        nullptr,                                                \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        nullptr,                                                \
        ## __VA_ARGS__)

#define QX_TRACE_ERROR_FROM(loggerInstanse, format, ...)        \
    loggerInstanse.process_output(                              \
        qx::logger::level::errors,                              \
        format,                                                 \
        nullptr,                                                \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        qx::logger::auto_terminal_color::yellow,                \
        ## __VA_ARGS__)

#define QX_TRACE_ASSERT_FROM(loggerInstanse, expr, format, ...) \
    loggerInstanse.process_output(                              \
        qx::logger::level::asserts,                             \
        format,                                                 \
        expr,                                                   \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        qx::logger::auto_terminal_color::red,                   \
        ## __VA_ARGS__)


// redefine theese macros in your own header with renaming only or using you instance of logger

// common info
#define QX_TRACE(format, ...)                                   \
    QX_TRACE_FROM(qx::logger_singleton::get_instance(), format, ## __VA_ARGS__)

// error info
#define QX_TRACE_ERROR(format, ...)                             \
    QX_TRACE_ERROR_FROM(qx::logger_singleton::get_instance(), format, ## __VA_ARGS__)

// assertion failed info
#define QX_TRACE_ASSERT(expr, format, ...)                      \
    QX_TRACE_ASSERT_FROM(qx::logger_singleton::get_instance(), expr, format, ## __VA_ARGS__)

namespace qx
{

//================================================================================
//
//!\class                         qx::logger
//
//!\brief   Logger class
//!\details ~
//
//!\author  Khrapov
//!\date    10.01.2020
//
//================================================================================
class logger
{
public:

    struct auto_terminal_color
    {
        static constexpr const char* reset          = "\033[0m";
        static constexpr const char* red            = "\033[0;31m";
        static constexpr const char* red_bold       = "\033[1;31m";
        static constexpr const char* green          = "\033[0;32m";
        static constexpr const char* green_bold     = "\033[1;32m";
        static constexpr const char* yellow         = "\033[0;33m";
        static constexpr const char* yellow_bold    = "\033[01;33m";
        static constexpr const char* blue           = "\033[0;34m";
        static constexpr const char* blue_bold      = "\033[1;34m";
        static constexpr const char* magenta        = "\033[0;35m";
        static constexpr const char* magenta_bold   = "\033[1;35m";
        static constexpr const char* cyan           = "\033[0;36m";
        static constexpr const char* cyan_bold      = "\033[1;36m";

        auto_terminal_color (const char* color) { std::cout << color; }
        ~auto_terminal_color(void)              { std::cout << reset; }
    };

    //!< Log files policy
    enum class policy
    {
        append,             //!< append all
        clear_then_uppend,  //!< clear file at start, then append
        folder_time,        //!< create new folder with time name
    };

    //!< Log level
    enum class level
    {
        info,       // _TR_ASSERT + TR_ERROR + TRACE
        errors,     // _TR_ASSERT + TR_ERROR
        asserts,    // _TR_ASSERT
        none,       // disable
    };

    //================================================================================
    //
    //!\struct                       TraceUnitInfo
    //!\author  Khrapov
    //!\date    10.01.2020
    //================================================================================
    struct TraceUnitInfo
    {
        string  sLogFileName;
        level   eConsoleLevel   = level::info;
        level   eFileLevel      = level::info;
    };

    using TraceUnitInfoMap = std::unordered_map<string, TraceUnitInfo>;

public:

         logger                     (void);
         ~logger                    (void);

    template<class ... Args>
    void process_output             (level                  eLogLevel,
                                     const char           * pszFormat,
                                     const char           * pszAssertExpression,
                                     const char           * pszFile,
                                     const char           * pszFunction,
                                     int                    nLine,
                                     const char           * pszColor,
                                     Args...                args);

    void register_unit              (const char           * pszUnitName,
                                     const TraceUnitInfo  & unit);
    void deregister_unit            (const char           * pszUnitName);

    void set_log_policy             (policy                 eLogPolicy);
    void set_logs_folder            (const char           * pszFolder);
    void set_using_colors           (bool                   bUsingColors);
    void set_keep_template_params   (bool                   bKeepTemplateParams);
    void set_keep_lambda_id         (bool                   bKeepLambdaId);

protected:

    void on_create                  (void);
    void on_terminate               (void);

private:

    const char* get_time_str        (void);

    void output_to_file             (const string         & sText,
                                     const string         & sFileName);
    void output_to_cout             (const string         & sText,
                                     const char           * pszAnsiiColor);

private:

    // buffers to decrease number of allocations
    string              m_sTime                 = "";
    string              m_sFormat               = "";
    string              m_sMsg                  = "";
    string              m_sFunction             = "";
    string              m_sPath                 = "";

    policy              m_eLogPolicy            = policy::append;
    string              m_sSessionTime          = string(get_time_str()) + '/';
    string              m_sFolder               = "";
    bool                m_bUsingColors          = false;
    bool                m_bKeepTemplateParams   = false;
    bool                m_bKeepLambdaId         = false;
    TraceUnitInfoMap    m_RegisteredUnits;
};

inline      logger::logger                   (void)                            { on_create();                                 }
inline      logger::~logger                  (void)                            { on_terminate();                              }
inline void logger::deregister_unit          (const char* pszUnitName)         { m_RegisteredUnits.erase(pszUnitName);        }
inline void logger::set_log_policy           (policy      eLogPolicy)          { m_eLogPolicy = eLogPolicy;                   }
inline void logger::set_using_colors         (bool        bUsingColors)        { m_bUsingColors = bUsingColors;               }
inline void logger::set_keep_template_params (bool        bKeepTemplateParams) { m_bKeepTemplateParams = bKeepTemplateParams; }
inline void logger::set_keep_lambda_id       (bool        bKeepLambdaId)       { m_bKeepLambdaId = bKeepLambdaId;             }

class logger_singleton : public logger
{
    QX_SINGLETON_CD(logger_singleton, on_create();, on_terminate(););
};

}

#include <qx/other/logger.inl>
