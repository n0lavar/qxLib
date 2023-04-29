/**

    @file      common.inl
    @author    Khrapov
    @date      29.04.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/

namespace qx
{

template<class T>
constexpr T abs(T value)
{
    return value < 0 ? -value : value;
}

template<class T>
constexpr bool epsilon_equal(T left, T right, T eps)
{
    return abs(left - right) < eps;
}

template<class T>
constexpr bool epsilon_zero(T value, T eps)
{
    return abs(value) < eps;
}

template<class T>
constexpr bool epsilon_less_equal(T left, T right, T eps)
{
    return left < right || epsilon_equal(left, right, eps);
}

template<class T>
constexpr bool epsilon_greater_equal(T left, T right, T eps)
{
    return left > right || epsilon_equal(left, right, eps);
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
inline double pow(T number, int nPower)
{
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Integral or floating point required");

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

template<std::integral I>
I maxpot(I nValue)
{
    static_assert(std::is_integral_v<I>, "Integral required");

    if (nValue == 0)
        return 0;

    std::bitset<std::numeric_limits<I>::digits> powers(static_cast<size_t>(abs(nValue)));

    I nPow = static_cast<I>(std::numeric_limits<I>::digits - 1);
    while (!powers.test(static_cast<size_t>(nPow)))
        --nPow;

    return nPow;
}

// trick to determine if an integer is between two integers (inclusive)
// with only one comparison/branch
// https://stackoverflow.com/a/17095534/8021662
QX_DISABLE_MSVC_WARNINGS(4018 4388);

template<class T, class compare_t>
constexpr bool between(T left, T value, T right, compare_t compare)
{
    if constexpr (std::is_enum_v<T>)
    {
        i64 l = static_cast<i64>(left);
        i64 r = static_cast<i64>(right);
        i64 v = static_cast<i64>(value);
        return between(l, v, r, compare);
    }
    else if constexpr (std::is_integral_v<T> && std::is_same_v<compare_t, std::less_equal<>>)
    {
        return compare(static_cast<size_t>(value - left), right - left);
    }
    else if constexpr (std::is_floating_point_v<T> && std::is_same_v<compare_t, std::less_equal<>>)
    {
        return epsilon_less_equal(left, value) && epsilon_less_equal(value, right);
    }
    else
    {
        return compare(left, value) && compare(value, right);
    }
}

template<class T, class compare_t>
constexpr bool between(T left, T value, T right)
{
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4388);
    return between(left, value, right, compare_t());
    QX_POP_SUPPRESS_WARNINGS();
}

QX_RESTORE_MSVC_WARNINGS(4018 4388);

} // namespace qx
