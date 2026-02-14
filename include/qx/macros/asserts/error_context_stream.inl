/**

    @file      error_context_stream.inl
    @author    Khrapov
    @date      10.02.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

inline error_context_stream::error_context_stream() noexcept
    : base_logger_stream({ .bProtectLog = false, .eMinFlushVerbosity = verbosity::none })
    , m_Data(qx::make_unique_ref<error_context_stream_data>())
{
}

inline threads_shared<error_context_stream::on_message_delegates_map_t>& error_context_stream::
    get_on_messages() noexcept
{
    return m_Data->onMessages;
}

inline threads_shared<error_context_stream::on_error_delegate>& error_context_stream::get_on_error() noexcept
{
    return m_Data->onError;
}

inline void error_context_stream::on_error() noexcept
{
    error_context_stream_data& data = *m_Data;
    data.disabledThreads.lock()->push_back(std::this_thread::get_id());
    data.onError.lock()->execute();
    std::erase(*data.disabledThreads.lock(), std::this_thread::get_id());
}

inline bool error_context_stream::log_unconditionally_required(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine) const noexcept
{
    return true;
}

inline void error_context_stream::do_log(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage)
{
    error_context_stream_data& data = *m_Data;
    if (!contains(*data.disabledThreads.lock(), std::this_thread::get_id()))
        (*data.onMessages.lock())[threadId].execute(eVerbosity, svMessage);
}

inline void error_context_stream::do_flush()
{
}

} // namespace qx
