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

#include <algorithm>
#include <array>
#include <functional>

namespace qx
{

// trick to determine if an integer is between two integers (inclusive)
// with only one comparison/branch
// https://stackoverflow.com/a/17095534/8021662
QX_DISABLE_MSVC_WARNINGS(4018 4388)

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
        return compare(static_cast<size_t>(value - left), right - left);
    }
    else if constexpr (
        std::is_floating_point_v<
            T> && std::is_same_v<Compare, std::less_equal<>>)
    {
        return qx::epsilon_less_equal(left, value)
               && qx::epsilon_less_equal(value, right);
    }
    else
    {
        return compare(left, value) && compare(value, right);
    }
}

QX_RESTORE_MSVC_WARNINGS(4018 4388)

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

/**
    @brief  Join arrays at compile-time
    @tparam T           - array value_type
    @tparam LeftLength  - left array length
    @tparam RightLength - right array length
    @param  rhs         - left array
    @param  lhs         - right array
    @retval             - new array where elements from the right array placed after elements from the left array
**/
template<typename T, std::size_t LeftLength, std::size_t RightLength>
constexpr std::array<T, LeftLength + RightLength> join_arrays(
    std::array<T, LeftLength>  rhs,
    std::array<T, RightLength> lhs)
{
    std::array<T, LeftLength + RightLength> res;
    auto current = std::copy(rhs.begin(), rhs.end(), res.begin());
    std::copy(lhs.begin(), lhs.end(), current);
    return res;
}

/**
    @brief  Create a container by constructing each element from the corresponding
            element of the original container
    @tparam ContainerTo   - target container type, must support value_type and push_back
    @tparam ContainerFrom - original container type, must support forward iteration
    @param  from          - original container
    @retval               - target container
**/
template<class ContainerTo, class ContainerFrom>
ContainerTo create_container(const ContainerFrom& from)
{
    ContainerTo container;

    for (const auto& item : from)
        container.push_back(typename ContainerTo::value_type(item));

    return container;
}

/**
    @brief  Get the size of memory allocated for container elements
    @tparam Container - container type
    @param  container - container const ref
    @retval           - the size of memory allocated for container elements
**/
template<class Container>
constexpr size_t bytes_size(const Container& container)
{
    return container.size() * sizeof(typename Container::value_type);
}

} // namespace qx
