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
concept is_enumeration = std::is_enum_v<T>;

template<class T>
concept enumeration = is_enumeration<T>;

template<class T>
concept is_iterator = requires(T)
{
    typename T::iterator_category;
};

template<class T>
concept is_random_access_iterator =
    is_iterator<T> && std::derived_from<typename T::iterator_category, std::random_access_iterator_tag>;

// clang-format off

template<class T, class RetVal = void, class ...Args>
concept callable = requires(T t, Args&&... args)
{
    { t(std::forward<Args>(args)...) } -> std::convertible_to<RetVal>;
};

// clang-format on

} // namespace qx
