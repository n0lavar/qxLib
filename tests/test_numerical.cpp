/**

    @file      test_numerical.cpp
    @author    Khrapov
    @date      10.03.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_numerical.cpp

#if QX_TEST_NUMERICAL

#include <qx/alg/numerical.h>
#include <qx/useful_macros.h>


TEST(numerical, gcd)
{
    ASSERT_EQ(qx::gcd(0, 0), 0);
    ASSERT_EQ(qx::gcd(0, 1), 0);
    ASSERT_EQ(qx::gcd(0, 10), 0);
    ASSERT_EQ(qx::gcd(1, 0), 0);
    ASSERT_EQ(qx::gcd(10, 0), 0);
    ASSERT_EQ(qx::gcd(10, 10), 10);
    ASSERT_EQ(qx::gcd(-10, 10), 10);
    ASSERT_EQ(qx::gcd(10, -10), 10);
    ASSERT_EQ(qx::gcd(-10, -10), 10);
    ASSERT_EQ(qx::gcd(15, 3), 3);
    ASSERT_EQ(qx::gcd(3, 15), 3);
    ASSERT_EQ(qx::gcd(-12, -10), 2);
    ASSERT_EQ(qx::gcd(-10, 12), 2);
    ASSERT_EQ(qx::gcd(17, 3), 1);
    ASSERT_EQ(qx::gcd(17, 1), 1);
    ASSERT_EQ(qx::gcd(-17, -16), 1);
    ASSERT_EQ(qx::gcd(-7, 1), 1);
}

TEST(numerical, lcm)
{
    ASSERT_EQ(qx::lcm(0, 0), 0);
    ASSERT_EQ(qx::lcm(0, 1), 0);
    ASSERT_EQ(qx::lcm(0, 10), 0);
    ASSERT_EQ(qx::lcm(1, 0), 0);
    ASSERT_EQ(qx::lcm(10, 0), 0);
    ASSERT_EQ(qx::lcm(10, 10), 10);
    ASSERT_EQ(qx::lcm(-10, 10), 10);
    ASSERT_EQ(qx::lcm(10, -10), 10);
    ASSERT_EQ(qx::lcm(-10, -10), 10);
    ASSERT_EQ(qx::lcm(15, 3), 15);
    ASSERT_EQ(qx::lcm(3, 15), 15);
    ASSERT_EQ(qx::lcm(-12, -10), 60);
    ASSERT_EQ(qx::lcm(-10, 12), 60);
    ASSERT_EQ(qx::lcm(17, 3), 51);
    ASSERT_EQ(qx::lcm(17, 1), 17);
    ASSERT_EQ(qx::lcm(-17, -16), 272);
    ASSERT_EQ(qx::lcm(-7, 1), 7);
}

TEST(numerical, pow)
{
    ASSERT_DOUBLE_EQ(qx::pow(0, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(-1, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(5, 0), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, 1), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, 5), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, -5), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(1, -1), 1.0);
    ASSERT_DOUBLE_EQ(qx::pow(4, 5), 1024.0);
    ASSERT_DOUBLE_EQ(qx::pow(4, -5), 0.0009765625);
}

TEST(numerical, maxpot)
{
    ASSERT_EQ(qx::maxpot(0), 0);
    ASSERT_EQ(qx::maxpot(1), 0);
    ASSERT_EQ(qx::maxpot(-1), 0);
    ASSERT_EQ(qx::maxpot(2), 1);
    ASSERT_EQ(qx::maxpot(-2), 1);
    ASSERT_EQ(qx::maxpot(3), 1);
    ASSERT_EQ(qx::maxpot(4), 2);
    ASSERT_EQ(qx::maxpot(7), 2);
    ASSERT_EQ(qx::maxpot(8), 3);
    ASSERT_EQ(qx::maxpot(17), 4);
}

TEST(numerical, find_prime_factors)
{
    ASSERT_EQ(
        qx::find_prime_factors(0),
        GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(
        qx::find_prime_factors(1),
        GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(
        qx::find_prime_factors(2),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2 }));
    ASSERT_EQ(
        qx::find_prime_factors(-1),
        GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(
        qx::find_prime_factors(-2),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { -2 }));
    ASSERT_EQ(
        qx::find_prime_factors(6),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3 }));
    ASSERT_EQ(
        qx::find_prime_factors(10),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 5 }));
    ASSERT_EQ(
        qx::find_prime_factors(144),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 2, 2, 2, 3, 3 }));
    ASSERT_EQ(
        qx::find_prime_factors(65),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 5, 13 }));
    ASSERT_EQ(
        qx::find_prime_factors(88),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 2, 2, 11 }));
    ASSERT_EQ(
        qx::find_prime_factors(-88),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { -2, 2, 2, 11 }));
}

TEST(numerical, find_primes)
{
    ASSERT_EQ(qx::find_primes(0), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(qx::find_primes(1), GTEST_SINGLE_ARGUMENT(std::vector<int> {}));
    ASSERT_EQ(
        qx::find_primes(2),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2 }));
    ASSERT_EQ(
        qx::find_primes(3),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3 }));
    ASSERT_EQ(
        qx::find_primes(4),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3 }));
    ASSERT_EQ(
        qx::find_primes(5),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5 }));
    ASSERT_EQ(
        qx::find_primes(6),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5 }));
    ASSERT_EQ(
        qx::find_primes(7),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(
        qx::find_primes(8),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(
        qx::find_primes(9),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(
        qx::find_primes(10),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7 }));
    ASSERT_EQ(
        qx::find_primes(11),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11 }));
    ASSERT_EQ(
        qx::find_primes(12),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11 }));
    ASSERT_EQ(
        qx::find_primes(13),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13 }));
    ASSERT_EQ(
        qx::find_primes(14),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13 }));
    ASSERT_EQ(
        qx::find_primes(15),
        GTEST_SINGLE_ARGUMENT(std::vector<int> { 2, 3, 5, 7, 11, 13 }));
    ASSERT_EQ(
        qx::find_primes(23),
        GTEST_SINGLE_ARGUMENT(
            std::vector<int> { 2, 3, 5, 7, 11, 13, 17, 19, 23 }));
}

TEST(numerical, is_prime)
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

#endif
