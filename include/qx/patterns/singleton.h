/**

    @file      singleton.h
    @brief     Singleton implementation
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

/**
    @def   _QX_SINGLETON_IMPL
    @brief Simple Meyer's singleton
    @param T              - your class type
    @param constructor    - constructor realization
    @param destructor     - destructor realization
    @param process_getter - getter processing realization
**/
#define _QX_SINGLETON_IMPL(T, constructor, destructor, process_getter) \
private:                                                               \
    T() constructor;                                                   \
    ~T() destructor;                                                   \
    T(const T&)                  = delete;                             \
    T(T&&)                       = delete;                             \
    const T& operator=(const T&) = delete;                             \
    const T& operator=(T&&)      = delete;                             \
                                                                       \
public:                                                                \
    static T& get_instance()                                           \
    {                                                                  \
        static T instance;                                             \
        process_getter return instance;                                \
    }                                                                  \
                                                                       \
private:

/**
    @def   QX_SINGLETON
    @brief Simple Meyer's singleton
    @param T - your class type
**/
#define QX_SINGLETON(T) _QX_SINGLETON_IMPL(T, = default, = default, )

/**
    @def   QX_SINGLETON_P
    @brief Simple Meyer's singleton
    @param T              - your class type
    @param process_getter - getter processing realization
**/
#define QX_SINGLETON_P(T, process_getter) _QX_SINGLETON_IMPL(T, = default, = default, process_getter)

/**
    @def   QX_SINGLETON_C
    @brief Simple Meyer's singleton
    @param T           - your class type
    @param constructor - constructor realization
**/
#define QX_SINGLETON_C(T, constructor) _QX_SINGLETON_IMPL(T, { constructor }, = default, )

/**
    @def   QX_SINGLETON_CP
    @brief Simple Meyer's singleton
    @param T              - your class type
    @param constructor    - constructor realization
    @param process_getter - getter processing realization
**/
#define QX_SINGLETON_CP(T, constructor, process_getter) \
    _QX_SINGLETON_IMPL(T, { constructor }, = default, process_getter)

/**
    @def   QX_SINGLETON_D
    @brief Simple Meyer's singleton
    @param T          - your class type
    @param destructor - destructor realization
**/
#define QX_SINGLETON_D(T, destructor) _QX_SINGLETON_IMPL(T, = default, { destructor }, )

/**
    @def   QX_SINGLETON_DP
    @brief Simple Meyer's singleton
    @param T              - your class type
    @param destructor     - destructor realization
    @param process_getter - getter processing realization
**/
#define QX_SINGLETON_DP(T, destructor, process_getter) _QX_SINGLETON_IMPL(T, = default, { destructor }, process_getter)

/**
    @def   QX_SINGLETON_CD
    @brief Simple Meyer's singleton
    @param T           - your class type
    @param constructor - constructor realization
    @param destructor  - destructor realization
**/
#define QX_SINGLETON_CD(T, constructor, destructor) _QX_SINGLETON_IMPL(T, { constructor }, { destructor }, )

/**
    @def   QX_SINGLETON_CDP
    @brief Simple Meyer's singleton
    @param T              - your class type
    @param constructor    - constructor realization
    @param destructor     - destructor realization
    @param process_getter - getter processing realization
**/
#define QX_SINGLETON_CDP(T, constructor, destructor, process_getter) \
    _QX_SINGLETON_IMPL(T, { constructor }, { destructor }, process_getter)
