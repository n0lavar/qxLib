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
#include <qx/rtti/rtti_cast.h>

#include <atomic>
#include <map>
#include <optional>
#include <ranges>
#include <unordered_map>

namespace qx
{

enum class component_status
{
    default_value = 0,
    disabled      = 1 << 0,
};

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
    struct status : time_ordered_priority_key
    {
        flags<component_status> statusFlags = component_status::default_value;

        using time_ordered_priority_key::operator<;
        constexpr bool operator==(const status&) const noexcept = default;
    };

    struct class_data
    {
        std::unordered_map<class_id, std::unique_ptr<class_data>> derivedClasses;
        std::vector<pointer_type>                                 components;
        std::multimap<status, base_component_t*>                  priorityCache;

        [[nodiscard]] class_data& get_or_add_class_data(class_id id) noexcept;
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
        flags<component_status>      statusFlags = component_status::default_value) noexcept;

    /**
        @brief  Remove the component from the container
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - component object
    **/
    [[maybe_unused]] std::unique_ptr<base_component_t> remove(const base_component_t* pRawComponent) noexcept;

    /**
        @brief  Try to get a component of the given type with the highest priority
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component pointer or nullptr
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] component_t* try_get(bool bIncludeDisabled = false) noexcept;

    /**
        @brief  Try to get a component of the given type with the highest priority
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component pointer or nullptr
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] const component_t* try_get(bool bIncludeDisabled = false) const noexcept;

    /**
        @brief  Try to get a component of the given type id with the highest priority
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  id               - type id
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component pointer or nullptr
    **/
    template<std::derived_from<base_component_t> component_t = base_component_t>
    [[nodiscard]] component_t* try_get(class_id id, bool bIncludeDisabled = false) noexcept;

    /**
        @brief  Try to get a component of the given type id with the highest priority
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  id               - type id
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component pointer or nullptr
    **/
    template<std::derived_from<base_component_t> component_t = base_component_t>
    [[nodiscard]] const component_t* try_get(class_id id, bool bIncludeDisabled = false) const noexcept;

    /**
        @brief  Get a component of the given type with the highest priority (no existence checks are performed)
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component reference
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] component_t& get(bool bIncludeDisabled = false) noexcept;

    /**
        @brief  Get a component of the given type with the highest priority (no existence checks are performed)
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component reference
    **/
    template<std::derived_from<base_component_t> component_t>
    [[nodiscard]] const component_t& get(bool bIncludeDisabled = false) const noexcept;

    /**
        @brief  Get a component of the given type with the highest priority (no existence checks are performed)
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  id               - type id
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component reference
    **/
    template<std::derived_from<base_component_t> component_t = base_component_t>
    [[nodiscard]] base_component_t& get(class_id id, bool bIncludeDisabled = false) noexcept;

    /**
        @brief  Get a component of the given type with the highest priority (no existence checks are performed)
        @tparam component_t      - component type which doesn't have to be a final class type, may be any base or super type
        @param  id               - type id
        @param  bIncludeDisabled - true if a search should include disabled components
        @retval                  - component reference
    **/
    template<std::derived_from<base_component_t> component_t = base_component_t>
    [[nodiscard]] const base_component_t& get(class_id id, bool bIncludeDisabled = false) const noexcept;

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
        @brief  Get component status
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - component status
    **/
    [[nodiscard]] std::optional<flags<component_status>> get_component_status(
        const base_component_t* pRawComponent) const noexcept;

    /**
        @brief  Set (override) a component status
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @param  newStatus     - new component status
        @retval               - true if a component has been found and a new value has been set
    **/
    [[maybe_unused]] bool set_component_status(
        const base_component_t* pRawComponent,
        flags<component_status> newStatus) noexcept;

    /**
        @brief  Add new component status flags to the current ones
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @param  newStatuses   - new component status flags 
        @retval               - true if a component has been found and a new value has been set
    **/
    [[maybe_unused]] bool add_component_status(
        const base_component_t* pRawComponent,
        flags<component_status> newStatuses) noexcept;

    /**
        @brief  Add component status flags from the current ones
        @param  pRawComponent    - raw component pointer which acts like a component's handle
        @param  statusesToRemove - component status flags to remove
        @retval                  - true if a component has been found and a new value has been set
    **/
    [[maybe_unused]] bool remove_component_status(
        const base_component_t* pRawComponent,
        flags<component_status> statusesToRemove) noexcept;

    /**
        @brief  Get component priority
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - component priority
    **/
    [[nodiscard]] std::optional<priority> get_component_priority(const base_component_t* pRawComponent) const noexcept;

    /**
        @brief  Set component priority
        @param  pRawComponent         - raw component pointer which acts like a component's handle
        @param  eNewComponentPriority - new component priority
        @retval                       - true if a component has been found and a new value has been set
    **/
    [[maybe_unused]] bool set_component_priority(
        const base_component_t* pRawComponent,
        priority                eNewComponentPriority) noexcept;

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
        @brief  Get a status of a given component
        @param  pRawComponent - raw component pointer which acts like a component's handle
        @retval               - status
    **/
    [[nodiscard]] std::optional<status> get_status(const base_component_t* pRawComponent) const noexcept;

    /**
        @brief   Set a status of a given component
        @warning This method may change the container, and you shall not use it while iterating over it
        @param   pRawComponent - raw component pointer which acts like a component's handle
        @param   status        - new component's status
        @retval                - true if the component is found and a status was set
    **/
    [[maybe_unused]] bool set_status(const base_component_t* pRawComponent, status status) noexcept;

    /**
        @brief  Get or add class data of a given type
        @tparam component_t              - final class type
        @tparam callable_t               - a callable that takes a class data
        @param  iterateClassDataFunction - a function that iterates over a class data from base_component_t + 1 to component_t
        @retval                          - or add class data
    **/
    template<
        std::derived_from<base_component_t> component_t,
        callable_c<void, class_data&>       callable_t = decltype(stub_callback)>
    class_data& get_or_add_class_data(callable_t iterateClassDataFunction = stub_callback) noexcept
    {
        /*
            |    | rtti_base | c1 | base_component_t | c2 | c3 | component_t |
            | t1 | <=======================================================> |
            | t2 | <===============================>                         |
            | t3 |                                    <====================> |
        */
        using t1 = typename component_t::inheritance_tuple_type;
        using t2 = typename base_component_t::inheritance_tuple_type;
        using t3 = tuple::remove_t<t1, t2>;

        class_data* pClassData = &m_RootClass;
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
        callable_c<void, class_data&>       callable_t = decltype(stub_callback)>
    const class_data& get_or_add_class_data(callable_t iterateClassDataFunction = stub_callback) const noexcept
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
    template<callable_c<void, class_data&> callable_t = decltype(stub_callback)>
    class_data& get_or_add_class_data(
        const base_component_t* pRawComponent,
        callable_t              iterateClassDataFunction = stub_callback) noexcept
    {
        class_data* pClassData = &m_RootClass;
        iterateClassDataFunction(*pClassData);

        std::span<const class_id> allIds = pRawComponent->get_inheritance_sequence();
        std::span<const class_id> baseClassIds(
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
    template<callable_c<void, class_data&> callable_t = decltype(stub_callback)>
    const class_data& get_or_add_class_data(
        const base_component_t* pRawComponent,
        callable_t              iterateClassDataFunction = stub_callback) const noexcept
    {
        return QX_CONST_CAST_THIS()->get_or_add_class_data(pRawComponent, std::move(iterateClassDataFunction));
    }

private:
    class_data m_RootClass;
};

} // namespace qx

#include <qx/containers/components.inl>
