/**

    @file      test_qualifiers.cpp
    @author    Khrapov
    @date      20.08.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#include <common.h>

#include <qx/meta/qualifiers.h>

//V_EXCLUDE_PATH *test_qualifiers.cpp

// clang-format off
static_assert(std::is_same_v<qx::copy_qualifiers_t<               int,  float>,                float>);
static_assert(std::is_same_v<qx::copy_qualifiers_t<const          int,  float>, const          float>);
static_assert(std::is_same_v<qx::copy_qualifiers_t<      volatile int,  float>,       volatile float>);
static_assert(std::is_same_v<qx::copy_qualifiers_t<const volatile int,  float>, const volatile float>);

static_assert(std::is_same_v<qx::switch_qualifiers_t<               int>, const volatile int>);
static_assert(std::is_same_v<qx::switch_qualifiers_t<const          int>,       volatile int>);
static_assert(std::is_same_v<qx::switch_qualifiers_t<      volatile int>, const          int>);
static_assert(std::is_same_v<qx::switch_qualifiers_t<const volatile int>,                int>);

static_assert(std::is_same_v<qx::switch_const_t<               int>, const          int>);
static_assert(std::is_same_v<qx::switch_const_t<const          int>,                int>);
static_assert(std::is_same_v<qx::switch_const_t<      volatile int>, const volatile int>);
static_assert(std::is_same_v<qx::switch_const_t<const volatile int>,       volatile int>);

static_assert(std::is_same_v<qx::switch_volatile_t<               int>,       volatile int>);
static_assert(std::is_same_v<qx::switch_volatile_t<const          int>, const volatile int>);
static_assert(std::is_same_v<qx::switch_volatile_t<      volatile int>,                int>);
static_assert(std::is_same_v<qx::switch_volatile_t<const volatile int>, const          int>);
// clang-format on
