/**

    @file      newtons_method.h
    @brief     Contains Newtons method
    @details   ~
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <cmath>

namespace qx
{

/**
    @brief  Find root of the equation using Newtons method
    @param  func                   - function
    @param  derivativeFunc         - derivative function (dfdx)
    @param  fInitialGuess          - initial root guess
    @param  fMaxError              - max error to stop searching
    @param  nMaxIterations         - max iterations number (sometimes alg breaks)
    @tparam FunctionType           - function that takes double and returns double
    @tparam DerivativeFunctionType - function that takes double and returns double
    @retval                        - approximate root
**/
template<class FunctionType, class DerivativeFunctionType>
inline double newtons_method(
    const FunctionType&           func,
    const DerivativeFunctionType& derivativeFunc,
    double                        fInitialGuess,
    double                        fMaxError      = 0.0001,
    size_t                        nMaxIterations = 10000)
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
