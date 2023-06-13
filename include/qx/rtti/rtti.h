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

#include <qx/macros/common.h>
#include <qx/rtti/class_identificator.h>
#include <qx/rtti/rtti_naming_strategy.h>

namespace qx
{

namespace detail
{

template<class T>
concept has_get_class_id_static = requires(T t) { T::get_class_id_static(); };

} // namespace detail

/**
    @brief  Get class id if C is supported qx RTTI system
    @tparam C - class to identify
    @retval   - class id
**/
template<class C>
inline class_identificator get_class_id() noexcept
{
    if constexpr (detail::has_get_class_id_static<C>)
    {
        return C::get_class_id_static();
    }
    else
    {
        return -1;
    }
}

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
class rtti_root
{
public:
    using BaseClass  = derived_base_t;
    using SuperClass = derived_base_t;
    using ThisClass  = derived_base_t;

public:
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

    static class_identificator get_class_id_static() noexcept
    {
        return 0;
    }

    virtual int get_class_id() const noexcept
    {
        return get_class_id_static();
    }

    auto operator<=>(const rtti_root&) const = default;

protected:
    virtual ~rtti_root() noexcept = default;

    virtual bool _is_base_id(class_identificator idBase) const noexcept
    {
        return idBase == get_class_id_static();
    }

    static class_identificator _get_next_id() noexcept
    {
        static class_identificator nId = get_class_id_static() + 1;
        return nId++;
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
#define QX_RTTI_CLASS(thisClass, ...)                                                               \
                                                                                                    \
public:                                                                                             \
    using ThisClass  = thisClass;                                                                   \
    using SuperClass = __VA_ARGS__;                                                                 \
    using BaseClass  = typename SuperClass::BaseClass;                                              \
                                                                                                    \
public:                                                                                             \
    virtual bool is_derived_from_id(qx::class_identificator id) const noexcept override             \
    {                                                                                               \
        return id == get_class_id_static() || SuperClass::is_derived_from_id(id);                   \
    }                                                                                               \
                                                                                                    \
    static constexpr qx::string_view get_class_name_static() noexcept                               \
    {                                                                                               \
        return BaseClass::template _get_class_name_by_strategy<QX_TEXT(QX_STRINGIFY(thisClass))>(); \
    }                                                                                               \
                                                                                                    \
    virtual qx::class_identificator get_class_id() const noexcept override                          \
    {                                                                                               \
        return get_class_id_static();                                                               \
    }                                                                                               \
                                                                                                    \
    static qx::class_identificator get_class_id_static() noexcept                                   \
    {                                                                                               \
        static auto id = BaseClass::_get_next_id();                                                 \
        return id;                                                                                  \
    }                                                                                               \
                                                                                                    \
    virtual qx::string_view get_class_name() const noexcept override                                \
    {                                                                                               \
        return get_class_name_static();                                                             \
    }                                                                                               \
                                                                                                    \
protected:                                                                                          \
    virtual bool _is_base_id(qx::class_identificator base_id) const noexcept override               \
    {                                                                                               \
        return base_id == qx::get_class_id<SuperClass>() || SuperClass::_is_base_id(base_id);       \
    }                                                                                               \
                                                                                                    \
private:

} // namespace qx
