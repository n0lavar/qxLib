//==============================================================================
//
//!\file                         type_traits.h
//
//!\brief       Type traits
//!\details     ~
//
//!\author      Khrapov
//!\date        10.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/temp/type_traits.h>

namespace qx
{

//-------------------------------- is_iterator -------------------------------

template<class T>
using iterator_category = typename T::iterator_category;

template<typename T, typename = void>
struct is_iterator
{
    static constexpr bool value = false;
};

// check if T is iterator (all iterators must contain iterator_category def
// important! some iterators are implemented as value_type* (see libstdc++ and std::array)
// in this case check will fail
template<typename T>
struct is_iterator<T, typename std::enable_if_t<is_detected<iterator_category, T>::value>>
{
    static constexpr bool value = true;
};

template< class T >
constexpr bool is_iterator_v = is_iterator<T>::value;



//--------------------------------- are_same ---------------------------------

template <typename ...>
struct are_same : std::true_type
{
};

template <typename S, typename T, typename ... Ts>
struct are_same <S, T, Ts...> : std::false_type
{
};

// check if all of variadic arguments are same type
template <typename T, typename ... Ts>
struct are_same <T, T, Ts...> : are_same<T, Ts...>
{
};

template <typename ... Ts>
inline constexpr bool are_same_v = are_same<Ts...>::value;



//------------------------------- iterator_value -------------------------------

// get value type of iterator
template<typename T, class = void>
struct iterator_value
{
};

// default implementation with ::value_type
template<class T>
struct iterator_value<T, typename std::enable_if_t<is_iterator_v<T>>>
{
    using type = typename T::value_type;
};

// some iterators may be implemented as pointers
template<class T>
struct iterator_value<T, typename std::enable_if_t<std::is_pointer_v<T>>>
{
    using type = std::remove_pointer_t<T>;
};

template<class T>
using iterator_value_t = typename iterator_value<T>::type;

}