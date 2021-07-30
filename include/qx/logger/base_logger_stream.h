//==============================================================================
//
//!\file                      base_logger_stream.h
//
//!\brief       Contains qx::base_logger_stream class
//!\details     ~
//
//!\author      Khrapov
//!\date        28.07.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/suppress_warnings.h>
#include <qx/containers/string.h>

#include <ctime>
#include <optional>
#include <unordered_map>

namespace qx
{

//!< Log level
enum class log_level
{
    info,       //!< asserts + errors + info
    errors,     //!< asserts + errors
    asserts,    //!< asserts
    none,       //!< disable
};

//==============================================================================
//
//!\struct                     qx::log_unit_info
//!\author  Khrapov
//!\date    28.07.2021
//==============================================================================
struct log_unit_info
{
    using format_func = std::function<
        void(
            string            & sMsg,                   // output message
            string            & sFormat,                // buffer for formatting
            log_level           eLogLevel,              // log level
            const char        * pszFormat,              // format string
            const char        * pszAssertExpression,    // assert expr or nullptr
            std::string_view    svTag,                  // tracing tag or nullptr
            std::string_view    svFile,                 // file name string
            std::string_view    svFunction,             // function name string
            int                 nLine,                  // code line number
            va_list             args                    // additional args for format
        )
    >;

    log_level   eUnitLevel  = log_level::info;
    format_func formatFunc;
};

//==============================================================================
//
//!\struct                        qx::log_unit
//!\author  Khrapov
//!\date    30.07.2021
//==============================================================================
struct log_unit
{
    log_unit_info* pUnitInfo = nullptr;
    std::string_view    svUnitName;
};

//==============================================================================
//
//!\class                    qx::base_logger_stream
//
//!\brief   Base class for logger streams
//!\details ~
//
//!\author  Khrapov
//!\date    28.07.2021
//
//==============================================================================
class base_logger_stream
{
public:

    static constexpr std::string_view DEFAULT_UNIT = "default";

public:

    base_logger_stream(void);
    virtual ~base_logger_stream(void) = default;

    virtual void process_output(
        std::string_view        svMessage,
        log_unit                logUnit) = 0;

    void output(
        log_level               eLogLevel,
        const char            * pszFormat,
        const char            * pszAssertExpression,
        std::string_view        svTag,
        std::string_view        svFile,
        std::string_view        svFunction,
        int                     nLine,
        va_list                 args);

    std::optional<log_unit> get_unit_info(
        std::string_view        svTag,
        std::string_view        svFile,
        std::string_view        svFunction) noexcept;

    void register_unit(
        std::string_view        svUnitName,
        const log_unit_info   & unit);

    void deregister_unit(
        std::string_view        svUnitName);

    static void format_line(
        string                & sMsg,
        string                & sFormat,
        log_level               eLogLevel,
        const char            * pszFormat,
        const char            * pszAssertExpression,
        std::string_view        svTag,
        std::string_view        svFile,
        std::string_view        svFunction,
        int                     nLine,
        va_list                 args) noexcept;

    static void format_time_string(
        string                & sTime) noexcept;

protected:

    string& get_time_buffer(void) noexcept;

private:

    std::unordered_map<string_hash, log_unit_info> m_Units;
    string  m_sBufferFormat;
    string  m_sBufferMessage;
    string  m_sBufferTime;
};

inline string& base_logger_stream::get_time_buffer(void) noexcept
{
    return m_sBufferTime;
}

}

#include <qx/logger/base_logger_stream.inl>
