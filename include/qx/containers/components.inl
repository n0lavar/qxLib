/**

    @file      components.inl
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<class base_component_t>
template<class super_class_t>
inline components<base_component_t>::iterator<super_class_t>::iterator(const super_class_t& other) noexcept
    : super_class_t(other)
{
}

template<class base_component_t>
template<class super_class_t>
inline auto* components<base_component_t>::iterator<super_class_t>::operator->(void) noexcept
{
    return *super_class_t::operator->();
}

template<class base_component_t>
template<class super_class_t>
inline auto& components<base_component_t>::iterator<super_class_t>::operator*(void) noexcept
{
    return *super_class_t::operator*();
}

template<class base_component_t>
template<class super_class_t>
inline components<base_component_t>::const_iterator<super_class_t>::const_iterator(const super_class_t& other) noexcept
    : super_class_t(other)
{
}

template<class base_component_t>
template<class super_class_t>
inline const auto* components<base_component_t>::const_iterator<super_class_t>::operator->() const noexcept
{
    return *super_class_t::operator->();
}

template<class base_component_t>
template<class super_class_t>
inline const auto& components<base_component_t>::const_iterator<super_class_t>::operator*() const noexcept
{
    return *super_class_t::operator*();
}

template<class base_component_t>
template<class component_t, class... args_t>
inline component_t* components<base_component_t>::add(args_t&&... args)
{
    return add_to<component_t>(std::make_unique<component_t>(std::forward<args_t>(args)...));
}

template<class base_component_t>
template<class component_t>
inline component_t* components<base_component_t>::add(std::unique_ptr<component_t> pComponent)
{
    return add_to<component_t>(std::move(pComponent));
}

template<class base_component_t>
template<class component_t>
inline component_t* components<base_component_t>::get() const
{
    return static_cast<component_t*>(get_by_id(component_t::get_class_id_static()));
}

template<class base_component_t>
inline base_component_t* components<base_component_t>::get_by_id(class_identificator id) const
{
    auto it = m_Components.find(id);
    return it != m_Components.end() ? it->second.get() : nullptr;
}

template<class base_component_t>
template<class component_t>
inline component_t* components<base_component_t>::add_to(pointer pComponent)
{
    auto pRawComponent = pComponent.get();

    m_Components.emplace(component_t::get_class_id_static(), std::move(pComponent));

    m_InsertionOrderComponents.push_back(pRawComponent);

    return static_cast<component_t*>(pRawComponent);
}

template<class base_component_t>
template<class component_t>
inline auto components<base_component_t>::get_all() const
{
    return get_all_by_id(component_t::get_class_id_static());
}

template<class base_component_t>
inline auto components<base_component_t>::get_all_by_id(class_identificator id) const
{
    return m_Components.equal_range(id);
}

template<class base_component_t>
template<class component_t>
inline typename components<base_component_t>::pointer components<base_component_t>::extract()
{
    if (auto it = m_Components.find(component_t::get_class_id_static()); it != m_Components.end())
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

template<class base_component_t>
template<class component_t>
inline bool components<base_component_t>::remove()
{
    return extract<component_t>().get() != nullptr;
}

template<class base_component_t>
template<class component_t>
inline void components<base_component_t>::remove_all()
{
    while (remove<component_t>())
        ;
}

template<class base_component_t>
template<class component_t>
inline bool components<base_component_t>::contains() const
{
    return get<component_t>() != nullptr;
}

template<class base_component_t>
auto components<base_component_t>::begin() noexcept
{
    return iterator<typename order_container::iterator>(m_InsertionOrderComponents.begin());
}

template<class base_component_t>
auto components<base_component_t>::end() noexcept
{
    return iterator<typename order_container::iterator>(m_InsertionOrderComponents.end());
}

template<class base_component_t>
auto components<base_component_t>::begin() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.begin());
}

template<class base_component_t>
auto components<base_component_t>::end() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.end());
}

template<class base_component_t>
auto components<base_component_t>::cbegin() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.cbegin());
}

template<class base_component_t>
auto components<base_component_t>::cend() const noexcept
{
    return const_iterator<typename order_container::const_iterator>(m_InsertionOrderComponents.cend());
}

template<class base_component_t>
auto components<base_component_t>::rbegin() noexcept
{
    return iterator<typename order_container::reverse_iterator>(m_InsertionOrderComponents.rbegin());
}

template<class base_component_t>
auto components<base_component_t>::rend() noexcept
{
    return iterator<typename order_container::reverse_iterator>(m_InsertionOrderComponents.rend());
}

template<class base_component_t>
auto components<base_component_t>::crbegin() const noexcept
{
    return const_iterator<typename order_container::const_reverse_iterator>(m_InsertionOrderComponents.crbegin());
}

template<class base_component_t>
auto components<base_component_t>::crend() const noexcept
{
    return const_iterator<typename order_container::const_reverse_iterator>(m_InsertionOrderComponents.crend());
}

template<class base_component_t>
size_t components<base_component_t>::size() const noexcept
{
    return m_Components.size();
}

template<class base_component_t>
bool components<base_component_t>::empty() const noexcept
{
    return m_Components.empty();
}

template<class base_component_t>
void components<base_component_t>::clear() noexcept
{
    m_Components.clear();
    m_InsertionOrderComponents.clear();
}

} // namespace qx
