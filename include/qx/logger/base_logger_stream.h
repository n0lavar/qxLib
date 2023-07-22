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
#include <qx/verbosity.h>

#include <ctime>
#include <functional>
#include <mutex>
#include <unordered_map>

QX_DEFINE_CATEGORY(CatLogger, qx::color::dark_turquoise());

namespace qx
{

struct logger_color_range
{
    std::pair<size_t, size_t> range { 0, 0 };
    color                     rangeColor = color::white();
};

struct logger_buffer
{
    string sMessage; // result message (output)

    // ranges must not intersect and must increase
    std::vector<logger_color_range> colors;

    void clear()
    {
        sMessage.clear();
        colors.clear();
    }
};

struct log_unit_info
{
    using format_func = std::function<void(
        logger_buffer&  buffers,
        verbosity       eVerbosity,
        const category& category,
        string_view     svFile,
        string_view     svFunction,
        int             nLine,
        string_view     swLogMessage)>;

    verbosity   eMinVerbosity = verbosity::log;
    format_func formatFunc;
};

struct log_unit
{
    log_unit_info* pUnitInfo = nullptr;
    string_view    svUnitName;
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
    static constexpr const char_type* k_svDefaultUnit = QX_TEXT("default");

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
        @tparam char_t       - char type, typically char or wchar_t
        @param  eVerbosity     message verbosity
        @param  category     - code category
        @param  svFile       - file name string
        @param  svFunction   - function name string
        @param  nLine        - code line number
        @param  swLogMessage - formatted log line
    **/
    void log(
        verbosity       eVerbosity,
        const category& category,
        string_view     svFile,
        string_view     svFunction,
        int             nLine,
        string_view     swLogMessage);

    /**
        @brief Register logger unit
        @param svUnitName - unit name (category name, file or function) 
        @param unit       - unit info 
    **/
    void register_unit(string_view svUnitName, const log_unit_info& unit) noexcept;

    /**
        @brief Deregister logger unit
        @param svUnitName - unit name (category name, file or function)
    **/
    void deregister_unit(string_view svUnitName) noexcept;

    /**
        @brief  Format time string to the buffer
        @param  sTime           - output time buffer
        @param  chDateDelimiter - char to use as delimiter in date part
        @param  chTimeDelimiter - char to use as delimiter in time part
    **/
    static void append_time_string(string& sTime, char_type chDateDelimiter, char_type chTimeDelimiter) noexcept;

protected:
    /**
        @brief  Get string buffers
        @retval        - string buffers
    **/
    logger_buffer& get_log_buffer() noexcept;

    /**
        @brief Format logger line
        @param  buffers      - string buffers to reduce num of allocations
        @param  eVerbosity   - message verbosity
        @param  category     - code category
        @param  svFile       - file name string
        @param  svFunction   - function name string
        @param  nLine        - code line number
        @param  swLogMessage - formatted log line
    **/
    virtual void format_line(
        logger_buffer&  buffers,
        verbosity       eVerbosity,
        const category& category,
        string_view     svFile,
        string_view     svFunction,
        int             nLine,
        string_view     swLogMessage) noexcept;

private:
    /**
        @brief Proceed stream logging
        @param svMessage  - message string
        @param logUnit    - log unit info
        @param colors     - color ranges to colorize output
        @param eVerbosity - this message verbosity
    **/
    virtual void do_log(
        string_view                            svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        verbosity                              eVerbosity) = 0;

    /**
        @brief  Try to find log unit info based on trace location info
        @param  svCategory - code category name
        @param  svFile     - file string
        @param  svFunction - function string
        @retval            - log unit info if found
    **/
    std::optional<log_unit> get_unit_info(string_view svCategory, string_view svFile, string_view svFunction) noexcept;

private:
    std::unordered_map<string_hash, log_unit_info> m_Units;
    logger_buffer                                  m_Buffer;
    std::mutex                                     m_Mutex;
    bool                                           m_bAlwaysFlush = false;
};

} // namespace qx

#include <qx/logger/base_logger_stream.inl>
