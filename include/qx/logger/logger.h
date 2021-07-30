//==============================================================================
//
//!\file                           logger.h
//
//!\brief       Tracing and logging
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/patterns/singleton.h>

#include <memory>

#define QX_TRACE_FROM(loggerInstance, format, ...)              \
    loggerInstance.output(                                      \
        qx::log_level::info,                                    \
        format,                                                 \
        nullptr,                                                \
        std::string_view(),                                     \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        ## __VA_ARGS__)

#define QX_TRACE_ERROR_FROM(loggerInstance, format, ...)        \
    loggerInstance.output(                                      \
        qx::log_level::errors,                                  \
        format,                                                 \
        nullptr,                                                \
        std::string_view(),                                     \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        ## __VA_ARGS__)

#define QX_TRACE_ASSERT_FROM(loggerInstance, expr, format, ...) \
    loggerInstance.output(                                      \
        qx::log_level::asserts,                                 \
        format,                                                 \
        # expr,                                                 \
        std::string_view(),                                     \
        QX_SHORT_FILE,                                          \
        __FUNCTION__,                                           \
        __LINE__,                                               \
        ## __VA_ARGS__)


// redefine these macros in your own header with renaming only or using your instance of logger

// common info
#define QX_TRACE(format, ...)                                   \
    QX_TRACE_FROM(qx::logger_singleton::get_instance(), format, ## __VA_ARGS__)

// error info
#define QX_TRACE_ERROR(format, ...)                             \
    QX_TRACE_ERROR_FROM(qx::logger_singleton::get_instance(), format, ## __VA_ARGS__)

// assertion failed info
#define QX_TRACE_ASSERT(expr, format, ...)                      \
    QX_TRACE_ASSERT_FROM(qx::logger_singleton::get_instance(), expr, format, ## __VA_ARGS__)

namespace qx
{

class logger_worker;

//================================================================================
//
//!\class                         qx::logger
//
//!\brief   Logger class
//!\details ~
//
//!\author  Khrapov
//!\date    10.01.2020
//
//================================================================================
class logger
{
public:

    void output (
        log_level          eLogLevel,
        const char       * pszFormat,
        const char       * pszAssertExpression,
        std::string_view   svTag,
        std::string_view   svFile,
        std::string_view   svFunction,
        int                nLine,
        ...);

    void add_stream(
        std::unique_ptr<base_logger_stream> pStream);

private:

    std::vector<std::unique_ptr<base_logger_stream>> m_Streams;
};

class logger_singleton : public logger
{
    QX_SINGLETON(logger_singleton);
};

}

#include <qx/logger/logger.inl>
