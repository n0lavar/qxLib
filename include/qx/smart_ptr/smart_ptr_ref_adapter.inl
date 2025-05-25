/**

    @file      smart_ptr_ref_adapter.inl
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx::details
{

template<template<class, class...> class pointer_t, class T, class... args_t>
template<class... constructor_args_t>
base_smart_ptr_ref_adapter<pointer_t, T, args_t...>::base_smart_ptr_ref_adapter(constructor_args_t&&... args)
    : original_pointer_type(std::forward<constructor_args_t>(args)...)
{
    // QX_ASSERT(original_pointer_type::get());
}

template<template<class, class...> class pointer_t, class T, class... args_t>
typename base_smart_ptr_ref_adapter<pointer_t, T, args_t...>::reference overload_functions_smart_ptr_ref_adapter<
    pointer_t,
    T,
    args_t...>::get() const noexcept
{
    return *super::original_pointer_type::get();
}

template<template<class, class...> class pointer_t, class T, class... args_t>
template<class... constructor_args_t>
overload_functions_smart_ptr_ref_adapter<pointer_t, T, args_t...>::overload_functions_smart_ptr_ref_adapter(
    constructor_args_t&&... args)
    : super(std::forward<constructor_args_t>(args)...)
{
}

} // namespace qx::details
