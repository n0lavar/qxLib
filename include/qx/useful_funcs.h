//==============================================================================
//
//!\file                        useful_funcs.h
//
//!\brief       Different useful functions
//!\details     ~
//
//!\author      Khrapov
//!\date        1.11.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/meta/constexpr_funcs.h>
#include <qx/typedefs.h>
#include <qx/config.h>
#include <qx/suppress_warnings.h>

#include <initializer_list>
#include <algorithm>
#include <cmath>
#include <functional>

namespace qx
{

//==============================================================================
//!\fn                      qx::between<T, Compare>
//
//!\brief  Checks if value is between left and right
//!\param  left  - left value
//!\param  right - right value
//!\param  value - value
//!\retval       - true if so
//!\author Khrapov
//!\date   3.11.2019
//==============================================================================
template<typename T, typename Compare = std::less_equal<>>
inline constexpr bool between(T left, T value, T right, Compare compare)
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
    else if constexpr (std::is_integral_v<T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return compare(static_cast<size_t>(value - left), (right - left));
    }
    else if constexpr (std::is_floating_point_v<T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return (left  < value || qx::meta::epsilon_equal(left,  value))
            && (value < right || qx::meta::epsilon_equal(value, right));
    }
    else
    {
        return compare(left, value) && compare(value, right);
    }

    QX_POP_SUPPRESS_WARNINGS
}
// overloading for disabling 4388 warning with Compare instantiation
template<typename T, typename Compare = std::less_equal<>>
constexpr bool between(T left, T value, T right)
{
    QX_PUSH_SUPPRESS_MSVC_WARNINGS(4388)
    return between(left, value, right, Compare());
    QX_POP_SUPPRESS_WARNINGS
}

//==============================================================================
//!\fn                              qx::pi
//
//!\brief  Get pi
//!\author Khrapov
//!\date   16.11.2019
//==============================================================================
template <typename T = float>
constexpr T pi()
{
    return static_cast<T>(3.14159265358979323846264338327950288);
}

//==============================================================================
//!\fn                      qx::destruct<iterator>
//
//!\brief  Call destructors
//!\param  start - start iterator
//!\param  end   - end iterator
//!\author Khrapov
//!\date   29.02.2020
//==============================================================================
template<class iterator>
inline void destruct(iterator start, iterator end)
{
    using T = typename iterator::value_type;
    if constexpr (std::is_compound_v<T>)
    {
        for (auto it = start; it < end; ++it)
            it->~T();
    }
}

}
