/**

    @file      components.inl
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class TBaseComponent>
template<class TSuperClass>
inline components<TBaseComponent>::iterator<TSuperClass>::iterator(const TSuperClass& other) noexcept
    : TSuperClass(other)
{
}

template<class TBaseComponent>
template<class TSuperClass>
inline auto* components<TBaseComponent>::iterator<TSuperClass>::operator->(void) noexcept
{
    return *TSuperClass::operator->();
}

template<class TBaseComponent>
template<class TSuperClass>
inline auto& components<TBaseComponent>::iterator<TSuperClass>::operator*(void) noexcept
{
    return *TSuperClass::operator*();
}

template<class TBaseComponent>
template<class TSuperClass>
inline components<TBaseComponent>::const_iterator<TSuperClass>::const_iterator(const TSuperClass& other) noexcept
    : TSuperClass(other)
{
}

template<class TBaseComponent>
template<class TSuperClass>
inline const auto* components<TBaseComponent>::const_iterator<TSuperClass>::operator->() const noexcept
{
    return *TSuperClass::operator->();
}

template<class TBaseComponent>
template<class TSuperClass>
inline const auto& components<TBaseComponent>::const_iterator<TSuperClass>::operator*() const noexcept
{
    return *TSuperClass::operator*();
}

template<class TBaseComponent>
template<class TComponent, class... Args>
inline TComponent* components<TBaseComponent>::add(Args&&... args)
{
    return add_to<TComponent>(std::make_unique<TComponent>(std::forward<Args>(args)...));
}

template<class TBaseComponent>
template<class TComponent>
inline TComponent* components<TBaseComponent>::add(std::unique_ptr<TComponent> pComponent)
{
    return add_to<TComponent>(std::move(pComponent));
}

template<class TBaseComponent>
template<class TKeyComponent>
inline TKeyComponent* components<TBaseComponent>::get() const
{
    return static_cast<TKeyComponent*>(get_by_id(TKeyComponent::get_class_id_static()));
}

template<class TBaseComponent>
inline TBaseComponent* components<TBaseComponent>::get_by_id(class_identificator id) const
{
    auto it = m_Components.find(id);
    return it != m_Components.end() ? it->second.get() : nullptr;
}

template<class TBaseComponent>
template<class TKeyComponent>
inline TKeyComponent* components<TBaseComponent>::add_to(pointer pComponent)
{
    auto pRawComponent = pComponent.get();

    m_Components.emplace(TKeyComponent::get_class_id_static(), std::move(pComponent));

    m_InsertionOrderComponents.push_back(pRawComponent);

    return static_cast<TKeyComponent*>(pRawComponent);
}

template<class TBaseComponent>
template<class TKeyComponent>
inline auto components<TBaseComponent>::get_all() const
{
    return get_all_by_id(TKeyComponent::get_class_id_static());
}

template<class TBaseComponent>
inline auto components<TBaseComponent>::get_all_by_id(class_identificator id) const
{
    return m_Components.equal_range(id);
}

template<class TBaseComponent>
template<class TKeyComponent>
inline typename components<TBaseComponent>::pointer components<TBaseComponent>::extract()
{
    if (auto it = m_Components.find(TKeyComponent::get_class_id_static()); it != m_Components.end())
    {
        auto pComponent = std::move(it->second);
        m_Components.erase(it);

        m_InsertionOrderComponents.erase(
            std::remove_if(
                m_InsertionOrderComponents.begin(),
                m_InsertionOrderComponents.end(),
                [&pComponent](auto pVectorComponent)
                {
                    return pVectorComponent == pComponent.get();
                }),
            m_InsertionOrderComponents.end());

        return pComponent;
    }
    else
    {
        return nullptr;
    }
}

template<class TBaseComponent>
template<class TKeyComponent>
inline bool components<TBaseComponent>::remove()
{
    return extract<TKeyComponent>().get() != nullptr;
}

template<class TBaseComponent>
template<class TKeyComponent>
inline void components<TBaseComponent>::remove_all()
{
    while (remove<TKeyComponent>())
        ;
}

template<class TBaseComponent>
template<class TKeyComponent>
inline bool components<TBaseComponent>::contains() const
{
    return get<TKeyComponent>() != nullptr;
}

template<class TBaseComponent>
auto components<TBaseComponent>::begin() noexcept
{
    return iterator<typename order_container::iterator>(m_InsertionOrderComponents.begin());
}

template<class TBaseComponent>
auto components<TBaseComponent>::end() noexcept
{
    return iterator<typename order_container::iterator>(m_InsertionOrderComponents.end());
}

template<class TBaseComponent>
auto components<TBaseComponent>::begin() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.begin());
}

template<class TBaseComponent>
auto components<TBaseComponent>::end() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.end());
}

template<class TBaseComponent>
auto components<TBaseComponent>::cbegin() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.cbegin());
}

template<class TBaseComponent>
auto components<TBaseComponent>::cend() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.cend());
}

template<class TBaseComponent>
auto components<TBaseComponent>::rbegin() noexcept
{
    return iterator<typename order_container::reverse_iterator>(m_InsertionOrderComponents.rbegin());
}

template<class TBaseComponent>
auto components<TBaseComponent>::rend() noexcept
{
    return iterator<typename order_container::reverse_iterator>(m_InsertionOrderComponents.rend());
}

template<class TBaseComponent>
auto components<TBaseComponent>::crbegin() const noexcept
{
    return const_iterator<typename order_container::const_reverse_iterator>(m_InsertionOrderComponents.crbegin());
}

template<class TBaseComponent>
auto components<TBaseComponent>::crend() const noexcept
{
    return const_iterator<typename order_container::const_reverse_iterator>(m_InsertionOrderComponents.crend());
}

template<class TBaseComponent>
size_t components<TBaseComponent>::size() const noexcept
{
    return m_Components.size();
}

template<class TBaseComponent>
bool components<TBaseComponent>::empty() const noexcept
{
    return m_Components.empty();
}

template<class TBaseComponent>
void components<TBaseComponent>::clear() noexcept
{
    m_Components.clear();
    m_InsertionOrderComponents.clear();
}

} // namespace qx
