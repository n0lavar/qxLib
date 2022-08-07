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
    @tparam LambdaType - lambda type
**/
template<class LambdaType>
struct recursive_lambda
{
    LambdaType lambda;

    template<class... Args>
    decltype(auto) operator()(Args&&... args) const
    {
        return lambda(*this, std::forward<Args>(args)...);
    }
};

/**
    @brief  Create lambda that can be called recursively 
    @tparam LambdaType - lambda type: see code example
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
template<class LambdaType>
recursive_lambda<std::decay_t<LambdaType>> make_recursive_lambda(LambdaType&& lambda)
{
    return { std::forward<LambdaType>(lambda) };
}

} // namespace qx
