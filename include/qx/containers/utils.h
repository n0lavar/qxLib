/**

    @file      utils.h
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <algorithm>
#include <array>
#include <span>

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
    @return          - filled array
**/
template<size_t N, class T>
constexpr std::array<T, N> make_array(T init_val = T());

/**
    @brief  Join arrays at compile-time
    @tparam T           - array value_type
    @tparam LeftLength  - left array length
    @tparam RightLength - right array length
    @param  rhs         - left array
    @param  lhs         - right array
    @return             - new array where elements from the right array placed after elements from the left array
**/
template<class T, std::size_t LeftLength, std::size_t RightLength>
constexpr std::array<T, LeftLength + RightLength> join_arrays(
    std::array<T, LeftLength>  rhs,
    std::array<T, RightLength> lhs);

/**
    @brief  Convert a span to an array
    @tparam N    - span and array compile time size
    @tparam T    - span and array type
    @param  span - span object
    @return      - array object
**/
template<std::size_t N, class T>
constexpr std::array<T, N> span_to_array(std::span<T, N> span);

/**
    @brief  Get the size of memory allocated for container elements
    @tparam container_t - container type
    @param  container   - container const ref
    @return             - the size of memory allocated for container elements
**/
template<class container_t>
constexpr size_t bytes_size(const container_t& container);

} // namespace qx

#include <qx/containers/utils.inl>
