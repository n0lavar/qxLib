/**

    @file      utils.h
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
    @tparam iterator_t - iterator type
    @param  itStart      - start iterator
    @param  itEnd        - end iterator
**/
template<class iterator_t>
inline void destruct(iterator_t itStart, iterator_t itEnd);

/**
    @brief  Fill array with value in constructor
    @tparam N        - number of elements in array
    @tparam T        - array value type
    @param  init_val - init value
    @retval          - filled array
**/
template<size_t N, class T>
constexpr auto make_array(T init_val = T());

/**
    @brief  Join arrays at compile-time
    @tparam T           - array value_type
    @tparam LeftLength  - left array length
    @tparam RightLength - right array length
    @param  rhs         - left array
    @param  lhs         - right array
    @retval             - new array where elements from the right array placed after elements from the left array
**/
template<class T, std::size_t LeftLength, std::size_t RightLength>
constexpr std::array<T, LeftLength + RightLength> join_arrays(
    std::array<T, LeftLength>  rhs,
    std::array<T, RightLength> lhs);

/**
    @brief  Create a container by constructing each element from the corresponding
            element of the original container
    @tparam result_container_t - target container type, must support value_type and push_back
    @tparam container_t        - original container type, must support forward iteration
    @param  from               - original container
    @retval                    - target container
**/
template<class result_container_t, class container_t>
result_container_t make_container(const container_t& from);

/**
    @brief  Get the size of memory allocated for container elements
    @tparam container_t - container type
    @param  container   - container const ref
    @retval             - the size of memory allocated for container elements
**/
template<class container_t>
constexpr size_t bytes_size(const container_t& container);

} // namespace qx

#include <qx/containers/utils.inl>
