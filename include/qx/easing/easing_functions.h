/**

    @file      easing_functions.h
    @brief     File contains easing functions
    @details   See https://doc.magnum.graphics/magnum/namespaceMagnum_1_1Animation_1_1Easing.html
               for details
               For all y = f(x):
               0.0 <= x <= 1.0
               f(0.0) = 0.0 (with epsilon = qx::easing::eps<T>())
               f(1.0) = 1.0 (with epsilon = qx::easing::eps<T>())
    @author    Khrapov
    @date      4.05.2021
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/math/float_compare.h>

#include <cmath>
#include <functional>
#include <numbers>

namespace qx::easing
{

// ------------------------------- function type -------------------------------

template<class T>
using func = std::function<T(T)>;

// ---------------------- epsilon for borders guarantees -----------------------

template<class T>
constexpr T eps();

template<>
constexpr float eps();

// ----------------------------- easing functions ------------------------------

template<class T>
constexpr T linear_func(T x) noexcept;

constexpr auto linear = linear_func<float>;

template<class T>
constexpr T step_func(T x) noexcept;

constexpr auto step = step_func<float>;

template<class T>
inline T smooth_step_func(T x) noexcept;

constexpr auto smooth_step = smooth_step_func<float>;

template<class T>
inline T smoother_step_func(T x) noexcept;

constexpr auto smoother_step = smoother_step_func<float>;

template<class T>
inline T quadratic_in_func(T x) noexcept;

constexpr auto quadratic_in = quadratic_in_func<float>;

template<class T>
constexpr T quadratic_out_func(T x) noexcept;

constexpr auto quadratic_out = quadratic_out_func<float>;

template<class T>
inline T quadratic_in_out_func(T x) noexcept;

constexpr auto quadratic_in_out = quadratic_in_out_func<float>;

template<class T>
inline T cubic_in_func(T x) noexcept;

constexpr auto cubic_in = cubic_in_func<float>;

template<class T>
inline T cubic_out_func(T x) noexcept;

constexpr auto cubic_out = cubic_out_func<float>;

template<class T>
inline T cubic_in_out_func(T x) noexcept;

constexpr auto cubic_in_out = cubic_in_out_func<float>;

template<class T>
inline T quartic_in_func(T x) noexcept;

constexpr auto quartic_in = quartic_in_func<float>;

template<class T>
inline T quartic_out_func(T x) noexcept;

constexpr auto quartic_out = quartic_out_func<float>;

template<class T>
inline T quartic_in_out_func(T x) noexcept;

constexpr auto quartic_in_out = quartic_in_out_func<float>;

template<class T>
inline T quintic_in_func(T x) noexcept;

constexpr auto quintic_in = quintic_in_func<float>;

template<class T>
inline T quintic_out_func(T x) noexcept;

constexpr auto quintic_out = quintic_out_func<float>;

template<class T>
inline T quintic_in_out_func(T x) noexcept;

constexpr auto quintic_in_out = quintic_in_out_func<float>;

template<class T>
inline T sine_in_func(T x) noexcept;

constexpr auto sine_in = sine_in_func<float>;

template<class T>
inline T sine_out_func(T x) noexcept;

constexpr auto sine_out = sine_out_func<float>;

template<class T>
inline T sine_in_out_func(T x) noexcept;

constexpr auto sine_in_out = sine_in_out_func<float>;

template<class T>
inline T circular_in_func(T x) noexcept;

constexpr auto circular_in = circular_in_func<float>;

template<class T>
inline T circular_out_func(T x) noexcept;

constexpr auto circular_out = circular_out_func<float>;

template<class T>
inline T circular_in_out_func(T x) noexcept;

constexpr auto circular_in_out = circular_in_out_func<float>;

template<class T>
inline T exponential_in_func(T x) noexcept;

constexpr auto exponential_in = exponential_in_func<float>;

template<class T>
inline T exponential_out_func(T x) noexcept;

constexpr auto exponential_out = exponential_out_func<float>;

template<class T>
inline T exponential_in_out_func(T x) noexcept;

constexpr auto exponential_in_out = exponential_in_out_func<float>;

template<class T>
inline T elastic_in_func(T x) noexcept;

constexpr auto elastic_in = elastic_in_func<float>;

template<class T>
inline T elastic_out_func(T x) noexcept;

constexpr auto elastic_out = elastic_out_func<float>;

template<class T>
inline T elastic_in_out_func(T x) noexcept;

constexpr auto elastic_in_out = elastic_in_out_func<float>;

template<class T>
inline T back_in_func(T x) noexcept;

constexpr auto back_in = back_in_func<float>;

template<class T>
inline T back_out_func(T x) noexcept;

constexpr auto back_out = back_out_func<float>;

template<class T>
inline T back_in_out_func(T x) noexcept;

constexpr auto back_in_out = back_in_out_func<float>;

template<class T>
inline T bounce_out_func(T x) noexcept;

constexpr auto bounce_out = bounce_out_func<float>;

template<class T>
inline T bounce_in_func(T x) noexcept;

constexpr auto bounce_in = bounce_in_func<float>;

template<class T>
inline T bounce_in_out_func(T x) noexcept;

constexpr auto bounce_in_out = bounce_in_out_func<float>;

} // namespace qx::easing

#include <qx/easing/easing_functions.inl>
