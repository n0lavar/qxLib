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

#ifndef QX_LOGGER_INSTANCE
    #define QX_LOGGER_INSTANCE qx::logger_singleton::get_instance()
#endif

/**
    @brief Log with category
    @param category  - category to be used to manage output
    @param eLogLevel - logging level
    @param format    - format string
    @param ...       - additional args for formatting
**/
#define QX_LOG_C(category, eLogLevel, format, ...) \
    QX_LOGGER_INSTANCE                             \
        .log(eLogLevel, format, category, QX_SHORT_FILE, qx::to_string(__FUNCTION__), __LINE__, ##__VA_ARGS__)

/**
    @def   QX_LOG
    @brief Log message
    @param eLogLevel - logging level 
    @param format    - format string
    @param ...       - additional args for formatting
**/
#define QX_LOG(eLogLevel, format, ...) QX_LOG_C(qx::category(nullptr), eLogLevel, format, ##__VA_ARGS__)

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
        @brief  Log to all streams
        @tparam char_t     - char type, typically char or wchar_t
        @param  eLogLevel  - log level
        @param  svFormat   - format string
        @param  category   - code category
        @param  svFile     - file name string
        @param  svFunction - function name string
        @param  nLine      - code line number
        @param  ...        - additional args for format
    **/
    void log(
        log_level       eLogLevel,
        string_view     svFormat,
        const category& category,
        string_view     svFile,
        string_view     svFunction,
        int             nLine,
        ...);

    /**
        @brief Flush all streams
    **/
    void flush();

    /**
        @brief Add output stream to the logger
        @param pStream - stream unique pointer
    **/
    void add_stream(std::unique_ptr<base_logger_stream> pStream) noexcept;

    /**
        @brief Reset logger and clear all streams
    **/
    void reset() noexcept;

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
