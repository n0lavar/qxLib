/**

    @file      components.h
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>
#include <qx/priority.h>
#include <qx/rtti/rtti.h>

#include <map>
#include <optional>
#include <ranges>
#include <unordered_map>

namespace qx
{

/**

    @class   components
    @brief   Container for components system
    @details Stores components and allows them to be accessed by a template argument or a class id.
             Each component has a priority, which is used to iterate through a sequence of objects of a type (final or any super type)
             or to use getter methods, where a component with the highest priority will be given.
             You can use qx::priority::disabled to exclude the component from iteration or getters result.
    @tparam  base_component_t - base component type
    @author  Khrapov
    @date    9.03.2021

**/
template<std::derived_from<rtti_pure_base> base_component_t>
class components
{
public:
    using pointer_type = std::unique_ptr<base_component_t>;

private:
    struct SClassData
    {
        struct SCacheData
        {
            base_component_t* pComponent  = nullptr;
            flags<status>     statusFlags = status::default_value;
        };

        std::unordered_map<class_identificator, std::unique_ptr<SClassData>> derivedClasses;
        std::vector<pointer_type>                                            components;
        std::multimap<priority, SCacheData, std::greater<priority>>          priorityCache;

        [[nodiscard]] SClassData& get_or_add_class_data(class_identificator id) noexcept;
    };

    static constexpr auto stub_callback = [](auto&&...)
    {
    };

public:
    /**
        @brief  Add a component
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type 
        @param  pComponent  - component object
        @param  ePriority   - initial component priority
        @param  statusFlags - initial component status
        @retval             - raw component pointer which acts like a component's handle
    **/
    template<std::derived_from<base_component_t> component_t>
    [[maybe_unused]] component_t* add(
        std::unique_ptr<component_t> pComponent,
        priority                     ePriority   = priority::normal,
        flags<status>                statusFlags = status::default_value) noexcept;

    /**
        @brief  Remove the component from the container
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - component object
    **/
    [[maybe_unused]] std::unique_ptr<base_component_t> remove(const base_component_t* pRawComponent) noexcept;

    /**
        @brief  Try to get a component of the given type with the highest priority
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type
        @retval             - component pointer or nullptr
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] component_t* try_get() noexcept;

    /**
        @brief  Try to get a component of the given type with the highest priority
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type
        @retval             - component pointer or nullptr
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] const component_t* try_get() const noexcept;

    /**
        @brief  Try to get a component of the given type id with the highest priority
        @param  id - type id
        @retval    - component pointer or nullptr
    **/
    [[nodiscard]] base_component_t* try_get(class_identificator id) noexcept;

    /**
        @brief  Try to get a component of the given type id with the highest priority
        @param  id - type id
        @retval    - component pointer or nullptr
    **/
    [[nodiscard]] const base_component_t* try_get(class_identificator id) const noexcept;

    /**
        @brief  Get a component of the given type with the highest priority (no existence checks are performed)
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type
        @retval             - component reference
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] component_t& get() noexcept;

    /**
        @brief  Get a component of the given type with the highest priority (no existence checks are performed)
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type
        @retval             - component reference
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] const component_t& get() const noexcept;

    /**
        @brief  Get a view which may be used in a ranged-based for loop and consists of components of a given type with decreasing non-disabled priority
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type
        @retval             - view of components
    **/
    template<std::derived_from<base_component_t> component_t = base_component_t>
    [[nodiscard]] auto view() noexcept;

    /**
        @brief  Get a view which may be used in a ranged-based for loop and consists of components of a given type with decreasing non-disabled priority
        @tparam component_t - component type which doesn't have to be a final class type, may be any base or super type
        @retval             - view of components
    **/
    template<std::derived_from<base_component_t> component_t = base_component_t>
    [[nodiscard]] auto view() const noexcept;

    /**
        @brief  Get a priority of a given component
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - component's priority or nullopt if can't find the component
    **/
    [[nodiscard]] std::optional<priority> get_priority(const base_component_t* pRawComponent) const noexcept;

    /**
        @brief  Set a priority of a given component
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @param  ePriority     - new component's priority
        @retval               - true if the component is found and a priority was set
    **/
    [[maybe_unused]] bool set_priority(const base_component_t* pRawComponent, priority ePriority) noexcept;

    /**
        @brief  Get a status of a given component
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - status
    **/
    [[nodiscard]] std::optional<flags<status>> get_status(const base_component_t* pRawComponent) const noexcept;

    /**
        @brief  Set a status of a given component
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @param  status        - new component's status
        @retval               - true if the component is found and a status was set
    **/
    [[maybe_unused]] bool set_status(const base_component_t* pRawComponent, flags<status> status) noexcept;

    /**
        @brief  Check if container doesn't have any components 
        @retval  - true if container doesn't have any components
    **/
    [[nodiscard]] bool empty() const noexcept;

    /**
        @brief Clear the container, e.g. remove all the components
    **/
    void clear() noexcept;

private:
    /**
        @brief  Get or add class data of a given type
        @tparam component_t              - final class type
        @tparam callable_t               - a callable that takes a class data
        @param  iterateClassDataFunction - a function that iterates over a class data from base_component_t + 1 to component_t
        @retval                          - or add class data
    **/
    template<
        std::derived_from<base_component_t> component_t,
        callable_c<void, SClassData&>       callable_t = decltype(stub_callback)>
    SClassData& get_or_add_class_data(callable_t iterateClassDataFunction = stub_callback) noexcept
    {
        /*
            |    | rtti_base | c1 | base_component_t | c2 | c3 | component_t |
            | t1 | <=======================================================> |
            | t2 | <===============================>                         |
            | t3 |                                    <====================> |
        */
        using t1 = typename component_t::inheritance_tuple;
        using t2 = typename base_component_t::inheritance_tuple;
        using t3 = tuple::remove_t<t1, t2>;

        SClassData* pClassData = &m_RootClass;
        iterateClassDataFunction(*pClassData);

        tuple::iterate<t3>(
            [&pClassData, &iterateClassDataFunction]<class T, size_t I>()
            {
                pClassData = &pClassData->get_or_add_class_data(T::get_class_id_static());
                iterateClassDataFunction(*pClassData);
            });

        return *pClassData;
    }

    /**
        @brief  Get or add class data of a given type
        @tparam component_t              - final class type
        @tparam callable_t               - a callable that takes a class data
        @param  iterateClassDataFunction - a function that iterates over a class data from base_component_t + 1 to component_t
        @retval                          - or add class data
    **/
    template<
        std::derived_from<base_component_t> component_t,
        callable_c<void, SClassData&>       callable_t = decltype(stub_callback)>
    const SClassData& get_or_add_class_data(callable_t iterateClassDataFunction = stub_callback) const noexcept
    {
        return QX_CONST_CAST_THIS()->template get_or_add_class_data<component_t>(std::move(iterateClassDataFunction));
    }

    /**
        @brief  Get or add class data of a given type
        @tparam callable_t               - a callable that takes a class data
        @param  pRawComponent            - an object used to identify a class type
        @param  iterateClassDataFunction - a function that iterates over a class data from base_component_t + 1 to component_t
        @retval                          - or add class data
    **/
    template<callable_c<void, SClassData&> callable_t = decltype(stub_callback)>
    SClassData& get_or_add_class_data(
        const base_component_t* pRawComponent,
        callable_t              iterateClassDataFunction = stub_callback) noexcept
    {
        SClassData* pClassData = &m_RootClass;
        iterateClassDataFunction(*pClassData);

        std::span<const class_identificator> allIds = pRawComponent->get_inheritance_sequence();
        std::span<const class_identificator> baseClassIds(
            std::ranges::find(allIds, base_component_t::get_class_id_static()),
            allIds.end());

        for (auto it = baseClassIds.begin() + 1; it != baseClassIds.end(); ++it)
        {
            pClassData = &pClassData->get_or_add_class_data(*it);
            iterateClassDataFunction(*pClassData);
        }

        return *pClassData;
    }

    /**
        @brief  Get or add class data of a given type
        @tparam callable_t               - a callable that takes a class data
        @param  pRawComponent            - an object used to identify a class type
        @param  iterateClassDataFunction - a function that iterates over a class data from base_component_t + 1 to component_t
        @retval                          - or add class data
    **/
    template<callable_c<void, SClassData&> callable_t = decltype(stub_callback)>
    const SClassData& get_or_add_class_data(
        const base_component_t* pRawComponent,
        callable_t              iterateClassDataFunction = stub_callback) const noexcept
    {
        return QX_CONST_CAST_THIS()->get_or_add_class_data(pRawComponent, std::move(iterateClassDataFunction));
    }

private:
    SClassData m_RootClass;
};

} // namespace qx

#include <qx/containers/components.inl>
