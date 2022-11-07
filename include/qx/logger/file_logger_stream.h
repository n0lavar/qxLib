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
    folder_time,       //!< create new folder with time name
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
    static constexpr std::string_view DEFAULT_FILE = "default.log";

    /**
        @struct file_logger_stream::log_file_data
        @date   19.08.2021
    **/
    struct log_file_data
    {
        string          sFileName;
        log_file_policy eLogPolicy   = log_file_policy::append;
        bool            bWroteToFile = false;
    };

public:
    /**
        @brief file_logger_stream object constructor
    **/
    file_logger_stream();

    /**
        @brief file_logger_stream object destructor
    **/
    virtual ~file_logger_stream() override;

    /**
        @brief Output to file
        @param svMessage - message string 
        @param logUnit   - log unit info
        @param eLogLevel - this message log level
    **/
    virtual void do_log(std::string_view svMessage, const log_unit& logUnit, log_level eLogLevel) override;

    /**
        @brief Output to file
        @param svMessage - message string 
        @param logUnit   - log unit info
        @param eLogLevel - this message log level
    **/
    virtual void do_log(std::wstring_view svMessage, const log_unit& logUnit, log_level eLogLevel) override;

    /**
        @brief Set logs folder
        @param svFolder - logs folder
    **/
    void set_logs_folder(std::string_view svFolder) noexcept;

    /**
        @brief Register output to specific file for specific unit
        @param svUnitName - unit name
        @param svFileName - file name
        @param eLogPolicy - log file policy
    **/
    void register_file(
        std::string_view svUnitName,
        std::string_view svFileName,
        log_file_policy  eLogPolicy = log_file_policy::append);

private:
    template<class char_type>
    void log_file(std::basic_string_view<char_type> svMessage, const log_unit& logUnit, log_level eLogLevel);

    /**
        @brief Fill string with file folder path
        @param eLogFilePolicy - file log policy
        @param sFileFolder    - output string
    **/
    void fill_file_folder(log_file_policy eLogFilePolicy, string& sFileFolder) const noexcept;

private:
    std::unordered_map<string_hash, log_file_data> m_Files;
    string                                         m_sFolder;
    string                                         m_sBufferPath;
    string                                         m_sSessionTime;
};

} // namespace qx

#include <qx/logger/file_logger_stream.inl>
