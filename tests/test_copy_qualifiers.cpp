/**

    @file      test_copy_qualifiers.cpp
    @author    Khrapov
    @date      20.08.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

#include <qx/meta/copy_qualifiers.h>

//V_EXCLUDE_PATH *test_copy_qualifiers.cpp

// clang-format off
static_assert(std::is_same_v<qx::copy_qualifiers_t<               int,  float>,                float>);
static_assert(std::is_same_v<qx::copy_qualifiers_t<const          int,  float>, const          float>);
static_assert(std::is_same_v<qx::copy_qualifiers_t<      volatile int,  float>,       volatile float>);
static_assert(std::is_same_v<qx::copy_qualifiers_t<const volatile int,  float>, const volatile float>);
// clang-format on
