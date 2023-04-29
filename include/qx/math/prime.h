/**

    @file      prime.h
    @brief     Contains prime numbers algorithms
    @details   ~
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <cmath>
#include <random>
#include <vector>

namespace qx
{

/**
    @brief      Find all prime factors
    @complexity O(sqrt(number))
    @tparam     I      - Integral type
    @param      nValue - number for search
    @retval            - all prime factors vector
**/
template<class I>
inline std::vector<I> find_prime_factors(I nValue)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    std::vector<I> factors;

    bool bValueNegative = false;
    if constexpr (std::numeric_limits<I>::min() < 0)
    {
        if (nValue < 0)
        {
            bValueNegative = true;
            nValue         = -nValue;
        }
    }

    if (nValue > 1)
    {
        while (nValue % 2 == 0)
        {
            factors.push_back(2);
            nValue /= 2;
        }

        I i          = 3u;
        I nMaxFactor = static_cast<I>(std::sqrt(nValue));
        while (i <= nMaxFactor)
        {
            while (nValue % i == 0)
            {
                factors.push_back(i);
                nValue /= i;
                nMaxFactor = static_cast<I>(std::sqrt(nValue));
            }

            i += 2;
        }

        if (nValue > 1)
            factors.push_back(nValue);
    }

    if constexpr (std::numeric_limits<I>::min() < 0)
        if (!factors.empty() && bValueNegative)
            factors[0] = -factors[0];

    return factors;
}

/**
    @brief      Find all primes between 2 and nMaxNumber
    @details    Sieve of Eratosthenes
    @complexity O(nMaxNumber * log(log(number)))
    @tparam     I          - Integral type
    @param      nMaxNumber - max number for search
    @retval                - all primes vector
**/
template<class I>
inline std::vector<I> find_primes(I nMaxNumber)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    std::vector<bool> isComposite(static_cast<size_t>(nMaxNumber) + 1, false);

    constexpr size_t first_composite_power_of_two = 4;
    for (size_t i = first_composite_power_of_two; i < static_cast<size_t>(nMaxNumber) + 1; i += 2)
    {
        isComposite[i] = true;
    }

    I nNextPrime = 3;
    I nStopAt    = static_cast<I>(std::sqrt(nMaxNumber + 1));
    while (nNextPrime <= nStopAt)
    {
        for (I i = nNextPrime * 2; i < nMaxNumber + 1; i += nNextPrime)
            isComposite[static_cast<size_t>(i)] = true;

        nNextPrime += 2;

        while (nNextPrime <= nMaxNumber && isComposite[static_cast<size_t>(nNextPrime)])
        {
            nNextPrime += 2;
        }
    }

    std::vector<I> primes;
    primes.reserve(static_cast<size_t>(nMaxNumber / 2)); // approximate size

    for (I i = 2; i < nMaxNumber + 1; ++i)
        if (!isComposite[static_cast<size_t>(i)])
            primes.push_back(i);

    primes.shrink_to_fit();
    return primes;
}

/**
    @brief      Is number prime
    @details    1.0 probability, high computational complexity
    @complexity O(sqrt(number))
    @param      nValue - number
    @retval            - true if prime
**/
inline bool is_prime(size_t nValue)
{
    return find_prime_factors(nValue).size() == 1;
}

/**
    @brief  Is number prime with some probability
    @param  nValue       - number
    @param  fProbability - probability (0, 1]
    @retval              - true is number is prime with some probability
**/
inline bool is_prime(size_t nValue, double fProbability)
{
    if (fProbability < 0)
        fProbability = -fProbability;

    if (fProbability >= 1 || std::fabs(fProbability) <= DBL_EPSILON)
        return is_prime(nValue);

    constexpr double fLog2 = 0.30102999566; // std::log(2)

    const size_t nTests = static_cast<size_t>(std::ceil(std::log(1.0 / (1.0 - fProbability)) / fLog2));

    std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_int_distribution<size_t> num_dist(2, nValue);

    for (size_t i = 0; i < nTests; i++)
    {
        const size_t nRandomNumber = num_dist(generator);
        if (static_cast<size_t>(pow(nRandomNumber, static_cast<int>(nValue) - 1)) % nValue != 1)
        {
            return false;
        }
    }

    return true;
}

} // namespace qx
