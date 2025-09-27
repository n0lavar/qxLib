/**

    @file      float_compare.inl
    @author    Khrapov
    @date      25.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

template<std::floating_point T>
constexpr bool float_compare(T fLeft, T fRight, T fEps)
{
    if (epsilon_equal(fLeft, fRight, fEps))
        return true;

    return qx::abs(fLeft - fRight) <= fEps * std::max(abs(fLeft), abs(fRight));
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

} // namespace qx
