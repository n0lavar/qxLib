/**

    @file      prime.gtest.cpp
    @author    Khrapov
    @date      7.08.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/
#include <common.h>

#include <qx/math/prime.h>

//V_EXCLUDE_PATH *.gtest.cpp

TEST(prime, find_prime_factors)
{
    ASSERT_EQ(qx::find_prime_factors(0), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(qx::find_prime_factors(1), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(qx::find_prime_factors(2), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2 }));
    ASSERT_EQ(qx::find_prime_factors(-1), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(qx::find_prime_factors(-2), GTEST_SINGLE_ARGUMENT(std::vector<int> { -2 }));
    ASSERT_EQ(qx::find_prime_factors(6), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3 }));
    ASSERT_EQ(qx::find_prime_factors(10), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 5 }));
    ASSERT_EQ(qx::find_prime_factors(144), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 2, 2, 2, 3, 3 }));
    ASSERT_EQ(qx::find_prime_factors(65), GTEST_SINGLE_ARGUMENT(std::vector<int> { 5, 13 }));
    ASSERT_EQ(qx::find_prime_factors(88), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 2, 2, 11 }));
    ASSERT_EQ(qx::find_prime_factors(-88), GTEST_SINGLE_ARGUMENT(std::vector<int> { -2, 2, 2, 11 }));
}

TEST(prime, find_primes)
{
    ASSERT_EQ(qx::find_primes(0), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(qx::find_primes(1), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(qx::find_primes(2), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2 }));
    ASSERT_EQ(qx::find_primes(3), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3 }));
    ASSERT_EQ(qx::find_primes(4), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3 }));
    ASSERT_EQ(qx::find_primes(5), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5 }));
    ASSERT_EQ(qx::find_primes(6), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5 }));
    ASSERT_EQ(qx::find_primes(7), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(qx::find_primes(8), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(qx::find_primes(9), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(qx::find_primes(10), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(qx::find_primes(11), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11 }));
    ASSERT_EQ(qx::find_primes(12), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11 }));
    ASSERT_EQ(qx::find_primes(13), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13 }));
    ASSERT_EQ(qx::find_primes(14), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13 }));
    ASSERT_EQ(qx::find_primes(15), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13 }));
    ASSERT_EQ(qx::find_primes(23), GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13, 17, 19, 23 }));
}

TEST(prime, is_prime)
{
    ASSERT_EQ(qx::is_prime(0), false);
    ASSERT_EQ(qx::is_prime(1), false);
    ASSERT_EQ(qx::is_prime(2), true);
    ASSERT_EQ(qx::is_prime(3), true);
    ASSERT_EQ(qx::is_prime(4), false);
    ASSERT_EQ(qx::is_prime(5), true);
    ASSERT_EQ(qx::is_prime(6), false);
    ASSERT_EQ(qx::is_prime(7), true);
    ASSERT_EQ(qx::is_prime(8), false);
    ASSERT_EQ(qx::is_prime(9), false);
    ASSERT_EQ(qx::is_prime(10), false);
    ASSERT_EQ(qx::is_prime(11), true);
    ASSERT_EQ(qx::is_prime(12), false);
    ASSERT_EQ(qx::is_prime(13), true);
    ASSERT_EQ(qx::is_prime(14), false);
    ASSERT_EQ(qx::is_prime(15), false);
    ASSERT_EQ(qx::is_prime(16), false);
    ASSERT_EQ(qx::is_prime(17), true);
    ASSERT_EQ(qx::is_prime(18), false);
    ASSERT_EQ(qx::is_prime(19), true);
}

TEST(prime, modular_arithmetic)
{
    constexpr size_t nMax = std::numeric_limits<size_t>::max();
    static_assert(qx::details::prime_multiply_mod(nMax - 1, nMax - 1, nMax) == 1);
    static_assert(qx::details::prime_power_mod(nMax - 1, 2, nMax) == 1);
    static_assert(qx::details::prime_power_mod(nMax - 1, 3, nMax) == nMax - 1);
    static_assert(qx::details::prime_power_mod(7, 0, 11) == 1);
    static_assert(qx::details::prime_power_mod(11, 10, 11) == 0);
    static_assert(qx::details::prime_power_mod(2, nMax, 3) == 2);

    for (size_t nModulus = 2; nModulus < 30; ++nModulus)
        for (size_t a = 0; a < nModulus; ++a)
            for (size_t b = 0; b < nModulus; ++b)
                EXPECT_EQ(qx::details::prime_multiply_mod(a, b, nModulus), (a * b) % nModulus);
}
