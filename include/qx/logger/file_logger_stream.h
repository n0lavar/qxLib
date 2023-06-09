/**

    @file      file_logger_stream.h
    @brief     Contains qx::file_logger_stream class
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>

#include <filesystem>
#include <fstream>

namespace qx
{

enum class log_file_policy
{
    append,            //!< append all
    clear_then_uppend, //!< clear file at start, then append
    time_name,         //!< create new file with time name
};

/**

    @class   file_logger_stream
    @brief   Logger stream for file output
    @details ~
    @author  Khrapov
    @date    28.07.2021

**/
class file_logger_stream : public base_logger_stream
{
public:
    /**
        @brief file_logger_stream object constructor
        @param bAlwaysFlush   - true if need to flush after every output, decreases performance
        @param eLogFilePolicy - policy to use
        @param svFileName     - log file name
    **/
    file_logger_stream(
        bool              bAlwaysFlush   = false,
        log_file_policy   eLogFilePolicy = log_file_policy::append,
        std::wstring_view svFileName     = L"application");

    /**
        @brief file_logger_stream object destructor
    **/
    virtual ~file_logger_stream() override;

    /**
        @brief Flush stream
    **/
    virtual void flush() override;

    /**
        @brief Output to file
        @param svMessage - message string 
        @param logUnit   - log unit info
        @param colors    - color ranges to colorize output
        @param eLogLevel - this message log level
    **/
    virtual void do_log(
        std::string_view                       svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        log_level                              eLogLevel) override;

    /**
        @brief Output to file
        @param svMessage - message string 
        @param logUnit   - log unit info
        @param colors    - color ranges to colorize output
        @param eLogLevel - this message log level
    **/
    virtual void do_log(
        std::wstring_view                      svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        log_level                              eLogLevel) override;

private:
    /**
        @brief  Log to file
        @tparam char_t    - char type
        @param  svMessage - message to log
        @param  logUnit   - log unit info
        @param  eLogLevel - this message log level
    **/
    template<class char_t>
    void log_file(std::basic_string_view<char_t> svMessage, const log_unit& logUnit, log_level eLogLevel);

private:
    std::basic_ofstream<wchar_t> m_WCharFile;
};

} // namespace qx

#include <qx/logger/file_logger_stream.inl>
