/**

    @file      base_logger_stream.h
    @brief     Contains qx::base_logger_stream class
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_converters.h>
#include <qx/macros/suppress_warnings.h>

#include <ctime>
#include <functional>
#include <unordered_map>

namespace qx
{

enum class log_level
{
    very_verbose,
    verbose,
    log,
    important,
    warning,
    error,
    critical,
    none,
};

template<class char_type>
struct logger_buffers
{
    basic_string<char_type> sMessage; // result message (output)
    basic_string<char_type> sFormat;
    basic_string<char_type> sTag;
    basic_string<char_type> sFile;
    basic_string<char_type> sFunction;
};

struct log_unit_info
{
    template<class char_type>
    using format_func = std::function<void(
        logger_buffers<char_type>& buffers,
        log_level                  eLogLevel,   // log level
        const char_type*           pszFormat,   // format string
        const char_type*           pszTag,      // tracing tag
        const char_type*           pszFile,     // file name
        const char_type*           pszFunction, // function name
        int                        nLine,       // code line number
        va_list                    args         // additional args for format
        )>;

    /**
        @brief  Get format func corresponding to char type
        @tparam char_type - char type
        @retval           - format func
    **/
    template<class char_type>
    const format_func<char_type>& get_format_func();

    log_level            eMinLogLevel = log_level::log;
    format_func<char>    formatFuncChar;
    format_func<wchar_t> formatFuncWChar;
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
        @brief  Output to stream
        @tparam char_type   - char type, typically char or wchar_t
        @param  eLogLevel   - log level
        @param  pszFormat   - format string
        @param  pszTag      - tracing tag
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  args        - additional args for format
    **/
    template<class char_type>
    void log(
        log_level        eLogLevel,
        const char_type* pszFormat,
        const char*      pszTag,
        const char*      pszFile,
        const char*      pszFunction,
        int              nLine,
        va_list          args);

    /**
        @brief Register logger unit
        @param svUnitName - unit name (tag, file or function) 
        @param unit       - unit info 
    **/
    void register_unit(std::string_view svUnitName, const log_unit_info& unit) noexcept;

    /**
        @brief Deregister logger unit
        @param svUnitName - unit name (tag, file or function)
    **/
    void deregister_unit(std::string_view svUnitName) noexcept;

    /**
        @brief  Format time string to the buffer
        @tparam char_type - char type
        @param  sTime - output time buffer
    **/
    template<class char_type>
    static void format_time_string(basic_string<char_type>& sTime) noexcept;

protected:
    /**
        @brief  Get string buffers
        @tparam char_type - char type
        @retval           - string buffers
    **/
    template<class char_type>
    logger_buffers<char_type>& get_string_buffers() noexcept;

private:
    /**
        @brief Proceed stream logging
        @param svMessage - message string
        @param logUnit   - log unit info
        @param eLogLevel - this message log level
    **/
    virtual void do_log(std::string_view svMessage, const log_unit& logUnit, log_level eLogLevel) = 0;

    /**
        @brief Proceed stream logging
        @param svMessage - message string
        @param logUnit   - log unit info
        @param eLogLevel - this message log level
    **/
    virtual void do_log(std::wstring_view svMessage, const log_unit& logUnit, log_level eLogLevel) = 0;

    /**
        @brief  Try to find log unit info based on trace location info
        @param  pszTag      - tag string
        @param  pszFile     - file string
        @param  pszFunction - function string
        @retval             - log unit info if found
    **/
    std::optional<log_unit> get_unit_info(const char* pszTag, const char* pszFile, const char* pszFunction) noexcept;

    /**
        @brief Format logger line
        @tparam char_type   - char type, typically char or wchar_t
        @param  buffers     - string buffers to reduce num of allocations
        @param  eLogLevel   - log level
        @param  pszFormat   - format string
        @param  pszTag      - tracing tag or nullptr
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  args        - additional args for format
    **/
    template<class char_type>
    static void format_line(
        logger_buffers<char_type>& buffers,
        log_level                  eLogLevel,
        const char_type*           pszFormat,
        const char_type*           pszTag,
        const char_type*           pszFile,
        const char_type*           pszFunction,
        int                        nLine,
        va_list                    args) noexcept;

private:
    std::unordered_map<string_hash, log_unit_info> m_Units;
    logger_buffers<char>                           m_BuffersChar;
    logger_buffers<wchar_t>                        m_BuffersWChar;
};

} // namespace qx

#include <qx/logger/base_logger_stream.inl>
