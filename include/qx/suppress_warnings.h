//==============================================================================
//
//!\file                       suppress_warnings.h
//
//!\brief       Supress warnings macros
//!\details     ~
//
//!\author      Khrapov
//!\date        11.11.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/config.h>

#if QX_WIN

    #define QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)    \
        __pragma(warning(push));                        \
        __pragma(warning(disable : warnings));

    #define QX_PUSH_SUPPRESS_ALL_WARNINGS \
        __pragma(warning(push, 0));

    #define QX_POP_SUPPRESS_WARNINGS \
        __pragma(warning(pop));

#else

    #define QX_PUSH_SUPPRESS_MSVC_WARNINGS(warnings)
    #define QX_PUSH_SUPPRESS_ALL_WARNINGS
    #define QX_POP_SUPPRESS_WARNINGS

#endif
