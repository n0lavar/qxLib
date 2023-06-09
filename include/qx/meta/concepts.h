/**

    @file      concepts.h
    @brief     Concepts not included in std yet
    @author    Khrapov
    @date      2.11.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <type_traits>
#include <utility>

namespace qx
{

template<class T>
concept is_enumeration = std::is_enum_v<T>;

template<class T>
concept enumeration = is_enumeration<T>;

template<class T>
concept is_iterator = requires(T) { typename T::iterator_category; };

template<class T>
concept is_random_access_iterator =
    is_iterator<T> && std::derived_from<typename T::iterator_category, std::random_access_iterator_tag>;

template<class T, class return_t, class... args_t>
concept callable_c = requires(T t, args_t&&... args) {
    {
        t(std::forward<args_t>(args)...)
    } -> std::convertible_to<return_t>;
};

} // namespace qx
