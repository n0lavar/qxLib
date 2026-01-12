/**

    @file      windows.h
    @author    Khrapov
    @date      11.01.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#if QX_WIN
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX

    #include <windows.h>

    #undef LoadBitmap
    #undef CreateFont
    #undef GetGeoInfo
#endif
