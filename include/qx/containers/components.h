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
#include <vector>

namespace qx
{

//==============================================================================
//
//!\class                qx::components<TBaseComponent>
//
//!\brief   Container for components system
//!\details Stores components and allows them to be accessed by template argument
//          Iterators allows to access components in the order in which they are added
//
//!\author  Khrapov
//!\date    9.03.2021
//
//==============================================================================
template<class TBaseComponent>
class components
{
public:

    using pointer         = std::unique_ptr<TBaseComponent>;
    using container       = std::unordered_multimap<class_identificator, pointer>;
    using order_container = std::vector<TBaseComponent*>;

    template<class TSuperClass>
    class iterator : public TSuperClass
    {
    public:

        iterator    (void)                      noexcept = default;
        iterator    (const iterator&)           noexcept = default;
        iterator    (iterator&&)                noexcept = default;
        iterator    (const TSuperClass& other)  noexcept
            : TSuperClass(other)
        {
        }

        auto* operator->(void) noexcept
        {
            return *TSuperClass::operator->();
        }
        auto& operator*(void) noexcept
        {
            return *TSuperClass::operator*();
        }
    };

    template<class TSuperClass>
    class const_iterator : public TSuperClass
    {
    public:

        const_iterator  (void)                          noexcept = default;
        const_iterator  (const const_iterator&)         noexcept = default;
        const_iterator  (const_iterator&&)              noexcept = default;
        const_iterator  (const TSuperClass    & other)  noexcept
            : TSuperClass(other)
        {
        }

        const auto* operator->(void) const noexcept
        {
            return *TSuperClass::operator->();
        }
        const auto& operator*(void) const noexcept
        {
            return *TSuperClass::operator*();
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

    auto begin  (void)          noexcept;
    auto end    (void)          noexcept;

    auto begin  (void) const    noexcept;
    auto end    (void) const    noexcept;

    auto cbegin (void) const    noexcept;
    auto cend   (void) const    noexcept;

    auto rbegin (void)          noexcept;
    auto rend   (void)          noexcept;

    auto crbegin(void) const    noexcept;
    auto crend  (void) const    noexcept;

    auto size   (void) const    noexcept;
    auto empty  (void) const    noexcept;
    auto clear  (void)          noexcept;

private:

    container       m_Components;
    order_container m_InsertionOrderComponents;
};

template<class TBaseComponent>
auto components<TBaseComponent>::begin(void) noexcept
{
    return iterator<typename order_container::iterator>(
        m_InsertionOrderComponents.begin());
}
template<class TBaseComponent>
auto components<TBaseComponent>::end(void) noexcept
{
    return iterator<typename order_container::iterator>(
        m_InsertionOrderComponents.end());
}
template<class TBaseComponent>
auto components<TBaseComponent>::begin(void) const noexcept
{
    return const_iterator<typename order_container::const_iterator>(
        m_InsertionOrderComponents.begin());
}
template<class TBaseComponent>
auto components<TBaseComponent>::end(void) const noexcept
{
    return const_iterator<typename order_container::const_iterator>(
        m_InsertionOrderComponents.end());
}
template<class TBaseComponent>
auto components<TBaseComponent>::cbegin(void) const noexcept
{
    return const_iterator<typename order_container::const_iterator>(
        m_InsertionOrderComponents.cbegin());
}
template<class TBaseComponent>
auto components<TBaseComponent>::cend(void) const noexcept
{
    return const_iterator<typename order_container::const_iterator>(
        m_InsertionOrderComponents.cend());
}
template<class TBaseComponent>
auto components<TBaseComponent>::rbegin(void) noexcept
{
    return iterator<typename order_container::reverse_iterator>(
        m_InsertionOrderComponents.rbegin());
}
template<class TBaseComponent>
auto components<TBaseComponent>::rend(void) noexcept
{
    return iterator<typename order_container::reverse_iterator>(
        m_InsertionOrderComponents.rend());
}
template<class TBaseComponent>
auto components<TBaseComponent>::crbegin(void) const noexcept
{
    return const_iterator<typename order_container::const_reverse_iterator>(
        m_InsertionOrderComponents.crbegin());
}
template<class TBaseComponent>
auto components<TBaseComponent>::crend(void) const noexcept
{
    return const_iterator<typename order_container::const_reverse_iterator>(
        m_InsertionOrderComponents.crend());
}
template<class TBaseComponent>
auto components<TBaseComponent>::size(void) const noexcept
{
    return m_Components.size();
}
template<class TBaseComponent>
auto components<TBaseComponent>::empty(void) const noexcept
{
    return m_Components.empty();
}
template<class TBaseComponent>
auto components<TBaseComponent>::clear(void) noexcept
{
    m_Components.clear();
    m_InsertionOrderComponents.clear();
}

}

#include <qx/containers/components.inl>
