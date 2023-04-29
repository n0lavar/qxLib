/**

    @file      recursive_lambda.h
    @brief     Contains qx::make_recursive_lambda function
    @details   ~
    @author    Khrapov
    @date      3.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @struct recursive_lambda
    @tparam lambda_t - lambda type
**/
template<class lambda_t>
struct recursive_lambda
{
    lambda_t lambda;

    template<class... args_t>
    decltype(auto) operator()(args_t&&... args)
    {
        return lambda(*this, std::forward<args_t>(args)...);
    }

    template<class... args_t>
    decltype(auto) operator()(args_t&&... args) const
    {
        return lambda(*this, std::forward<args_t>(args)...);
    }
};

/**
    @brief  Create lambda that can be called recursively 
    @tparam lambda_t - lambda type: see code example
    @param  lambda     - lambda object
    @retval            - lambda that can be called recursively

    @code
    auto calc_fibonacci = qx::make_recursive_lambda(
        [](const auto& calc_fibonacci, int n) -> int // return value is required
        {
            if (n == 1 || n == 2)
                return 1;

            if (n == 0)
                return 0;

            return calc_fibonacci(n - 1) + calc_fibonacci(n - 2);
        });

    int nResult = calc_fibonacci(6);
    @endcode
**/
template<class lambda_t>
recursive_lambda<std::decay_t<lambda_t>> make_recursive_lambda(lambda_t&& lambda)
{
    return { std::forward<lambda_t>(lambda) };
}

} // namespace qx
