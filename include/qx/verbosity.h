/**

    @file      verbosity.h
    @author    Khrapov
    @date      23.07.2023
    @copyright (c) Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_view.h>

#ifndef QX_CONF_COMPILE_TIME_VERBOSITY
    #define QX_CONF_COMPILE_TIME_VERBOSITY qx::verbosity::detailed
#endif

namespace qx
{

enum class verbosity
{
    detailed,  // very frequently repeated messages, for example, on every update
    verbose,   // messages you don't want to be displayed by default
    log,       // default level
    important, // same as log but highlighted if possible
    warning,   // not yet an error, but something to look out for
    error,     // an error after which it is possible to continue the program
    critical,  // an error that makes it impossible to continue the program
    none,      // message is not displayed
};

/**
    @brief  Check if the verbosity level is an error
    @param  eVerbosity - verbosity level to check
    @retval            - true if the verbosity level is error or critical, false otherwise
**/
constexpr bool is_error(verbosity eVerbosity) noexcept
{
    return eVerbosity == verbosity::error || eVerbosity == verbosity::critical;
}

} // namespace qx

template<class char_t>
struct QX_FMT_NS::formatter<qx::verbosity, char_t>
{
    bool bLog = false;

    template<class format_parse_context_t>
    constexpr auto parse(format_parse_context_t& ctx)
    {
        auto it = ctx.begin();

        // format for logs. [X] form.
        if (it != ctx.end() && *it == QX_CHAR_PREFIX(char_t, 'l'))
        {
            ++it;
            bLog = true;
        }

        if (it != ctx.end() && *it != QX_CHAR_PREFIX(char_t, '}'))
            throw QX_FMT_NS::format_error("unknown spec");

        return it;
    }

    template<class format_context_type>
    constexpr auto format(qx::verbosity value, format_context_type& ctx) const
    {
        auto get_log_name = [value]() -> basic_string_view<char_t>
        {
            switch (value)
            {
            case qx::verbosity::detailed:
                return QX_STR_PREFIX(char_t, "[D]");
            case qx::verbosity::verbose:
                return QX_STR_PREFIX(char_t, "[V]");
            case qx::verbosity::log:
                return QX_STR_PREFIX(char_t, "   ");
            case qx::verbosity::important:
                return QX_STR_PREFIX(char_t, "[I]");
            case qx::verbosity::warning:
                return QX_STR_PREFIX(char_t, "[W]");
            case qx::verbosity::error:
                return QX_STR_PREFIX(char_t, "[E]");
            case qx::verbosity::critical:
                return QX_STR_PREFIX(char_t, "[C]");
            case qx::verbosity::none:
                return QX_STR_PREFIX(char_t, "   ");
            }

            return QX_STR_PREFIX(char_t, "   ");
        };

        auto get_full_name = [value]() -> basic_string_view<char_t>
        {
            switch (value)
            {
            case qx::verbosity::detailed:
                return QX_STR_PREFIX(char_t, "detailed");
            case qx::verbosity::verbose:
                return QX_STR_PREFIX(char_t, "verbose");
            case qx::verbosity::log:
                return QX_STR_PREFIX(char_t, "log");
            case qx::verbosity::important:
                return QX_STR_PREFIX(char_t, "important");
            case qx::verbosity::warning:
                return QX_STR_PREFIX(char_t, "warning");
            case qx::verbosity::error:
                return QX_STR_PREFIX(char_t, "error");
            case qx::verbosity::critical:
                return QX_STR_PREFIX(char_t, "critical");
            case qx::verbosity::none:
                return QX_STR_PREFIX(char_t, "none");
            }

            return QX_STR_PREFIX(char_t, "");
        };

        return QX_FMT_NS::format_to(ctx.out(), QX_STR_PREFIX(char_t, "{}"), bLog ? get_log_name() : get_full_name());
    }
};
