/**

    @file      file_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/logger/time_string.h>

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

struct file_logger_config
{
    // if it's required to protect log with a mutex
    bool bProtectLog = false;

    // if it's required to flush after every output, decreases performance
    bool bAlwaysFlush = false;

    // policy to use
    log_file_policy eLogFilePolicy = log_file_policy::append;

    // log file name
    string_view svFileName = QXT("application");
};

/**

    @class   file_logger_stream
    @brief   Logger stream for file output
    @author  Khrapov
    @date    28.07.2021

**/
class file_logger_stream : public base_logger_stream
{
public:
    /**
        @brief file_logger_stream object constructor
        @param config - file logger configuration
    **/
    file_logger_stream(file_logger_config config = file_logger_config());

    file_logger_stream(file_logger_stream&&) noexcept = default;

    virtual ~file_logger_stream() override;

    // base_logger_stream
    //
    virtual void flush() override;
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) override;

private:
    std::basic_ofstream<char_type> m_File;
};

} // namespace qx

#include <qx/logger/file_logger_stream.inl>
