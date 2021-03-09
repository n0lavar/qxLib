//==============================================================================
//
//!\file                     components_container.h
//
//!\brief       Contains qx::components_container class
//!\details     ~
//
//!\author      Khrapov
//!\date        7.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/rtti.h>

#include <memory>
#include <unordered_map>

namespace qx
{

//==============================================================================
//
//!\class           qx::components_container<TBaseComponent>
//
//!\brief   Container for components system
//!\details ~
//
//!\author  Khrapov
//!\date    9.03.2021
//
//==============================================================================
template<class TBaseComponent>
class components_container
{
public:

    using component_ptr = std::unique_ptr<TBaseComponent>;
    using components_container_type = std::unordered_multimap<
        class_identificator,
        component_ptr
    >;

    // iterator wrapper to hide implementation detail ".second"
    class iterator : public components_container_type::iterator
    {
        using super_class = typename components_container_type::iterator;

    public:

        auto* operator->(void) noexcept
        {
            return super_class::operator->()->second.get();
        }
        auto& operator*(void) noexcept
        {
            return *super_class::operator*().second.get();
        }
    };

    // const_iterator wrapper to hide implementation detail ".second"
    class const_iterator : public components_container_type::const_iterator
    {
        using super_class = typename components_container_type::const_iterator;

    public:

        const auto* operator->(void) const noexcept
        {
            return super_class::operator->()->second.get();
        }
        const auto& operator*(void) const noexcept
        {
            return *super_class::operator*().second.get();
        }
    };

public:

    template<class TComponent, class... Args>
    TComponent* add(Args&&... args);

    template<class TComponent>
    TComponent* add(std::unique_ptr<TComponent> pComponent);

    template<class TKeyComponent>
    TKeyComponent* get(void) const;

    TBaseComponent* get_by_id(class_identificator id) const;

    template<class TKeyComponent>
    TKeyComponent* add_to(component_ptr pComponent);

    template<class TKeyComponent>
    auto get_all(void) const;

    auto get_all_by_id(class_identificator id) const;

    template<class TKeyComponent>
    component_ptr extract(void);

    template<class TKeyComponent>
    bool remove(void);

    template<class TKeyComponent>
    void remove_all(void);

    template<class TKeyComponent>
    bool contains(void) const;

    iterator       begin  (void)       noexcept { return iterator(m_Components.begin()); }
    const_iterator begin  (void) const noexcept { return const_iterator(m_Components.begin()); }
    const_iterator cbegin (void) const noexcept { return const_iterator(m_Components.cbegin()); }
    iterator       end    (void)       noexcept { return iterator(m_Components.end()); }
    const_iterator end    (void) const noexcept { return const_iterator(m_Components.end()); }
    const_iterator cend   (void) const noexcept { return const_iterator(m_Components.cend()); }

    auto size  (void) const noexcept { return m_Components.size(); }
    auto empty (void) const noexcept { return m_Components.empty(); }
    auto clear (void)       noexcept { return m_Components.clear(); }

private:

    components_container_type m_Components;
};

}

#include <qx/containers/components_container.inl>
