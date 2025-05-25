/**

    @file      smart_ptr_ref_adapter.h
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <memory>

namespace qx::details
{

template<template<class, class...> class pointer_t, class T, class... args_t>
class base_smart_ptr_ref_adapter : public pointer_t<T, args_t...>
{
public:
    using original_pointer_type = pointer_t<T, args_t...>;
    using super                 = original_pointer_type;
    using element_type          = T;
    using pointer               = T*;
    using reference             = T&;

    base_smart_ptr_ref_adapter()               = delete;
    base_smart_ptr_ref_adapter(std::nullptr_t) = delete;

protected:
    base_smart_ptr_ref_adapter(base_smart_ptr_ref_adapter&&) noexcept            = default;
    base_smart_ptr_ref_adapter& operator=(base_smart_ptr_ref_adapter&&) noexcept = default;

    template<class... constructor_args_t>
    base_smart_ptr_ref_adapter(constructor_args_t&&... args);

private:
    using original_pointer_type::get;
    using original_pointer_type::reset;
    using original_pointer_type::operator bool;
    using original_pointer_type::operator=;
};

template<template<class, class...> class pointer_t, class T, class... args_t>
class overload_functions_smart_ptr_ref_adapter : public base_smart_ptr_ref_adapter<pointer_t, T, args_t...>
{
public:
    using super                 = base_smart_ptr_ref_adapter<pointer_t, T, args_t...>;
    using original_pointer_type = typename super::original_pointer_type;
    using element_type          = typename super::element_type;
    using pointer               = typename super::pointer;
    using reference             = typename super::reference;

    super::reference get() const noexcept;

protected:
    overload_functions_smart_ptr_ref_adapter(overload_functions_smart_ptr_ref_adapter&&) noexcept            = default;
    overload_functions_smart_ptr_ref_adapter& operator=(overload_functions_smart_ptr_ref_adapter&&) noexcept = default;

    template<class... constructor_args_t>
    overload_functions_smart_ptr_ref_adapter(constructor_args_t&&... args);
};

template<template<class> class pointer_t, class T, class... args_t>
class smart_ptr_ref_adapter;

} // namespace qx::details

namespace std
{

template<template<class, class...> class pointer_t, class T, class... args_t>
struct hash<qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...>>
{
    size_t operator()(const qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...>& adaper) const noexcept
    {
        return hash<pointer_t<T, args_t...>>()(adaper);
    }
};

template<template<class, class...> class pointer_t, class T, class... args_t>
void swap(
    qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...>& lhs,
    qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...>& rhs) noexcept
{
    lhs.swap(rhs);
}

} // namespace std

#include <qx/smart_ptr/smart_ptr_ref_adapter.inl>
