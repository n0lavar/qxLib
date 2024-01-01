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
#include <qx/rtti/class_identificator.h>
#include <qx/rtti/rtti_naming_strategy.h>

#include <array>
#include <span>

namespace qx
{

namespace details
{

template<class T>
concept has_get_class_id_static = requires(T t) { T::get_class_id_static(); };

} // namespace details

/**
    @brief  Get class id if C is supported qx RTTI system
    @tparam C - class to identify
    @retval   - class id
**/
template<class C>
inline class_identificator get_class_id() noexcept
{
    if constexpr (details::has_get_class_id_static<C>)
    {
        return C::get_class_id_static();
    }
    else
    {
        return std::numeric_limits<class_identificator>::max();
    }
}

// utility class to let you use std::derived_from
class rtti_pure_base
{
public:
    auto operator<=>(const rtti_pure_base&) const = default;
};

/**

    @class   rtti_root
    @brief   RTTI root class
    @details All other classes must be inherited from this class
             to allow you to use RTTI functions
    @tparam  derived_base_t    - derived class type
    @tparam  naming_strategy_t - \see rtti_naming_strategy.h
    @author  Khrapov
    @date    10.09.2021

**/
template<class derived_base_t, template<string_literal> class naming_strategy_t = rtti_naming_strategy_class_name>
class rtti_root : public rtti_pure_base
{
public:
    using base_class_type   = derived_base_t;
    using super_class_type  = derived_base_t;
    using this_class_type   = derived_base_t;
    using inheritance_tuple = std::tuple<rtti_root>;

public:
    rtti_root() noexcept                 = default;
    rtti_root(const rtti_root&) noexcept = default;
    rtti_root(rtti_root&&) noexcept      = default;

    template<class rtti_type>
    bool is_derived_from() const noexcept
    {
        return _is_base_id(qx::get_class_id<rtti_type>()) || qx::get_class_id<rtti_type>() == get_class_id();
    }

    template<class rtti_type>
    bool is() const noexcept
    {
        return get_class_id() == rtti_type::get_class_id_static();
    }

    bool is(string_view svClassName) const noexcept
    {
        return svClassName == get_class_name();
    }

    bool is(class_identificator id) const noexcept
    {
        return id == get_class_id();
    }

    virtual bool is_derived_from_id(class_identificator id) const noexcept
    {
        return id == get_class_id_static();
    }

    static constexpr string_view get_class_name_static() noexcept
    {
        return _get_class_name_by_strategy<QX_TEXT(QX_STRINGIFY(rtti_root))>();
    }

    virtual string_view get_class_name() const noexcept
    {
        return get_class_name_static();
    }

    static constexpr class_identificator get_class_id_static() noexcept
    {
        return 0;
    }

    virtual class_identificator get_class_id() const noexcept
    {
        return get_class_id_static();
    }

    virtual std::span<const class_identificator> get_inheritance_sequence() const = 0;

    auto operator<=>(const rtti_root&) const = default;

protected:
    virtual ~rtti_root() noexcept = default;

    virtual bool _is_base_id(class_identificator idBase) const noexcept
    {
        return idBase == get_class_id_static();
    }

    template<string_literal DerivedName>
    static constexpr string_view _get_class_name_by_strategy() noexcept
    {
        return naming_strategy_t<DerivedName>::get_name();
    }
};

/**
    @def   QX_RTTI_CLASS
    @brief Macro for every class inherited from class with QX_RTTI_BASE_CLASS macro
    @param thisClass  - this class name
    @param ...        - super class name (must implement QX_RTTI_CLASS or QX_RTTI_BASE_CLASS macro)
**/
#define QX_RTTI_CLASS(thisClass, ...)                                                                           \
                                                                                                                \
public:                                                                                                         \
    using this_class_type   = thisClass;                                                                        \
    using super_class_type  = __VA_ARGS__;                                                                      \
    using base_class_type   = typename super_class_type::base_class_type;                                       \
    using inheritance_tuple = qx::tuple::join_t<typename super_class_type::inheritance_tuple, this_class_type>; \
                                                                                                                \
public:                                                                                                         \
    virtual bool is_derived_from_id(qx::class_identificator id) const noexcept override                         \
    {                                                                                                           \
        return id == get_class_id_static() || super_class_type::is_derived_from_id(id);                         \
    }                                                                                                           \
    static constexpr qx::string_view get_class_name_static() noexcept                                           \
    {                                                                                                           \
        return base_class_type::template _get_class_name_by_strategy<QX_TEXT(QX_STRINGIFY(thisClass))>();       \
    }                                                                                                           \
    virtual qx::class_identificator get_class_id() const noexcept override                                      \
    {                                                                                                           \
        return get_class_id_static();                                                                           \
    }                                                                                                           \
    static constexpr qx::class_identificator get_class_id_static() noexcept                                     \
    {                                                                                                           \
        return QX_STRING_HASH(#thisClass);                                                                      \
    }                                                                                                           \
    virtual qx::string_view get_class_name() const noexcept override                                            \
    {                                                                                                           \
        return get_class_name_static();                                                                         \
    }                                                                                                           \
    virtual std::span<const qx::class_identificator> get_inheritance_sequence() const override                  \
    {                                                                                                           \
        static constexpr auto ids = []()                                                                        \
        {                                                                                                       \
            std::array<qx::class_identificator, std::tuple_size_v<inheritance_tuple>> ids_;                     \
            qx::tuple::iterate<inheritance_tuple>(                                                              \
                [&ids_]<class T, size_t I>()                                                                    \
                {                                                                                               \
                    ids_[I] = T::get_class_id_static();                                                         \
                });                                                                                             \
            return ids_;                                                                                        \
        }();                                                                                                    \
        return ids;                                                                                             \
    }                                                                                                           \
                                                                                                                \
protected:                                                                                                      \
    virtual bool _is_base_id(qx::class_identificator base_id) const noexcept override                           \
    {                                                                                                           \
        return base_id == qx::get_class_id<super_class_type>() || super_class_type::_is_base_id(base_id);       \
    }                                                                                                           \
                                                                                                                \
private:

} // namespace qx
