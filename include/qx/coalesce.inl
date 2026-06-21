/**

    @file      coalesce.inl
    @author    Khrapov
    @date      27.09.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

namespace details
{

template<class T>
struct select_reference
{
    using type = T;
};

template<class T>
struct select_reference<T&>
{
    using type = std::reference_wrapper<T>;
};

} // namespace details

template<class return_t, class... args_t>
constexpr return_t coalesce(args_t&&... args)
{
    using return_type = typename details::select_reference<return_t>::type;

    size_t                     nArg = 0;
    std::optional<return_type> optResult;

    (
        [&nArg, &optResult]<class T>(T&& arg)
        {
            if (nArg++ == sizeof...(args_t) || predicates::is_valid(arg))
            {
                optResult = static_cast<return_type>(std::forward<T>(arg));
                return true;
            }
            else
            {
                return false;
            }
        }(std::forward<args_t>(args))
        || ...);

    return std::move(*optResult);
}

template<class... args_t>
    requires(same_variadic_args_v<args_t...>)
constexpr auto coalesce(args_t&&... args)
{
    using return_type = typename details::select_reference<typename same_variadic_args<args_t...>::type>::type;

    size_t                     nArg = 0;
    std::optional<return_type> optResult;

    (
        [&nArg, &optResult]<class T>(T&& arg)
        {
            if (nArg++ == sizeof...(args_t) || predicates::is_valid(arg))
            {
                optResult = std::forward<T>(arg);
                return true;
            }
            else
            {
                return false;
            }
        }(std::forward<args_t>(args))
        || ...);

    return std::move(*optResult);
}

} // namespace qx
