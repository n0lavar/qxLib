/**

    @file      debugger_logger_stream.inl
    @author    Khrapov
    @date      12.11.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

inline debugger_logger_stream::debugger_logger_stream() : base_logger_stream(true)
{
}

inline void debugger_logger_stream::flush()
{
}

inline void debugger_logger_stream::do_log(
    string_view                            svMessage,
    const log_unit&                        logUnit,
    const std::vector<logger_color_range>& colors,
    verbosity                              eVerbosity)
{
#if QX_WIN
    if (IsDebuggerPresent())
    {
        thread_local string sMessage;
        sMessage = svMessage;
        OutputDebugString(sMessage.c_str());
    }
#endif
}

} // namespace qx
