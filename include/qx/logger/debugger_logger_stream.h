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
    @author  Khrapov
    @date    12.11.2023

**/
class debugger_logger_stream : public base_logger_stream
{
    QX_RTTI_CLASS(debugger_logger_stream, base_logger_stream);

public:
    /**
        @brief debugger_logger_stream object constructor
        @param eMinFlushVerbosity - the minimum verbosity level at which flush will be called
    **/
    debugger_logger_stream(verbosity eMinFlushVerbosity = verbosity::error);

    debugger_logger_stream(debugger_logger_stream&&) noexcept = default;

private:
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
};

} // namespace qx

#include <qx/logger/debugger_logger_stream.inl>
