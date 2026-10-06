/**

    @file      prime.h
    @author    Khrapov
    @date      6.08.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

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
inline std::vector<I> find_prime_factors(I nValue);

/**
    @brief      Find all primes between 2 and nMaxNumber
    @details    Sieve of Eratosthenes
    @complexity O(nMaxNumber * log(log(number)))
    @tparam     I          - Integral type
    @param      nMaxNumber - max number for search
    @retval                - all primes vector
**/
template<class I>
inline std::vector<I> find_primes(I nMaxNumber);

/**
    @brief      Is number prime
    @details    1.0 probability, high computational complexity
    @complexity O(sqrt(number))
    @param      nValue - number
    @retval            - true if prime
**/
inline bool is_prime(size_t nValue);

/**
    @brief  Is number prime with some probability
    @param  nValue       - number
    @param  fProbability - probability (0, 1]
    @retval              - true is number is prime with some probability
**/
inline bool is_prime(size_t nValue, double fProbability);

} // namespace qx

#include <qx/math/prime.inl>
