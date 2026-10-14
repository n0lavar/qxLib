/**

    @file      easing_functions.inl
    @author    Khrapov
    @date      14.10.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/

namespace qx::easing
{

template<class T>
constexpr T eps()
{
    return T(1e-14f);
}

template<>
constexpr float eps()
{
    return 1e-6f;
}

template<class T>
constexpr T linear_func(T x) noexcept
{
    return x;
}

template<class T>
constexpr T step_func(T x) noexcept
{
    return x < T(0.5f) ? T(0.0f) : T(1.0f);
}

template<class T>
inline T smooth_step_func(T x) noexcept
{
    if (epsilon_less_equal(x, T(0.0f)))
        return T(0.0f);
    else if (epsilon_greater_equal(x, T(1.0f)))
        return T(1.0f);
    else
        return (T(3.0f) - T(2.0f) * x) * std::pow(x, T(2.0f));
}

template<class T>
inline T smoother_step_func(T x) noexcept
{
    if (epsilon_less_equal(x, T(0.0f)))
        return T(0.0f);
    else if (epsilon_greater_equal(x, T(1.0f)))
        return T(1.0f);
    else
        return std::pow(x, T(3.0f)) * (x * (x * T(6.0f) - T(15.0f)) + T(10.0f));
}

template<class T>
inline T quadratic_in_func(T x) noexcept
{
    return std::pow(x, T(2.0f));
}

template<class T>
constexpr T quadratic_out_func(T x) noexcept
{
    return -x * (x - T(2.0f));
}

template<class T>
inline T quadratic_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
        return T(2.0f) * std::pow(x, T(2.0f));
    else
        return T(1.0f) - T(2.0f) * std::pow(T(1.0f) - x, T(2.0f));
}

template<class T>
inline T cubic_in_func(T x) noexcept
{
    return std::pow(x, T(3.0f));
}

template<class T>
inline T cubic_out_func(T x) noexcept
{
    return std::pow(x - T(1.0f), T(3.0f)) + T(1.0f);
}

template<class T>
inline T cubic_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
        return T(4.0f) * std::pow(x, T(3.0f));
    else
        return T(1.0f) - T(4.0f) * std::pow(T(1.0f) - x, T(3.0f));
}

template<class T>
inline T quartic_in_func(T x) noexcept
{
    return std::pow(x, T(4.0f));
}

template<class T>
inline T quartic_out_func(T x) noexcept
{
    return T(1.0f) - std::pow(T(1.0f) - x, T(4.0f));
}

template<class T>
inline T quartic_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
        return 8 * std::pow(x, T(4.0f));
    else
        return T(1.0f) - T(8.0f) * std::pow(T(1.0f) - x, T(4.0f));
}

template<class T>
inline T quintic_in_func(T x) noexcept
{
    return std::pow(x, T(5.0f));
}

template<class T>
inline T quintic_out_func(T x) noexcept
{
    return T(1.0f) + std::pow(x - T(1.0f), T(5.0f));
}

template<class T>
inline T quintic_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
        return T(16.0f) * std::pow(x, T(5.0f));
    else
        return T(1.0f) - T(16.0f) * std::pow(T(1.0f) - x, T(5.0f));
}

template<class T>
inline T sine_in_func(T x) noexcept
{
    return T(1.0f) + static_cast<T>(std::sin(std::numbers::pi_v<T> / T(2.0f) * (x - T(1.0f))));
}

template<class T>
inline T sine_out_func(T x) noexcept
{
    return static_cast<T>(std::sin(std::numbers::pi_v<T> / T(2.0f) * x));
}

template<class T>
inline T sine_in_out_func(T x) noexcept
{
    return T(0.5f) * (T(1.0f) - static_cast<T>(std::cos(x * std::numbers::pi_v<T>)));
}

template<class T>
inline T circular_in_func(T x) noexcept
{
    return T(1.0f) - std::sqrt(T(1.0f) - std::pow(x, T(2.0f)));
}

template<class T>
inline T circular_out_func(T x) noexcept
{
    return std::sqrt((T(2.0f) - x) * x);
}

template<class T>
inline T circular_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
    {
        return T(0.5f) * (T(1.0f) - std::sqrt(T(1.0f) - T(4.0f) * std::pow(x, T(2.0f))));
    }
    else
    {
        return T(0.5f) * (T(1.0f) + std::sqrt(-T(4.0f) * std::pow(x, T(2.0f)) + T(8.0f) * x - T(3.0f)));
    }
}

template<class T>
inline T exponential_in_func(T x) noexcept
{
    return x <= T(0.0f) ? T(0.0f) : std::pow(T(2.0f), T(10.0f) * (x - T(1.0f)));
}

template<class T>
inline T exponential_out_func(T x) noexcept
{
    return x >= T(1.0f) ? T(1.0f) : T(1.0f) - std::pow(T(2.0f), -T(10.0f) * x);
}

template<class T>
inline T exponential_in_out_func(T x) noexcept
{
    if (x <= T(0.0f))
        return T(0.0f);
    else if (x < T(0.5f))
        return T(0.5f) * std::pow(T(2.0f), T(20.0f) * x - T(10.0f));
    else if (x < T(1.0f))
        return T(1.0f) - T(0.5f) * std::pow(T(2.0f), T(10.0f) - T(20.0f) * x);
    else
        return T(1.0f);
}

template<class T>
inline T elastic_in_func(T x) noexcept
{
    return std::pow(T(2.0f), T(10.0f) * (x - T(1.0f)))
           * static_cast<T>(std::sin(T(13.0f) * std::numbers::pi_v<T> / T(2.0f) * x));
}

template<class T>
inline T elastic_out_func(T x) noexcept
{
    return T(1.0f)
           - std::pow(T(2.0f), -T(10.0f) * x)
                 * static_cast<T>(std::sin(T(13.0f) * std::numbers::pi_v<T> / T(2.0f) * (x + T(1.0f))));
}

template<class T>
inline T elastic_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
    {
        return T(0.5f) * std::pow(T(2.0f), T(10.0f) * (T(2.0f) * x - T(1.0f)))
               * static_cast<T>(std::sin(T(13.0f) * std::numbers::pi_v<T> * x));
    }
    else
    {
        return T(1.0f)
               - T(0.5f) * std::pow(T(2.0f), T(10.0f) * (T(1.0f) - T(2.0f) * x))
                     * static_cast<T>(std::sin(T(13.0f) * std::numbers::pi_v<T> * x));
    }
}

template<class T>
inline T back_in_func(T x) noexcept
{
    return x * (std::pow(x, T(2.0f)) - static_cast<T>(std::sin(std::numbers::pi_v<T> * x)));
}

template<class T>
inline T back_out_func(T x) noexcept
{
    const T fInv = T(1.0f) - x;
    return T(1.0f) - fInv * (fInv * fInv - static_cast<T>(std::sin(std::numbers::pi_v<T> * fInv)));
}

template<class T>
inline T back_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
    {
        const T f2t = T(2.0f) * x;
        return T(0.5f) * f2t * (f2t * f2t - static_cast<T>(std::sin(std::numbers::pi_v<T> * f2t)));
    }
    else
    {
        const T fInv = T(2.0f) - T(2.0f) * x;
        return T(1.0f) - T(0.5f) * fInv * (fInv * fInv - static_cast<T>(std::sin(std::numbers::pi_v<T> * fInv)));
    }
}

template<class T>
inline T bounce_out_func(T x) noexcept
{
    if (x < T(4.0f) / T(11.0f))
    {
        return (T(121.0f) * std::pow(x, T(2.0f))) / T(16.0f);
    }
    else if (x < T(8.0f) / T(11.0f))
    {
        return T(363.0f) / T(40.0f) * std::pow(x, T(2.0f)) - T(99.0f) / T(10.0f) * x + T(17.0f) / T(5.0f);
    }
    else if (x < T(9.0f) / T(10.0f))
    {
        return T(4356.0f) / T(361.0f) * std::pow(x, T(2.0f)) - T(35442.0f) / T(1805.0f) * x + T(16061.0f) / T(1805.0f);
    }
    else
    {
        return T(54.0f) / T(5.0f) * std::pow(x, T(2.0f)) - T(513.0f) / T(25.0f) * x + T(268.0f) / T(25.0f);
    }
}

template<class T>
inline T bounce_in_func(T x) noexcept
{
    return T(1.0f) - bounce_out_func<T>(T(1.0f) - x);
}

template<class T>
inline T bounce_in_out_func(T x) noexcept
{
    if (x < T(0.5f))
        return T(0.5f) * bounce_in_func<T>(T(2.0f) * x);
    else
        return T(0.5f) * bounce_out_func<T>(T(2.0f) * x - T(1.0f)) + T(0.5f);
}

} // namespace qx::easing
