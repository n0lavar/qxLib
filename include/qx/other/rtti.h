//==============================================================================
//
//!\file                            rtti.h
//
//!\brief       Using QX_RTTI_CLASS_BASE and QX_RTTI_CLASS_DERIVED macros
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

#include <qx/other/constexpr_conter.h>

namespace qx
{

template<class C>
inline constexpr int get_class_id(void)
{
    return -1;
}

template <typename X>
struct is_derived
{
    template <typename Y>
    static constexpr bool from() noexcept
    {
        return qx::get_class_id<X>() == qx::get_class_id<Y>() ||
               is_derived<typename X::SuperClass>::template from<Y>();
    }
};

using class_counter = constexpr_counter<struct class_counter_tag>;

}

// defining this macros in required classes allows to use:
//
// qx::get_class_id<name>():    returns constexpr unique id of each class, 
//                              you can use it in "switch" or "if" with object->get_class_id()
//                              returns -1 if class is not registrated
//
// qx::is_derived<class_1>::from<class_1>():
//                              returns constexpr true if class_1 derived from class_1
//
// pObject->is_derived_from<base>(): 
//                              replacement for if (auto pBase = dynamic_cast<base*>(pObject))
//                              returns true if class of pObject is derived from base type of pObject is base
//
// name::BaseClass              base class
// name::SuperClass             super blass
// name::ThisClass              this class

// define this macro in the end of the base class
#define QX_RTTI_CLASS_BASE(base)                                            \
                                                                            \
public:                                                                     \
                                                                            \
    using SuperClass = base;                                                \
    using BaseClass  = base;                                                \
    using ThisClass  = base;                                                \
                                                                            \
    template<class RTTI_TYPE>                                               \
    friend constexpr int qx::get_class_id(void);                            \
                                                                            \
    template <typename RTTI_TYPE>                                           \
    bool is_derived_from() const noexcept                                   \
    {                                                                       \
        return is_base_id(qx::get_class_id<RTTI_TYPE>()) ||                 \
               qx::get_class_id<RTTI_TYPE>() == get_class_id();             \
    }                                                                       \
                                                                            \
    virtual int get_class_id(void) const noexcept;                          \
                                                                            \
protected:                                                                  \
                                                                            \
    virtual bool is_base_id(int base_id) const noexcept;                    \
                                                                            \
private:                                                                    \
                                                                            \
    static constexpr int s_ClassId = qx::class_counter::next();             \
};                                                                          \
                                                                            \
namespace qx                                                                \
{                                                                           \
    template<>                                                              \
    inline constexpr int get_class_id<base>(void)                           \
    {                                                                       \
        return base::s_ClassId;                                             \
    }                                                                       \
                                                                            \
    template <>                                                             \
    struct is_derived<base>                                                 \
    {                                                                       \
        template <typename Y>                                               \
        static constexpr bool from() noexcept                               \
        {                                                                   \
            return qx::get_class_id<base>() == qx::get_class_id<Y>();       \
        }                                                                   \
    };                                                                      \
}                                                                           \
                                                                            \
inline bool base::is_base_id(int base_id) const noexcept                    \
{                                                                           \
    return base_id == qx::get_class_id<base>();                             \
}                                                                           \
                                                                            \
inline int base::get_class_id(void) const noexcept                          \
{                                                                           \
    return qx::get_class_id<base>();                                        \
                                                                            \

// define this macro in the end of each derived class
#define QX_RTTI_CLASS_DERIVED(derived, super)                               \
                                                                            \
public:                                                                     \
                                                                            \
    using SuperClass = super;                                               \
    using BaseClass  = SuperClass::BaseClass;                               \
    using ThisClass  = derived;                                             \
                                                                            \
    template<class RTTI_TYPE>                                               \
    friend constexpr int qx::get_class_id(void);                            \
                                                                            \
    virtual int get_class_id (void) const noexcept override;                \
                                                                            \
protected:                                                                  \
                                                                            \
    virtual bool is_base_id(int base_id) const noexcept override            \
    {                                                                       \
        return base_id == qx::get_class_id<SuperClass>() ||                 \
               SuperClass::is_base_id(base_id);                             \
    }                                                                       \
                                                                            \
private:                                                                    \
                                                                            \
    static constexpr int s_ClassId = qx::class_counter::next();             \
};                                                                          \
                                                                            \
namespace qx                                                                \
{                                                                           \
    template<>                                                              \
    inline constexpr int get_class_id<derived>(void)                        \
    {                                                                       \
        return derived::s_ClassId;                                          \
    }                                                                       \
}                                                                           \
                                                                            \
inline int derived::get_class_id(void) const noexcept                       \
{                                                                           \
    return qx::get_class_id<derived>();                                     \
