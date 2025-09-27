/**

    @file      type_traits.h
    @author    Khrapov
    @data      10.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/meta/concepts.h>

namespace qx
{

// ------------------------------------------------- same_variadic_args ------------------------------------------------

template<class...>
struct same_variadic_args;

template<class T>
struct same_variadic_args<T> : std::true_type
{
    using type = T;
};

template<class first_t, class second_t, class... rest_t>
struct same_variadic_args<first_t, second_t, rest_t...> : std::false_type
{
};

// check if all of variadic arguments are same type
template<class first_t, class... rest_ty>
struct same_variadic_args<first_t, first_t, rest_ty...> : same_variadic_args<first_t, rest_ty...>
{
};

template<class... args_t>
constexpr bool same_variadic_args_v = same_variadic_args<args_t...>::value;



// ----------------------------------------------- specific_variadic_args ----------------------------------------------

template<class T, class... args_t>
struct specific_variadic_args
{
    static constexpr bool value = std::conjunction_v<std::is_same<T, args_t>...>;
};

template<class T, class... args_t>
static constexpr bool specific_variadic_args_v = specific_variadic_args<T, args_t...>::value;


// --------------------------------------------------- iterator_value --------------------------------------------------

// get value type of iterator
template<class T, class = void>
struct iterator_value
{
};

// default implementation with ::value_type
template<class T>
struct iterator_value<T, std::enable_if_t<is_iterator<T>>>
{
    using type = typename T::value_type;
};

// some iterators may be implemented as pointers
template<class T>
struct iterator_value<T, std::enable_if_t<std::is_pointer_v<T>>>
{
    using type = std::remove_pointer_t<T>;
};

template<class T>
using iterator_value_t = typename iterator_value<T>::type;



// ---------------------------------------------- is_specialization_exist ----------------------------------------------

namespace details
{

template<class T, std::size_t = sizeof(T)>
std::true_type is_specialization_exist_impl(T*);

std::false_type is_specialization_exist_impl(...);

} // namespace details

// decide if a struct/class specialization exist
template<class T>
using is_specialization_exist = decltype(details::is_specialization_exist_impl(std::declval<T*>()));

template<class T>
constexpr bool is_specialization_exist_v = is_specialization_exist<T>::value;



// ------------------------------------------------ is_specialization_of -----------------------------------------------

template<class test_t, template<class...> class reference_t>
struct is_specialization_of : std::false_type
{
};

template<template<class...> class reference_t, class... args_t>
struct is_specialization_of<reference_t<args_t...>, reference_t> : std::true_type
{
};

// --------------------------------------------------- visit_overload --------------------------------------------------

/**
    @struct  visit_overload
    @details This struct allows to visit std::variant with lambdas
    @note    https://www.cppstories.com/2018/09/visit-variants/
    @tparam  args_t - lambda types

    @code
    struct Fluid { };
    struct LightItem { };
    struct HeavyItem { };
    struct FragileItem { };

    int main() {
        std::variant<Fluid, LightItem, HeavyItem, FragileItem> package;

        std::visit(qx::visit_overload
            {
                [](const Fluid& )     { std::cout << "fluid\n"; },
                [](const LightItem& ) { std::cout << "light item\n"; },
                [](const auto&)       { std::cout << "default\n"; }
            },
            package);
    }
    @endcode 
**/
template<class... args_t>
struct visit_overload : args_t...
{
    using args_t::operator()...;
};

template<class... args_t>
visit_overload(args_t...) -> visit_overload<args_t...>;

} // namespace qx
