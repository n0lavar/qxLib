/**

    @file      logger.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/flags.h>
#include <qx/containers/string/string_converters.h>
#include <qx/logger/fwrite_logger_stream.h>
#include <qx/logger/logger_formatters.h>
#include <qx/macros/details/macro_user_message.h>
#include <qx/memory/sbo_poly.h>
#include <qx/patterns/singleton.h>

#include <ranges>
#include <shared_mutex>

/**
    @page logger_readme logger
    @include README.md
*/

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
    using logger_sbo = sbo_poly<
        base_logger_stream,
#if QX_CLANG || QX_APPLE_CLANG || QX_GNU
        1024
#else
        512
#endif
        >;

    // For best performance, do not allocate anything in this function and return the modified sMessage object.
    // See default_formatter for an example.
    using format_signature = string(
        const category&,
        verbosity,
        std::thread::id,
        std::chrono::system_clock::time_point,
        string_view,
        string_view,
        int,
        string);
    using format_function_pointer = format_signature*;
    using format_function         = std::function<format_signature>;

    struct category_data
    {
        verbosity       eRuntimeVerbosity = verbosity::detailed;
        format_function formatFunction;
    };

    using category_data_map  = std::unordered_map<string_view, category_data>;
    using logger_string_pool = string_pool<>;

    enum class message_necessity_type
    {
        not_required            = 0,
        default_verbosity       = 1 << 0,
        category_verbosity      = 1 << 1,
        one_of_streams_requires = 1 << 2
    };

public:
    logger() noexcept;
    virtual ~logger() noexcept;

    /**
        @brief  Add an output stream to the logger
        @tparam stream_t - stream type, derived from base_logger_stream
        @param  stream   - stream object
    **/
    template<sbo_poly_assignable_c<base_logger_stream> stream_t>
    void add_stream(stream_t stream) noexcept;

    /**
        @brief   Get the first occurrence of a stream of the given type
        @warning This must be protected with get_streams_mutex() shared lock
        @tparam  stream_t - stream type to search for
        @retval           - stream pointer or nullptr if no stream found
    **/
    template<sbo_poly_assignable_c<base_logger_stream> stream_t>
    stream_t* get_stream() noexcept;

    /**
        @brief   Get all the streams of the given type
        @warning This must be protected with get_streams_mutex() shared lock
        @tparam  stream_t - stream type to search for
        @retval           - streams view
    **/
    template<sbo_poly_assignable_c<base_logger_stream> stream_t>
    auto get_streams() noexcept;

    /**
        @brief  Get streams mutex
        @retval  - streams mutex
    **/
    std::shared_mutex& get_streams_mutex() noexcept;

    /**
        @brief  Remove all the streams of the given type
        @tparam stream_t - stream type to search for
        @retval          - number of streams removed
    **/
    template<sbo_poly_assignable_c<base_logger_stream> stream_t>
    size_t remove_streams() noexcept;

    /**
        @brief Add custom rules for category
        @param category - category to register
        @param data     - category data
    **/
    void register_category(const category& category, category_data data) noexcept;

    /**
        @brief Add custom rules for category
        @param svCategoryName - category name, must stay valid while the logger is alive (category existence is not checked)
        @param data           - category data
    **/
    void register_category(string_view svCategoryName, category_data data) noexcept;

    /**
        @brief Set a function that will be used as the default formatter in case no formatter found in categories registered
        @param pFormatter - default formatter
    **/
    void set_default_formatter(format_function_pointer pFormatter) noexcept;

    /**
        @brief   Log to all streams
        @warning All input args must be ready for async work (i.e. be stable)
        @param   category    - code category
        @param   eVerbosity  - message verbosity
        @param   threadId    - thread where the log is called
        @param   messageTime - message creation time
        @param   svFile      - file name string
        @param   svFunction  - function name string
        @param   nLine       - code line number
        @param   message     - user message string
    **/
    virtual void log(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine,
        logger_string_pool::item              message);

    /**
        @brief Flush all streams
    **/
    virtual void flush();

    /**
        @brief Reset logger and clear all streams
    **/
    virtual void reset() noexcept;

    /**
        @brief   Check if this message will go somewhere
        @details Typically you don't want to use it.
                 It may be useful with async logging to avoid unnecessary formatting and queueing.
        @param   category    - code category
        @param   eVerbosity  - message verbosity
        @param   threadId    - thread where the log is called
        @param   messageTime - message creation time
        @param   svFile      - file name string
        @param   svFunction  - function name string
        @param   nLine       - code line number
        @retval              - get message necessity type
    **/
    flags<message_necessity_type> get_message_necessity_type(
        const category&                       category,
        verbosity                             eVerbosity,
        std::thread::id                       threadId,
        std::chrono::system_clock::time_point messageTime,
        string_view                           svFile,
        string_view                           svFunction,
        int                                   nLine) const noexcept;

    // only for internal usage in macros
    logger_string_pool* _get_string_pool() noexcept;

private:
    QX_PERF_SHARED_MUTEX(m_StreamsMutex);
    std::vector<logger_sbo> m_Streams;

    QX_PERF_SHARED_MUTEX(m_RegisteredCategoriesMutex);
    category_data_map m_RegisteredCategories;

    logger_string_pool m_StringsPool;

    std::atomic<format_function_pointer> m_DefaultFormatFunction = format_message_qx;
    static_assert(std::atomic<format_function_pointer>::is_always_lock_free);
};

QX_FLAGS_ENUM_CLASS(logger::message_necessity_type);

/**

    @class   logger_singleton
    @brief   Default logger instance
    @author  Khrapov
    @date    19.08.2021

**/
class logger_singleton final : public singleton<logger_singleton>
{
public:
    logger& get_logger() noexcept
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
inline logger& get_logger() noexcept
{
    return g_pGlobalLogger ? *g_pGlobalLogger : logger_singleton::get_instance().get_logger();
}

} // namespace qx

#ifndef _QX_LOG_C
// __FUNCTION__ isn't a char array on linux, so we need to convert it
    #define _QX_LOG_C(verbosityCheckKeyword, category, eVerbosity, ...)               \
        do                                                                            \
        {                                                                             \
            verbosityCheckKeyword const auto& _category = category;                   \
            if verbosityCheckKeyword (eVerbosity >= _category.get_verbosity())        \
            {                                                                         \
                qx::logger& _logger = qx::get_logger();                               \
                _logger.log(                                                          \
                    _category,                                                        \
                    eVerbosity,                                                       \
                    std::this_thread::get_id(),                                       \
                    std::chrono::system_clock::now(),                                 \
                    QX_SHORT_FILE,                                                    \
                    qx::convert_string_literal<qx::char_type, __FUNCTION__>(),        \
                    QX_LINE,                                                          \
                    _QX_MACRO_USER_MESSAGE(_logger._get_string_pool(), __VA_ARGS__)); \
            }                                                                         \
        } while (false)
#endif

#include <qx/logger/logger.inl>
