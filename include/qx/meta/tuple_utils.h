/**

    @file      tuple_utils.h
    @brief     Contains utils for working with std::tuple
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <tuple>
#include <type_traits>

namespace qx::tuple
{

// -------------------------------------------------------- join -------------------------------------------------------

/**
    @struct join
    @brief  Appends types or another tuple to tuple
**/
template<class...>
struct join
{
};

template<class... first_pack_t, class... second_pack_t>
struct join<std::tuple<first_pack_t...>, std::tuple<second_pack_t...>>
{
    using type = std::tuple<first_pack_t..., second_pack_t...>;
};

template<class... first_pack_t, class second_t, class... optional_args_t>
struct join<std::tuple<first_pack_t...>, second_t, optional_args_t...>
{
    using type = std::tuple<first_pack_t..., second_t, optional_args_t...>;
};

template<class... args_t>
using join_t = typename join<args_t...>::type;

// ------------------------------------------------------- remove ------------------------------------------------------

namespace details
{

template<class...>
struct remove_single
{
};

template<class target_t, class... pack_t>
struct remove_single<target_t, std::tuple<pack_t...>>
{
    using type = std::tuple<pack_t...>;
};

template<class target_t, class parameter_t, class... pack_t>
struct remove_single<target_t, std::tuple<parameter_t, pack_t...>>
{
    using type = typename join<
        std::conditional_t<std::is_same_v<target_t, parameter_t>, std::tuple<>, std::tuple<parameter_t>>,
        typename remove_single<target_t, std::tuple<pack_t...>>::type>::type;
};

} // namespace details

/**
    @struct remove
    @brief  Removes all types from the second argument from the first tuple
**/
template<class...>
struct remove
{
};

template<class... types_t>
struct remove<std::tuple<types_t...>, std::tuple<>>
{
    using type = std::tuple<types_t...>;
};

template<class target_t, class... remaining_targets_t, class... types_t>
struct remove<std::tuple<types_t...>, std::tuple<target_t, remaining_targets_t...>>
{
    using type = typename details::remove_single<
        target_t,
        typename remove<std::tuple<types_t...>, std::tuple<remaining_targets_t...>>::type>::type;
};

template<class... args_t>
using remove_t = typename remove<args_t...>::type;

// ------------------------------------------------------ contains -----------------------------------------------------

namespace details
{

template<class T, class tuple_t>
struct contains;

template<class T>
struct contains<T, std::tuple<>> : std::false_type
{
};

template<class T, class U, class... args_t>
struct contains<T, std::tuple<U, args_t...>> : contains<T, std::tuple<args_t...>>
{
};

template<class T, class... args_t>
struct contains<T, std::tuple<T, args_t...>> : std::true_type
{
};

} // namespace details

/**
    @struct contains
    @brief  Check that tuple type contains T
    @tparam tuple_t - std::tuple<> type
    @tparam T       - type to check
**/
template<class tuple_t, class T>
using contains = details::contains<T, tuple_t>;

template<class tuple_t, class T>
static constexpr bool contains_v = contains<tuple_t, T>::value;

// ----------------------------------------------------- transform -----------------------------------------------------

/**
    @struct transform
    @brief  Get a new tuple type by transforming every type inside a given tuple
    @tparam tuple_t          - std::tuple<> type
    @tparam transformation_t - transformation type, for ex. std::add_pointer, std::remove_pointer etc. (without `_t`!)
**/
template<class tuple_t, template<class T> class transformation_t>
struct transform;

template<template<class T> class transformation_t, class... args_t>
struct transform<std::tuple<args_t...>, transformation_t>
{
    using type = std::tuple<typename transformation_t<args_t>::type...>;
};

template<class tuple_t, template<class T> class transformation_t>
using transform_t = typename transform<tuple_t, transformation_t>::type;

// ------------------------------------------------------- index -------------------------------------------------------

/**
    @struct index
    @brief  Get an index of the first occurrence of the given type
    @tparam tuple_t - std::tuple<> type
    @tparam T       - type to check
**/
template<class tuple_t, class T>
struct index;

template<class T, class... args_t>
struct index<std::tuple<T, args_t...>, T>
{
    static constexpr size_t value = 0;
};

template<class T, class U, class... args_t>
struct index<std::tuple<U, args_t...>, T>
{
    static constexpr size_t value = 1 + index<std::tuple<args_t...>, T>::value;
};

template<class tuple_t, class T>
constexpr size_t index_v = index<tuple_t, T>::value;

// ------------------------------------------------------ iterate ------------------------------------------------------

/**
    @brief  Iterate over a tuple with a callable that receives a type along with a its index 
    @tparam tuple_t         - std::tuple<> type
    @tparam type_callable_t - callable type
    @param  callable        - callable object

    @code
    using tuple_type = std::tuple<float, int, std::string, unsigned, size_t>;
    qx::tuple::iterate<tuple_type>(
        []<class T, size_t I>()
        {
            // ...
        });
    @endcode
**/
template<class tuple_t, class type_callable_t>
constexpr void iterate(const type_callable_t& callable)
{
    // we need to add a pointer because we can't compile a tuple with an abstract class type
    using tuple_pointer_type = transform_t<tuple_t, std::add_pointer>;

    auto temp_callable = [&callable]<class T>(const T&)
    {
        callable.template operator()<std::remove_pointer_t<T>, index_v<tuple_pointer_type, T>>();
    };

    std::apply(
        [&temp_callable](auto&&... args)
        {
            ((temp_callable(args)), ...);
        },
        tuple_pointer_type());
}

} // namespace qx::tuple
