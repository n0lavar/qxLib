/**

    @file      logger_formatters.h
    @author    Khrapov
    @date      11.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/containers/string/string.h>
#include <qx/macros/suppress_warnings.h>
#include <qx/verbosity.h>

#include <chrono>
#include <thread>

namespace qx
{

/**
    @brief  Format time string to the buffer
    @tparam out_it_t        - output iterator type
    @param  it              - output iterator
    @param  chDateDelimiter - char to use as delimiter in date part
    @param  chTimeDelimiter - char to use as delimiter in time part
    @param  time            - time to append
**/
template<class out_it_t>
inline void append_time_string(
    out_it_t                              it,
    char_type                             chDateDelimiter,
    char_type                             chTimeDelimiter,
    std::chrono::system_clock::time_point time) noexcept;

/**
    @brief  Get verbosity prefix
    @param  eVerbosity - message verbosity
    @retval            - verbosity prefix
**/
constexpr string_view get_verbosity_prefix(verbosity eVerbosity) noexcept;

/**
    @brief   The qx style log line formatter
    @code Examples:
   [08.01.2026_23:51:41] Time? Is it really that time again?
   [08.01.2026_23:51:41][CatCore] Time? Is it really that time again?
[W][08.01.2026_23:51:41] Time? Is it really that time again?
[W][08.01.2026_23:51:41][CatCore] Time? Is it really that time again?
    @endcode
    @param   category    - code category
    @param   eVerbosity  - message verbosity
    @param   threadId    - thread where the log is called
    @param   messageTime - message creation time
    @param   svFile      - file name string
    @param   svFunction  - function name string
    @param   nLine       - code line number
    @param   sMessage    - user message string
    @retval              - the formatted log line (the same object as sMessage)
**/
inline string format_message_qx(
    const category&                       category,
    verbosity                             eVerbosity,
    std::thread::id                       threadId,
    std::chrono::system_clock::time_point messageTime,
    string_view                           svFile,
    string_view                           svFunction,
    int                                   nLine,
    string                                sMessage) noexcept;

} // namespace qx

#include <qx/logger/logger_formatters.inl>
