/**

    @file      rtti_creator_strategy.h
    @brief     Contains creator strategies for qx::rtti_root class
    @details   The creator strategy creates instances of classes derived from
               qx::rtti_root
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string_view>

namespace qx
{

using class_identificator = int;

template<class BaseClass, class... Args>
using rtti_class_factory = std::function<std::unique_ptr<BaseClass>(Args...)>;

/**

    @class   rtti_stub_creator
    @brief   Default creator for classes derived from qx::rtti_root
    @details Does not register classes,
             does not allocate memory,
             and returns nullptr in factory methods
    @tparam  BaseClass - base class type
    @tparam  Args      - args for type creation
    @author  Khrapov
    @date    7.09.2021

**/
template<class BaseClass, class... Args>
class rtti_stub_creator
{
public:
    using factory = rtti_class_factory<BaseClass, Args...>;

public:
    [[nodiscard]] static std::unique_ptr<BaseClass> create_object(
        class_identificator,
        Args&&...)
    {
        return nullptr;
    }

    [[nodiscard]] static std::unique_ptr<BaseClass> create_object(
        std::string_view,
        Args&&...)
    {
        return nullptr;
    }

    static bool register_class(factory, class_identificator, std::string_view)
    {
        return false;
    }
};

/**

    @class   rtti_creator
    @brief   Creator for classes derived from qx::rtti_root
    @details Performs registration of classes inherited from BaseClass
             and creates their instances by their ID and name.
             Allocates memory.
    @tparam  BaseClass - base class type
    @tparam  Args      - args for type creation
    @author  Khrapov
    @date    7.09.2021

**/
template<class BaseClass, class... Args>
class rtti_creator
{
public:
    using factory = rtti_class_factory<BaseClass, Args...>;

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
        m_FactoriesById[id]            = factory;
        m_FactoriesByName[svClassName] = factory;
        return true;
    }

private:
    static inline std::map<class_identificator, factory> m_FactoriesById;
    static inline std::map<std::string_view, factory>    m_FactoriesByName;
};

} // namespace qx
