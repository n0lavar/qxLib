/**

    @file      file_logger_stream_ofstream.h
    @author    Khrapov
    @date      14.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/logger/base_file_logger_stream.h>
#include <qx/math/units/data.h>

#include <fstream>

namespace qx
{

/**

    @class   file_logger_stream_ofstream
    @brief   std::ofstream based file logger stream
    @details UTF-8 LE (char) or UTF-16 LE (wchar_t)
    @author  Khrapov
    @date    14.01.2026

**/
class file_logger_stream_ofstream : public base_file_logger_stream
{
public:
    /**
        @brief file_logger_stream_ofstream object constructor
        @param streamConfig - file logger configuration
        @param bufferSize   - Outer buffer size for a FILE. if 0, the default buffer is used
                              The buffer size determines how often data will be flushed.
                              The default value of 8192 chars corresponds to ~30-50 lines of logs.
    **/
    file_logger_stream_ofstream(
        const config&             streamConfig = config(),
        unit<size_t, units::data> bufferSize   = { 8192 * sizeof(char_type), units::data::bytes }) noexcept;
    file_logger_stream_ofstream(file_logger_stream_ofstream&&) noexcept = default;

    virtual ~file_logger_stream_ofstream() override;

    // base_logger_stream
    //
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) override;
    virtual void do_flush() override;

private:
    std::basic_ofstream<char_type> m_File;
    std::vector<char_type>         m_Buffer;
};

} // namespace qx

#include <qx/logger/file_logger_stream_ofstream.inl>
