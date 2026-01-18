/**

    @file      cout_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_converters.h>
#include <qx/logger/base_standard_streams_stream.h>

#include <iostream>

namespace qx
{

/**

    @class   cout_logger_stream
    @brief   Logger stream based on std::cout output
    @author  Khrapov
    @date    28.07.2021

**/
class cout_logger_stream : public base_standard_streams_stream
{
public:
    struct config : base_standard_streams_stream::config
    {
        // don't synchronize to the standard C streams after each input/output operation
        bool bDisableStdioSync = true;

        // untie cin from cout
        bool bUntieCin = true;
    };

public:
    /**
        @brief cout_logger_stream object constructor
        @param optStreamConfig - logger stream configuration
    **/
    cout_logger_stream(std::optional<config> optStreamConfig = {});

    cout_logger_stream(cout_logger_stream&&) noexcept = default;


    // base_logger_stream
    //
    virtual void do_flush() override;

private:
    virtual void cout_colorized(verbosity eVerbosity, string_view svMessage, const color& rangeColor) override;
    virtual void cout_common(verbosity eVerbosity, string_view svMessage) override;
};

} // namespace qx

#include <qx/logger/cout_logger_stream.inl>
