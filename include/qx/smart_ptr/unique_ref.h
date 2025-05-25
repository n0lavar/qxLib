/**

    @file      unique_ref.h
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/smart_ptr/smart_ptr_ref_adapter.h>

namespace qx
{

/**
    @brief   A version of std::unique_ptr that cannot have an invalid value (nullptr) (compile time guaranteed).
    @details Can only be constructed with make_unique_ref or make_unique_ref_with_deleter.
             Cannot be constructed from / assigned from / reset from a unique_ptr.
    @tparam  T         - type to store
    @tparam  deleter_t - optional custom deleter
**/
template<class T, class deleter_t = std::default_delete<T>>
using unique_ref = details::smart_ptr_ref_adapter<std::unique_ptr, T, deleter_t>;

/**
    @brief  Make a unique ref (same as std::make_unique but for qx::unique_ref)
    @tparam T                  - type to store
    @tparam constructor_args_t - T constructor types
    @param  args               - T constructor values
    @retval                    - made unique_ref
**/
template<class T, class... constructor_args_t>
unique_ref<T> make_unique_ref(constructor_args_t&&... args);

/**
    @brief  Make a unique ref with a custom deleter
    @tparam T                  - type to store
    @tparam deleter_t          - custom constructor type
    @tparam constructor_args_t - T constructor types
    @param  deleter            - custom constructor
    @param  args               - T constructor values
    @retval                    - made unique_ref
**/
template<class T, class deleter_t, class... constructor_args_t>
unique_ref<T, deleter_t> make_unique_ref_with_deleter(deleter_t deleter, constructor_args_t&&... args);

namespace details
{

template<class T, class... args_t>
class smart_ptr_ref_adapter<std::unique_ptr, T, args_t...>
    : public overload_functions_smart_ptr_ref_adapter<std::unique_ptr, T, args_t...>
{
    struct private_token
    {
    };

    template<class _T, class... _constructor_args_t>
    friend unique_ref<_T> qx::make_unique_ref(_constructor_args_t&&... args);

    template<class _T, class _deleter_t, class... _constructor_args_t>
    friend unique_ref<_T, _deleter_t> qx::make_unique_ref_with_deleter(
        _deleter_t deleter,
        _constructor_args_t&&... args);

public:
    using super                 = overload_functions_smart_ptr_ref_adapter<std::unique_ptr, T, args_t...>;
    using original_pointer_type = typename super::original_pointer_type;
    using element_type          = typename super::element_type;
    using pointer               = typename super::pointer;
    using reference             = typename super::reference;

    smart_ptr_ref_adapter(smart_ptr_ref_adapter&&) noexcept            = default;
    smart_ptr_ref_adapter& operator=(smart_ptr_ref_adapter&&) noexcept = default;

    void reset(smart_ptr_ref_adapter other) noexcept;

    // private constructor, use qx::make_unique_ref or qx::make_unique_ref_with_deleter instead
    template<class... constructor_args_t>
    smart_ptr_ref_adapter(private_token, constructor_args_t&&... args);

private:
    using super::release;
};

} // namespace details

} // namespace qx

#include <qx/smart_ptr/unique_ref.inl>
