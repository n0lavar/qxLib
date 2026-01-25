/**

    @file      cout_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_converters.h>
#include <qx/logger/base_standard_streams_stream.h>

namespace qx
{

/**

    @class   cout_logger_stream
    @brief   Logger stream based on std::cout output
    @details On Linux, output is always `UTF8` (aka char) even with qx::char_type == wchar_t.
    @author  Khrapov
    @date    28.07.2021

**/
class cout_logger_stream : public base_standard_streams_stream
{
public:
    struct config : base_standard_streams_stream::config
    {
        // Optimization: Don't synchronize to the standard C streams after each input/output operation.
        // Be careful, as it changes the global setting. You'll need to revert it manually if needed.
        bool bDisableStdioSync = false;

        // Optimization: Untie cin from cout.
        // Tied streams ensure that one stream is flushed automatically before each I/O operation on the other stream.
        // Be careful, as it changes the global setting. You'll need to revert it manually if needed.
        bool bUntieCin = false;
    };

public:
    /**
        @brief cout_logger_stream object constructor
        @param optStreamConfig - logger stream configuration
    **/
    cout_logger_stream(std::optional<config> optStreamConfig = {}) noexcept;

    cout_logger_stream(cout_logger_stream&&) noexcept = default;


    // base_logger_stream
    //
    virtual void do_flush() override;

private:
    // base_standard_streams_stream
    //
    virtual void cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor) override;
    virtual void cout_common(verbosity eVerbosity, string_view svMessage) override;
};

} // namespace qx

#include <qx/logger/cout_logger_stream.inl>
