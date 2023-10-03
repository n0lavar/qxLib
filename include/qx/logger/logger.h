/**

    @file      logger.h
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
    @param category   - category to be used to manage output
    @param eVerbosity - message verbosity
    @param format     - format string
    @param ...        - additional args for formatting
**/
#define QX_LOG_C(category, eVerbosity, format, ...) \
    QX_LOGGER_INSTANCE                              \
        .log(eVerbosity, format, category, QX_SHORT_FILE, qx::to_string(__FUNCTION__), __LINE__, ##__VA_ARGS__)

/**
    @def   QX_LOG
    @brief Log message
    @param eVerbosity - message verbosity 
    @param format     - format string
    @param ...        - additional args for formatting
**/
#define QX_LOG(eVerbosity, format, ...) QX_LOG_C(CatDefault, eVerbosity, format, ##__VA_ARGS__)

namespace qx
{

template<class... args_t>
concept log_acceptable_args = (sizeof...(args_t) > 0 && format_acceptable_args<char_type, args_t...>);

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
        @param  eVerbosity - message verbosity
        @param  svFormat   - format string
        @param  category   - code category
        @param  svFile     - file name string
        @param  svFunction - function name string
        @param  nLine      - code line number
    **/
    void log(
        verbosity       eVerbosity,
        string_view     svFormat,
        const category& category,
        string_view     svFile,
        string_view     svFunction,
        int             nLine);

    /**
        @brief  Log to all streams
        @tparam args_t     - template parameter pack type
        @param  eVerbosity - message verbosity
        @param  sFormat    - format string
        @param  category   - code category
        @param  svFile     - file name string
        @param  svFunction - function name string
        @param  nLine      - code line number
        @param  args       - additional args for format
    **/
    template<class... args_t>
        requires(log_acceptable_args<args_t...>)
    void log(
        verbosity                eVerbosity,
        format_string<args_t...> sFormat,
        const category&          category,
        string_view              svFile,
        string_view              svFunction,
        int                      nLine,
        const args_t&... args);

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

    /**
        @brief   Returns true if any of streams will accept this message
        @details Typically you don't want to use it
                 It may be useful with async logging to avoid unnecessary formatting and queueing
        @param   category   - code category
        @param   eVerbosity - message verbosity
        @param   svFile     - file name string
        @param   svFunction - function name string
        @retval             - true if any of streams will accept this message
    **/
    bool will_any_stream_accept(
        const category& category,
        verbosity       eVerbosity,
        string_view     svFile,
        string_view     svFunction) const noexcept;

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
