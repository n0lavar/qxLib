/**

    @file      error_context_stream.h
    @author    Khrapov
    @date      10.02.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/algo/contains.h>
#include <qx/logger/base_logger_stream.h>
#include <qx/patterns/delegate.h>
#include <qx/smart_ptr/threads_shared.h>
#include <qx/smart_ptr/unique_ref.h>

#include <unordered_map>

namespace qx
{

/**

    @class   error_context_stream
    @brief   A stream that allows capturing all messages and redirecting them to error contexts
    @author  Khrapov
    @date    10.02.2026

**/
class error_context_stream : public base_logger_stream
{
    QX_RTTI_CLASS(error_context_stream, base_logger_stream);
    QX_NONCOPYABLE(error_context_stream);
    QX_MOVABLE(error_context_stream);

public:
    using on_message_delegate_t      = delegate<void(verbosity, string_view)>;
    using on_message_delegates_map_t = std::unordered_map<std::thread::id, on_message_delegate_t>;
    using on_error_delegate          = delegate<void()>;

public:
    error_context_stream() noexcept;

    /**
        @brief  Get on messages delegate
        @retval  - on messages delegate
    **/
    threads_shared<on_message_delegates_map_t>& get_on_messages() noexcept;

    /**
        @brief  Get on error delegate
        @retval  - on error delegate
    **/
    threads_shared<on_error_delegate>& get_on_error() noexcept;

    /**
        @brief Emit error event for all listeners
    **/
    void on_error() noexcept;

private:
    // base_logger_stream
    //
    virtual bool log_unconditionally_required(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine) const noexcept override;
    void do_log(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine,
        string_view                           svMessage) override;
    void do_flush() override;

private:
    struct error_context_stream_data
    {
        threads_shared<on_message_delegates_map_t>   onMessages;
        threads_shared<on_error_delegate>            onError;
        threads_shared<std::vector<std::thread::id>> disabledThreads;
    };
    unique_ref<error_context_stream_data> m_Data;
};

} // namespace qx

#include <qx/asserts/error_context_stream.inl>
