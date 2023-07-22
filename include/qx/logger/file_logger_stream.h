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
        bool            bAlwaysFlush   = false,
        log_file_policy eLogFilePolicy = log_file_policy::append,
        string_view     svFileName     = L"application");

    /**
        @brief file_logger_stream object destructor
    **/
    virtual ~file_logger_stream() override;

    // base_logger_stream
    //
    virtual void flush() override;
    virtual void do_log(
        string_view                            svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        verbosity                              eVerbosity) override;

private:
    std::wofstream m_File;
};

} // namespace qx

#include <qx/logger/file_logger_stream.inl>
