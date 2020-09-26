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
//!\macro                 _QX_SINGLETON_IMPL
//
//!\brief       Simple Meyer's singleton
//!\details     use QX_SINGLETON(yourClass) in the beginning of your class
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#define _QX_SINGLETON_IMPL(T, constructor, destructor, process_getter)  \
private:                                                                \
                                                                        \
          T             (void)      constructor;                        \
         ~T             (void)      destructor;                         \
          T             (const T&)  = delete;                           \
          T             (T&&)       = delete;                           \
    const T& operator=  (const T&)  = delete;                           \
    const T& operator=  (T&&)       = delete;                           \
                                                                        \
public:                                                                 \
                                                                        \
    static T& get_instance()                                            \
    {                                                                   \
        static T instance;                                              \
        process_getter                                                  \
        return instance;                                                \
    }                                                                   \
                                                                        \
private:

#define QX_SINGLETON(T)                                              _QX_SINGLETON_IMPL(T, =default,      =default,     )
#define QX_SINGLETON_P(T, process_getter)                            _QX_SINGLETON_IMPL(T, =default,      =default,     process_getter)
#define QX_SINGLETON_C(T, constructor)                               _QX_SINGLETON_IMPL(T, {constructor}, =default,     )
#define QX_SINGLETON_CP(T, constructor, process_getter)              _QX_SINGLETON_IMPL(T, {constructor}, =default,     process_getter)
#define QX_SINGLETON_D(T, destructor)                                _QX_SINGLETON_IMPL(T, =default,      {destructor}, )
#define QX_SINGLETON_DP(T, destructor, process_getter)               _QX_SINGLETON_IMPL(T, =default,      {destructor}, process_getter)
#define QX_SINGLETON_CD(T, constructor, destructor)                  _QX_SINGLETON_IMPL(T, {constructor}, {destructor}, )
#define QX_SINGLETON_CDP(T, constructor, destructor, process_getter) _QX_SINGLETON_IMPL(T, {constructor}, {destructor}, process_getter)
