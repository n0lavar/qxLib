/**

    @file      transform.inl
    @author    Khrapov
    @date      1.10.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

namespace details
{

template<class T>
concept has_reserve_func = requires(T t) {
    {
        t.reserve(size_t())
    };
};

template<class T>
concept has_size_func = requires(T t) {
    {
        t.size()
    } -> std::convertible_to<size_t>;
};

} // namespace details

template<
    template<class...>
    class result_container_t,
    class input_container_t,
    class transform_callable_t,
    class... result_container_rest_t>
auto transform_return(input_container_t&& input, const transform_callable_t& transformCallable)
{
    using result_type             = decltype(transformCallable(*input.begin()));
    using result_container_full_t = result_container_t<result_type, result_container_rest_t...>;
    result_container_full_t result;

    if constexpr (details::has_reserve_func<result_container_full_t> && details::has_size_func<input_container_t>)
        result.reserve(input.size());

    for (auto&& inputElement : input)
        result.insert(result.end(), transformCallable(std::forward<decltype(inputElement)>(inputElement)));

    return result;
}

}
