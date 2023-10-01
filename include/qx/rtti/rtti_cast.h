/**

    @file      rtti_cast.h
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/meta/type_traits.h>

#include <memory>
#include <type_traits>

namespace qx
{

namespace details
{

template<class T, class from_t>
concept has_is_derived_from = requires(T* t) { t->template is_derived_from<from_t>(); };

} // namespace details

/**
    @brief   Returns Y* if X or element_type of X is inherited from Y, otherwise nullptr
    @details Pointer class should contain QX_RTTI_CLASS
    @tparam  Y     - type to cast to
    @tparam  X     - smart pointer type or some class to test type
    @param   value - smart pointer object or some class to test object
    @retval        - Y* if X or element_type of X is inherited from Y, otherwise nullptr
**/
template<class Y, class X>
Y* rtti_cast(X& value)
{
    using T = std::decay_t<X>;
    if constexpr (is_specialization_of<T, std::shared_ptr>::value || is_specialization_of<T, std::unique_ptr>::value)
    {
        using smart_pointer_t = typename std::remove_reference_t<decltype(value)>::element_type;
        if constexpr (details::has_is_derived_from<smart_pointer_t, Y>)
            if (value && value->template is_derived_from<Y>())
                return static_cast<Y*>(value.get());
    }
    else
    {
        if constexpr (details::has_is_derived_from<T, Y>)
            if (value.template is_derived_from<Y>())
                return static_cast<Y*>(&value);
    }

    return nullptr;
}

/**
    @brief   Returns Y* if X is inherited from Y, otherwise nullptr
    @details Pointer class should contain QX_RTTI_CLASS
    @tparam  Y       - type to cast to
    @tparam  X       - type to cast from
    @param   pointer - raw pointer
    @retval          - Y* if X is inherited from pointer class, otherwise nullptr
**/
template<class Y, class X>
Y* rtti_cast(X* pointer)
{
    if constexpr (details::has_is_derived_from<X, Y>)
        if (pointer && pointer->template is_derived_from<Y>())
            return static_cast<Y*>(pointer);

    return nullptr;
}

} // namespace qx
