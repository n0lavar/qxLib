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

#include <qx/rtti/rtti_creator_strategy.h>
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
    @tparam  _CreatorStrategy - \see rtti_creator_strategy.h
    @tparam  _NamingStrategy  - \see rtti_naming_strategy.h
    @tparam  Args             - arguments for derived class instance creation
    @author  Khrapov
    @date    10.09.2021

**/
template<
    class _DerivedBase,
    template<class, class> class _CreatorStrategy = rtti_stub_creator,
    template<string_literal> class _NamingStrategy =
        rtti_naming_strategy_class_name,
    class... Args>
class rtti_root : public _CreatorStrategy<_DerivedBase, Args...>
{
public:
    using BaseClass       = _DerivedBase;
    using SuperClass      = _DerivedBase;
    using ThisClass       = _DerivedBase;
    using CreatorStrategy = _CreatorStrategy<_DerivedBase, Args...>;

public:
    template<typename RTTI_TYPE>
    bool is_derived_from() const noexcept
    {
        return _is_base_id(qx::get_class_id<RTTI_TYPE>())
               || qx::get_class_id<RTTI_TYPE>() == get_class_id();
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

    static bool _register_class(
        typename CreatorStrategy::factory factory,
        class_identificator               id,
        std::string_view                  svName)
    {
        if (factory && !svName.empty())
            return CreatorStrategy::register_class(factory, id, svName);
        else
            return false;
    }

    static class_identificator _get_next_id()
    {
        static class_identificator nId = 1;
        return nId++;
    }

    template<class Derived>
    static std::unique_ptr<BaseClass> _create_object(Args&&... args)
    {
        if constexpr (std::is_constructible_v<Derived, Args...>)
            return std::make_unique<Derived>(std::forward<Args>(args)...);
        else
            return nullptr;
    }

    template<string_literal DerivedName>
    static constexpr std::string_view _get_class_name_by_strategy()
    {
        return _NamingStrategy<DerivedName>::get_name();
    }
};

/**
    @def   QX_RTTI_CLASS
    @brief Macro for every class inherited from class with QX_RTTI_BASE_CLASS macro
    @param thisClass  - this class name
    @param superClass - super class name (must implement QX_RTTI_CLASS or QX_RTTI_BASE_CLASS macro)
**/
#define QX_RTTI_CLASS(thisClass, superClass)                                   \
                                                                               \
public:                                                                        \
    using BaseClass  = SuperClass::BaseClass;                                  \
    using SuperClass = superClass;                                             \
    using ThisClass  = thisClass;                                              \
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
        return _get_class_name_by_strategy<QX_STRINGIFY(thisClass)>();         \
    }                                                                          \
                                                                               \
    virtual qx::class_identificator get_class_id(void) const noexcept override \
    {                                                                          \
        return get_class_id_static();                                          \
    }                                                                          \
                                                                               \
    static qx::class_identificator get_class_id_static(void) noexcept          \
    {                                                                          \
        static auto id = _get_next_id();                                       \
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
    }                                                                          \
                                                                               \
private:                                                                       \
    static inline bool m_bRegistered = _register_class(                        \
        _create_object<ThisClass>,                                             \
        get_class_id_static(),                                                 \
        get_class_name_static());

} // namespace qx
