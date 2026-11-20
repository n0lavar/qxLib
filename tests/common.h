/**

    @file      common.h
    @brief     Tests configuring
    @author    Khrapov
    @date      8.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/suppress_warnings.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS();
#include <gtest/gtest.h>
QX_POP_SUPPRESS_WARNINGS();

#define QX_GTEST_SINGLE_ARGUMENT(...) (__VA_ARGS__)
