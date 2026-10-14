/**

    @file      rtti.inl
    @author    Khrapov
    @date      14.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

template<class naming_strategy_t>
template<class T>
inline bool rtti_root<naming_strategy_t>::is_derived_from() const noexcept
{
    constexpr class_id typeId = T::get_class_id_static();
    return _is_base_id(typeId) || typeId == get_class_id();
}

template<class naming_strategy_t>
template<class T>
inline bool rtti_root<naming_strategy_t>::is() const noexcept
{
    return get_class_id() == T::get_class_id_static();
}

template<class naming_strategy_t>
inline bool rtti_root<naming_strategy_t>::is(string_view svClassName) const noexcept
{
    return svClassName == get_class_name();
}

template<class naming_strategy_t>
inline bool rtti_root<naming_strategy_t>::is(const class_id& id) const noexcept
{
    return id == get_class_id();
}

template<class naming_strategy_t>
inline bool rtti_root<naming_strategy_t>::is_derived_from_id(const class_id& id) const noexcept
{
    return is_derived_from_id_static(id);
}

template<class naming_strategy_t>
constexpr bool rtti_root<naming_strategy_t>::is_derived_from_id_static(const class_id& id) noexcept
{
    return id == get_class_id_static();
}

template<class naming_strategy_t>
constexpr string_view rtti_root<naming_strategy_t>::get_class_name_static() noexcept
{
    return naming_strategy_type::get_name(type_strings<this_class_type>::get_signature());
}

template<class naming_strategy_t>
inline string_view rtti_root<naming_strategy_t>::get_class_name() const noexcept
{
    return get_class_name_static();
}

template<class naming_strategy_t>
constexpr class_id rtti_root<naming_strategy_t>::get_class_id_static() noexcept
{
    constexpr class_id id = class_id::create<this_class_type>();
    return id;
}

template<class naming_strategy_t>
inline class_id rtti_root<naming_strategy_t>::get_class_id() const noexcept
{
    return get_class_id_static();
}

template<class naming_strategy_t>
inline bool rtti_root<naming_strategy_t>::_is_base_id(const class_id& idBase) const noexcept
{
    return idBase == get_class_id_static();
}

} // namespace qx
