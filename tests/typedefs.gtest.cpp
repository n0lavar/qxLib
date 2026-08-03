/**

    @file      typedefs.gtest.cpp
    @author    Khrapov
    @date      26.09.2020
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

#include <qx/typedefs.h>

//V_EXCLUDE_PATH *.gtest.cpp

static_assert(sizeof(u8) == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(u64) == 8);
static_assert(sizeof(i8) == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);
