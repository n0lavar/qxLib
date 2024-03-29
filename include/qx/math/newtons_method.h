/**

    @file      newtons_method.h
    @author    Khrapov
    @date      6.08.2022
    @copyright � Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <cmath>

namespace qx
{

/**
    @brief  Find root of the equation using Newtons method
    @param  func                  - function
    @param  derivativeFunc        - derivative function (dfdx)
    @param  fInitialGuess         - initial root guess
    @param  fMaxError             - max error to stop searching
    @param  nMaxIterations        - max iterations number (sometimes alg breaks)
    @tparam function_t            - function that takes double and returns double
    @tparam derivative_function_t - function that takes double and returns double
    @retval                       - approximate root
**/
template<class function_t, class derivative_function_t>
inline double newtons_method(
    const function_t&            func,
    const derivative_function_t& derivativeFunc,
    double                       fInitialGuess,
    double                       fMaxError      = 0.0001,
    size_t                       nMaxIterations = 10000)
{
    double x = fInitialGuess;

    for (size_t i = 0; i < nMaxIterations; i++)
    {
        const double y = func(x);

        if (std::abs(y) < fMaxError)
            break;

        x -= y / derivativeFunc(x);
    }

    return x;
}

} // namespace qx
