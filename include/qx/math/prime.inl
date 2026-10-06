/**

    @file      prime.inl
    @author    Khrapov
    @date      6.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx
{

namespace details
{

// Operands must be smaller than the nonzero modulus; avoid overflowing their sum.
constexpr size_t prime_add_mod(size_t a, size_t b, size_t nModulus) noexcept
{
    return a >= nModulus - b ? a - (nModulus - b) : a + b;
}

constexpr size_t prime_multiply_mod(size_t a, size_t b, size_t nModulus) noexcept
{
    size_t nResult = 0;
    while (b != 0)
    {
        if (b & 1)
            nResult = prime_add_mod(nResult, a, nModulus);
        b >>= 1;
        a = prime_add_mod(a, a, nModulus);
    }
    return nResult;
}

constexpr size_t prime_power_mod(size_t nBase, size_t nExponent, size_t nModulus) noexcept
{
    nBase %= nModulus;
    size_t nResult = 1;
    while (nExponent != 0)
    {
        if (nExponent & 1)
            nResult = prime_multiply_mod(nResult, nBase, nModulus);
        nExponent >>= 1;
        nBase = prime_multiply_mod(nBase, nBase, nModulus);
    }
    return nResult;
}

} // namespace details

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

inline bool is_prime(size_t nValue)
{
    return find_prime_factors(nValue).size() == 1;
}

inline bool is_prime(size_t nValue, double fProbability)
{
    if (fProbability < 0)
        fProbability = -fProbability;

    if (fProbability >= 1 || std::fabs(fProbability) <= DBL_EPSILON)
        return is_prime(nValue);

    constexpr double fLog2 = 0.30102999566; // std::log(2)

    const double nTests = std::ceil(std::log(1.0 / (1.0 - fProbability)) / fLog2);

    std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));

    std::uniform_int_distribution<size_t> num_dist(2, nValue);

    for (unsigned i = 0; i < nTests; ++i)
    {
        const size_t nRandomNumber = num_dist(generator);
        if (details::prime_power_mod(nRandomNumber, nValue - 1, nValue) != 1)
        {
            return false;
        }
    }

    return true;
}

} // namespace qx
