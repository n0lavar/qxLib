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

#include <qx/rtti/class_identificator.h>
#include <qx/rtti/rtti_naming_strategy.h>
#include <qx/useful_macros.h>

namespace qx
{

namespace detail
{

template<typename T>
concept has_get_class_id_static = requires(T t)
{
    T::get_class_id_static();
};

} // namespace detail

/**
    @brief  Get class id if C is supported qx RTTI system
    @tparam C - class to identify
    @retval   - class id
**/
template<class C>
inline class_identificator get_class_id(void) noexcept
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
    @tparam  _DerivedBase     - derived class type
    @tparam  _NamingStrategy  - \see rtti_naming_strategy.h
    @author  Khrapov
    @date    10.09.2021

**/
template<
    class _DerivedBase,
    template<string_literal> class _NamingStrategy =
        rtti_naming_strategy_class_name>
class rtti_root
{
public:
    using BaseClass  = _DerivedBase;
    using SuperClass = _DerivedBase;
    using ThisClass  = _DerivedBase;

public:
    template<typename RTTI_TYPE>
    bool is_derived_from() const noexcept
    {
        return _is_base_id(qx::get_class_id<RTTI_TYPE>())
               || qx::get_class_id<RTTI_TYPE>() == get_class_id();
    }

    template<typename RTTI_TYPE>
    bool is() const noexcept
    {
        return get_class_id() == RTTI_TYPE::get_class_id_static();
    }

    virtual bool is_derived_from_id(class_identificator id) const noexcept
    {
        return id == get_class_id_static();
    }

    static constexpr std::string_view get_class_name_static(void) noexcept
    {
        return _get_class_name_by_strategy<QX_STRINGIFY(rtti_root)>();
    }

    virtual std::string_view get_class_name(void) const noexcept
    {
        return get_class_name_static();
    }

    static class_identificator get_class_id_static(void) noexcept
    {
        return 0;
    }

    virtual int get_class_id(void) const noexcept
    {
        return get_class_id_static();
    }

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
    static constexpr std::string_view _get_class_name_by_strategy() noexcept
    {
        return _NamingStrategy<DerivedName>::get_name();
    }
};

/**
    @def   QX_RTTI_CLASS
    @brief Macro for every class inherited from class with QX_RTTI_BASE_CLASS macro
    @param thisClass  - this class name
    @param ...        - super class name (must implement QX_RTTI_CLASS or QX_RTTI_BASE_CLASS macro)
**/
#define QX_RTTI_CLASS(thisClass, ...)                                          \
                                                                               \
public:                                                                        \
    using ThisClass  = thisClass;                                              \
    using SuperClass = __VA_ARGS__;                                            \
    using BaseClass  = typename SuperClass::BaseClass;                         \
                                                                               \
public:                                                                        \
    virtual bool is_derived_from_id(qx::class_identificator id)                \
        const noexcept override                                                \
    {                                                                          \
        return id == get_class_id_static()                                     \
               || SuperClass::is_derived_from_id(id);                          \
    }                                                                          \
                                                                               \
    static constexpr std::string_view get_class_name_static(void) noexcept     \
    {                                                                          \
        return BaseClass::template _get_class_name_by_strategy<QX_STRINGIFY(   \
            thisClass)>();                                                     \
    }                                                                          \
                                                                               \
    virtual qx::class_identificator get_class_id(void) const noexcept override \
    {                                                                          \
        return get_class_id_static();                                          \
    }                                                                          \
                                                                               \
    static qx::class_identificator get_class_id_static(void) noexcept          \
    {                                                                          \
        static auto id = BaseClass::_get_next_id();                            \
        return id;                                                             \
    }                                                                          \
                                                                               \
    virtual std::string_view get_class_name(void) const noexcept override      \
    {                                                                          \
        return get_class_name_static();                                        \
    }                                                                          \
                                                                               \
protected:                                                                     \
    virtual bool _is_base_id(qx::class_identificator base_id)                  \
        const noexcept override                                                \
    {                                                                          \
        return base_id == qx::get_class_id<SuperClass>()                       \
               || SuperClass::_is_base_id(base_id);                            \
    }

} // namespace qx
