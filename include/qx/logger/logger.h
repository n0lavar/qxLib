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

#include <qx/suppress_warnings.h>
#include <qx/containers/string.h>
#include <qx/patterns/singleton.h>

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>

#define QX_TRACE_FROM(loggerInstanse, format, ...)              \
    loggerInstanse.process_output(                              \
        qx::logger::level::info,                                \
        format,                                                 \
        nullptr,                                                \
        nullptr,                                                \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        std::string_view(),                                     \
        ## __VA_ARGS__)

#define QX_TRACE_ERROR_FROM(loggerInstanse, format, ...)        \
    loggerInstanse.process_output(                              \
        qx::logger::level::errors,                              \
        format,                                                 \
        nullptr,                                                \
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
        # expr,                                                 \
        nullptr,                                                \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        qx::logger::auto_terminal_color::red,                   \
        ## __VA_ARGS__)


// redefine theese macros in your own header with renaming only or using your instance of logger

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

class logger_worker;

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
    friend class logger_worker;

public:

    struct auto_terminal_color
    {
        static constexpr std::string_view reset         = "\033[0m";
        static constexpr std::string_view red           = "\033[0;31m";
        static constexpr std::string_view red_bold      = "\033[1;31m";
        static constexpr std::string_view green         = "\033[0;32m";
        static constexpr std::string_view green_bold    = "\033[1;32m";
        static constexpr std::string_view yellow        = "\033[0;33m";
        static constexpr std::string_view yellow_bold   = "\033[01;33m";
        static constexpr std::string_view blue          = "\033[0;34m";
        static constexpr std::string_view blue_bold     = "\033[1;34m";
        static constexpr std::string_view magenta       = "\033[0;35m";
        static constexpr std::string_view magenta_bold  = "\033[1;35m";
        static constexpr std::string_view cyan          = "\033[0;36m";
        static constexpr std::string_view cyan_bold     = "\033[1;36m";

        auto_terminal_color (std::string_view color) { std::cout << color; }
        ~auto_terminal_color(void)                   { std::cout << reset; }
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
        info,               // asserts + errors + info
        errors,             // asserts + errors
        asserts,            // asserts
        none,               // disable
    };

    struct unit_info
    {
        using format_func = std::function<
            void(
                string    & sMsg,               // output message
                string    & sFormat,            // buffer for formatting
                level       eLogLevel,          // log level
                const char* pszFormat,          // format string
                const char* pszAssertExpression,// assert expr or nullptr
                const char* pszTag,             // trasing tag or nullptr
                const char* pszFile,            // file name string
                const char* pszFunction,        // function name string
                int         nLine,              // code line number
                va_list     args                // additional args for format
            )
        >;

        string      sLogFileName;
        level       eConsoleLevel   = level::info;
        level       eFileLevel      = level::info;
        format_func formatFunc      = logger::format_line;  // function for formatting this unit

        unit_info() = default;
        unit_info(
            const string      & _sLogFileName,
            level               _eConsoleLevel  = level::info,
            level               _eFileLevel     = level::info,
            const format_func & _formatFunc     = logger::format_line)
            : sLogFileName  (_sLogFileName)
            , eConsoleLevel (_eConsoleLevel)
            , eFileLevel    (_eFileLevel)
            , formatFunc    (_formatFunc)
        {
        }
    };

    class runtime_unit_info
    {
    public:

        runtime_unit_info(const unit_info& u)
            : m_TraceUnitInfo(u)
        {
        }

        const unit_info& get_trace_unit_info() const
        {
            return m_TraceUnitInfo;
        }

        bool is_wrote_to_file() const
        {
            return m_bWroteToFile;
        }

        void set_wrote_to_file(bool bWrote = true)
        {
            m_bWroteToFile = bWrote;
        }

    private:

        unit_info m_TraceUnitInfo;
        bool m_bWroteToFile = false;
    };

    static constexpr std::string_view DEFAULT_UNIT = "default";
    static constexpr std::string_view DEFAULT_FILE = "default.log";

public:

                logger              (void);
                ~logger             (void);

    void        process_output      (level              eLogLevel,
                                     const char       * pszFormat,
                                     const char       * pszAssertExpression,
                                     const char       * pszTag,
                                     const char       * pszFile,
                                     const char       * pszFunction,
                                     int                nLine,
                                     std::string_view   svColor,
                                     ...);

    void        register_unit       (std::string_view   svUnitName,
                                     const unit_info  & unit);
    void        deregister_unit     (std::string_view   svUnitName);

    void        set_log_policy      (policy             eLogPolicy);
    void        set_logs_folder     (const char       * pszFolder);
    void        set_using_colors    (bool               bUsingColors);

    static void format_time_string  (string           & sTime);

protected:

    void        on_create           (void);
    void        on_terminate        (void);

private:

    using trace_unit_info_map = std::unordered_map<string_hash, runtime_unit_info>;

    static void format_line        (string            & sMsg,
                                    string            & sFormat,
                                    level               eLogLevel,
                                    const char        * pszFormat,
                                    const char        * pszAssertExpression,
                                    const char        * pszTag,
                                    const char        * pszFile,
                                    const char        * pszFunction,
                                    int                 nLine,
                                    va_list             args);

    runtime_unit_info* get_unit_info(level              eLogLevel,
                                    const char        * pszTag,
                                    const char        * pszFile,
                                    const char        * pszFunction);

    bool        output_to_file      (const string     & sText,
                                     const string     & sFileName);
    void        output_to_cout      (const string     & sText,
                                     std::string_view   svAsciiColor);

private:

    // buffers to decrease number of allocations
    string              m_sTime             = "";
    string              m_sFormat           = "";
    string              m_sMsg              = "";
    string              m_sPath             = "";

    policy              m_eLogPolicy        = policy::append;
    string              m_sSessionTime      = "";
    string              m_sFolder           = "";
    bool                m_bUsingColors      = false;
    trace_unit_info_map m_RegisteredUnits;
};

inline logger::logger(void)
{
    on_create();
}
inline logger::~logger(void)
{
    on_terminate();
}
inline void logger::set_log_policy(policy eLogPolicy)
{
    m_eLogPolicy = eLogPolicy;
}
inline void logger::set_using_colors(bool bUsingColors)
{
    m_bUsingColors = bUsingColors;
}

class logger_singleton : public logger
{
    QX_SINGLETON_CD(logger_singleton, on_create();, on_terminate(););
};

}

#include <qx/logger/logger.inl>
