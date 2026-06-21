/**

    @file      base_file_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/logger/logger_formatters.h>

#include <filesystem>

namespace qx
{

enum class log_file_policy
{
    append,                 //!< append all
    clear_then_upend,       //!< clear file at start, then append
    time_name,              //!< create new file with creation time name
    time_name_keep_current, //!< the current file name: svFilePrefix, old ones: svFilePrefix_last_modification_time
};

/**

    @class   base_file_logger_stream
    @brief   Base class for all file logger streams
    @author  Khrapov
    @date    28.07.2021

**/
class base_file_logger_stream : public base_logger_stream
{
    QX_RTTI_CLASS(base_file_logger_stream, base_logger_stream);

public:
    struct config : base_logger_stream::config
    {
        log_file_policy eLogFilePolicy  = log_file_policy::append;
        size_t          nMaxLogFiles    = 0; // number of log files to keep if using time_name policy (logs rotation)
        string_view     svLogsDirectory = QXT("./"); // current working directory
        string_view     svFilePrefix    = QXT("qx_app");
        string_view     svFileExtension = QXT(".log");
    };

public:
    /**
        @brief file_logger_stream object constructor
        @param streamConfig - file logger configuration
    **/
    base_file_logger_stream(const config& streamConfig) noexcept;
    base_file_logger_stream(base_file_logger_stream&&) noexcept = default;

protected:
    /**
        @brief  Create a folder (if required) and get log file path
        @param  config - file logger configuration
        @retval        - log file path, empty path on error
    **/
    std::filesystem::path prepare_folder_and_get_log_file_path(const config& config) noexcept;
};

} // namespace qx

#include <qx/logger/base_file_logger_stream.inl>
