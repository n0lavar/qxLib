/**

    @file      rtti.h
    @brief     RTTI system based on polymorphism
    @details   Using QX_RTTI_BASE_CLASS and QX_RTTI_CLASS macros
               will let you to use RTTI advantages without enabling RTTI in compiler's flags
               common logic is taken from
               https://github.com/qualab/xakep-RTTI (Vladimir Kerimov, qualab)
               
    @author    Khrapov
    @date      24.08.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/suppress_warnings.h>

namespace qx
{

using class_identificator = int;

namespace detail
{

template<typename T>
concept has_get_class_id_static = requires(T t)
{
    T::get_class_id_static();
};

template<typename T, typename From>
concept has_is_derived_from = requires(T* t)
{
    t->template is_derived_from<From>();
};

} // namespace detail

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

} // namespace qx

namespace qx
{

/**
    @brief   Returns Y* if Y is inherited from pointer class, otherwise nullptr
    @details Pointer class should contain QX_RTTI_CLASS
    @tparam  Y       - type to cast to
    @param   pointer - unique or shared pointer
    @retval          - Y* if Y is inherited from pointer class, otherwise nullptr
**/
template<typename Y>
Y* rtti_cast(auto& pointer)
{
    using smart_pointer_t =
        typename std::remove_reference_t<decltype(pointer)>::element_type;
    if constexpr (detail::has_is_derived_from<smart_pointer_t, Y>)
        if (pointer && pointer->template is_derived_from<Y>())
            return static_cast<Y*>(pointer.get());

    return nullptr;
}

/**
    @brief   Returns Y* if Y is inherited from pointer class, otherwise nullptr
    @details Pointer class should contain QX_RTTI_CLASS
    @tparam  Y       - type to cast to
    @tparam  X       - type to cast from
    @param   pointer - raw pointer
    @retval          - Y* if Y is inherited from pointer class, otherwise nullptr
**/
template<typename Y, typename X>
Y* rtti_cast(X* pointer)
{
    if constexpr (detail::has_is_derived_from<X, Y>)
        if (pointer && pointer->template is_derived_from<Y>())
            return static_cast<Y*>(pointer);

    return nullptr;
}

} // namespace qx

#ifndef QX_RTTI_CLASS_NAME
    #define QX_RTTI_CLASS_NAME(className) #className
#endif

/**
    @def   QX_RTTI_BASE_CLASS
    @brief Macro for your root class. All other classes must be inherited from
           thisClass to allow you to use RTTI functions
    @param thisClass - this class name
**/
#define QX_RTTI_BASE_CLASS(thisClass)                                          \
public:                                                                        \
    using SuperClass = thisClass;                                              \
    using BaseClass  = thisClass;                                              \
    using ThisClass  = thisClass;                                              \
                                                                               \
    template<typename RTTI_TYPE>                                               \
    bool is_derived_from() const noexcept                                      \
    {                                                                          \
        return is_base_id(qx::get_class_id<RTTI_TYPE>())                       \
               || qx::get_class_id<RTTI_TYPE>() == get_class_id();             \
    }                                                                          \
                                                                               \
    virtual bool is_derived_from_id(qx::class_identificator id) const noexcept \
    {                                                                          \
        return id == get_class_id_static();                                    \
    }                                                                          \
                                                                               \
    static constexpr std::string_view get_class_name_static(void) noexcept     \
    {                                                                          \
        return QX_RTTI_CLASS_NAME(thisClass);                                  \
    }                                                                          \
                                                                               \
    virtual std::string_view get_class_name(void) const noexcept               \
    {                                                                          \
        return get_class_name_static();                                        \
    }                                                                          \
                                                                               \
    static qx::class_identificator get_class_id_static(void) noexcept          \
    {                                                                          \
        static qx::class_identificator nId = get_next_id();                    \
        return nId;                                                            \
    }                                                                          \
                                                                               \
    virtual int get_class_id(void) const noexcept                              \
    {                                                                          \
        return get_class_id_static();                                          \
    }                                                                          \
                                                                               \
protected:                                                                     \
    virtual bool is_base_id(qx::class_identificator base_id) const noexcept    \
    {                                                                          \
        return base_id == get_class_id_static();                               \
    }                                                                          \
                                                                               \
    static qx::class_identificator get_next_id(void) noexcept                  \
    {                                                                          \
        static qx::class_identificator nId = 0;                                \
        return nId++;                                                          \
    }

/**
    @def   QX_RTTI_CLASS
    @brief Macro for every class inherited from class with QX_RTTI_BASE_CLASS macro
    @param thisClass  - this class name
    @param superClass - super class name (must implement QX_RTTI_CLASS or QX_RTTI_BASE_CLASS macro)
**/
#define QX_RTTI_CLASS(thisClass, superClass)                                   \
                                                                               \
public:                                                                        \
    using SuperClass = superClass;                                             \
    using BaseClass  = SuperClass::BaseClass;                                  \
    using ThisClass  = thisClass;                                              \
                                                                               \
    virtual bool is_derived_from_id(qx::class_identificator id)                \
        const noexcept override                                                \
    {                                                                          \
        return id == get_class_id_static()                                     \
               || SuperClass::is_derived_from_id(id);                          \
    }                                                                          \
                                                                               \
    static constexpr std::string_view get_class_name_static(void) noexcept     \
    {                                                                          \
        return QX_RTTI_CLASS_NAME(thisClass);                                  \
    }                                                                          \
                                                                               \
    virtual qx::class_identificator get_class_id(void) const noexcept override \
    {                                                                          \
        return get_class_id_static();                                          \
    }                                                                          \
                                                                               \
    static qx::class_identificator get_class_id_static(void) noexcept          \
    {                                                                          \
        static qx::class_identificator nId = get_next_id();                    \
        return nId;                                                            \
    }                                                                          \
                                                                               \
    virtual std::string_view get_class_name(void) const noexcept override      \
    {                                                                          \
        return get_class_name_static();                                        \
    }                                                                          \
                                                                               \
protected:                                                                     \
    virtual bool is_base_id(qx::class_identificator base_id)                   \
        const noexcept override                                                \
    {                                                                          \
        return base_id == qx::get_class_id<SuperClass>()                       \
               || SuperClass::is_base_id(base_id);                             \
    }
