/**

    @file      type_traits.h
    @brief     Type traits
    @author    Khrapov10.09.202020.08.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/meta/concepts.h>

namespace qx
{

//--------------------------------- are_same ---------------------------------

template<class...>
struct are_same : std::true_type
{
};

template<class S, class T, class... Ts>
struct are_same<S, T, Ts...> : std::false_type
{
};

// check if all of variadic arguments are same type
template<class T, class... Ts>
struct are_same<T, T, Ts...> : are_same<T, Ts...>
{
};

template<class... Ts>
constexpr bool are_same_v = are_same<Ts...>::value;



//------------------------------- iterator_value -------------------------------

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



//--------------------------- is_specialization_exist --------------------------

namespace detail
{
template<class T, std::size_t = sizeof(T)>
std::true_type is_specialization_exist_impl(T*);

std::false_type is_specialization_exist_impl(...);
} // namespace detail

// decide if a struct/class specialization exist
template<class T>
using is_specialization_exist = decltype(detail::is_specialization_exist_impl(std::declval<T*>()));

template<class T>
constexpr bool is_specialization_exist_v = is_specialization_exist<T>::value;



//---------------------------- is_specialization_of ----------------------------

template<class Test, template<class...> class Ref>
struct is_specialization_of : std::false_type
{
};

template<template<class...> class Ref, class... Args>
struct is_specialization_of<Ref<Args...>, Ref> : std::true_type
{
};

// ----------------------------- qx::visit_overload ----------------------------

/**
    @struct  visit_overload
    @details This struct allows to visit std::variant with lambdas
    @note    https://www.cppstories.com/2018/09/visit-variants/
    @tparam  Ts - lambda types

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
template<class... Ts>
struct visit_overload : Ts...
{
    using Ts::operator()...;
};

template<class... Ts>
visit_overload(Ts...) -> visit_overload<Ts...>;

} // namespace qx