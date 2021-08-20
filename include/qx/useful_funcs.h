/**

    @file      useful_funcs.h
    @brief     Different useful functions
    @author    Khrapov
    @date      1.11.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/math.h>
#include <qx/suppress_warnings.h>
#include <qx/typedefs.h>

#include <array>
#include <functional>

namespace qx
{

/**
    @brief  Checks if value is between left and right
    @tparam T       - value type
    @tparam Compare - comparator type
    @param  left    - left value
    @param  value   - value
    @param  right   - right value
    @param  compare - comparator function
    @retval         - true, left <= value <= right
**/
template<typename T, typename Compare = std::less_equal<>>
constexpr bool between(T left, T value, T right, Compare compare)
{
    // trick to determine if an integer is between two integers (inclusive)
    // with only one comparison/branch
    // https://stackoverflow.com/a/17095534/8021662
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4018 4388)

    if constexpr (std::is_enum_v<T>)
    {
        i64 l = static_cast<i64>(left);
        i64 r = static_cast<i64>(right);
        i64 v = static_cast<i64>(value);
        return between(l, v, r, compare);
    }
    else if constexpr (
        std::is_integral_v<T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return compare(static_cast<size_t>(value - left), (right - left));
    }
    else if constexpr (
        std::is_floating_point_v<
            T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return (left < value || qx::epsilon_equal(left, value))
               && (value < right || qx::epsilon_equal(value, right));
    }
    else
    {
        return compare(left, value) && compare(value, right);
    }

    QX_POP_SUPPRESS_WARNINGS
}

/**
    @brief   Checks if value is between left and right
    @details Overloading for disabling 4388 warning with Compare instantiation
    @tparam  T       - value type
    @tparam  Compare - comparator type
    @param   left    - left value
    @param   value   - value
    @param   right   - right value
    @retval          - true, left <= value <= right
**/
template<typename T, typename Compare = std::less_equal<>>
constexpr bool between(T left, T value, T right)
{
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4388)
    return between(left, value, right, Compare());
    QX_POP_SUPPRESS_WARNINGS
}

/**
    @brief  Call destructors
    @tparam iterator - iterator type
    @param  start    - start iterator
    @param  end      - end iterator
**/
template<class iterator>
inline void destruct(iterator start, iterator end)
{
    using T = typename iterator::value_type;
    if constexpr (std::is_compound_v<T>)
    {
        for (auto it = start; it != end; ++it)
            it->~T();
    }
}

/**
    @brief  Fill array with value in constructor
    @tparam N        - number of elements in array
    @tparam T        - array value type
    @param  init_val - init value
    @retval          - filled array
**/
template<size_t N, typename T>
constexpr auto make_array(T init_val = T())
{
    std::array<T, N> ret;
    ret.fill(init_val);
    return ret;
}

} // namespace qx
