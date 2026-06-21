/**

    @file      shared_ref.inl
    @author    Khrapov
    @date      25.05.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class T, class... constructor_args_t>
shared_ref<T> make_shared_ref(constructor_args_t&&... args)
{
    return shared_ref<T>(
        typename shared_ref<T>::private_token(),
        std::make_shared<T>(std::forward<constructor_args_t>(args)...));
}

namespace details
{

template<class T>
template<class U>
    requires std::constructible_from<std::shared_ptr<T>, std::shared_ptr<U>&&>
smart_ptr_ref_adapter<std::shared_ptr, T>::smart_ptr_ref_adapter(
    smart_ptr_ref_adapter<std::shared_ptr, U>&& other) noexcept
    : super(static_cast<std::shared_ptr<U>&&>(other))
{
}

template<class T>
void smart_ptr_ref_adapter<std::shared_ptr, T>::reset(smart_ptr_ref_adapter other) noexcept
{
    *this = std::move(other);
}

template<class T>
typename smart_ptr_ref_adapter<std::shared_ptr, T>::original_pointer_type smart_ptr_ref_adapter<std::shared_ptr, T>::
    to_shared_ptr()
{
    return *this;
}

template<class T>
template<class... constructor_args_t>
smart_ptr_ref_adapter<std::shared_ptr, T>::smart_ptr_ref_adapter(private_token, constructor_args_t&&... args)
    : super(std::forward<constructor_args_t>(args)...)
{
}

} // namespace details

} // namespace qx
