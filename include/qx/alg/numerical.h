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
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

namespace qx
{ 

//============================================================================
//!\fn                              gcd<I>
//
//!\brief    Greatest common divisor
//!\details  Euclid's algorithm
//           based on fact gcd(A, B) == gcd(B, A mod B)
//!\property O(log(second))
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
//!\property O(log(second))
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
//!\brief    Power function for integer power
//!\details  about 2.22 times (positive powers)
//                 1.7  times (positive and negative powers)
//                 2.33 times (negative powers)
//                 faster then std::pow 
//!\property O(log(power))
//!\param    number - integral of floating point value
//!\param    power  - integral power
//!\retval          - number ^ power
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename T, typename I>
double pow(T number, I power)
{
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Integral or floating point required");
    static_assert(std::is_integral<I>::value, "Integral required");

    bool bNegativePower = power < 0;
    power = static_cast<I>(std::abs(static_cast<long long>(power)));

    double result = 1.0;
    switch (power)
    {
    case 0:                                                 break;
    case 1: result = static_cast<double>(number);           break;
    case 2: result = static_cast<double>(number) * number;  break;
    default:
        std::bitset<std::numeric_limits<I>::digits> powerBitset(power);
        std::array<double, std::numeric_limits<I>::digits> powers;

        powers[0] = static_cast<double>(number);

        I curPower = I(1);
        I curIndex = I(1);

        while (curPower < power)
        {
            powers[curIndex] = powers[static_cast<size_t>(curIndex) - 1] * powers[static_cast<size_t>(curIndex) - 1];
            curPower *= 2;
            curIndex++;
        }

        for (size_t i = 0; i < curIndex; i++)
            if (powerBitset.test(i))
                result *= powers[i];

        break;
    }

    return bNegativePower ? 1.0 / result : result;
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

//============================================================================
//!\fn                     find_prime_factors<UI>
//
//!\brief    Find all prime factors
//!\property O(sqrt(number))
//!\param    number - number for search
//!\retval          - all prime factors vector
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename UI>
std::vector<UI> find_prime_factors(UI number)
{
    static_assert(std::is_unsigned<UI>::value, "Unsigned integral required");

    std::vector<UI> factors;
    
    while (number % 2 == 0)
    {
        factors.push_back(2);
        number /= 2;
    }

    UI i = 3u;
    UI max_factor = static_cast<UI>(std::sqrt(number));
    while (i <= max_factor)
    {
        while (number % i == 0)
        {
            factors.push_back(i);
            number /= i;
            max_factor = static_cast<UI>(std::sqrt(number));
        }

        i += 2;
    }

    if (number > 1)
        factors.push_back(number);

    return factors;
}

//============================================================================
//!\fn                         find_primes<UI>
//
//!\brief    Find all primes between 2 and max_number
//!\details  Sieve of Eratosthenes
//!\property O(max_number * log(log(number)))
//!\param    max_number - max number for search
//!\retval              - all primes vector
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename UI>
std::vector<UI> find_primes(UI max_number)
{
    static_assert(std::is_unsigned<UI>::value, "Unsigned integral required");

    std::vector<bool> isComposite(static_cast<size_t>(max_number) + 1, false);

    for (size_t i = 4; i < max_number; i += 2)
        isComposite[i] = true;

    UI next_prime = 3u;
    UI stop_at = static_cast<UI>(std::sqrt(max_number));
    while (next_prime <= stop_at)
    {
        for (UI i = next_prime * 2; i < max_number; i += next_prime)
            isComposite[i] = true;

        next_prime += 2;

        while (next_prime <= max_number && isComposite[next_prime])
            next_prime += 2;
    }

    std::vector<UI> primes;
    primes.reserve(max_number / 2); // approximate size
    for (UI i = 2; i < max_number; i++)
        if (!isComposite[i])
            primes.push_back(i);

    primes.shrink_to_fit();
    return primes;
}

//============================================================================
//!\fn                             is_prime
//
//!\brief    Is number prime
//!\details  1.0 probability, high computational complexity
//!\property O(sqrt(number))
//!\param    number - number
//!\retval          - true if prime
//!\author   Khrapov
//!\date     2.02.2020
//============================================================================
bool is_prime(size_t number)
{
    return find_prime_factors(number).size() == 1;
}

//============================================================================
//!\fn                             is_prime
//
//!\brief  Is number prime with some probability
//!\param  number      - number
//!\param  probability - probability (0, 1]
//!\retval             - true is number is prime with some probability
//!\author Khrapov
//!\date   2.02.2020
//============================================================================
bool is_prime(size_t number, double probability)
{
    if (probability < 0)
        probability = -probability;

    if (probability >= 1 || probability == 0)
        return is_prime(number);

    constexpr double log_2 = 0.30102999566; // std::log(2)
    size_t num_tests = static_cast<size_t>(std::ceil(std::log(1.0 / (1.0 - probability)) / log_2));

    std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<size_t> num_dist(2, number);
    for (size_t i = 0; i < num_tests; i++)
    {
        size_t randomNumber = num_dist(generator);
        if (static_cast<size_t>(pow(randomNumber, number - 1)) % number != 1)
            return false;
    }

    return true;
}

}
