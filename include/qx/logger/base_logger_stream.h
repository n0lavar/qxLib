/**

    @file      base_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/containers/string/string_converters.h>
#include <qx/internal/perf_scope.h>
#include <qx/rtti/rtti.h>
#include <qx/verbosity.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

QX_DEFINE_CATEGORY(CatLogger, qx::color::dark_turquoise());

namespace qx
{

/**

    @class   base_logger_stream
    @brief   Base class for logger streams
    @author  Khrapov
    @date    28.07.2021

**/
class base_logger_stream : public rtti_root<>
{
    QX_RTTI_CLASS(base_logger_stream, rtti_root<>);

public:
    struct config
    {
        // if it's required to protect log with a mutex
        bool bProtectLog = true;

        // the minimum verbosity level at which flush will be called
        verbosity eMinFlushVerbosity = verbosity::error;
    };

public:
    /**
        @brief base_logger_stream object constructor
        @param streamConfig - logger configuration
    **/
    base_logger_stream(const config& streamConfig) noexcept;

    base_logger_stream(base_logger_stream&&) noexcept = default;

    /**
        @brief  Output to stream
        @tparam char_t      - char type, typically char or wchar_t
        @param  category    - code category
        @param  eVerbosity  - message verbosity
        @param  threadId    - thread where the log is called
        @param  messageTime - message creation time
        @param  svFile      - file name string
        @param  svFunction  - function name string
        @param  nLine       - code line number
        @param  svMessage   - formatted log line
    **/
    void log(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine,
        string_view                           svMessage);

    /**
        @brief Flush the stream
    **/
    void flush();

    /**
        @brief  Returns true if this message should be processed by this stream
                even if the logger filters did not pass it. 
        @param  category    - code category
        @param  eVerbosity  - message verbosity
        @param  threadId    - thread where the log is called
        @param  messageTime - message creation time
        @param  svFile      - file name string
        @param  svFunction  - function name string
        @param  nLine       - code line number
        @retval             - true is this message is unconditionally required by this stream
    **/
    virtual bool log_unconditionally_required(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine) const noexcept;

private:
    /**
        @brief Proceed stream logging
        @param category    - code category
        @param eVerbosity  - this message verbosity
        @param threadId    - thread where the log is called
        @param messageTime - message creation time
        @param svFile      - file name string
        @param svFunction  - function name string
        @param nLine       - code line number
        @param svMessage   - message string
    **/
    virtual void do_log(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine,
        string_view                           svMessage) = 0;

    /**
        @brief Flush the stream
    **/
    virtual void do_flush() = 0;

private:
    std::unique_ptr<std::recursive_mutex> m_pMutex;
    bool                                  m_bProtectLog        = true;
    verbosity                             m_eMinFlushVerbosity = verbosity::error;
};

} // namespace qx

#include <qx/logger/base_logger_stream.inl>
