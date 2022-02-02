/**

    @file      numerical.h
    @brief     Numerical algorithms
    @author    Khrapov
    @date      1.02.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <array>
#include <bitset>
#include <cmath>
#include <ctime>
#include <limits>
#include <random>
#include <vector>

namespace qx
{

/**
    @brief      Greatest common divisor
    @details    Euclid's algorithm
                based on fact gcd(A, B) == gcd(B, A mod B)
    @complexity O(log(second))
    @param      nFirst  - first num
    @param      nSecond - second num
    @retval             - greatest common divisor if first and second > 0, otherwise 0
**/
inline int gcd(int nFirst, int nSecond)
{
    if (nFirst == 0 || nSecond == 0)
        return 0;

    while (nSecond != 0)
    {
        const int nRemainder = nFirst % nSecond;
        nFirst               = nSecond;
        nSecond              = nRemainder;
    }

    return std::abs(nFirst);
}

/**
    @brief      Least common multiple
    @complexity O(log(second))
    @param      nFirst  - first num
    @param      nSecond - second num
    @retval             - least common multiple if first and second > 0, otherwise 0
**/
inline int lcm(int nFirst, int nSecond)
{
    if (nFirst == 0 || nSecond == 0)
        return 0;

    nFirst  = std::abs(nFirst);
    nSecond = std::abs(nSecond);

    return nFirst / gcd(nFirst, nSecond) * nSecond;
}

/**
    @brief      Power function for integer power
    @details    About 2.22 times (positive powers)
                      1.7  times (positive and negative powers)
                      2.33 times (negative powers)
                      faster then std::pow
    @complexity O(log(power))
    @tparam     T       - Integral or floating point type
    @param      nNumber - integral of floating point value
    @param      nPower  - integral power
    @retval             - number ^ power
**/
template<typename T>
inline double pow(T nNumber, int nPower)
{
    static_assert(
        std::is_integral_v<T> || std::is_floating_point_v<T>,
        "Integral or floating point required");

    const bool   bNegativePower = nPower < 0;
    const size_t nPositivePower = static_cast<size_t>(std::abs(nPower));

    double fResult = 1.0;
    switch (nPositivePower)
    {
    case 0:
        break;

    case 1:
        fResult = static_cast<double>(nNumber);
        break;

    case 2:
        fResult = static_cast<double>(nNumber * nNumber);
        break;

    default:
        const std::bitset<std::numeric_limits<int>::digits> powerBitSet(
            nPositivePower);

        std::array<double, std::numeric_limits<int>::digits> powers;

        powers[0] = static_cast<double>(nNumber);

        size_t nCurPower = 1;
        size_t nCurIndex = 1;

        while (nCurPower < nPositivePower)
        {
            powers[nCurIndex] = powers[nCurIndex - 1] * powers[nCurIndex - 1];
            nCurPower *= 2;
            nCurIndex++;
        }

        for (size_t i = 0; i < static_cast<size_t>(nCurIndex); i++)
            if (powerBitSet.test(i))
                fResult *= powers[i];

        break;
    }

    return bNegativePower ? 1.0 / fResult : fResult;
}

/**
    @brief  Max power of two in integer
    @tparam I      - Integral type
    @param  nValue - number
    @retval        - max power of two in number
**/
template<typename I>
inline I maxpot(I nValue)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    if (nValue == I(0))
        return I(0);

    std::bitset<std::numeric_limits<I>::digits> powers(
        static_cast<size_t>(std::abs(nValue)));

    I nPow = static_cast<I>(std::numeric_limits<I>::digits - 1);
    while (!powers.test(static_cast<size_t>(nPow)))
        --nPow;

    return nPow;
}

/**
    @brief      Find all prime factors
    @complexity O(sqrt(number))
    @tparam     I      - Integral type
    @param      nValue - number for search
    @retval            - all prime factors vector
**/
template<typename I>
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
template<typename I>
inline std::vector<I> find_primes(I nMaxNumber)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    std::vector<bool> isComposite(static_cast<size_t>(nMaxNumber) + 1, false);

    constexpr size_t first_composite_power_of_two = 4;
    for (size_t i = first_composite_power_of_two;
         i < static_cast<size_t>(nMaxNumber) + 1;
         i += 2)
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

        while (nNextPrime <= nMaxNumber
               && isComposite[static_cast<size_t>(nNextPrime)])
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

    const size_t nTests = static_cast<size_t>(
        std::ceil(std::log(1.0 / (1.0 - fProbability)) / fLog2));

    std::default_random_engine generator(
        static_cast<unsigned>(std::time(nullptr))); //-V202

    std::uniform_int_distribution<size_t> num_dist(2, nValue);

    for (size_t i = 0; i < nTests; i++)
    {
        const size_t nRandomNumber = num_dist(generator);
        if (static_cast<size_t>(
                pow(nRandomNumber, static_cast<int>(nValue) - 1)) //-V202
                % nValue
            != 1)
        {
            return false;
        }
    }

    return true;
}

} // namespace qx
