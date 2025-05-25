/**

    @file      shared_ref.h
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/smart_ptr/smart_ptr_ref_adapter.h>

namespace qx
{

/**
    @brief   A version of std::shared_ptr that cannot have an invalid value (nullptr) (compile time guaranteed).
    @details Can only be constructed with make_shared_ref.
             Cannot be constructed from / assigned from / reset from a shared_ptr.
             shared_ptr can be extracted via to_shared_ptr().
    @tparam  T - type to store
**/
template<class T>
using shared_ref = details::smart_ptr_ref_adapter<std::shared_ptr, T>;

/**
    @brief  Make a unique ref (same as std::make_shared but for qx::shared_ref)
    @tparam T                  - type to store
    @tparam constructor_args_t - T constructor types
    @param  args               - T constructor values
    @retval                    - made shared_ref
**/
template<class T, class... constructor_args_t>
shared_ref<T> make_shared_ref(constructor_args_t&&... args);

namespace details
{

template<class T, class... args_t>
class smart_ptr_ref_adapter<std::shared_ptr, T, args_t...>
    : public overload_functions_smart_ptr_ref_adapter<std::shared_ptr, T, args_t...>
{
    struct private_token
    {
    };

    template<class _T, class... _constructor_args_t>
    friend shared_ref<_T> qx::make_shared_ref(_constructor_args_t&&... args);

public:
    using super                 = overload_functions_smart_ptr_ref_adapter<std::shared_ptr, T, args_t...>;
    using original_pointer_type = typename super::original_pointer_type;
    using element_type          = typename super::element_type;
    using pointer               = typename super::pointer;
    using reference             = typename super::reference;

    smart_ptr_ref_adapter(smart_ptr_ref_adapter&&) noexcept            = default;
    smart_ptr_ref_adapter& operator=(smart_ptr_ref_adapter&&) noexcept = default;

    void reset(smart_ptr_ref_adapter other) noexcept;

    original_pointer_type to_shared_ptr();

    // private constructor, use qx::make_shared_ref instead
    template<class... constructor_args_t>
    smart_ptr_ref_adapter(private_token, constructor_args_t&&... args);
};

} // namespace details

} // namespace qx

#include <qx/smart_ptr/shared_ref.inl>
