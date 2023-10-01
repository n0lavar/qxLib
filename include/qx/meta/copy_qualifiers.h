/**

    @file      copy_qualifiers.h
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

} // namespace qx
