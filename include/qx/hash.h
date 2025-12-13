/**

    @file      hash.h
    @author    Khrapov
    @date      18.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <cstddef>

namespace qx
{

/**
    @brief   Get an object hash
    @details A simple wrapper over std::hash
             that removes the need to specify the type and unnecessary parentheses.
    @tparam  T     - object type
    @param   value - object value
    @retval        - object hash
**/
template<class T>
constexpr size_t get_hash(const T& value) noexcept
{
    return std::hash<T>()(value);
}

/**
    @brief  Combine hashes
    @tparam T     - object type
    @param  seed  - input/output hash value
    @param  value - object to hash
**/
template<class T>
constexpr void hash_combine(size_t& seed, const T& value) noexcept
{
    seed ^= get_hash(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

} // namespace qx
