/**

    @file      windows.h
    @author    Khrapov
    @date      11.01.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/macros/suppress_warnings.h>

#if QX_WIN
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX

QX_PUSH_SUPPRESS_ALL_WARNINGS();
    #include <windows.h>
QX_POP_SUPPRESS_WARNINGS();

    #undef LoadBitmap
    #undef CreateFont
    #undef GetGeoInfo
#endif
