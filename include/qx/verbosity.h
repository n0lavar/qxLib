/**

    @file      verbosity.h
    @author    Khrapov
    @date      23.07.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

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
inline bool is_error(verbosity eVerbosity) noexcept
{
    return eVerbosity == verbosity::error || eVerbosity == verbosity::critical;
}

} // namespace qx
