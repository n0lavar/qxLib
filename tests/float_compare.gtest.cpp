/**

    @file      float_compare.gtest.cpp
    @author    Khrapov
    @date      25.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/math/float_compare.h>

// ----------------------------- qx::epsilon_equal -----------------------------

static_assert(qx::epsilon_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.45, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.48, 0.1));
static_assert(qx::epsilon_equal(0.5, 0.49, 0.1));
static_assert(!qx::epsilon_equal(0.5, 0.39, 0.1));

// ------------------------------ qx::epsilon_zero -----------------------------

static_assert(qx::epsilon_zero(0.0));
static_assert(qx::epsilon_zero(0.f));
static_assert(!qx::epsilon_zero(0.1));
static_assert(!qx::epsilon_zero(1.0));

// --------------------------- qx::epsilon_less_equal --------------------------

static_assert(qx::epsilon_less_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_less_equal(0.2, 0.45, 0.1));
static_assert(qx::epsilon_less_equal(0.0, 0.48, 0.1));
static_assert(!qx::epsilon_less_equal(0.5, 0.2, 0.1));
static_assert(!qx::epsilon_less_equal(0.5, 0.39, 0.1));

// ------------------------- qx::epsilon_greater_equal -------------------------

static_assert(qx::epsilon_greater_equal(0.5, 0.41, 0.1));
static_assert(qx::epsilon_greater_equal(0.5, 0.45, 0.1));
static_assert(qx::epsilon_greater_equal(0.5, 0.3, 0.1));
static_assert(!qx::epsilon_greater_equal(0.2, 0.49, 0.1));
static_assert(!qx::epsilon_greater_equal(0.0, 0.39, 0.1));
