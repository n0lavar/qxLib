//==============================================================================
//
//!\file                            config.h
//
//!\brief       Config macros
//!\details     ~
//
//!\author      Khrapov
//!\date        25.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#ifdef _WIN64
    #define QX_WIN 1
#else
    #define QX_WIN 0
#endif

#ifdef __APPLE__
    #define QX_MACOS 1
#else
    #define QX_MACOS 0
#endif

#ifdef __linux__
    #define QX_LINUX 1
#else
    #define QX_LINUX 0
#endif