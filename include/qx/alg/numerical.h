//============================================================================
//
//!\file                         numerical.h
//
//!\brief       numerical algorithms
//!\details     ~
//
//!\author      Khrapov
//!\date        1.02.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#pragma once

#include <bitset>
#include <limits>
#include <array>

#include <qx/other/useful_macros.h>

namespace qx::alg
{ 

//============================================================================
//!\fn                              gcd<I>
//
//!\brief    Greatest common divisor
//!\details  Euclid's algorithm
//           based on fact gcd(A, B) == gcd(B, A mod B)
//!\property O(log(B))
//!\param    first  - first num
//!\param    second - second num
//!\retval          - greatest common divisor
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename I>
I gcd(I first, I second)
{
    static_assert(std::is_integral<I>::value, "Integral required");

    while (second != 0)
    {
        I remainder = first % second;
        first = second;
        second = remainder;
    }

    return first;
}

//============================================================================
//!\fn                              lcm<I>
//
//!\brief    Least common multiple
//!\property O(log(B))
//!\param    first  - first num
//!\param    second - second num
//!\retval        - least common multiple
//!\author Khrapov
//!\date   1.02.2020
//============================================================================
template<typename I>
I lcm(I first, I second)
{
    return first / gcd(first, second) * second;
}

//============================================================================
//!\fn                            pow<T, I>
//
//!\brief    Power function for unsigned integer power
//!\details  about 2.22 times faster then std::pow
//!\property O(log(power))
//!\param    number - integral of floating point value
//!\param    power  - integral power
//!\retval          - number ^ power
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename T, typename UI>
T pow(T number, UI power)
{
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Integral or floating point required");
    static_assert(std::is_unsigned<UI>::value, "Unsigned integral required");

    T result(0);
    switch (power)
    {
    case 0: result = T(1);              break;
    case 1: result = number;            break;
    case 2: result = result * result;   break;
    default:
        std::bitset<std::numeric_limits<UI>::digits>   bitset(power);
        std::array<T, std::numeric_limits<UI>::digits> powers;

        powers[0] = number;

        UI curPower = UI(1);
        UI curIndex = UI(1);

        while (curPower < power)
        {
            powers[curIndex] = powers[curIndex - 1] * powers[curIndex - 1];
            curPower *= 2;
            curIndex++;
        }

        for (size_t i = 0; i < curIndex; i++)
            if (bitset.test(i))
                result *= powers[i];

        break;
    }

    return result;
}

//============================================================================
//!\fn                            maxpot<I>
//
//!\brief  Max power of two in integer
//!\param  number - number
//!\retval        - max power of two in number
//!\author Khrapov
//!\date   1.02.2020
//============================================================================
template<typename UI>
UI maxpot(UI number)
{
    static_assert(std::is_unsigned<UI>::value, "Unsigned integral required");

    UI rv = 0;

    while (number)
        rv |= number >>= 1;

    return ++rv;
}

#if 0
//============================================================================
//!\fn                        prime_factors<UI>
//
//!\brief  Find all prime factors
//!\param  number - number for search
//!\retval        - all prime factors vector
//!\author Khrapov
//!\date   1.02.2020
//============================================================================
template<typename UI>
std::vector<UI> prime_factors(UI number)
{

}
#endif

}
