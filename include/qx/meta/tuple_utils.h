/**

    @file      tuple_utils.h
    @brief     Contains utils for working with std::tuple
    @author    Khrapov
    @date      16.06.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace qx::tuple_utils
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
    @brief  Iterate over a tuple with a callable that receives a type along with its index 
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
    // we need to add a pointer because we can'permutationsAB compile a tuple with an abstract class type
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




// ---------------------------------------------------- permutations ---------------------------------------------------

namespace permutations_details
{
constexpr size_t pow(size_t n1, size_t n2)
{
    size_t nResult = 1;
    for (size_t i = 0; i < n2; ++i)
        nResult *= n1;

    return nResult;
}

template<class... tuples_t>
struct merge_tuples;

template<class... args_t>
struct merge_tuples<std::tuple<args_t...>>
{
    using type = std::tuple<args_t...>;
};

template<class... args_1_t, class... args_2_t, class... args_rest_t>
struct merge_tuples<std::tuple<args_1_t...>, std::tuple<args_2_t...>, args_rest_t...>
{
    using type = typename merge_tuples<std::tuple<args_1_t..., args_2_t...>, args_rest_t...>::type;
};

template<class inner_tuples_tuple_t, class... all_types_t>
struct generate_layer;

template<class... inner_tuples_t, class... all_types_t>
struct generate_layer<std::tuple<inner_tuples_t...>, all_types_t...>
{
private:
    template<class inner_tuple_t>
    struct generator
    {
        using type = std::tuple<typename join<inner_tuple_t, all_types_t>::type...>;
    };

public:
    using type = typename merge_tuples<typename generator<inner_tuples_t>::type...>::type;
};

template<class all_tuples_t, class prev_new_tuples_t, size_t nCombinations, class... all_types_t>
struct combine;

template<bool bBreak /* = true */, class all_tuples_t, class new_tuples_t, size_t nCombinations, class... all_types_t>
struct break_or_combine
{
    using type = all_tuples_t;
};

template<class all_tuples_t, class new_tuples_t, size_t nCombinations, class... all_types_t>
struct break_or_combine</* bool bBreak = */ false, all_tuples_t, new_tuples_t, nCombinations, all_types_t...>
{
    using type =
        typename combine<join_t<all_tuples_t, new_tuples_t>, new_tuples_t, nCombinations, all_types_t...>::type;
};

template<class all_tuples_t, class prev_new_tuples_t, size_t nCombinations, class... all_types_t>
struct combine
{
private:
    using new_tuples_t = typename generate_layer<prev_new_tuples_t, all_types_t...>::type;

public:
    using type = typename break_or_combine<
        nCombinations == std::tuple_size_v<all_tuples_t>,
        all_tuples_t,
        new_tuples_t,
        nCombinations,
        all_types_t...>::type;
};

} // namespace permutations_details

/**
    @struct permutations
    @brief  Generates k-permutations with repetition for all_types_t
    @tparam all_types_t - types for permutations

    @code
    using t = qx::tuple::permutations_t<A, B>;
    static_assert(std::is_same_v<
        t,
        std::tuple<std::tuple<A>, std::tuple<B>, std::tuple<A, A>, std::tuple<A, B>, std::tuple<B, A>, std::tuple<B, B>>>);
    @endcode 
**/
template<class... all_types_t>
struct permutations
{
    static constexpr size_t nTypes        = sizeof...(all_types_t);
    static constexpr size_t nCombinations = nTypes * (permutations_details::pow(nTypes, nTypes) - 1) / (nTypes - 1);
    using start_tuples_t                  = std::tuple<std::tuple<all_types_t>...>;
    using type =
        typename permutations_details::combine<start_tuples_t, start_tuples_t, nCombinations, all_types_t...>::type;
};

template<class... all_types_t>
using permutations_t = typename permutations<all_types_t...>::type;




// ------------------------------------------------- cartesian product -------------------------------------------------

namespace cartesian_product_details
{

template<class prefix_t, class tuple_t>
struct prepend_to_all;

template<class prefix_t, class... rest_types_t>
struct prepend_to_all<prefix_t, std::tuple<rest_types_t...>>
{
    using type = std::tuple<typename join<std::tuple<prefix_t>, rest_types_t>::type...>;
};

template<class... tuples_t>
struct flatten;

template<>
struct flatten<>
{
    using type = std::tuple<>;
};

template<class... first_tuple_args_t>
struct flatten<std::tuple<first_tuple_args_t...>>
{
    using type = std::tuple<first_tuple_args_t...>;
};

template<class... first_tuple_args_t, class... second_tuple_args_t, class... rest_tuples_t>
struct flatten<std::tuple<first_tuple_args_t...>, std::tuple<second_tuple_args_t...>, rest_tuples_t...>
{
    using type = typename flatten<std::tuple<first_tuple_args_t..., second_tuple_args_t...>, rest_tuples_t...>::type;
};

} // namespace cartesian_product_details

template<class... input_tuples_t>
struct cartesian_product;

template<>
struct cartesian_product<>
{
    using type = std::tuple<std::tuple<>>;
};

template<class first_input_tuple_t, class... rest_input_tuples_t>
struct cartesian_product<first_input_tuple_t, rest_input_tuples_t...>
{
private:
    using tail_product_type = typename cartesian_product<rest_input_tuples_t...>::type;

    template<class element_t>
    struct expand
    {
        using type = typename cartesian_product_details::prepend_to_all<element_t, tail_product_type>::type;
    };

    template<class... elements_t>
    struct expand_all;

    template<class... elements_t>
    struct expand_all<std::tuple<elements_t...>>
    {
        using type = typename cartesian_product_details::flatten<typename expand<elements_t>::type...>::type;
    };

public:
    using type = typename expand_all<first_input_tuple_t>::type;
};

template<class... tuples_args_t>
using cartesian_product_t = typename cartesian_product<tuples_args_t...>::type;




// ------------------------------------------------------- all of ------------------------------------------------------

template<template<class> class predicate_t, class... args_t>
concept all_of_c = (predicate_t<args_t>::value && ...);

template<template<class> class predicate_t, class tuple_t>
struct all_of;

template<template<class> class predicate_t, class... args_t>
struct all_of<predicate_t, std::tuple<args_t...>>
{
    static constexpr bool value = all_of_c<predicate_t, args_t...>;
};

template<template<class> class predicate_t, class... args_t>
constexpr bool all_of_v = all_of<predicate_t, args_t...>::value;

} // namespace qx::tuple_utils
