//==============================================================================
//
//!\file                            rtti.h
//
//!\brief       Using QX_RTTI_CLASS_BASE and QX_RTTI_CLASS macros
//              will let you to use RTTI advantages without enabling RTTI in compiler's flags
//!\details     common logic is taken from
//              https://github.com/qualab/xakep-RTTI (Vladimir Kerimov, qualab)
//
//!\author      Khrapov
//!\date        24.08.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/suppress_warnings.h>

#include <string_view>
#include <type_traits>

namespace qx
{

namespace detail
{
    template<typename T>
    concept has_get_class_id_static = requires(T t) { T::get_class_id_static(); };

    template<typename T, typename From>
    concept has_is_derived_from = requires(T* t) { t->template is_derived_from<From>(); };
}

template<class C>
inline int get_class_id(void) noexcept
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

template <typename X>
struct is_derived
{
    template <typename Y>
    static bool from() noexcept
    {
        if constexpr (detail::has_get_class_id_static<X> && detail::has_get_class_id_static<Y>)
        {
            return X::get_class_id_static() == Y::get_class_id_static() ||
                is_derived<typename X::SuperClass>::template from<Y>();
        }
        else
        {
            return false;
        }
    }
};

}

#ifndef QX_RTTI_CLASS_NAME
    #define QX_RTTI_CLASS_NAME(className) # className
#endif

namespace qx
{

//==============================================================================
//
//!\class                        qx::rtti_base
//
//!\brief   Base class for rtti system
//!\details ~
//
//!\author  Khrapov
//!\date    7.01.2021
//
//==============================================================================
class rtti_base
{
public:

    using SuperClass = rtti_base;
    using BaseClass  = rtti_base;
    using ThisClass  = rtti_base;

    virtual ~rtti_base() noexcept = default;

    template <typename RTTI_TYPE>
    bool is_derived_from() const noexcept
    {
        return is_base_id(qx::get_class_id<RTTI_TYPE>()) ||
               qx::get_class_id<RTTI_TYPE>() == get_class_id();
    }

    static constexpr std::string_view get_class_name_static(void) noexcept
    {
        return QX_RTTI_CLASS_NAME(rtti_base);
    }

    virtual std::string_view get_class_name(void) const noexcept
    {
        return get_class_name_static();
    }

    static int get_class_id_static(void) noexcept
    {
        static int nId = get_next_id();
        return nId;
    }

    virtual int get_class_id(void) const noexcept
    {
        return get_class_id_static();
    }

protected:

    virtual bool is_base_id(int base_id) const noexcept
    {
        return base_id == get_class_id_static();
    }

    static int get_next_id(void) noexcept
    {
        static int nId = 0;
        return nId++;
    }
};

template <>
struct is_derived<rtti_base>
{
    template <typename Y>
    static bool from() noexcept
    {
        if constexpr (detail::has_get_class_id_static<Y>)
            return rtti_base::get_class_id_static() == Y::get_class_id_static();
        else
            return false;
    }
};

//==============================================================================
//!\fn                          qx::rtti_cast<Y>
//
//!\brief   Returns Y* if Y is inherited from pointer class, otherwise nullptr
//!\details Pointer class should contain QX_RTTI_CLASS
//!\param   pointer - unique or shader pointer
//!\retval          - Y* if Y is inherited from pointer class, otherwise nullptr
//!\author  Khrapov
//!\date    5.02.2021
//==============================================================================
template<typename Y>
Y* rtti_cast(auto& pointer)
{
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4946)

    // the class of this pointer is guaranteed to inherit from Y
    // by is_derived_from(), reinterpret_cast is for successful compilation only
    using smart_pointer_t = typename std::remove_reference_t<decltype(pointer)>::element_type;
    if constexpr (detail::has_is_derived_from<smart_pointer_t, Y>)
        if (pointer && pointer->is_derived_from<Y>())
            return reinterpret_cast<Y*>(pointer.get());

    return nullptr;

    QX_POP_SUPPRESS_WARNINGS
}

//==============================================================================
//!\fn                         qx::rtti_cast<Y, X>
//
//!\brief   Returns Y* if Y is inherited from pointer class, otherwise nullptr
//!\details Pointer class should contain QX_RTTI_CLASS
//!\param   pointer - raw pointer
//!\retval          - Y* if Y is inherited from pointer class, otherwise nullptr
//!\author  Khrapov
//!\date    5.02.2021
//==============================================================================
template<typename Y, typename X>
Y* rtti_cast(X* pointer)
{
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4946)

    // the class of this pointer is guaranteed to inherit from Y
    // by is_derived_from(), reinterpret_cast is for successful compilation only
    if constexpr (detail::has_is_derived_from<X, Y>)
        if (pointer && pointer->is_derived_from<Y>())
            return reinterpret_cast<Y*>(pointer);

    return nullptr;

    QX_POP_SUPPRESS_WARNINGS
}

}


#define QX_RTTI_CLASS(thisClass, superClass)                                \
                                                                            \
public:                                                                     \
                                                                            \
    using SuperClass = superClass;                                          \
    using BaseClass  = SuperClass::BaseClass;                               \
    using ThisClass  = thisClass;                                           \
                                                                            \
    static constexpr std::string_view get_class_name_static(void) noexcept  \
    {                                                                       \
        return QX_RTTI_CLASS_NAME(thisClass);                               \
    }                                                                       \
                                                                            \
    virtual int get_class_id(void) const noexcept override                  \
    {                                                                       \
        return get_class_id_static();                                       \
    }                                                                       \
                                                                            \
    static int get_class_id_static(void) noexcept                           \
    {                                                                       \
        static int nId = get_next_id();                                     \
        return nId;                                                         \
    }                                                                       \
                                                                            \
    virtual std::string_view get_class_name(void) const noexcept override   \
    {                                                                       \
        return get_class_name_static();                                     \
    }                                                                       \
                                                                            \
protected:                                                                  \
                                                                            \
    virtual bool is_base_id(int base_id) const noexcept override            \
    {                                                                       \
        return base_id == qx::get_class_id<SuperClass>() ||                 \
               SuperClass::is_base_id(base_id);                             \
    }
