/**

    @file      debugger_logger_stream.inl
    @author    Khrapov
    @date      12.11.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

inline debugger_logger_stream::debugger_logger_stream(verbosity eMinFlushVerbosity)
    : base_logger_stream({ .bProtectLog = false, .eMinFlushVerbosity = eMinFlushVerbosity })
{
}

inline void debugger_logger_stream::do_log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
#if QX_WIN
    if (IsDebuggerPresent())
    {
        thread_local wstring sMessage;
        sMessage = to_wstring(svMessage);
        OutputDebugStringW(sMessage.c_str());
    }
#endif
}

inline void debugger_logger_stream::do_flush()
{
}

} // namespace qx
