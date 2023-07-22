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
concept enumeration_c = is_enumeration<T>;

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

namespace detail
{

template<class range_t, class T>
concept is_iterator_arrow_operator_of_t_type = requires(range_t t) {
    {
        t.begin().operator->()
    } -> std::convertible_to<const T*>;
    {
        t.end().operator->()
    } -> std::convertible_to<const T*>;
};

template<class range_t, class T>
concept is_iterator_t_pointer = requires(range_t t) {
    {
        t.begin()
    } -> std::convertible_to<const T*>;
    {
        t.end()
    } -> std::convertible_to<const T*>;
};

} // namespace detail

template<class range_t, class T>
concept range_of_t_c =
    detail::is_iterator_arrow_operator_of_t_type<range_t, T> || detail::is_iterator_t_pointer<range_t, T>;

} // namespace qx
