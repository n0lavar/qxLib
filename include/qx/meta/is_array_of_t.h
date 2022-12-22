/**

    @file      is_array_of_t.h
    @brief     Contains qx::is_array_of_t trait
    @details   ~
    @author    Khrapov
    @date      20.12.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <cstddef>
#include <type_traits>

namespace qx
{

// clang-format off

/**
    @struct  is_array_of_t
    @detaild Check if TArray is an array of TElement
    @tparam  TArray   - possible array type
    @tparam  TElement - array element type
**/
template <class TArray, class TElement> struct is_array_of_t                 : std::false_type { };
                                   
template <class T>           struct is_array_of_t<               T[],     T> : std::true_type  { };
template <class T>           struct is_array_of_t<const          T[],     T> : std::true_type  { };
template <class T>           struct is_array_of_t<      volatile T[],     T> : std::true_type  { };
template <class T>           struct is_array_of_t<const volatile T[],     T> : std::true_type  { };
                                                                                               
template <class T, size_t N> struct is_array_of_t<               T[N],    T> : std::true_type  { };
template <class T, size_t N> struct is_array_of_t<const          T[N],    T> : std::true_type  { };
template <class T, size_t N> struct is_array_of_t<      volatile T[N],    T> : std::true_type  { };
template <class T, size_t N> struct is_array_of_t<const volatile T[N],    T> : std::true_type  { };
                                                                                               
template <class T, size_t N> struct is_array_of_t<               T(&)[N], T> : std::true_type  { };
template <class T, size_t N> struct is_array_of_t<const          T(&)[N], T> : std::true_type  { };
template <class T, size_t N> struct is_array_of_t<      volatile T(&)[N], T> : std::true_type  { };
template <class T, size_t N> struct is_array_of_t<const volatile T(&)[N], T> : std::true_type  { };

// clang-format on

template<class TArray, class TElement>
constexpr bool is_array_of_t_v = is_array_of_t<TArray, TElement>::value;

} // namespace qx
