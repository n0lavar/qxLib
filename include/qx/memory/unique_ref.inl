/**

    @file      unique_ref.inl
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<class T, class... constructor_args_t>
unique_ref<T> make_unique_ref(constructor_args_t&&... args)
{
    return unique_ref<T>(
        typename unique_ref<T>::private_token(),
        std::make_unique<T>(std::forward<constructor_args_t>(args)...));
}

template<class T, class deleter_t, class... constructor_args_t>
unique_ref<T, deleter_t> make_unique_ref_with_deleter(deleter_t deleter, constructor_args_t&&... args)
{
    return unique_ref<T, deleter_t>(
        typename unique_ref<T, deleter_t>::private_token(),
        std::unique_ptr<T, deleter_t>(new T(std::forward<constructor_args_t>(args)...), std::move(deleter)));
}

namespace details
{

template<class T, class... args_t>
void smart_ptr_ref_adapter<std::unique_ptr, T, args_t...>::reset(smart_ptr_ref_adapter other) noexcept
{
    *this = std::move(other);
}

template<class T, class... args_t>
template<class... constructor_args_t>
smart_ptr_ref_adapter<std::unique_ptr, T, args_t...>::smart_ptr_ref_adapter(private_token, constructor_args_t&&... args)
    : super(std::forward<constructor_args_t>(args)...)
{
}

} // namespace details

} // namespace qx
