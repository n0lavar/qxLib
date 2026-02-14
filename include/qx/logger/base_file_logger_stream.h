/**

    @file      base_file_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/logger/logger_formatters.h>

#include <filesystem>

namespace qx
{

enum class log_file_policy
{
    append,            //!< append all
    clear_then_uppend, //!< clear file at start, then append
    time_name,         //!< create new file with time name
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
        // policy to use
        log_file_policy eLogFilePolicy = log_file_policy::append;

        // log file name
        string_view svFileName = QXT("qx_app.log");
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
        @param  eLogFilePolicy - policy to use
        @param  svFileName     - log file name
        @retval                - log file path, empty path on error
    **/
    static std::filesystem::path create_folder_and_get_log_file_path(
        log_file_policy eLogFilePolicy,
        string_view     svFileName) noexcept;
};

} // namespace qx

#include <qx/logger/base_file_logger_stream.inl>
