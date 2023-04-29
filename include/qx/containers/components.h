/**

    @file      components.h
    @brief     Contains qx::components class
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/rtti/rtti.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace qx
{

/**

    @class   components
    @brief   Container for components system
    @details Stores components and allows them to be accessed by template argument
             Iterators allows to access components in the order in which they are added
    @tparam  base_component_t - base component type
    @author  Khrapov
    @date    9.03.2021

**/
template<class base_component_t>
class components
{
public:
    using pointer         = std::unique_ptr<base_component_t>;
    using container       = std::unordered_multimap<class_identificator, pointer>;
    using order_container = std::vector<base_component_t*>;

    /**

        @class   iterator
        @brief   Iterator to hide dereference implementation detail 
        @tparam  super_class_t - super class type
        @author  Khrapov
        @date    8.08.2021

    **/
    template<class super_class_t>
    class iterator : public super_class_t
    {
    public:
        iterator() noexcept                = default;
        iterator(const iterator&) noexcept = default;
        iterator(iterator&&) noexcept      = default;
        iterator(const super_class_t& other) noexcept;
        auto* operator->() noexcept;
        auto& operator*() noexcept;
    };

    /**

        @class   const_iterator
        @brief   Const iterator to hide dereference implementation detail
        @tparam  super_class_t - super class type
        @author  Khrapov
        @date    8.08.2021

    **/
    template<class super_class_t>
    class const_iterator : public super_class_t
    {
    public:
        const_iterator() noexcept                      = default;
        const_iterator(const const_iterator&) noexcept = default;
        const_iterator(const_iterator&&) noexcept      = default;
        const_iterator(const super_class_t& other) noexcept;
        const auto* operator->() const noexcept;
        const auto& operator*() const noexcept;
    };

public:
    /**
        @brief  Add component by constructing in place
        @tparam component_t - component type
        @tparam args_t      - type of variadic args for component construction
        @param  args        - variadic args for component construction
        @retval             - component pointer
    **/
    template<class component_t, class... args_t>
    component_t* add(args_t&&... args);

    /**
        @brief  Add component
        @tparam component_t - component type
        @param  pComponent  - component unique pointer
        @retval             - component pointer
    **/
    template<class component_t>
    component_t* add(std::unique_ptr<component_t> pComponent);

    /**
        @brief  Get first component with TKeyComponent key
        @note   "founded first" is not "added first"
        @tparam component_t - the type-identifier that was used when adding the component
        @retval             - component pointer or nullptr if not found
    **/
    template<class component_t>
    component_t* get() const;

    /**
        @brief  Get first component with "class_identificator" key
        @note   "founded first" is not "added first"
        @param  id - class id
        @retval    - component pointer or nullptr if not found
    **/
    base_component_t* get_by_id(class_identificator id) const;

    /**
        @brief  Add component with TKeyComponent id
        @tparam component_t - the type-identifier that will be used when searching for component
        @param  pComponent  - component unique pointer
        @retval             - component pointer
    **/
    template<class component_t>
    component_t* add_to(pointer pComponent);

    /**
        @brief  Get all components with TKeyComponent key
        @tparam component_t - the type-identifier that was used when adding the component
        @retval             - components range
    **/
    template<class component_t>
    auto get_all() const;

    /**
        @brief  Get all components with "class_identificator" key
        @param  id - class id
        @retval    - components range
    **/
    auto get_all_by_id(class_identificator id) const;

    /**
        @brief  Extract component from container
        @tparam component_t - the type-identifier that was used when adding the component
        @retval             - component unique pointer or nullptr if not found
    **/
    template<class component_t>
    pointer extract();

    /**
        @brief  Remove component from container
        @tparam component_t - the type-identifier that was used when adding the component
        @retval             - true if removed
    **/
    template<class component_t>
    bool remove();

    /**
        @brief  Remove all components with "type" key from container
        @tparam component_t - the type-identifier that was used when adding the component
    **/
    template<class component_t>
    void remove_all();

    /**
        @brief  Is container contains value with TKeyComponent key
        @tparam component_t - the type-identifier that was used when adding the component
        @retval             - true if contains
    **/
    template<class component_t>
    bool contains() const;

    /**
        @brief  Return iterator to beginning
        @retval - iterator to beginning
    **/
    auto begin() noexcept;

    /**
        @brief  Return iterator to end
        @retval - iterator to end
    **/
    auto end() noexcept;

    /**
        @brief  Return iterator to beginning
        @retval - iterator to beginning
    **/
    auto begin() const noexcept;

    /**
        @brief  Return iterator to end
        @retval - iterator to end
    **/
    auto end() const noexcept;

    /**
        @brief  Return const iterator to beginning
        @retval - const iterator to beginning
    **/
    auto cbegin() const noexcept;

    /**
        @brief  Return const iterator to end
        @retval - const iterator to end
    **/
    auto cend() const noexcept;

    /**
        @brief  Return reverse iterator to reverse beginning
        @retval - reverse iterator to reverse beginning
    **/
    auto rbegin() noexcept;

    /**
        @brief  Return reverse iterator to reverse end
        @retval - reverse iterator to reverse end
    **/
    auto rend() noexcept;

    /**
        @brief  Return const reverse iterator to reverse beginning
        @retval - const reverse iterator to reverse beginning
    **/
    auto crbegin() const noexcept;

    /**
        @brief  Return const reverse iterator to reverse end
        @retval - const reverse iterator to reverse end
    **/
    auto crend() const noexcept;

    /**
        @brief  Get number of components in container
        @retval - number of components in container
    **/
    size_t size() const noexcept;

    /**
        @brief  Is component empty
        @retval - true if component empty
    **/
    bool empty() const noexcept;

    /**
        @brief  Clear container
    **/
    void clear() noexcept;

private:
    container       m_Components;
    order_container m_InsertionOrderComponents;
};

} // namespace qx

#include <qx/containers/components.inl>
