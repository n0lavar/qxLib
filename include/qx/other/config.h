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


#if defined(_WIN64) || defined(_WIN32)
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


#if _DEBUG
    #define QX_DEBUG 1
    #define QX_RELEASE 0
#else
    #define QX_DEBUG 0
    #define QX_RELEASE 1
#endif
