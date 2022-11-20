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
#include <mutex>

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
    loggerInstance.log(eLogLevel, format, pszTag, QX_SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__)

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
#define QX_LOG(eLogLevel, format, ...) QX_TLOG(qx::log_tag(nullptr), eLogLevel, format, ##__VA_ARGS__)

/**
    @brief Define a log tag that may be used in QX_TLOG macro
    @param name - log tag name
**/
#define QX_DEFINE_LOG_TAG(name) constexpr qx::log_tag name(#name);


namespace qx
{

/**

    @class   log_tag
    @brief   Class for identifying log tags
    @details ~
    @author  Khrapov
    @date    12.11.2022

**/
class log_tag
{
public:
    /**
        @brief log_tag object constructor
    **/
    constexpr explicit log_tag(const char* pszName) : m_pszName(pszName)
    {
    }

    /**
        @brief  Get tag name
        @retval tag name
    **/
    constexpr const char* get_name() const
    {
        return m_pszName;
    }

private:
    const char* m_pszName = nullptr;
};


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
        @param  tag         - logging tag
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  ...         - additional args for format
    **/
    template<class char_type>
    void log(
        log_level        eLogLevel,
        const char_type* pszFormat,
        log_tag          tag,
        const char*      pszFile,
        const char*      pszFunction,
        int              nLine,
        ...);

    /**
        @brief  Log to all streams
        @tparam char_type   - char type, typically char or wchar_t
        @param  eLogLevel   - log level
        @param  sFormat     - format string
        @param  tag      - logging tag
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  ...         - additional args for format
    **/
    template<class char_type>
    void log(
        log_level                      eLogLevel,
        const basic_string<char_type>& sFormat,
        log_tag                        tag,
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
        @param  pszTag      - logging tag
        @param  pszFile     - file name string
        @param  pszFunction - function name string
        @param  nLine       - code line number
        @param  args        - template parameter pack
    **/
    template<class char_type>
    void do_log(
        log_level        eLogLevel,
        const char_type* pszFormat,
        const char*      pszTag,
        const char*      pszFile,
        const char*      pszFunction,
        int              nLine,
        va_list          args);

private:
    std::vector<std::unique_ptr<base_logger_stream>> m_Streams;

    // simple synchronization so far
    // may be improved if it will become a problem
    std::mutex m_Mutex;
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
