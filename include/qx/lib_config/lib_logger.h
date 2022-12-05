/**

    @file      lib_logger.h
    @brief     Contains QX_LIB_LOG macro
    @details   These macros should be used in lib only
    @author    Khrapov
    @date      19.07.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/logger/logger.h>

#ifndef QX_LIB_LOG
    #define QX_LIB_LOG(eLogLevel, format, ...) QX_TLOG("qxLib", eLogLevel, format, __VA_ARGS__)
#endif
