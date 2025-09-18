/**

    @file      singleton.h
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

namespace qx
{

/**

    @class   base_singleton
    @brief   Base singleton class
    @author  Khrapov
    @date    18.09.2025

**/
class base_singleton
{
    template<class T, class... dependencies_t>
        requires(std::is_base_of_v<base_singleton, dependencies_t> && ...)
    friend class singleton;

public:
    virtual ~base_singleton() = default;

private:
    base_singleton() = default;
};

/**

    @class   singletons_manager
    @brief   The class provides a solution to the fiasco static deinitialization for qx::singleton
             by storing all singletons in one place and removing them in the reverse order of addition.
    @author  Khrapov
    @date    18.09.2025

**/
class singletons_manager
{
    template<class T, class... dependencies_t>
        requires(std::is_base_of_v<base_singleton, dependencies_t> && ...)
    friend class singleton;

public:
    singletons_manager(const singletons_manager&)                  = delete;
    singletons_manager(singletons_manager&&)                       = delete;
    const singletons_manager& operator=(const singletons_manager&) = delete;
    const singletons_manager& operator=(singletons_manager&&)      = delete;

private:
    singletons_manager() noexcept = default;
    ~singletons_manager() noexcept;

    /**
        @brief  Returns singletons manager instance
        @retval  - singletons manager instance
    **/
    static singletons_manager& get_instance() noexcept;

    /**
        @brief Add a new singleton
        @note  Thread safe
        @param pSingleton - new singleton
    **/
    void add(std::unique_ptr<base_singleton> pSingleton) noexcept;

private:
    std::mutex                                   m_SingletonsMutex;
    std::vector<std::unique_ptr<base_singleton>> m_Singletons;
};

/**

    @class   singleton
    @brief   Inherit the necessary singleton class from this 
    @details You can override init() and a destructor
    @tparam  T              - singleton type
    @tparam  dependencies_t - singleton dependencies, they will be initialized before this one,
                              unless they have already been initialized
    @author  Khrapov
    @date    18.09.2025

**/
template<class T, class... dependencies_t>
    requires(std::is_base_of_v<base_singleton, dependencies_t> && ...)
class singleton : public base_singleton
{
    friend T;

public:
    /**
        @brief  Get singleton instance
        @retval  - singleton instance
    **/
    static T& get_instance();

    /**
        @brief Init the singleton (called on the first get_instance())
    **/
    virtual void init();

    singleton(const singleton&)            = delete;
    singleton(singleton&&)                 = delete;
    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

private:
    singleton() noexcept = default;
};

} // namespace qx

#include <qx/patterns/singleton.inl>
