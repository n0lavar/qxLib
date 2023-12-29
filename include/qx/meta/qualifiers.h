/**

    @file      qualifiers.h
    @author    Khrapov
    @date      20.08.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

namespace qx
{

// clang-format off

/**
    @struct  copy_qualifiers
    @details Convert target_t to the type with test_t qualifiers
    @tparam  test_t   - type to test, may be "const", "volatile"
    @tparam  target_t - type to apply qualifiers to
**/
template <class test_t, class target_t> struct copy_qualifiers;

template <class test_t, class target_t> struct copy_qualifiers                                   { using type =                target_t; };
template <class test_t, class target_t> struct copy_qualifiers<const          test_t,  target_t> { using type = const          target_t; };
template <class test_t, class target_t> struct copy_qualifiers<      volatile test_t,  target_t> { using type =       volatile target_t; };
template <class test_t, class target_t> struct copy_qualifiers<const volatile test_t,  target_t> { using type = const volatile target_t; };
// clang-format on

template<class test_t, class target_t>
using copy_qualifiers_t = typename copy_qualifiers<test_t, target_t>::type;



// clang-format off


/**
    @struct  switch_qualifiers
    @details Switch (add or remove) const and volatile 
    @tparam  T - type to switch
**/
template <class T> struct switch_qualifiers;

template <class T> struct switch_qualifiers                   { using type = const volatile T; };
template <class T> struct switch_qualifiers<const          T> { using type =       volatile T; };
template <class T> struct switch_qualifiers<      volatile T> { using type = const          T; };
template <class T> struct switch_qualifiers<const volatile T> { using type =                T; };
// clang-format on

template<class T>
using switch_qualifiers_t = typename switch_qualifiers<T>::type;



// clang-format off

/**
    @struct  switch_const
    @details Switch (add or remove) const 
    @tparam  T - type to switch
**/
template<class T> struct switch_const;

template <class T> struct switch_const          { using type = const T; };
template <class T> struct switch_const<const T> { using type =       T; };
// clang-format on

template<class T>
using switch_const_t = typename switch_const<T>::type;



// clang-format off

/**
    @struct  switch_volatile
    @details Switch (add or remove) volatile 
    @tparam  T - type to switch
**/
template<class T> struct switch_volatile;

template <class T> struct switch_volatile             { using type = volatile T; };
template <class T> struct switch_volatile<volatile T> { using type =          T; };
// clang-format on

template<class T>
using switch_volatile_t = typename switch_volatile<T>::type;

} // namespace qx
