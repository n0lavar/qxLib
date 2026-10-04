/**

    @file      logger_specifiers.h
    @author    Khrapov
    @date      9.09.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/category.h>
#include <qx/containers/string/string_converters.h>
#include <qx/verbosity.h>

#include <chrono>
#include <thread>

namespace qx
{

// Values that can be used in logger patterns.
// Must be kept in line with format_log_specifiers().
enum class logger_specifiers
{
    // Type: `qx::category`
    // Supports `{category:l}` ("log"),
    // which results in `[CatName]` and so on, and `` for `CatDefault`.
    category = 0,

    // Type: `qx::verbosity`
    // Supports `{verbosity:l}` ("log"),
    // which results in `[V]` ("verbose") and so on, and `   ` for the `qx::verbosity::log`.
    verbosity = 1,

    // Type: `std::thread::id`
    // Always results in `0` for now (`std::thread::id` is formattable since C++23).
    thread_id = 2,

    // Type: `std::chrono::system_clock::time_point`
    // Seconds floored value.
    time = 3,

    // Type: `qx::string_view`
    // QX_SHORT_FILE value
    file = 4,

    // Type: `qx::string_view`
    // __FUNCTION__ value.
    function = 5,

    // Type: `int`
    // QX_LINE value.
    line = 6,

    // Type: `qx::string_view`
    // Formatting result.
    message = 7,
};

enum class compile_pattern_result
{
    ok,
    unclosed_field,
    unmatched_closing_brace,
    unknown_specifier,
    invalid_field,
};

/**
    @brief   Compile an fmt pattern with named arguments into replacement fields
    @details This function is required because std format doesn't support named arguments.
             This function doesn't allocate.
    @tparam  char_t   - char type (char, wchar_t, etc)
    @tparam  traits_t - char traits. \see string_traits.h
    @param   sPattern - fmt pattern that must have only arguments from logger_specifiers.
                        One type may be absent or present multiple times.
                        You can use any format specifiers.
                        The result will be in the same string.
    @retval           - Compilation result. If != ok, sPattern is considered invalid.
**/
template<class char_t, class traits_t>
compile_pattern_result compile_pattern(basic_string<char_t, traits_t>& sPattern) noexcept;

/**
    @brief  Format sStorage using qx::logger_specifiers
    @param  sStorage    - where to put the result
    @param  svPattern   - formatting pattern, see qx::logger_specifiers
    @param  category    - code category
    @param  eVerbosity  - message verbosity
    @param  threadId    - thread where the log is called
    @param  messageTime - message creation time
    @param  svFile      - file name string
    @param  svFunction  - function name string
    @param  nLine       - code line number
    @param  svMessage   - user message string
**/
inline void format_log_specifiers(
    string&                               sStorage,
    string_view                           svPattern,
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string_view                           svMessage);

} // namespace qx

#include <qx/logger/logger_specifiers.inl>
