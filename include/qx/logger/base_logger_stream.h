/**

    @file      base_logger_stream.h
    @brief     Contains qx::base_logger_stream class
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/containers/string/string_converters.h>
#include <qx/internal/perf_scope.h>
#include <qx/macros/suppress_warnings.h>

#include <ctime>
#include <functional>
#include <mutex>
#include <unordered_map>

QX_DEFINE_CATEGORY(CatLogger, qx::color::dark_turquoise());

namespace qx
{

enum class log_level
{
    very_verbose, // very frequently repeated messages, for example, on every update
    verbose,      // messages you don't want to be displayed by default
    log,          // default level
    important,    // same as log but highlighted if possible
    warning,      // not yet an error, but something to look out for
    error,        // an error after which it is possible to continue the program
    critical,     // an error that makes it impossible to continue the program
    none,         // message is not displayed
};

struct logger_color_range
{
    std::pair<size_t, size_t> range { 0, 0 };
    color                     rangeColor = color::white();
};

template<class char_t>
struct logger_buffer
{
    basic_string<char_t> sMessage; // result message (output)
    basic_string<char_t> sFormat;
    basic_string<char_t> sFile;
    basic_string<char_t> sFunction;
    basic_string<char_t> sCategory;

    // ranges must not intersect and must increase
    std::vector<logger_color_range> colors;

    void clear()
    {
        sMessage.clear();
        sFormat.clear();
        sFile.clear();
        sFunction.clear();
        sCategory.clear();
        colors.clear();
    }
};

struct log_unit_info
{
    template<class char_t>
    using format_func = std::function<void(
        logger_buffer<char_t>& buffers,
        log_level              eLogLevel,   // log level
        const category&        category,    // code category
        const char_t*          pszFormat,   // format string
        const char_t*          pszFile,     // file name
        const char_t*          pszFunction, // function name
        int                    nLine,       // code line number
        va_list                args         // additional args for format
        )>;

    /**
        @brief  Get format func corresponding to char type
        @tparam char_t - char type
        @retval        - format func
    **/
    template<class char_t>
    const format_func<char_t>& get_format_func();

    log_level            eMinLogLevel = log_level::log;
    format_func<char>    formatFuncChar;
    format_func<wchar_t> formatFuncWChar;
};

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
        @param bAlwaysFlush - true if need to flush after every output, decreases performance
    **/
    base_logger_stream(bool bAlwaysFlush);

    /**
        @brief base_logger_stream object destructor
    **/
    virtual ~base_logger_stream() = default;

    /**
        @brief Flush stream
    **/
    virtual void flush() = 0;

    /**
        @brief  Output to stream
        @tparam char_t      - char type, typically char or wchar_t
        @param  eLogLevel   - log level
        @param  pszFormat   - format string
        @param  category    - code category
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  args        - additional args for format
    **/
    template<class char_t>
    void log(
        log_level       eLogLevel,
        const char_t*   pszFormat,
        const category& category,
        const char*     pszFile,
        const char*     pszFunction,
        int             nLine,
        va_list         args);

    /**
        @brief Register logger unit
        @param svUnitName - unit name (category name, file or function) 
        @param unit       - unit info 
    **/
    void register_unit(std::string_view svUnitName, const log_unit_info& unit) noexcept;

    /**
        @brief Deregister logger unit
        @param svUnitName - unit name (category name, file or function)
    **/
    void deregister_unit(std::string_view svUnitName) noexcept;

    /**
        @brief  Format time string to the buffer
        @tparam char_t          - char type
        @param  sTime           - output time buffer
        @param  chDateDelimiter - char to use as delimiter in date part
        @param  chTimeDelimiter - char to use as delimiter in time part
    **/
    template<class char_t>
    static void format_time_string(
        basic_string<char_t>& sTime,
        char_t                chDateDelimiter,
        char_t                chTimeDelimiter) noexcept;

protected:
    /**
        @brief  Get string buffers
        @tparam char_t - char type
        @retval        - string buffers
    **/
    template<class char_t>
    logger_buffer<char_t>& get_log_buffer() noexcept;

private:
    /**
        @brief Proceed stream logging
        @param svMessage - message string
        @param logUnit   - log unit info
        @param colors    - color ranges to colorize output
        @param eLogLevel - this message log level
    **/
    virtual void do_log(
        std::string_view                       svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        log_level                              eLogLevel) = 0;

    /**
        @brief Proceed stream logging
        @param svMessage - message string
        @param logUnit   - log unit info
        @param colors    - color ranges to colorize output
        @param eLogLevel - this message log level
    **/
    virtual void do_log(
        std::wstring_view                      svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        log_level                              eLogLevel) = 0;

    /**
        @brief  Try to find log unit info based on trace location info
        @param  pszCategory - code category name
        @param  pszFile     - file string
        @param  pszFunction - function string
        @retval             - log unit info if found
    **/
    std::optional<log_unit> get_unit_info(
        const char* pszCategory,
        const char* pszFile,
        const char* pszFunction) noexcept;

    /**
        @brief Format logger line
        @tparam char_t      - char type, typically char or wchar_t
        @param  buffers     - string buffers to reduce num of allocations
        @param  eLogLevel   - log level
        @param  category    - code category
        @param  pszFormat   - format string
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  args        - additional args for format
    **/
    template<class char_t>
    static void format_line(
        logger_buffer<char_t>& buffers,
        log_level              eLogLevel,
        const category&        category,
        const char_t*          pszFormat,
        const char_t*          pszFile,
        const char_t*          pszFunction,
        int                    nLine,
        va_list                args) noexcept;

private:
    std::unordered_map<string_hash, log_unit_info> m_Units;
    logger_buffer<char>                            m_BufferChar;
    logger_buffer<wchar_t>                         m_BufferWChar;
    std::mutex                                     m_Mutex;
    bool                                           m_bAlwaysFlush = false;
};

} // namespace qx

#include <qx/logger/base_logger_stream.inl>
