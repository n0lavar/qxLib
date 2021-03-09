//==============================================================================
//
//!\file                    components_container.inl
//
//!\brief       Contains qx::components_container class
//!\details     ~
//
//!\author      Khrapov
//!\date        7.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

//==============================================================================
//!\fn qx::components_container<TBaseComponent>::add<TComponent, ...Args>
//
//!\brief  Add component by constructing in place
//!\param  ...args - arguments for component constructing
//!\retval         - component pointer
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TComponent, class... Args>
inline TComponent* components_container<TBaseComponent>::add(Args&&... args)
{
    return add_to<TComponent>(std::make_unique<TComponent>(
        std::forward<Args>(args)...));
}

//==============================================================================
//!\fn     qx::components_container<TBaseComponent>::add<TComponent>
//
//!\brief  Add component
//!\param  pComponent - component unique ptr
//!\retval            - component pointer
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TComponent>
inline TComponent* components_container<TBaseComponent>::add(
    std::unique_ptr<TComponent> pComponent)
{
    return add_to<TComponent>(std::move(pComponent));
}

//==============================================================================
//!\fn    qx::components_container<TBaseComponent>::get<TKeyComponent>
//
//!\brief  Get first component with "type" key
//!\tparam TKeyComponent - the type-identifier that was used when adding
//                         the component
//!\retval               - component pointer or nullptr if not found
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TKeyComponent>
inline TKeyComponent* components_container<TBaseComponent>::get(void) const
{
    return static_cast<TKeyComponent*>(get_by_id(
        TKeyComponent::get_class_id_static()));
}

//==============================================================================
//!\fn          components_container<TBaseComponent>::get_by_id
//
//!\brief  Get first component with "class_identificator" key
//!\param  id - class id
//!\retval    - component pointer or nullptr if not found
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template<class TBaseComponent>
inline TBaseComponent * components_container<TBaseComponent>::get_by_id(
    class_identificator id) const
{
    auto it = m_Components.find(id);
    return it != m_Components.end()
        ? it->second.get()
        : nullptr;
}

//==============================================================================
//!\fn  qx::components_container<TBaseComponent>::add_to<TKeyComponent>
//
//!\brief  Add component with type id
//!\tparam TKeyComponent - the type-identifier that will be used when searching
//                         for component
//!\param  pComponent    - component unique ptr
//!\retval               - component pointer
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template<class TBaseComponent>
template<class TKeyComponent>
inline TKeyComponent * components_container<TBaseComponent>::add_to(
    component_ptr pComponent)
{
    auto pRawComponent = pComponent.get();
    m_Components.emplace(
        TKeyComponent::get_class_id_static(),
        std::move(pComponent));

    return static_cast<TKeyComponent*>(pRawComponent);
}

//==============================================================================
//!\fn  qx::components_container<TBaseComponent>::get_all<TKeyComponent>
//
//!\brief  Get all components with "type" key
//!\tparam TKeyComponent - the type-identifier that was used when adding
//                         the component
//!\retval               - components range
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TKeyComponent>
inline auto components_container<TBaseComponent>::get_all(void) const
{
    return get_all_by_id(TKeyComponent::get_class_id_static());
}

//==============================================================================
//!\fn      qx::components_container<TBaseComponent>::get_all_by_id
//
//!\brief  Get all components with "class_identificator" key
//!\param  id - class id
//!\retval    - components range
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template<class TBaseComponent>
inline auto qx::components_container<TBaseComponent>::get_all_by_id(
    class_identificator id) const
{
    return m_Components.equal_range(id);
}

//==============================================================================
//!\fn  qx::components_container<TBaseComponent>::extract<TKeyComponent>
//
//!\brief  Extract component from container
//!\tparam TKeyComponent - the type-identifier that was used when adding
//                         the component
//!\retval               - component pointer or nullptr if not found
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TKeyComponent>
inline typename components_container<TBaseComponent>::component_ptr
    components_container<TBaseComponent>::extract(void)
{
    if (auto it = m_Components.find(TKeyComponent::get_class_id_static());
        it != m_Components.end())
    {
        auto pComponent = std::move(it->second);
        m_Components.erase(it);
        return pComponent;
    }
    else
    {
        return nullptr;
    }
}

//==============================================================================
//!\fn  qx::components_container<TBaseComponent>::remove<TKeyComponent>
//
//!\brief  Remove component from container
//!\tparam TKeyComponent - the type-identifier that was used when adding
//                         the component
//!\retval               - true if removed
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TKeyComponent>
inline bool components_container<TBaseComponent>::remove(void)
{
    return extract<TKeyComponent>().get() != nullptr;
}

//==============================================================================
//!\fn qx::components_container<TBaseComponent>::remove_all<TKeyComponent>
//
//!\brief  Remove all components with "type" key from container
//!\tparam TKeyComponent - the type-identifier that was used when adding
//                         the component
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template <class TBaseComponent>
template <class TKeyComponent>
inline void components_container<TBaseComponent>::remove_all(void)
{
    while (remove<TKeyComponent>());
}

//==============================================================================
//!\fn qx::components_container<TBaseComponent>::contains<TKeyComponent>
//
//!\brief  Is container contains value with "type" key
//!\tparam TKeyComponent - the type-identifier that was used when adding
//                         the component
//!\retval               - true if contains
//!\author Khrapov
//!\date   9.03.2021
//==============================================================================
template<class TBaseComponent>
template<class TKeyComponent>
inline bool components_container<TBaseComponent>::contains(void) const
{
    return get<TKeyComponent>() != nullptr;
}

}
