/**

    @file      contains.h
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <algorithm>

namespace qx
{

/**
    @brief  Check if range contains value
    @tparam fwd_it_t - forward iterator type
    @tparam T        - value type
    @param  itBegin  - range begin iterator
    @param  itEnd    - range end iterator
    @param  value    - value to check
    @retval          - true if range contains value
**/
template<class fwd_it_t, class T>
bool contains(fwd_it_t itBegin, fwd_it_t itEnd, const T& value)
{
    return std::find(itBegin, itEnd, value) != itEnd;
}

/**
    @brief  Check if container contains value
    @tparam container_t - container type
    @tparam T           - value type
    @param  container   - container to search in
    @param  value       - value to check
    @retval             - true if container contains value
**/
template<class container_t, class T>
bool contains(const container_t& container, const T& value)
{
    return contains(container.begin(), container.end(), value);
}

/**
    @brief  Check if at least one of range elements satisfies predicate
    @tparam fwd_it_t    - forward iterator type
    @tparam predicate_t - predicate type
    @param  itBegin     - range begin iterator
    @param  itEnd       - range end iterator
    @param  predicate   - predicate to check
    @retval             - true if at least one of range elements satisfies predicate
**/
template<class fwd_it_t, class predicate_t>
bool contains_if(fwd_it_t itBegin, fwd_it_t itEnd, const predicate_t& predicate)
{
    return std::find_if(itBegin, itEnd, predicate) != itEnd;
}

/**
    @brief  Check if at least one of container elements satisfies predicate
    @tparam container_t - container type
    @tparam predicate_t - predicate type
    @param  container   - container to search in
    @param  predicate   - predicate to check
    @retval             - true if at least one of container elements satisfies predicate
**/
template<class container_t, class predicate_t>
bool contains_if(const container_t& container, const predicate_t& predicate)
{
    return contains_if(container.begin(), container.end(), predicate);
}

} // namespace qx
