/**

    @file      base_logger_stream.h
    @author    Khrapov
    @date      28.07.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/internal/perf_scope.h>
#include <qx/verbosity.h>

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
    /**
        @brief base_logger_stream object constructor
        @param bAlwaysFlush - true if need to flush after every output, decreases performance
    **/
    base_logger_stream(bool bAlwaysFlush = false);

    base_logger_stream(base_logger_stream&&) noexcept = default;

    virtual ~base_logger_stream() = default;

    /**
        @brief Flush stream
    **/
    virtual void flush() = 0;

    /**
        @brief  Output to stream
        @tparam char_t     - char type, typically char or wchar_t
        @param  category   - code category
        @param  eVerbosity   message verbosity
        @param  svMessage  - formatted log line
    **/
    void log(const category& category, verbosity eVerbosity, string_view svMessage);

private:
    /**
        @brief Proceed stream logging
        @param eVerbosity - this message verbosity
        @param category   - code category
        @param svMessage  - message string
    **/
    virtual void do_log(const category& category, verbosity eVerbosity, string_view svMessage) = 0;

private:
    bool m_bAlwaysFlush = false;
};

} // namespace qx

#include <qx/logger/base_logger_stream.inl>
