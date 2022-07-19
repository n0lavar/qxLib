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
    @def   QX_LOG_COMMON
    @brief Common macro for logging. Prefer using QX_TLOG or QX_LOG
    @param loggerInstance - logger instance 
    @param pszTag         - tag, can be used to manage output 
    @param eLogLevel      - logging level 
    @param format         - format string
    @param ...            - additional args for formatting
**/
#define QX_LOG_COMMON(loggerInstance, pszTag, eLogLevel, format, ...) \
    loggerInstance.output(eLogLevel, format, pszTag, QX_SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__)

/**
    @brief Log with tag
    @param pszTag    - tag, can be used to manage output
    @param eLogLevel - logging level
    @param format    - format string
    @param ...       - additional args for formatting
**/
#define QX_TLOG(pszTag, eLogLevel, format, ...) \
    QX_LOG_COMMON(qx::logger_singleton::get_instance(), pszTag, eLogLevel, format, ##__VA_ARGS__)

/**
    @def   QX_LOG
    @brief Log message
    @param eLogLevel - logging level 
    @param format    - format string
    @param ...       - additional args for formatting
**/
#define QX_LOG(eLogLevel, format, ...) QX_TLOG(nullptr, eLogLevel, format, ##__VA_ARGS__)


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
        @param eLogLevel   - log level
        @param pszFormat   - format string
        @param pszTag      - logging tag
        @param pszFile     - file name string
        @param pszFunction - function name string
        @param nLine       - code line number
        @param ...         - additional args for format
    **/
    void output(
        log_level   eLogLevel,
        const char* pszFormat,
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
