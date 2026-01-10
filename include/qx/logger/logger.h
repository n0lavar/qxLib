/**

    @file      logger.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/logger/base_logger_stream.h>
#include <qx/macros/details/macro_user_message.h>
#include <qx/patterns/singleton.h>
#include <qx/sbo/sbo_poly.h>

#ifndef _QX_LOG_C
    #define _QX_LOG_C(verbosityCheckKeyword, category, eVerbosity, ...)        \
        do                                                                     \
        {                                                                      \
            verbosityCheckKeyword const auto& _category = category;            \
            if verbosityCheckKeyword (eVerbosity >= _category.get_verbosity()) \
            {                                                                  \
                qx::get_logger().log(                                          \
                    _category,                                                 \
                    eVerbosity,                                                \
                    QX_SHORT_FILE,                                             \
                    __FUNCTION__,                                              \
                    QX_LINE,                                                   \
                    _QX_MACRO_USER_MESSAGE(__VA_ARGS__));                      \
            }                                                                  \
        } while (false)
#endif

/**
    @brief Log with category
    @param category   - category to be used to manage output
    @param eVerbosity - message verbosity
    @param ...        - user message and its format args. the format string should be without QXT
**/
#define QX_LOG_C(category, eVerbosity, ...) _QX_LOG_C(constexpr, category, eVerbosity, ##__VA_ARGS__)

/**
    @brief Log message
    @param eVerbosity - message verbosity 
    @param ...        - user message and its format args. the format string should be without QXT
**/
#define QX_LOG(eVerbosity, ...) QX_LOG_C(QX_GET_FILE_CATEGORY(), eVerbosity, ##__VA_ARGS__)

/**
    @brief Log with category and with non compile time category check
    @param category   - category to be used to manage output
    @param eVerbosity - message verbosity
    @param ...        - user message and its format args. the format string should be without QXT
**/
#define QX_LOG_REF(category, eVerbosity, ...) _QX_LOG_C(, category, eVerbosity, ##__VA_ARGS__)

namespace qx
{

/**

    @class   logger
    @brief   Logger class
    @author  Khrapov
    @date    10.01.2020

**/
class logger
{
public:
    virtual ~logger() noexcept = default;

    /**
        @brief   Log to all streams
        @warning All input args must be ready for async work (i.e. be stable)
        @param   category   - code category
        @param   eVerbosity - message verbosity
        @param   svFile     - file name string
        @param   svFunction - function name string
        @param   nLine      - code line number
        @param   sMessage   - message string
    **/
    virtual void log(
        const category& category,
        verbosity       eVerbosity,
        string_view     svFile,
        cstring_view    svFunction,
        int             nLine,
        string          sMessage);

    /**
        @brief   Log to all streams
        @warning All input args (except for sFormat and args) must be ready for async work (i.e. be stable)
        @tparam  args_t     - template parameter pack type
        @param   category   - code category
        @param   eVerbosity - message verbosity
        @param   svFile     - file name string
        @param   svFunction - function name string
        @param   nLine      - code line number
        @param   sFormat    - format string
        @param   args       - additional args for format
    **/
    template<class... args_t>
        requires(log_acceptable_args_c<args_t...>)
    void log(
        const category&                        category,
        verbosity                              eVerbosity,
        string_view                            svFile,
        cstring_view                           svFunction,
        int                                    nLine,
        format_string_strong_checks<args_t...> sFormat,
        args_t&&... args);

    /**
        @brief Flush all streams
    **/
    virtual void flush();

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
    virtual void reset() noexcept;

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
        cstring_view    svFunction) const noexcept;

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

// Change this variable to override the logger instance used in QX_LOG macros
inline logger* g_pGlobalLogger = nullptr;

/**
    @brief  Get the logger instance used in QX_LOG macros
    @retval  - logger instance
**/
inline logger& get_logger()
{
    return g_pGlobalLogger ? *g_pGlobalLogger : logger_singleton::get_instance().get_logger();
}

} // namespace qx

#include <qx/logger/logger.inl>
