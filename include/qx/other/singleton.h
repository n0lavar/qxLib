//==============================================================================
//
//!\file                         singleton.h
//
//!\brief       Singleton implementation
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

//==============================================================================
//
//!\macro                   _SINGLETON_IMPL
//
//!\brief       Simple Meyer's singletone
//!\details     use SINGLETON(yourClass) in the beginning of your class
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#define _SINGLETON_IMPL(T, constructor, destructor)         \
private:                                                    \
          T             (void)      constructor;            \
         ~T             (void)      destructor;             \
          T             (const T&)  = delete;               \
          T             (T&&)       = delete;               \
    const T& operator=  (const T&)  = delete;               \
    const T& operator=  (T&&)       = delete;               \
                                                            \
public:                                                     \
    static T& getInstance()                                 \
    {                                                       \
        static T instance;                                  \
        return instance;                                    \
    }                                                       \
                                                            \
private:

#define SINGLETON(T)                                _SINGLETON_IMPL(T, =default,      =default)
#define SINGLETON_C(T, constructor)                 _SINGLETON_IMPL(T, {constructor}, =default)
#define SINGLETON_D(T, destructor)                  _SINGLETON_IMPL(T, =default,      {destructor})
#define SINGLETON_CD(T, constructor, destructor)    _SINGLETON_IMPL(T, {constructor}, {destructor})
