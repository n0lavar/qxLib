/**

    @file      components.inl
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<std::derived_from<rtti_pure_base> base_component_t>
typename components<base_component_t>::class_data& components<base_component_t>::class_data::get_or_add_class_data(
    class_id id) noexcept
{
    if (const auto it = derivedClasses.find(id); it != derivedClasses.end())
        return *it->second.get();

    auto pClassData    = std::make_unique<class_data>();
    auto pRawClassData = pClassData.get();
    derivedClasses[id] = std::move(pClassData);
    return *pRawClassData;
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
component_t* components<base_component_t>::add(
    std::unique_ptr<component_t> pComponent,
    priority                     ePriority,
    flags<component_status>      statusFlags) noexcept
{
    if (!pComponent)
        return nullptr;

    auto        pRawComponent = pComponent.get();
    class_data& classData     = get_or_add_class_data(
        pRawComponent,
        [ePriority, statusFlags, pRawComponent](class_data& classData)
        {
            classData.priorityCache.emplace(
                status { .ePriority = ePriority, .statusFlags = statusFlags },
                pRawComponent);
        });
    classData.components.push_back(std::move(pComponent));
    return pRawComponent;
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::unique_ptr<base_component_t> components<base_component_t>::remove(const base_component_t* pRawComponent) noexcept
{
    if (!pRawComponent)
        return nullptr;

    class_data& classData = get_or_add_class_data(
        pRawComponent,
        [pRawComponent](class_data& classData)
        {
            std::erase_if(
                classData.priorityCache,
                [pRawComponent](const auto& pair)
                {
                    return pair.second == pRawComponent;
                });
        });

    const auto it = std::ranges::find_if(
        classData.components,
        [pRawComponent](const pointer_type& pointer)
        {
            return pointer.get() == pRawComponent;
        });

    if (it == classData.components.end())
        return nullptr;

    std::unique_ptr<base_component_t> pComponent = std::move(*it);
    classData.components.erase(it);
    return pComponent;
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
component_t* components<base_component_t>::try_get(bool bIncludeDisabled) noexcept
{
    class_data& classData = get_or_add_class_data<component_t>();
    const auto  it        = std::ranges::find_if(
        classData.priorityCache,
        [bIncludeDisabled](const auto& pair)
        {
            return bIncludeDisabled || !pair.first.statusFlags.contains(component_status::disabled);
        });

    return it != classData.priorityCache.end() ? static_cast<component_t*>(it->second) : nullptr;
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
const component_t* components<base_component_t>::try_get(bool bIncludeDisabled) const noexcept
{
    return QX_CONST_CAST_THIS()->template try_get<component_t>(bIncludeDisabled);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
component_t* components<base_component_t>::try_get(class_id id, bool bIncludeDisabled) noexcept
{
    // we could improve it from O(N) to O(log(N)) if we could use id->is_derived_from(id) without an object itself
    // we will do it when a reflection system is fully implemented
    const auto it = std::ranges::find_if(
        m_RootClass.priorityCache,
        [id, bIncludeDisabled](const auto& pair)
        {
            return (bIncludeDisabled || !pair.first.statusFlags.contains(component_status::disabled))
                   && pair.second->is_derived_from_id(id);
        });

    return it != m_RootClass.priorityCache.end() ? rtti_cast<component_t>(it->second) : nullptr;
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
const component_t* components<base_component_t>::try_get(class_id id, bool bIncludeDisabled) const noexcept
{
    return QX_CONST_CAST_THIS()->template try_get<component_t>(id, bIncludeDisabled);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
component_t& components<base_component_t>::get(bool bIncludeDisabled) noexcept
{
    return *try_get<component_t>(bIncludeDisabled);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
const component_t& components<base_component_t>::get(bool bIncludeDisabled) const noexcept
{
    return QX_CONST_CAST_THIS()->template get<component_t>(bIncludeDisabled);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
base_component_t& components<base_component_t>::get(class_id id, bool bIncludeDisabled) noexcept
{
    return *try_get<component_t>(id, bIncludeDisabled);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
const base_component_t& components<base_component_t>::get(class_id id, bool bIncludeDisabled) const noexcept
{
    return QX_CONST_CAST_THIS()->template get<component_t>(id, bIncludeDisabled);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
auto components<base_component_t>::view() noexcept
{
    class_data& classData = get_or_add_class_data<component_t>();
    return classData.priorityCache
           | std::views::filter(
               [](const auto& pair)
               {
                   return pair.second->template is_derived_from<component_t>()
                          && !pair.first.statusFlags.contains(component_status::disabled);
               })
           | std::views::transform(
               [](auto& pair) -> component_t&
               {
                   return *static_cast<component_t*>(pair.second);
               });
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
auto components<base_component_t>::view() const noexcept
{
    const class_data& classData = get_or_add_class_data<component_t>();
    return classData.priorityCache
           | std::views::filter(
               [](const auto& pair)
               {
                   return pair.second->template is_derived_from<component_t>()
                          && !pair.first.statusFlags.contains(component_status::disabled);
               })
           | std::views::transform(
               [](const auto& pair) -> const component_t&
               {
                   return *static_cast<const component_t*>(pair.second);
               });
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::optional<flags<component_status>> components<base_component_t>::get_component_status(
    const base_component_t* pRawComponent) const noexcept
{
    std::optional<status> optComponentStatus = get_status(pRawComponent);
    return optComponentStatus ? std::optional(optComponentStatus->statusFlags) : std::nullopt;
}

template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::set_component_status(
    const base_component_t* pRawComponent,
    flags<component_status> newStatus) noexcept
{
    std::optional<status> optComponentStatus = get_status(pRawComponent);
    if (!optComponentStatus)
        return false;

    optComponentStatus->statusFlags = newStatus;
    return set_status(pRawComponent, *optComponentStatus);
}

template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::add_component_status(
    const base_component_t* pRawComponent,
    flags<component_status> newStatuses) noexcept
{
    std::optional<flags<component_status>> optComponentStatus = get_component_status(pRawComponent);
    if (!optComponentStatus)
        return false;

    optComponentStatus->add(newStatuses);
    return set_component_status(pRawComponent, *optComponentStatus);
}

template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::remove_component_status(
    const base_component_t* pRawComponent,
    flags<component_status> statusesToRemove) noexcept
{
    std::optional<flags<component_status>> optComponentStatus = get_component_status(pRawComponent);
    if (!optComponentStatus)
        return false;

    optComponentStatus->remove(statusesToRemove);
    return set_component_status(pRawComponent, *optComponentStatus);
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::optional<priority> components<base_component_t>::get_component_priority(
    const base_component_t* pRawComponent) const noexcept
{
    std::optional<status> optComponentStatus = get_status(pRawComponent);
    return optComponentStatus ? std::optional(optComponentStatus->ePriority) : std::nullopt;
}

template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::set_component_priority(
    const base_component_t* pRawComponent,
    priority                eNewComponentPriority) noexcept
{
    std::optional<status> optComponentStatus = get_status(pRawComponent);
    if (!optComponentStatus)
        return false;

    optComponentStatus->ePriority = eNewComponentPriority;
    return set_status(pRawComponent, *optComponentStatus);
}

template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::empty() const noexcept
{
    return m_RootClass.priorityCache.empty();
}

template<std::derived_from<rtti_pure_base> base_component_t>
void components<base_component_t>::clear() noexcept
{
    m_RootClass.derivedClasses.clear();
    m_RootClass.components.clear();
    m_RootClass.priorityCache.clear();
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::optional<typename components<base_component_t>::status> components<base_component_t>::get_status(
    const base_component_t* pRawComponent) const noexcept
{
    if (!pRawComponent)
        return std::nullopt;

    auto it = std::ranges::find_if(
        m_RootClass.priorityCache,
        [pRawComponent](const auto& pair)
        {
            return pair.second == pRawComponent;
        });

    return it != m_RootClass.priorityCache.end() ? std::optional<status>(it->first) : std::nullopt;
}


template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::set_status(const base_component_t* pRawComponent, status status) noexcept
{
    if (!pRawComponent)
        return false;

    bool bChanged = true;
    get_or_add_class_data(
        pRawComponent,
        [pRawComponent, status, &bChanged](class_data& classData)
        {
            const auto it = std::ranges::find_if(
                classData.priorityCache,
                [pRawComponent](const auto& pair)
                {
                    return pair.second == pRawComponent;
                });

            if (it == classData.priorityCache.end())
            {
                bChanged = false;
                return;
            }

            if (it->first != status)
            {
                classData.priorityCache.emplace(status, it->second);
                classData.priorityCache.erase(it);
            }
        });

    return bChanged;
}

} // namespace qx
