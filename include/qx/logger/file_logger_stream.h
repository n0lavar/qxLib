//==============================================================================
//
//!\file                      file_logger_stream.h
//
//!\brief       Contains qx::file_logger_stream class
//!\details     ~
//
//!\author      Khrapov
//!\date        28.07.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/logger/base_logger_stream.h>

#include <filesystem>
#include <fstream>

namespace qx
{

//!< Log files policy
enum class log_file_policy
{
    append,             //!< append all
    clear_then_uppend,  //!< clear file at start, then append
    folder_time,        //!< create new folder with time name
};

//==============================================================================
//
//!\class                    qx::file_logger_stream
//
//!\brief   Logger stream for file output
//!\details ~
//
//!\author  Khrapov
//!\date    28.07.2021
//
//==============================================================================
class file_logger_stream : public base_logger_stream
{
    static constexpr std::string_view DEFAULT_FILE = "default.log";

    struct log_file_data
    {
        string          sFileName;
        log_file_policy eLogPolicy   = log_file_policy::append;
        bool            bWroteToFile = false;
    };

public:

    file_logger_stream(void);

    virtual ~file_logger_stream(void);

    virtual void process_output(
        std::string_view    svMessage,
        log_unit            logUnit) override;

    void set_logs_folder (
        std::string_view    svFolder) noexcept;

    void register_file(
        std::string_view    svUnitName,
        std::string_view    svFileName,
        log_file_policy     eLogPolicy = log_file_policy::append);

private:

    void fill_file_folder(
        log_file_policy     eLogFilePolicy,
        string            & sFileFolder) const noexcept;

private:

    std::unordered_map<string_hash, log_file_data> m_Files;
    string  m_sFolder;
    string  m_sBufferPath;
    string  m_sSessionTime;
};

}

#include <qx/logger/file_logger_stream.inl>
