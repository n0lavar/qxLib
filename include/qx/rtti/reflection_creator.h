/**

    @file      reflection_creator.h
    @brief     
    @details   
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/reflection/class_identificator.h>
#include <qx/useful_macros.h>

#include <functional>
#include <map>
#include <memory>
#include <string_view>

namespace qx
{

template<class BaseClass, class... Args>
using reflection_class_factory =
    std::function<std::unique_ptr<BaseClass>(Args...)>;

/**

    @class   reflection_creator
    @brief   
    @details Performs registration of classes inherited from BaseClass
             and creates their instances by their ID and name.
             Allocates memory.
    @tparam  BaseClass - base class type
    @tparam  Args      - args for type creation
    @author  Khrapov
    @date    7.09.2021

**/
template<class BaseClass, class... Args>
class reflection_creator
{
public:
    using factory = reflection_class_factory<BaseClass, Args...>;

public:
    [[nodiscard]] static std::unique_ptr<BaseClass> create_object(
        class_identificator id,
        Args&&... args)
    {
        if (auto it = m_FactoriesById.find(id); it != m_FactoriesById.end())
            return it->second(std::forward<Args>(args)...);

        return nullptr;
    }

    [[nodiscard]] static std::unique_ptr<BaseClass> create_object(
        std::string_view svClassName,
        Args&&... args)
    {
        if (auto it = m_FactoriesByName.find(svClassName);
            it != m_FactoriesByName.end())
        {
            return it->second(std::forward<Args>(args)...);
        }

        return nullptr;
    }

    static bool register_class(
        factory             factory,
        class_identificator id,
        std::string_view    svClassName)
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

template<class BaseClass, class ThisClass, class... Args>
static std::unique_ptr<BaseClass> _create_object(Args&&... args)
{
    if constexpr (std::is_constructible_v<ThisClass, Args...>)
        return std::make_unique<ThisClass>(std::forward<Args>(args)...);
    else
        return nullptr;
}

#define QX_REGISTER_CREATOR(...)                                   \
private:                                                           \
    static inline bool QX_LINE_NAME(s_bRegistered) =               \
        qx::reflection_creator<ThisClass>::register_class(         \
            qx::_create_object<BaseClass, ThisClass, __VA_ARGS__>, \
            get_class_id_static(),                                 \
            get_class_name_static());


} // namespace qx
