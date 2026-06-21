/**

    @file      error_context.h
    @author    Khrapov
    @date      10.02.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/asserts/error_context_stream.h>
#include <qx/logger/logger.h>

namespace qx
{

/**

    @class   error_context
    @brief   Collects all log messages in the scope of its lifetime and outputs them when any assertion is triggered.
             Particularly useful in multithreaded context where many threads write simultaneously,
             allowing seeing a clear thread output.
    @details Requires qx::error_context_stream to be added to the logger to work.
             Does not display anything if there were no log messages.
             Otherwise, it displays the header, all messages, and then the footer for visual differentiation.
             Doesn't catch constexpr verbosity erased messages.
    @warning Does not support fibres and coroutines (thread switching)
    @author  Khrapov
    @date    10.02.2026

**/
class error_context
{
    QX_NONCOPYMOVABLE(error_context);

public:
    /**
        @brief error_context object constructor
        @param eMinCaptureVerbosity - minimum verbosity of messages this context should capture
        @param svHeader             - a header to add when there is at least one message
        @param svFooter             - a footer to add when there is at least one message
    **/
    error_context(
        verbosity   eMinCaptureVerbosity,
        string_view svHeader = QXT("Error context start"),
        string_view svFooter = QXT("Error context end")) noexcept;

    ~error_context() noexcept;

private:
    /**
        @brief Message capturing event
        @param eVerbosity - message verbosity
        @param svMessage  - message text
    **/
    void on_message(verbosity eVerbosity, string_view svMessage) noexcept;

    /**
        @brief Error occured event
        @param errorThreadId - the thread where error occured
    **/
    void on_error(std::thread::id errorThreadId) noexcept;

private:
    const string_view     m_svHeader;
    const string_view     m_svFooter;
    const verbosity       m_eMinCatchVerbosity;
    const std::thread::id m_ThreadId = std::this_thread::get_id();
    string                m_sMessages;
    delegate_token_type   m_OnMessagesToken;
    delegate_token_type   m_OnErrorToken;
};

} // namespace qx

#include <qx/asserts/error_context.inl>
