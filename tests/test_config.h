/**

    @file      test_config.h
    @brief     Tests configuring
    @author    Khrapov
    @date      8.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/suppress_warnings.h>

QX_PUSH_SUPPRESS_ALL_WARNINGS
#include <gtest/gtest.h>
QX_POP_SUPPRESS_WARNINGS

#define GTEST_SINGLE_ARGUMENT(...) (__VA_ARGS__)

// clang-format off

#ifndef QX_TEST_SORT
    #define QX_TEST_SORT 1
#endif

#ifndef QX_TEST_NUMERICAL
    #define QX_TEST_NUMERICAL 1
#endif

#ifndef QX_TEST_FUNCTIONAL
    #define QX_TEST_FUNCTIONAL 1
#endif

#ifndef QX_TEST_LIST_SE
    #define QX_TEST_LIST_SE 1
#endif

#ifndef QX_TEST_STRING
    #define QX_TEST_STRING 1
#endif

#ifndef QX_TEST_VECTOR2D
    #define QX_TEST_VECTOR2D 1
#endif

#ifndef QX_TEST_TRIANGULAR_VECTOR
    #define QX_TEST_TRIANGULAR_VECTOR 1
#endif

#ifndef QX_TEST_SMART_ENUM
    #define QX_TEST_SMART_ENUM 1
#endif

#ifndef QX_TEST_RTTI
    #define QX_TEST_RTTI 1
#endif

#ifndef QX_TEST_CONSTEXPR_SEQUENCE
    #define QX_TEST_CONSTEXPR_SEQUENCE 1
#endif

#ifndef QX_TEST_CONSTEXPR_RANDOM
    #define QX_TEST_CONSTEXPR_RANDOM 1
#endif

#ifndef QX_TEST_CONSTEXPR_FUNCS
    #define QX_TEST_CONSTEXPR_FUNCS 1
#endif

#ifndef QX_TEST_CONSTEXPR_FLAG
    #define QX_TEST_CONSTEXPR_FLAG 1
#endif

#ifndef QX_TEST_USEFUL_FUNCS
    #define QX_TEST_USEFUL_FUNCS 1
#endif

#ifndef QX_TEST_USEFUL_MACROS
    #define QX_TEST_USEFUL_MACROS 1
#endif

#ifndef QX_TEST_SINGLETON
    #define QX_TEST_SINGLETON 1
#endif

#ifndef QX_TEST_TYPEDEFS
    #define QX_TEST_TYPEDEFS 1
#endif

#ifndef QX_TEST_TYPE_TRAITS
    #define QX_TEST_TYPE_TRAITS 1
#endif

#ifndef QX_TEST_MATH
    #define QX_TEST_MATH 1
#endif

#ifndef QX_TEST_BENCHMARK
    #define QX_TEST_BENCHMARK 1
#endif

#ifndef QX_TEST_LOGGER
    #define QX_TEST_LOGGER 1
#endif

#ifndef QX_TEST_THREAD_WORKER
    #define QX_TEST_THREAD_WORKER 1
#endif

#ifndef QX_TEST_ASSERT
    #define QX_TEST_ASSERT 1
#endif

#ifndef QX_TEST_THREADS_SHARED
    #define QX_TEST_THREADS_SHARED 1
#endif

#ifndef QX_TEST_OBSERVER
    #define QX_TEST_OBSERVER 1
#endif

#ifndef QX_TEST_COMPONENTS
    #define QX_TEST_COMPONENTS 1
#endif

#ifndef QX_TEST_STATE
    #define QX_TEST_STATE 1
#endif

#ifndef QX_TEST_EASING_FUNCTIONS
    #define QX_TEST_EASING_FUNCTIONS 1
#endif

#ifndef QX_TEST_EASING_ELEMENT
    #define QX_TEST_EASING_ELEMENT 1
#endif
 
#ifndef QX_TEST_EASING_SEQUENCE
    #define QX_TEST_EASING_SEQUENCE 1
#endif

#ifndef QX_TEST_MOVING_AVERAGE
    #define QX_TEST_MOVING_AVERAGE 1
#endif

#ifndef QX_TEST_STRING_UTILS
    #define QX_TEST_STRING_UTILS 1
#endif

#ifndef QX_TEST_STRING_LITERAL
    #define QX_TEST_STRING_LITERAL 1
#endif

// clang-format on
