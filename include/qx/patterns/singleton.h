/**

    @file      singleton.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @struct  singleton_traits
    @tparam  T - singleton class
**/
template<class T>
struct singleton_traits
{
    /**
        @brief Called when singleton constructed
        @param instance - singleton instance
    **/
    static void on_constructed(T& instance)
    {
    }

    /**
        @brief Called when singleton proceeds getter
        @param instance - singleton instance
    **/
    static void on_getter(T& instance)
    {
    }

    /**
        @brief Called before singleton destructed
        @param instance - singleton instance
    **/
    static void on_destructed(T& instance)
    {
    }
};

} // namespace qx

/**
    @def     QX_SINGLETON_S
    @brief   Simple Meyer's singleton
    @details Implement singleton_traits for your type to change creation,
             getting and destruction behaviour
    @param   T          - your class type
    @param   specifiers - type specifiers, such as "static" or "thread_safe"
**/
#define QX_SINGLETON_S(T, specifiers)                   \
private:                                                \
    friend struct qx::singleton_traits<T>;              \
                                                        \
    T()                                                 \
    {                                                   \
        qx::singleton_traits<T>::on_constructed(*this); \
    }                                                   \
    ~T()                                                \
    {                                                   \
        qx::singleton_traits<T>::on_destructed(*this);  \
    }                                                   \
    T(const T&)                  = delete;              \
    T(T&&)                       = delete;              \
    const T& operator=(const T&) = delete;              \
    const T& operator=(T&&)      = delete;              \
                                                        \
public:                                                 \
    static T& get_instance()                            \
    {                                                   \
        specifiers T instance;                          \
        qx::singleton_traits<T>::on_getter(instance);   \
        return instance;                                \
    }                                                   \
                                                        \
private:

/**
    @def     QX_SINGLETON
    @details Implement singleton_traits for your type to change creation,
             getting and destruction behaviour
    @brief   Simple Meyer's singleton
    @param   T - your class type
**/
#define QX_SINGLETON(T) QX_SINGLETON_S(T, static)
