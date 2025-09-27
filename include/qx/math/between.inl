/**

    @file      between.inl
    @author    Khrapov
    @date      25.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/

namespace qx
{

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
