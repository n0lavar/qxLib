/**

    @file      utils.h
    @brief     Contains various utils for containers
    @details   ~
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <algorithm>
#include <array>

namespace qx
{

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
    auto                                    current = std::copy(rhs.begin(), rhs.end(), res.begin());
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
