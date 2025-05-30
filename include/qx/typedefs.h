﻿/**

    @file      typedefs.h
    @author    Khrapov
    @date      18.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <cmath>
#include <cstdint>

//!< 1 or 2 bytes for pointer arithmetic
using mem_t = char*;

//!< 0 .. 255
using u8 = std::uint8_t;
//!< 0 .. 65 535
using u16 = std::uint16_t;
//!< 0 .. 4 294 967 295
using u32 = std::uint32_t;
//!< 0 .. 18 446 744 073 709 551 615
using u64 = std::uint64_t;

//!< - 128 .. 127
using i8 = std::int8_t;
//!< – 32 768 .. 32 767
using i16 = std::int16_t;
//!< − 2 147 483 648 .. 2 147 483 647
using i32 = std::int32_t;
//!< − 9 223 372 036 854 775 808 .. 9 223 372 036 854 775 807
using i64 = std::int64_t;


using f32 = std::float_t;
using f64 = std::double_t;
