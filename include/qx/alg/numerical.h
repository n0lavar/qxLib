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
//!\fn                              gcd
//
//!\brief    Greatest common divisor
//!\details  Euclid's algorithm
//           based on fact gcd(A, B) == gcd(B, A mod B)
//!\property O(log(second))
//!\param    first  - first num
//!\param    second - second num
//!\retval          - greatest common divisor if first and second > 0, otherwise 0
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
int gcd(int first, int second)
{
    if (first == 0 || second == 0)
        return 0;

    while (second != 0)
    {
        int remainder = first % second;
        first = second;
        second = remainder;
    }

    return std::abs(first);
}

//============================================================================
//!\fn                              lcm
//
//!\brief    Least common multiple
//!\property O(log(second))
//!\param    first  - first num
//!\param    second - second num
//!\retval          - least common multiple if first and second > 0, otherwise 0
//!\author Khrapov
//!\date   1.02.2020
//============================================================================
int lcm(int first, int second)
{
    if (first == 0 || second == 0)
        return 0;

    first  = std::abs(first);
    second = std::abs(second);

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
template<typename T>
double pow(T number, int power)
{
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Integral or floating point required");

    bool bNegativePower = power < 0;
    power = std::abs(power);

    double result = 1.0;
    switch (power)
    {
    case 0:                                                 break;
    case 1: result = static_cast<double>(number);           break;
    case 2: result = static_cast<double>(number) * number;  break;
    default:
        std::bitset<std::numeric_limits<int>::digits> powerBitset(power);
        std::array<double, std::numeric_limits<int>::digits> powers;

        powers[0] = static_cast<double>(number);

        int curPower = 1;
        int curIndex = 1;

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
template<typename I>
I maxpot(I number)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    if (number == I(0))
        return I(0);

    std::bitset<std::numeric_limits<I>::digits> powers(std::abs(number));
    I pow = std::numeric_limits<I>::digits - 1;
    while (!powers.test(pow))
        pow--;

    return pow;
}

//============================================================================
//!\fn                     find_prime_factors<I>
//
//!\brief    Find all prime factors
//!\property O(sqrt(number))
//!\param    number - number for search
//!\retval          - all prime factors vector
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename I>
std::vector<I> find_prime_factors(I number)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    std::vector<I> factors;

    if (number < 0)
        number = -number;

    if (number > 1)
    {
        while (number % 2 == 0)
        {
            factors.push_back(2);
            number /= 2;
        }

        I i = 3u;
        I max_factor = static_cast<I>(std::sqrt(number));
        while (i <= max_factor)
        {
            while (number % i == 0)
            {
                factors.push_back(i);
                number /= i;
                max_factor = static_cast<I>(std::sqrt(number));
            }

            i += 2;
        }

        if (number > 1)
            factors.push_back(number);
    }

    return factors;
}

//============================================================================
//!\fn                         find_primes<I>
//
//!\brief    Find all primes between 2 and max_number
//!\details  Sieve of Eratosthenes
//!\property O(max_number * log(log(number)))
//!\param    max_number - max number for search
//!\retval              - all primes vector
//!\author   Khrapov
//!\date     1.02.2020
//============================================================================
template<typename I>
std::vector<I> find_primes(I max_number)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    std::vector<bool> isComposite(static_cast<size_t>(max_number) + 1, false);

    for (size_t i = 4; i < static_cast<size_t>(max_number) + 1; i += 2)
        isComposite[i] = true;

    I next_prime = 3;
    I stop_at = static_cast<I>(std::sqrt(max_number + 1));
    while (next_prime <= stop_at)
    {
        for (I i = next_prime * 2; i < max_number + 1; i += next_prime)
            isComposite[i] = true;

        next_prime += 2;

        while (next_prime <= max_number && isComposite[next_prime])
            next_prime += 2;
    }

    std::vector<I> primes;
    primes.reserve(max_number / 2); // approximate size

    for (I i = 2; i < max_number + 1; i++)
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
    return find_prime_factors(static_cast<int>(number)).size() == 1;
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
        if (static_cast<size_t>(pow(randomNumber, static_cast<int>(number - 1))) % number != 1)
            return false;
    }

    return true;
}

}
