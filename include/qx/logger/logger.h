/**

    @file      logger.h
    @brief     Contains qx::logger class
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/logger/base_logger_stream.h>
#include <qx/patterns/singleton.h>

#include <memory>

/**
    @def   QX_LOG_COMMON
    @brief Common macro for logging. Prefer using QX_TLOG or QX_LOG
    @param loggerInstance - logger instance 
    @param category       - category to be used to manage output 
    @param eLogLevel      - logging level 
    @param format         - format string
    @param ...            - additional args for formatting
**/
#define QX_LOG_COMMON(loggerInstance, category, eLogLevel, format, ...) \
    loggerInstance.log(eLogLevel, format, category, QX_SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__)

/**
    @brief Log with category
    @param category  - category to be used to manage output
    @param eLogLevel - logging level
    @param format    - format string
    @param ...       - additional args for formatting
**/
#define QX_LOG_C(category, eLogLevel, format, ...) \
    QX_LOG_COMMON(qx::logger_singleton::get_instance(), category, eLogLevel, format, ##__VA_ARGS__)

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
        @tparam char_type   - char type, typically char or wchar_t
        @param  eLogLevel   - log level
        @param  pszFormat   - format string
        @param  category    - code category
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  ...         - additional args for format
    **/
    template<class char_type>
    void log(
        log_level        eLogLevel,
        const char_type* pszFormat,
        category         category,
        const char*      pszFile,
        const char*      pszFunction,
        int              nLine,
        ...);

    /**
        @brief  Log to all streams
        @tparam char_type   - char type, typically char or wchar_t
        @param  eLogLevel   - log level
        @param  sFormat     - format string
        @param  category    - code category
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  ...         - additional args for format
    **/
    template<class char_type>
    void log(
        log_level                      eLogLevel,
        const basic_string<char_type>& sFormat,
        category                       category,
        const char*                    pszFile,
        const char*                    pszFunction,
        int                            nLine,
        ...);

    /**
        @brief Add output stream to the logger
        @param pStream - stream unique pointer
    **/
    void add_stream(std::unique_ptr<base_logger_stream> pStream);

private:
    /**
        @brief  Common method for logging
        @tparam char_type   - char type, typically char or wchar_t
        @param  eLogLevel   - log level
        @param  pszFormat   - format string
        @param  pszCategory - code category name
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  args        - template parameter pack
    **/
    template<class char_type>
    void do_log(
        log_level        eLogLevel,
        const char_type* pszFormat,
        const char*      pszCategory,
        const char*      pszFile,
        const char*      pszFunction,
        int              nLine,
        va_list          args);

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
