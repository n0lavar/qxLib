/**

    @file      common.inl
    @author    Khrapov
    @date      29.04.2023
    @copyright (c) Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class T>
constexpr T abs(T value)
{
    return value < 0 ? -value : value;
}

template<std::integral T>
constexpr bool is_odd(T val)
{
    return (val & 1) == 1;
}

template<std::integral T>
constexpr bool is_even(T val)
{
    return (val & 1) == 0;
}

constexpr int gcd(int nFirst, int nSecond)
{
    if (nFirst == 0 || nSecond == 0)
        return 0;

    while (nSecond != 0)
    {
        const int nRemainder = nFirst % nSecond;
        nFirst               = nSecond;
        nSecond              = nRemainder;
    }

    return abs(nFirst);
}

constexpr int lcm(int nFirst, int nSecond)
{
    if (nFirst == 0 || nSecond == 0)
        return 0;

    nFirst  = abs(nFirst);
    nSecond = abs(nSecond);

    return nFirst / gcd(nFirst, nSecond) * nSecond;
}

template<class T>
constexpr double pow(T number, int nPower)
{
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Integral or floating point required");

    if (!std::is_constant_evaluated())
    {
        const bool   bNegativePower = nPower < 0;
        const size_t nPositivePower = static_cast<size_t>(std::abs(nPower));

        double fResult = 1.0;
        switch (nPositivePower)
        {
        case 0:
            break;

        case 1:
            fResult = static_cast<double>(number);
            break;

        case 2:
            fResult = static_cast<double>(number * number);
            break;

        default:
            const std::bitset<std::numeric_limits<int>::digits> powerBitSet(nPositivePower);

            std::array<double, std::numeric_limits<int>::digits> powers;

            powers[0] = static_cast<double>(number);

            size_t nCurPower = 1;
            size_t nCurIndex = 1;

            while (nCurPower < nPositivePower)
            {
                powers[nCurIndex] = powers[nCurIndex - 1] * powers[nCurIndex - 1];
                nCurPower *= 2;
                nCurIndex++;
            }

            for (size_t i = 0; i < nCurIndex; ++i)
                if (powerBitSet.test(i))
                    fResult *= powers[i];

            break;
        }

        return bNegativePower ? 1.0 / fResult : fResult;
    }
    else
    {
        if (nPower == 0)
        {
            return 1.0;
        }
        else if (nPower < 0)
        {
            return 1.0 / pow(number, -nPower);
        }
        else
        {
            double fResult = 1.0;
            for (int i = 0; i < nPower; ++i)
                fResult *= static_cast<double>(number);

            return fResult;
        }
    }
}

template<std::integral I>
I maxpot(I nValue)
{
    if (nValue == 0)
        return 0;

    std::bitset<std::numeric_limits<I>::digits> powers(static_cast<size_t>(abs(nValue)));

    I nPow = static_cast<I>(std::numeric_limits<I>::digits - 1);
    while (!powers.test(static_cast<size_t>(nPow)))
        --nPow;

    return nPow;
}

} // namespace qx
