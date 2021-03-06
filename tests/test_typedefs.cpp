//==============================================================================
//
//!\file                       test_typedefs.cpp
//
//!\brief       Tests for typedefs
//!\details     ~
//
//!\author      Khrapov
//!\date        26.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_typedefs.cpp

#if QX_TEST_TYPEDEFS

#include <limits>
#include <qx/typedefs.h>
#include <qx/useful_macros.h>

static_assert(sizeof(u8)  == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(u64) == 8);
static_assert(sizeof(i8)  == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

#endif
