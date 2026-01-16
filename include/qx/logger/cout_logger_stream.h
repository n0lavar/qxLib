/**

    @file      cout_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_converters.h>
#include <qx/logger/base_logger_stream.h>
#include <qx/logger/terminal_color.h>

#include <iostream>

namespace qx
{

/**

    @class   cout_logger_stream
    @brief   Logger stream for std::cout output
    @author  Khrapov
    @date    28.07.2021

**/
class cout_logger_stream : public base_logger_stream
{
public:
    struct config : base_logger_stream::config
    {
        bool bUseColors = true;

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
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) override;
    virtual void do_flush() override;

    /**
        @brief Set whether cout output should be colored
        @param bUsingColors - true if cout output should be colored
    **/
    void set_using_colors(bool bUsingColors) noexcept;

private:
    bool m_bUsingColors = true;
};

} // namespace qx

#include <qx/logger/cout_logger_stream.inl>
