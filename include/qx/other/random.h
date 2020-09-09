//==============================================================================
//
//!\file                           random.h
//
//!\brief       random functions
//!\details     ~
//
//!\author      Khrapov
//!\date        22.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <type_traits>
#include <ctime>
#include <random>

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
typename std::enable_if<std::is_integral_v<T>, T>::type random (T min, T max)
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
typename std::enable_if<std::is_floating_point_v<T>, T>::type random(T min, T max)
{
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(generator);
}

}
