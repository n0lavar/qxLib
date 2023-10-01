/**

    @file      cout_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/logger/terminal_color.h>

#include <iostream>

namespace qx
{

/**

    @class   cout_logger_stream
    @brief   Logger stream for std::cout output
    @details ~
    @author  Khrapov
    @date    28.07.2021

**/
class cout_logger_stream : public base_logger_stream
{
public:
    /**
        @brief cout_logger_stream object constructor
        @param bAlwaysFlush      - true if need to flush after every output, decreases performance
        @param bUseColors        - use color when output is not info
        @param bDisableStdioSync - don't synchronize to the standard C streams after each input/output operation
        @param bUntieCin         - untie cin from cout
    **/
    cout_logger_stream(
        bool bAlwaysFlush      = false,
        bool bUseColors        = true,
        bool bDisableStdioSync = true,
        bool bUntieCin         = true);

    // base_logger_stream
    //
    virtual void flush() override;
    virtual void do_log(
        string_view                            svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        verbosity                              eVerbosity) override;

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
