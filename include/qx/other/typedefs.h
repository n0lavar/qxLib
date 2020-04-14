//============================================================================
//
//!\file                          typedefs.h
//
//!\brief       Project typedefs
//!\details     ~
//
//!\author      Khrapov
//!\date        18.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <stdint.h>

using mem_t = char*;                //!< 1 byte for pointer arithmetic

using u8    = uint8_t;              //!<                           0 .. 255
using u16   = uint16_t;             //!<                           0 .. 65 535
using u32   = uint32_t;             //!<                           0 .. 4 294 967 295
using u64   = uint64_t;             //!<                           0 .. 18 446 744 073 709 551 615

using i8    = int8_t;               //!<                       - 128 .. 127
using i16   = int16_t;              //!<                    – 32 768 .. 32 767
using i32   = int32_t;              //!<             − 2 147 483 648 .. 2 147 483 647
using i64   = int64_t;              //!< − 9 223 372 036 854 775 808 .. 9 223 372 036 854 775 807

static_assert(sizeof(u8 ) == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4); //-V112
static_assert(sizeof(u64) == 8);
static_assert(sizeof(i8 ) == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4); //-V112
static_assert(sizeof(i64) == 8);

// not using constexpr for compatibility with u8 - u64 types
#define UINT_EMPTY_VALUE (-1)
