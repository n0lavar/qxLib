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

template<class...>
struct join
{
};

template<class... first_pack_t, class... second_pack_t>
struct join<std::tuple<first_pack_t...>, std::tuple<second_pack_t...>>
{
    using type = std::tuple<first_pack_t..., second_pack_t...>;
};

template<class... args_t>
using join_t = typename join<args_t...>::type;

// ------------------------------------------------------- remove ------------------------------------------------------

namespace detail
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

} // namespace detail

template<class... pack_t>
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
    using type = typename detail::remove_single<
        target_t,
        typename remove<std::tuple<types_t...>, std::tuple<remaining_targets_t...>>::type>::type;
};

template<class... args_t>
using remove_t = typename remove<args_t...>::type;

// ------------------------------------------------------ contains -----------------------------------------------------

namespace detail
{

template<class T, class tuple_t>
struct contains;

template<class T>
struct contains<T, std::tuple<>> : std::false_type
{
};

template<class T, class U, class... Ts>
struct contains<T, std::tuple<U, Ts...>> : contains<T, std::tuple<Ts...>>
{
};

template<class T, class... Ts>
struct contains<T, std::tuple<T, Ts...>> : std::true_type
{
};

} // namespace detail

template<class tuple_t, class T>
using contains = detail::contains<T, tuple_t>;

template<class tuple_t, class T>
static constexpr bool contains_v = contains<tuple_t, T>::value;

} // namespace qx::tuple
