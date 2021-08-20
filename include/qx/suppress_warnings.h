/**

    @file      suppress_warnings.h
    @brief     Suppress warnings macros
    @author    Khrapov
    @date      11.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/config.h>

#if QX_WIN

    /**
        @macro QX_PUSH_SUPPRESS_MSVC_WARNINGS
        @brief Disable specified MSVC warnings
        @param warnings - MSVC warnings numbers separated by space
    **/
    #define QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings) \
        __pragma(warning(push));                     \
        __pragma(warning(disable : warnings));

    /**
        @macro QX_PUSH_SUPPRESS_ALL_WARNINGS
        @brief Disable all warnings
    **/
    #define QX_PUSH_SUPPRESS_ALL_WARNINGS __pragma(warning(push, 0));

    /**
        @macro QX_POP_SUPPRESS_WARNINGS
        @brief Enable all warnings
    **/
    #define QX_POP_SUPPRESS_WARNINGS __pragma(warning(pop));

#else

    #define QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)
    #define QX_PUSH_SUPPRESS_ALL_WARNINGS
    #define QX_POP_SUPPRESS_WARNINGS

#endif
