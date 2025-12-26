/**

    @file      logger.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/patterns/singleton.h>
#include <qx/sbo/sbo_poly.h>

#ifndef QX_LOGGER_INSTANCE
    #define QX_LOGGER_INSTANCE qx::logger_singleton::get_instance().get_logger()
#endif

#ifndef QX_LOG_C
    /**
        @brief Log with category
        @param category   - category to be used to manage output
        @param eVerbosity - message verbosity
        @param format     - format string
        @param ...        - additional args for formatting
    **/
    #define QX_LOG_C(category, eVerbosity, format, ...) \
        QX_LOGGER_INSTANCE.log(                         \
            eVerbosity,                                 \
            QXT(format),                                \
            category,                                   \
            QX_SHORT_FILE,                              \
            qx::to_string(__FUNCTION__),                \
            QX_LINE,                                    \
            ##__VA_ARGS__)
#endif

#ifndef QX_LOG
    /**
        @def   QX_LOG
        @brief Log message
        @param eVerbosity - message verbosity 
        @param format     - format string
        @param ...        - additional args for formatting
    **/
    #define QX_LOG(eVerbosity, format, ...) QX_LOG_C(CatDefault, eVerbosity, format, ##__VA_ARGS__)
#endif

namespace qx
{

template<class... args_t>
concept log_acceptable_args_c = (sizeof...(args_t) > 0 && format_acceptable_args_c<char_type, args_t...>);

/**

    @class   logger
    @brief   Logger class
    @author  Khrapov
    @date    10.01.2020

**/
class logger
{
public:
    /**
        @brief  Log to all streams
        @param  category   - code category
        @param  eVerbosity - message verbosity
        @param  svFile     - file name string
        @param  svFunction - function name string
        @param  nLine      - code line number
        @param  svMessage  - message string
    **/
    void log(
        const category& category,
        verbosity       eVerbosity,
        string_view     svFile,
        string_view     svFunction,
        int             nLine,
        string_view     svMessage);

    /**
        @brief  Log to all streams
        @tparam args_t     - template parameter pack type
        @param  category   - code category
        @param  eVerbosity - message verbosity
        @param  svFile     - file name string
        @param  svFunction - function name string
        @param  nLine      - code line number
        @param  sFormat    - format string
        @param  args       - additional args for format
    **/
    template<class... args_t>
        requires(log_acceptable_args_c<args_t...>)
    void log(
        const category&                        category,
        verbosity                              eVerbosity,
        string_view                            svFile,
        string_view                            svFunction,
        int                                    nLine,
        format_string_strong_checks<args_t...> sFormat,
        args_t&&... args);

    /**
        @brief Flush all streams
    **/
    void flush();

    /**
        @brief  Add an output stream to the logger
        @tparam stream_t - stream type, derived from base_logger_stream
        @param  stream   - stream object
    **/
    template<sbo_poly_assignable_c<base_logger_stream> stream_t>
    void add_stream(stream_t stream) noexcept;

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
    std::vector<sbo_poly<base_logger_stream, 1024>> m_Streams;
};

/**

    @class   logger_singleton
    @brief   Default logger instance
    @author  Khrapov
    @date    19.08.2021

**/
class logger_singleton final : public singleton<logger_singleton>
{
public:
    logger& get_logger()
    {
        return m_Logger;
    }

private:
    logger m_Logger;
};

} // namespace qx

#include <qx/logger/logger.inl>
