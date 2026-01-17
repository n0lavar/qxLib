/**

    @file      base_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/containers/string/string_converters.h>
#include <qx/internal/perf_scope.h>
#include <qx/verbosity.h>

#include <memory>
#include <mutex>

QX_DEFINE_CATEGORY(CatLogger, qx::color::dark_turquoise());

namespace qx
{

/**

    @class   base_logger_stream
    @brief   Base class for logger streams
    @author  Khrapov
    @date    28.07.2021

**/
class base_logger_stream
{
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
    base_logger_stream(const config& streamConfig);

    base_logger_stream(base_logger_stream&&) noexcept = default;

    virtual ~base_logger_stream() = default;

    /**
        @brief  Output to stream
        @tparam char_t     - char type, typically char or wchar_t
        @param  category   - code category
        @param  eVerbosity   message verbosity
        @param  svMessage  - formatted log line
    **/
    void log(const category& category, verbosity eVerbosity, string_view svMessage);

    /**
        @brief Flush the stream
    **/
    void flush();

private:
    /**
        @brief Proceed stream logging
        @param eVerbosity - this message verbosity
        @param category   - code category
        @param svMessage  - message string
    **/
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) = 0;

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
