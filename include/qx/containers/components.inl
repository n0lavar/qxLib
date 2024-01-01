/**

    @file      components.inl
    @author    Khrapov
    @date      7.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

template<std::derived_from<rtti_pure_base> base_component_t>
typename components<base_component_t>::SClassData& components<base_component_t>::SClassData::get_or_add_class_data(
    class_identificator id) noexcept
{
    if (const auto it = derivedClasses.find(id); it != derivedClasses.end())
        return *it->second.get();

    auto pClassData    = std::make_unique<SClassData>();
    auto pRawClassData = pClassData.get();
    derivedClasses[id] = std::move(pClassData);
    return *pRawClassData;
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
component_t* components<base_component_t>::add(
    std::unique_ptr<component_t> pComponent,
    priority                     ePriority,
    flags<status>                statusFlags) noexcept
{
    if (!pComponent)
        return nullptr;

    auto        pRawComponent = pComponent.get();
    SClassData& classData     = get_or_add_class_data(
        pRawComponent,
        [ePriority, statusFlags, pRawComponent](SClassData& classData)
        {
            classData.priorityCache.emplace(ePriority, typename SClassData::SCacheData(pRawComponent, statusFlags));
        });
    classData.components.push_back(std::move(pComponent));
    return pRawComponent;
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::unique_ptr<base_component_t> components<base_component_t>::remove(const base_component_t* pRawComponent) noexcept
{
    if (!pRawComponent)
        return nullptr;

    SClassData& classData = get_or_add_class_data(
        pRawComponent,
        [pRawComponent](SClassData& classData)
        {
            std::erase_if(
                classData.priorityCache,
                [pRawComponent](const auto& pair)
                {
                    return pair.second.pComponent == pRawComponent;
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
component_t* components<base_component_t>::try_get() noexcept
{
    SClassData& classData = get_or_add_class_data<component_t>();
    const auto  it        = std::ranges::find_if(
        classData.priorityCache,
        [](const auto& pair)
        {
            return !pair.second.statusFlags.contains(status::disabled);
        });

    return it != classData.priorityCache.end() ? static_cast<component_t*>(it->second.pComponent) : nullptr;
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
const component_t* components<base_component_t>::try_get() const noexcept
{
    return QX_CONST_CAST_THIS()->template try_get<component_t>();
}

template<std::derived_from<rtti_pure_base> base_component_t>
base_component_t* components<base_component_t>::try_get(class_identificator id) noexcept
{
    // we could improve it from O(N) to O(log(N)) if we could use id->is_derived_from(id) without an object itself
    // we will do it when a reflection system is fully implemented
    const auto it = std::ranges::find_if(
        m_RootClass.priorityCache,
        [id](const auto& pair)
        {
            return !pair.second.statusFlags.contains(status::disabled)
                   && pair.second.pComponent->is_derived_from_id(id);
        });

    return it != m_RootClass.priorityCache.end() ? it->second.pComponent : nullptr;
}

template<std::derived_from<rtti_pure_base> base_component_t>
const base_component_t* components<base_component_t>::try_get(class_identificator id) const noexcept
{
    return QX_CONST_CAST_THIS()->try_get(id);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
component_t& components<base_component_t>::get() noexcept
{
    SClassData& classData = get_or_add_class_data<component_t>();
    const auto  it        = std::ranges::find_if(
        classData.priorityCache,
        [](const auto& pair)
        {
            return !pair.second.statusFlags.contains(status::disabled);
        });

    return *static_cast<component_t*>(it->second.pComponent);
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
const component_t& components<base_component_t>::get() const noexcept
{
    return QX_CONST_CAST_THIS()->template get<component_t>();
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
auto components<base_component_t>::view() noexcept
{
    SClassData& classData = get_or_add_class_data<component_t>();
    return classData.priorityCache
           | std::views::filter(
               [](const auto& pair)
               {
                   return pair.second.pComponent->template is_derived_from<component_t>()
                          && !pair.second.statusFlags.contains(status::disabled);
               })
           | std::views::transform(
               [](auto& pair) -> component_t&
               {
                   return *static_cast<component_t*>(pair.second.pComponent);
               });
}

template<std::derived_from<rtti_pure_base> base_component_t>
template<std::derived_from<base_component_t> component_t>
auto components<base_component_t>::view() const noexcept
{
    const SClassData& classData = get_or_add_class_data<component_t>();
    return classData.priorityCache
           | std::views::filter(
               [](const auto& pair)
               {
                   return pair.second.pComponent->template is_derived_from<component_t>()
                          && !pair.second.statusFlags.contains(status::disabled);
               })
           | std::views::transform(
               [](const auto& pair) -> const component_t&
               {
                   return *static_cast<const component_t*>(pair.second.pComponent);
               });
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::optional<priority> components<base_component_t>::get_priority(const base_component_t* pRawComponent) const noexcept
{
    if (!pRawComponent)
        return std::nullopt;

    auto it = std::ranges::find_if(
        m_RootClass.priorityCache,
        [pRawComponent](const auto& pair)
        {
            return pair.second.pComponent == pRawComponent;
        });

    return it != m_RootClass.priorityCache.end() ? std::optional<priority>(it->first) : std::nullopt;
}


template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::set_priority(const base_component_t* pRawComponent, priority ePriority) noexcept
{
    if (!pRawComponent)
        return false;

    bool bChanged = true;
    get_or_add_class_data(
        pRawComponent,
        [pRawComponent, ePriority, &bChanged](SClassData& classData)
        {
            const auto it = std::ranges::find_if(
                classData.priorityCache,
                [pRawComponent](const auto& pair)
                {
                    return pair.second.pComponent == pRawComponent;
                });

            if (it == classData.priorityCache.end())
            {
                bChanged = false;
                return;
            }

            if (it->first != ePriority)
            {
                classData.priorityCache.emplace(ePriority, it->second);
                classData.priorityCache.erase(it);
            }
        });

    return bChanged;
}

template<std::derived_from<rtti_pure_base> base_component_t>
std::optional<flags<status>> components<base_component_t>::get_status(
    const base_component_t* pRawComponent) const noexcept
{
    if (!pRawComponent)
        return std::nullopt;

    auto it = std::ranges::find_if(
        m_RootClass.priorityCache,
        [pRawComponent](const auto& pair)
        {
            return pair.second.pComponent == pRawComponent;
        });

    return it != m_RootClass.priorityCache.end() ? std::optional<flags<status>>(it->second.statusFlags) : std::nullopt;
}


template<std::derived_from<rtti_pure_base> base_component_t>
bool components<base_component_t>::set_status(const base_component_t* pRawComponent, flags<status> status) noexcept
{
    if (!pRawComponent)
        return false;

    bool bChanged = true;
    get_or_add_class_data(
        pRawComponent,
        [pRawComponent, status, &bChanged](SClassData& classData)
        {
            const auto it = std::ranges::find_if(
                classData.priorityCache,
                [pRawComponent](const auto& pair)
                {
                    return pair.second.pComponent == pRawComponent;
                });

            if (it == classData.priorityCache.end())
            {
                bChanged = false;
                return;
            }

            it->second.statusFlags = status;
        });

    return bChanged;
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

} // namespace qx
