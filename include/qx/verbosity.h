/**

    @file      verbosity.h
    @brief     Contains qx::verbosity enum
    @author    Khrapov
    @date      23.07.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

namespace qx
{

enum class verbosity
{
    very_verbose, // very frequently repeated messages, for example, on every update
    verbose,      // messages you don't want to be displayed by default
    log,          // default level
    important,    // same as log but highlighted if possible
    warning,      // not yet an error, but something to look out for
    error,        // an error after which it is possible to continue the program
    critical,     // an error that makes it impossible to continue the program
    none,         // message is not displayed
};

}
