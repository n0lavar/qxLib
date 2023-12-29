/**

    @file      debugger_logger_stream.h
    @author    Khrapov
    @date      12.11.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/logger/terminal_color.h>

#if QX_WIN
    #include "debugapi.h"
#endif

namespace qx
{

/**

    @class   debugger_logger_stream
    @brief   Logger stream for a debugger output (VS: output window)
    @details ~
    @author  Khrapov
    @date    12.11.2023

**/
class debugger_logger_stream : public base_logger_stream
{
public:
    /**
        @brief debugger_logger_stream object constructor
    **/
    debugger_logger_stream();

private:
    // base_logger_stream
    //
    void flush() override;
    void do_log(
        string_view                            svMessage,
        const log_unit&                        logUnit,
        const std::vector<logger_color_range>& colors,
        verbosity                              eVerbosity) override;
};

} // namespace qx

#include <qx/logger/debugger_logger_stream.inl>
