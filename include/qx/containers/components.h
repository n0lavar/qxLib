//==============================================================================
//
//!\file                       components.h
//
//!\brief       Contains qx::components class
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
//!\class                qx::components<TBaseComponent>
//
//!\brief   Container for components system
//!\details ~
//
//!\author  Khrapov
//!\date    9.03.2021
//
//==============================================================================
template<class TBaseComponent>
class components
{
public:

    using pointer   = std::unique_ptr<TBaseComponent>;
    using container = std::unordered_multimap<class_identificator, pointer>;

    // iterator wrapper to hide implementation detail ".second"
    class iterator : public container::iterator
    {
        using super_class = typename container::iterator;

    public:

        iterator    (void)                      noexcept = default;
        iterator    (const iterator   & other)  noexcept = default;
        iterator    (iterator&&)                noexcept = default;
        iterator    (const super_class& other)  noexcept
            : super_class(other)
        {
        }

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
    class const_iterator : public container::const_iterator
    {
        using super_class = typename container::const_iterator;

    public:

        const_iterator  (void)                          noexcept = default;
        const_iterator  (const const_iterator & other)  noexcept = default;
        const_iterator  (const_iterator&&)              noexcept = default;
        const_iterator  (const super_class    & other)  noexcept
            : super_class(other)
        {
        }

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
    TKeyComponent* add_to(pointer pComponent);

    template<class TKeyComponent>
    auto get_all(void) const;

    auto get_all_by_id(class_identificator id) const;

    template<class TKeyComponent>
    pointer extract(void);

    template<class TKeyComponent>
    bool remove(void);

    template<class TKeyComponent>
    void remove_all(void);

    template<class TKeyComponent>
    bool contains(void) const;

    auto begin (void)       { return iterator(m_Components.begin()); }
    auto begin (void) const { return const_iterator(m_Components.begin()); }
    auto cbegin(void) const { return const_iterator(m_Components.cbegin()); }
    auto end   (void)       { return iterator(m_Components.end()); }
    auto end   (void) const { return const_iterator(m_Components.end()); }
    auto cend  (void) const { return const_iterator(m_Components.cend()); }

    auto size  (void) const noexcept { return m_Components.size(); }
    auto empty (void) const noexcept { return m_Components.empty(); }
    auto clear (void)       noexcept { return m_Components.clear(); }

private:

    container m_Components;
};

}

#include <qx/containers/components.inl>
