/**

    @file      rtti_cast.h
    @brief     Contains cast functions for qx RTTI system
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <type_traits>

namespace qx
{

namespace detail
{

template<typename T, typename From>
concept has_is_derived_from = requires(T* t) { t->template is_derived_from<From>(); };

} // namespace detail

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
    using smart_pointer_t = typename std::remove_reference_t<decltype(pointer)>::element_type;
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
