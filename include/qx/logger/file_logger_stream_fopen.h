/**

    @file      file_logger_stream_fopen.h
    @author    Khrapov
    @date      14.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/logger/base_file_logger_stream.h>
#include <qx/math/units/data.h>

#include <cstdio>

namespace qx
{

/**

    @class   file_logger_stream_fopen
    @brief   FILE* based file logger stream
    @details UTF-8 LE (char) or UTF-16 LE (wchar_t)
    @author  Khrapov
    @date    15.01.2026

**/
class file_logger_stream_fopen : public base_file_logger_stream
{
    QX_RTTI_CLASS(file_logger_stream_fopen, base_file_logger_stream);

public:
    /**
        @brief file_logger_stream_fopen object constructor
        @param streamConfig - File logger configuration
        @param bufferSize   - Outer buffer size for a FILE. if 0, the default buffer is used
                              The buffer size determines how often data will be flushed.
                              The default value of 8192 chars corresponds to ~30-50 lines of logs.
    **/
    file_logger_stream_fopen(
        const config&             streamConfig = config(),
        unit<size_t, units::data> bufferSize   = { 8192 * sizeof(char_type), units::data::bytes }) noexcept;
    file_logger_stream_fopen(file_logger_stream_fopen&& other) noexcept;

    virtual ~file_logger_stream_fopen() override;

    // base_logger_stream
    //
    virtual void do_log(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine,
        string_view                           svMessage) override;
    virtual void do_flush() override;

private:
    std::vector<char> m_Buffer;
    FILE*             m_pFile = nullptr;
};

} // namespace qx

#include <qx/logger/file_logger_stream_fopen.inl>
