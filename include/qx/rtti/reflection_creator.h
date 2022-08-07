/**

    @file      reflection_creator.h
    @brief     Contains reflection creator functionality
    @details   The creator allows you to create instances
               of the class using its name or ID
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>
#include <qx/rtti/class_identificator.h>

#include <functional>
#include <map>
#include <memory>
#include <string_view>

namespace qx
{

/**

    @class   reflection_creator
    @brief   Reflection creator
    @details Performs registration of classes inherited from BaseClass
             and creates their instances by their ID and name.
             Allocates memory.
    @tparam  BaseClass - base class type
    @tparam  SmartPtr  - smart pointer class type
    @tparam  Args      - args for type creation
    @author  Khrapov
    @date    7.09.2021

**/
template<class BaseClass, template<class> class SmartPtr, class... Args>
class reflection_creator
{
public:
    using factory = std::function<SmartPtr<BaseClass>(Args...)>;

public:
    /**
        @brief  Create object based on class id
        @param  id   - class id
        @param  args - template parameter pack
        @retval      - class instance or nullptr if can't find factory or can't create
    **/
    [[nodiscard]] static SmartPtr<BaseClass> create_object(class_identificator id, Args&&... args)
    {
        if (auto it = m_FactoriesById.find(id); it != m_FactoriesById.end())
            return it->second(std::forward<Args>(args)...);

        return nullptr;
    }

    /**
        @brief  Create object based on class name
        @param  svClassName - class name
        @param  args        - template parameter pack
        @retval             - class instance or nullptr if can't find factory or can't create
    **/
    [[nodiscard]] static SmartPtr<BaseClass> create_object(std::string_view svClassName, Args&&... args)
    {
        if (auto it = m_FactoriesByName.find(svClassName); it != m_FactoriesByName.end())
        {
            return it->second(std::forward<Args>(args)...);
        }

        return nullptr;
    }

    /**
        @brief  Register class so it can be constructed by creator
        @param  factory     - class factory
        @param  id          - class id
        @param  svClassName - class name
        @retval             - true if registered
    **/
    static bool _register_class(factory factory, class_identificator id, std::string_view svClassName)
    {
        if (factory && !svClassName.empty())
        {
            m_FactoriesById[id]            = factory;
            m_FactoriesByName[svClassName] = factory;
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    static inline std::map<class_identificator, factory> m_FactoriesById;
    static inline std::map<std::string_view, factory>    m_FactoriesByName;
};

namespace detail
{

template<class BaseClass, class T, class... Args>
static std::unique_ptr<BaseClass> create_unique(Args&&... args)
{
    if constexpr (std::is_constructible_v<T, Args...>)
        return std::make_unique<T>(std::forward<Args>(args)...);
    else
        return nullptr;
}

template<class BaseClass, class T, class... Args>
static std::shared_ptr<BaseClass> create_shared(Args&&... args)
{
    if constexpr (std::is_constructible_v<T, Args...>)
        return std::make_shared<T>(std::forward<Args>(args)...);
    else
        return nullptr;
}

} // namespace detail

/**
    @def     QX_REGISTER_UNIQUE_CREATOR
    @brief   Macro for base class. Use YourClass::Creator::create_object
    @details std::unique_ptr version
    @param   ... - constructor args types
**/
#define QX_REGISTER_UNIQUE_CREATOR(...) \
    using CreatorRoot = ThisClass;      \
    using Creator     = qx::reflection_creator<CreatorRoot, std::unique_ptr, __VA_ARGS__>;

/**
    @def     QX_REGISTER_UNIQUE_CONSTRUCTOR
    @brief   Macro for all classes inherited from base class
    @details std::unique_ptr version
    @param   ... - constructor args types
**/
#define QX_REGISTER_UNIQUE_CONSTRUCTOR(...)                                             \
private:                                                                                \
    static inline volatile bool QX_LINE_NAME(s_bRegistered) = Creator::_register_class( \
        qx::detail::create_unique<CreatorRoot, ThisClass, __VA_ARGS__>,                 \
        get_class_id_static(),                                                          \
        get_class_name_static());

/**
    @def     QX_REGISTER_SHARED_CREATOR
    @brief   Macro for base class. Use YourClass::Creator::create_object
    @details std::shared_ptr version
    @param   ... - constructor args types
**/
#define QX_REGISTER_SHARED_CREATOR(...) \
    using CreatorRoot = ThisClass;      \
    using Creator     = qx::reflection_creator<CreatorRoot, std::shared_ptr, __VA_ARGS__>;

/**
    @def     QX_REGISTER_SHARED_CONSTRUCTOR
    @brief   Macro for all classes inherited from base class
    @details std::shared_ptr version
    @param   ... - constructor args types
**/
#define QX_REGISTER_SHARED_CONSTRUCTOR(...)                                             \
private:                                                                                \
    static inline volatile bool QX_LINE_NAME(s_bRegistered) = Creator::_register_class( \
        qx::detail::create_shared<CreatorRoot, ThisClass, __VA_ARGS__>,                 \
        get_class_id_static(),                                                          \
        get_class_name_static());

#define QX_REGISTER_CREATOR     QX_REGISTER_UNIQUE_CREATOR
#define QX_REGISTER_CONSTRUCTOR QX_REGISTER_UNIQUE_CONSTRUCTOR

} // namespace qx
