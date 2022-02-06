/**

    @file      base_logger_stream.h
    @brief     Contains qx::base_logger_stream class
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/suppress_warnings.h>

#include <ctime>
#include <unordered_map>

namespace qx
{

enum class log_level
{
    info,    //!< asserts + errors + info
    errors,  //!< asserts + errors
    asserts, //!< asserts
    none,    //!< disable
};

/**
    @struct log_unit_info
    @date   28.07.2021
**/
struct log_unit_info
{
    using format_func = std::function<void(
        string&     sMsg,                // output message
        string&     sFormat,             // buffer for formatting
        log_level   eLogLevel,           // log level
        const char* pszFormat,           // format string
        const char* pszAssertExpression, // assert expr or nullptr
        const char* pszTag,              // tracing tag
        const char* pszFile,             // file name
        const char* pszFunction,         // function name
        int         nLine,               // code line number
        va_list     args                 // additional args for format
        )>;

    log_level   eUnitLevel = log_level::info;
    format_func formatFunc;
};

/**
    @struct log_unit
    @date   30.07.2021
**/
struct log_unit
{
    log_unit_info*   pUnitInfo = nullptr;
    std::string_view svUnitName;
};

/**

    @class   base_logger_stream
    @brief   Base class for logger streams
    @details ~
    @author  Khrapov
    @date    28.07.2021

**/
class base_logger_stream
{
public:
    static constexpr const char* k_svDefaultUnit = "default";

public:
    /**
        @brief base_logger_stream object constructor
    **/
    base_logger_stream();

    /**
        @brief base_logger_stream object destructor
    **/
    virtual ~base_logger_stream() = default;

    /**
        @brief Output message to the stream
        @param svMessage - message string
        @param logUnit   - log unit info
    **/
    virtual void process_output(
        std::string_view svMessage,
        const log_unit&  logUnit) = 0;

    /**
        @brief Output to stream
        @param eLogLevel           - log level
        @param pszFormat           - format string
        @param pszAssertExpression - assert expr or nullptr
        @param pszTag              - tracing tag
        @param pszFile             - file name string
        @param pszFunction         - function name string
        @param nLine               - code line number
        @param args                - additional args for format
    **/
    void output(
        log_level   eLogLevel,
        const char* pszFormat,
        const char* pszAssertExpression,
        const char* pszTag,
        const char* pszFile,
        const char* pszFunction,
        int         nLine,
        va_list     args);

    /**
        @brief  Try to find log unit info based on trace location info
        @param  pszTag      - tag string
        @param  pszFile     - file string
        @param  pszFunction - function string
        @retval             - log unit info if found
    **/
    std::optional<log_unit> get_unit_info(
        const char* pszTag,
        const char* pszFile,
        const char* pszFunction) noexcept;

    /**
        @brief Register logger unit
        @param svUnitName - unit name (tag, file or function) 
        @param unit       - unit info 
    **/
    void register_unit(std::string_view svUnitName, const log_unit_info& unit);

    /**
        @brief Deregister logger unit
        @param svUnitName - unit name (tag, file or function)
    **/
    void deregister_unit(std::string_view svUnitName);

    /**
        @brief Format logger line
        @param sMsg                - output msg
        @param sFormat             - buffer for formatting
        @param eLogLevel           - log level
        @param pszFormat           - format string
        @param pszAssertExpression - assert expr or nullptr
        @param pszTag              - tracing tag or nullptr
        @param pszFile             - file name string
        @param pszFunction         - function name string
        @param nLine               - code line number
        @param args                - additional args for format
    **/
    static void format_line(
        string&     sMsg,
        string&     sFormat,
        log_level   eLogLevel,
        const char* pszFormat,
        const char* pszAssertExpression,
        const char* pszTag,
        const char* pszFile,
        const char* pszFunction,
        int         nLine,
        va_list     args) noexcept;

    /**
        @brief Format time string to the buffer
        @param sTime - output time buffer
    **/
    static void format_time_string(string& sTime) noexcept;

protected:
    /**
        @brief  Get time buffer string
        @retval - time buffer string
    **/
    string& get_time_buffer() noexcept;

private:
    std::unordered_map<string_hash, log_unit_info> m_Units;
    string                                         m_sBufferFormat;
    string                                         m_sBufferMessage;
    string                                         m_sBufferTime;
};

} // namespace qx

#include <qx/logger/base_logger_stream.inl>
