/**

    @file      logger.h
    @brief     Contains qx::logger class
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/patterns/singleton.h>

#include <memory>

/**
    @def   QX_LOG_FROM
    @brief Log common info from instance
    @param loggerInstance - logger instance 
    @param format         - format string
    @param ...            - additional args for formatting
**/
#define QX_LOG_FROM(loggerInstance, format, ...) \
    loggerInstance.output(                       \
        qx::log_level::info,                     \
        format,                                  \
        nullptr,                                 \
        nullptr,                                 \
        QX_SHORT_FILE,                           \
        __FUNCTION__,                            \
        __LINE__,                                \
        ##__VA_ARGS__)

/**
    @def   QX_LOG_WARNING_FROM
    @brief Log warnings from instance
    @param loggerInstance - logger instance 
    @param format         - format string
    @param ...            - additional args for formatting
**/
#define QX_LOG_WARNING_FROM(loggerInstance, format, ...) \
    loggerInstance.output(                               \
        qx::log_level::warnings,                         \
        format,                                          \
        nullptr,                                         \
        nullptr,                                         \
        QX_SHORT_FILE,                                   \
        __FUNCTION__,                                    \
        __LINE__,                                        \
        ##__VA_ARGS__)

/**
    @def   QX_LOG_ERROR_FROM
    @brief Log error from instance
    @param loggerInstance - logger instance
    @param format         - format string
    @param ...            - additional args for formatting
**/
#define QX_LOG_ERROR_FROM(loggerInstance, format, ...) \
    loggerInstance.output(                             \
        qx::log_level::errors,                         \
        format,                                        \
        nullptr,                                       \
        nullptr,                                       \
        QX_SHORT_FILE,                                 \
        __FUNCTION__,                                  \
        __LINE__,                                      \
        ##__VA_ARGS__)

/**
    @def   QX_LOG_ASSERT_FROM
    @brief Log assert from instance
    @param loggerInstance - logger instance
    @param expr           - assert expression
    @param format         - format string
    @param ...            - additional args for formatting
**/
#define QX_LOG_ASSERT_FROM(loggerInstance, expr, format, ...) \
    loggerInstance.output(                                    \
        qx::log_level::asserts,                               \
        format,                                               \
        #expr,                                                \
        nullptr,                                              \
        QX_SHORT_FILE,                                        \
        __FUNCTION__,                                         \
        __LINE__,                                             \
        ##__VA_ARGS__)


// redefine these macros in your own header with renaming only or using your instance of logger

/**
    @def   QX_LOG
    @brief Log common info
    @param format - format string
    @param ...    - additional args for formatting
**/
#define QX_LOG(format, ...) \
    QX_LOG_FROM(qx::logger_singleton::get_instance(), format, ##__VA_ARGS__)

/**
    @def   QX_LOG_WARNING
    @brief Log warning
    @param format - format string
    @param ...    - additional args for formatting
**/
#define QX_LOG_WARNING(format, ...)           \
    QX_LOG_WARNING_FROM(                      \
        qx::logger_singleton::get_instance(), \
        format,                               \
        ##__VA_ARGS__)

/**
    @def   QX_LOG_ERROR
    @brief Log error
    @param format - format string
    @param ...    - additional args for formatting
**/
#define QX_LOG_ERROR(format, ...)             \
    QX_LOG_ERROR_FROM(                        \
        qx::logger_singleton::get_instance(), \
        format,                               \
        ##__VA_ARGS__)

/**
    @def   QX_LOG_ASSERT
    @brief Log assertion
    @param expr   - assert expression
    @param format - format string
    @param ...    - additional args for formatting
**/
#define QX_LOG_ASSERT(expr, format, ...)      \
    QX_LOG_ASSERT_FROM(                       \
        qx::logger_singleton::get_instance(), \
        expr,                                 \
        format,                               \
        ##__VA_ARGS__)

namespace qx
{

/**

    @class   logger
    @brief   Logger class
    @details ~
    @author  Khrapov
    @date    10.01.2020

**/
class logger
{
public:
    /**
        @brief Process tracings
        @param eLogLevel           - log level
        @param pszFormat           - format string
        @param pszAssertExpression - assert expr or nullptr
        @param pszTag              - tracing tag
        @param pszFile             - file name string
        @param pszFunction         - function name string
        @param nLine               - code line number
        @param ...                 - additional args for format
    **/
    void output(
        log_level   eLogLevel,
        const char* pszFormat,
        const char* pszAssertExpression,
        const char* pszTag,
        const char* pszFile,
        const char* pszFunction,
        int         nLine,
        ...);

    /**
        @brief Add output stream to the logger
        @param pStream - stream unique pointer
    **/
    void add_stream(std::unique_ptr<base_logger_stream> pStream);

private:
    std::vector<std::unique_ptr<base_logger_stream>> m_Streams;
};

/**

    @class   logger_singleton
    @brief   Default logger instance
    @details ~
    @author  Khrapov
    @date    19.08.2021

**/
class logger_singleton : public logger
{
    QX_SINGLETON(logger_singleton);
};

} // namespace qx

#include <qx/logger/logger.inl>
