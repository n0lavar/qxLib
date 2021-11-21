/**

    @file      concepts.h
    @brief     Concepts not included in std yet
    @author    Khrapov
    @date      2.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <type_traits>

namespace qx
{

template<class T>
concept enumeration = std::is_enum_v<T>;

}
