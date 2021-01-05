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

#include <string_view>

namespace qx
{

template<class C>
int get_class_id(void)
{
    return -1;
}

template <typename X>
struct is_derived
{
    template <typename Y>
    static bool from() noexcept
    {
        return qx::get_class_id<X>() == qx::get_class_id<Y>() ||
               is_derived<typename X::SuperClass>::template from<Y>();
    }
};

}

#ifndef QX_RTTI_CLASS_NAME
    #define QX_RTTI_CLASS_NAME(className) # className
#endif

// defining this macros in required classes allows to use:
//
// qx::get_class_id<name>():    returns unique id of each class,
//                              you can use it in "switch" or "if" with object->get_class_id()
//                              returns -1 if class is not registrated
//
// qx::get_class_name_static()  returns name of class, if enabled in QX_RTTI_CLASS_NAME
//
// qx::is_derived<class_1>::from<class_1>():
//                              returns true if class_1 derived from class_1
//
// pObject->is_derived_from<base>():
//                              replacement for if (auto pBase = dynamic_cast<base*>(pObject))
//                              returns true if class of pObject is derived from base type of pObject is base
//
// pObject->get_class_name()    returns name of pObject class even if pObject is pointer of base class,
//                              if enabled in QX_RTTI_CLASS_NAME
//
// name::BaseClass              base class
// name::SuperClass             super blass
// name::ThisClass              this class

namespace qx
{

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

    virtual int get_class_id(void) const noexcept
    {
        return get_class_id_static();
    }

    static int get_class_id_static(void) noexcept
    {
        static int nId = get_next_id();
        return nId;
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

template<>
inline int get_class_id<rtti_base>(void) noexcept
{
    return rtti_base::get_class_id_static();
}

template <>
struct is_derived<rtti_base>
{
    template <typename Y>
    static bool from() noexcept
    {
        return qx::get_class_id<rtti_base>() == qx::get_class_id<Y>();
    }
};

}



// define this macro in the end of each derived class
#define QX_RTTI_CLASS_DERIVED(thisClass, superClass)                        \
                                                                            \
public:                                                                     \
                                                                            \
    using SuperClass = superClass;                                          \
    using BaseClass  = SuperClass::BaseClass;                               \
    using ThisClass  = thisClass;                                           \
                                                                            \
    virtual int get_class_id (void) const noexcept override                 \
    {                                                                       \
        return get_class_id_static();                                       \
    }                                                                       \
                                                                            \
    static constexpr std::string_view get_class_name_static(void) noexcept  \
    {                                                                       \
        return QX_RTTI_CLASS_NAME(thisClass);                               \
    }                                                                       \
                                                                            \
    virtual std::string_view get_class_name(void) const noexcept override   \
    {                                                                       \
        return get_class_name_static();                                     \
    }                                                                       \
                                                                            \
    static int get_class_id_static(void) noexcept                           \
    {                                                                       \
        static int nId = get_next_id();                                     \
        return nId;                                                         \
    }                                                                       \
                                                                            \
protected:                                                                  \
                                                                            \
    virtual bool is_base_id(int base_id) const noexcept override            \
    {                                                                       \
        return base_id == qx::get_class_id<SuperClass>() ||                 \
               SuperClass::is_base_id(base_id);                             \
    }                                                                       \
};                                                                          \
                                                                            \
namespace qx                                                                \
{                                                                           \
    template<>                                                              \
    inline int get_class_id<thisClass>(void) noexcept                       \
    {                                                                       \
        return thisClass::get_class_id_static();                            \
    }