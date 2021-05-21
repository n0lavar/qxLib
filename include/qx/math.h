//==============================================================================
//
//!\file                            math.h
//
//!\brief       Math functions
//!\details     ~
//
//!\author      Khrapov
//!\date        22.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <ctime>
#include <limits>
#include <random>
#include <type_traits>

namespace qx
{

//==============================================================================
//!\fn                         qx::random<T>
//
//!\brief  Get random generated integral value [min, max]
//!\param  min - min uniform distribution value (including)
//!\param  max - max uniform distribution value (including)
//!\retval     - random generated integral value
//!\author Khrapov
//!\date   22.03.2020
//==============================================================================
template<class T>
typename std::enable_if_t<std::is_integral_v<T>, T> random(T min, T max)
{
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(generator);
}

//==============================================================================
//!\fn                         qx::random<T>
//
//!\brief  Get random generated real value [min, max]
//!\param  min - min uniform distribution value (including)
//!\param  max - max uniform distribution value (including)
//!\retval     - random generated integral value
//!\author Khrapov
//!\date   22.03.2020
//==============================================================================
template<class T>
typename std::enable_if_t<std::is_floating_point_v<T>, T> random(T min, T max)
{
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(generator);
}

//==============================================================================
//!\fn                          qx::meta::abs<T>
//
//!\brief  Constexpr absolute value
//!\param  value - value
//!\retval       - absolute value
//!\author Khrapov
//!\date   24.09.2020
//==============================================================================
template<typename T>
constexpr T abs(T value)
{
    return value < 0 ? -value : value;
}

//==============================================================================
//!\fn                        qx::epsilon_equal<T>
//
//!\brief  Constexpr comparison function for a user defined epsilon values
//!\param  left  - left value
//!\param  right - right value
//!\param  eps   - epsilon value
//!\retval       - true if |left - right| < eps
//!\author Khrapov
//!\date   24.09.2020
//==============================================================================
template<typename T>
constexpr bool epsilon_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return abs(left - right) < eps;
}

//==============================================================================
//!\fn                     qx::epsilon_less_equal<T>
//
//!\brief  Constexpr comparison function for a user defined epsilon values
//!\param  left  - left value
//!\param  right - right value
//!\param  eps   - epsilon value
//!\retval       - true if left < right or |left - right| < eps
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
constexpr bool epsilon_less_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return left < right || epsilon_equal(left, right, eps);
}

//==============================================================================
//!\fn                    qx::epsilon_greater_equal<T>
//
//!\brief  Constexpr comparison function for a user defined epsilon values
//!\param  left  - left value
//!\param  right - right value
//!\param  eps   - epsilon value
//!\retval       - true if left > right or |left - right| < eps
//!\author Khrapov
//!\date   5.05.2021
//==============================================================================
template<typename T>
constexpr bool epsilon_greater_equal(T left, T right, T eps = std::numeric_limits<T>::epsilon())
{
    return left > right || epsilon_equal(left, right, eps);
}


}
