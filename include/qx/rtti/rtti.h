/**

    @file      rtti.h
    @brief     RTTI system based on polymorphism
    @details   Using qx::rtti_root and QX_RTTI_CLASS
               will let you to use RTTI advantages without enabling
               RTTI in compiler's flags
               common logic is taken from
               https://github.com/qualab/xakep-RTTI (Vladimir Kerimov, qualab)
    @author    Khrapov
    @date      24.08.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_hash.h>
#include <qx/macros/common.h>
#include <qx/meta/tuple_utils.h>
#include <qx/rtti/class_id.h>
#include <qx/rtti/rtti_naming_strategy.h>

#include <array>
#include <span>

namespace qx
{

// utility class to let you use std::derived_from
class rtti_pure_base
{
    template<class naming_strategy_t>
    friend class rtti_root;

public:
    auto operator<=>(const rtti_pure_base&) const = default;

protected:
    rtti_pure_base() = default;
};

/**

    @class   rtti_root
    @brief   RTTI root class
    @details All other classes must be inherited from this class
             to allow you to use RTTI functions
    @tparam  naming_strategy_t - \see rtti_naming_strategy.h
    @author  Khrapov
    @date    10.09.2021

**/
template<class naming_strategy_t = rtti_naming_strategy_class_name>
class rtti_root : public rtti_pure_base
{
public:
    using base_class_type        = rtti_root;
    using super_class_type       = rtti_root;
    using this_class_type        = rtti_root;
    using inheritance_tuple_type = std::tuple<this_class_type>;
    using naming_strategy_type   = naming_strategy_t;

public:
    rtti_root() noexcept                 = default;
    rtti_root(const rtti_root&) noexcept = default;
    rtti_root(rtti_root&&) noexcept      = default;

    template<class T>
    bool is_derived_from() const noexcept
    {
        constexpr class_id typeId = T::get_class_id_static();
        return _is_base_id(typeId) || typeId == get_class_id();
    }

    template<class T>
    bool is() const noexcept
    {
        return get_class_id() == T::get_class_id_static();
    }

    bool is(string_view svClassName) const noexcept
    {
        return svClassName == get_class_name();
    }

    bool is(class_id id) const noexcept
    {
        return id == get_class_id();
    }

    virtual bool is_derived_from_id(class_id id) const noexcept
    {
        return is_derived_from_id_static(id);
    }

    static constexpr bool is_derived_from_id_static(class_id id) noexcept
    {
        return id == get_class_id_static();
    }

    static constexpr string_view get_class_name_static() noexcept
    {
        return naming_strategy_type::get_name(type_strings<this_class_type>::get_signature());
    }

    virtual string_view get_class_name() const noexcept
    {
        return get_class_name_static();
    }

    static constexpr class_id get_class_id_static() noexcept
    {
        return class_id::create<this_class_type>();
    }

    virtual class_id get_class_id() const noexcept
    {
        return get_class_id_static();
    }

    virtual std::span<const class_id> get_inheritance_sequence() const = 0;

    auto operator<=>(const rtti_root&) const = default;

protected:
    virtual ~rtti_root() noexcept = default;

    virtual bool _is_base_id(class_id idBase) const noexcept
    {
        return idBase == get_class_id_static();
    }
};

namespace filters
{

template<class T>
constexpr auto rtti()
{
    return [](const auto& value)
    {
        return value.template is_derived_from<T>();
    };
}

} // namespace filters


/**
    @def   QX_RTTI_CLASS
    @brief Macro for every class inherited from class with QX_RTTI_BASE_CLASS macro
    @param thisClass  - this class name
    @param ...        - super class name (must implement QX_RTTI_CLASS or QX_RTTI_BASE_CLASS macro)
**/
#define QX_RTTI_CLASS(thisClass, ...)                                                                               \
                                                                                                                    \
public:                                                                                                             \
    using this_class_type  = thisClass;                                                                             \
    using super_class_type = __VA_ARGS__;                                                                           \
    using base_class_type  = typename super_class_type::base_class_type;                                            \
    using inheritance_tuple_type =                                                                                  \
        qx::tuple::join_t<typename super_class_type::inheritance_tuple_type, this_class_type>;                      \
                                                                                                                    \
public:                                                                                                             \
    static constexpr bool is_derived_from_id_static(qx::class_id id) noexcept                                       \
    {                                                                                                               \
        return id == get_class_id_static() || super_class_type::is_derived_from_id_static(id);                      \
    }                                                                                                               \
    virtual bool is_derived_from_id(qx::class_id id) const noexcept override                                        \
    {                                                                                                               \
        return is_derived_from_id_static(id);                                                                       \
    }                                                                                                               \
    static constexpr qx::string_view get_class_name_static() noexcept                                               \
    {                                                                                                               \
        return base_class_type::naming_strategy_type::get_name(qx::type_strings<this_class_type>::get_signature()); \
    }                                                                                                               \
    virtual qx::class_id get_class_id() const noexcept override                                                     \
    {                                                                                                               \
        return get_class_id_static();                                                                               \
    }                                                                                                               \
    static constexpr qx::class_id get_class_id_static() noexcept                                                    \
    {                                                                                                               \
        return qx::class_id::create<this_class_type>();                                                             \
    }                                                                                                               \
    virtual qx::string_view get_class_name() const noexcept override                                                \
    {                                                                                                               \
        return get_class_name_static();                                                                             \
    }                                                                                                               \
    virtual std::span<const qx::class_id> get_inheritance_sequence() const override                                 \
    {                                                                                                               \
        static constexpr auto ids = []()                                                                            \
        {                                                                                                           \
            std::array<qx::class_id, std::tuple_size_v<inheritance_tuple_type>> ids_;                               \
            qx::tuple::iterate<inheritance_tuple_type>(                                                             \
                [&ids_]<class T, size_t I>()                                                                        \
                {                                                                                                   \
                    ids_[I] = T::get_class_id_static();                                                             \
                });                                                                                                 \
            return ids_;                                                                                            \
        }();                                                                                                        \
        return ids;                                                                                                 \
    }                                                                                                               \
                                                                                                                    \
protected:                                                                                                          \
    virtual bool _is_base_id(qx::class_id base_id) const noexcept override                                          \
    {                                                                                                               \
        return base_id == super_class_type::get_class_id_static() || super_class_type::_is_base_id(base_id);        \
    }                                                                                                               \
                                                                                                                    \
private:                                                                                                            \
    QX_EMPTY_MACRO

} // namespace qx
