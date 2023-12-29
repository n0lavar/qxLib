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
    @brief  Check if at least one of range's elements satisfies a predicate
    @tparam fwd_it_t    - forward iterator type
    @tparam predicate_t - predicate type
    @param  itBegin     - range begin iterator
    @param  itEnd       - range end iterator
    @param  predicate   - predicate to check
    @retval             - true if at least one of range elements satisfies a predicate
**/
template<class fwd_it_t, class predicate_t>
bool contains_if(fwd_it_t itBegin, fwd_it_t itEnd, const predicate_t& predicate)
{
    return std::find_if(itBegin, itEnd, predicate) != itEnd;
}

/**
    @brief  Check if at least one of range's elements satisfies a predicate
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

/**
    @brief  Check that at least one element from the first range is equal to at least one element from the second range
    @tparam where_fwd_it_t - first range's iterator type
    @tparam what_fwd_it_t  - second range's iterator type
    @param  itWhereBegin   - first range's start iterator
    @param  itWhereEnd     - first range's end iterator
    @param  itWhatBegin    - second range's start iterator
    @param  itWhatEnd      - second range's end iterator
    @retval                - true if found 
**/
template<class where_fwd_it_t, class what_fwd_it_t>
constexpr bool contains_any(
    where_fwd_it_t itWhereBegin,
    where_fwd_it_t itWhereEnd,
    what_fwd_it_t  itWhatBegin,
    what_fwd_it_t  itWhatEnd)
{
    for (what_fwd_it_t it = itWhatBegin; it != itWhatEnd; ++it)
        if (contains(itWhereBegin, itWhereEnd, *it))
            return true;

    return false;
}

/**
    @brief  Check that at least one element from the first range is equal to at least one element from the second range
    @tparam where_container_t - first range's type
    @tparam what_container_t  - second range's type
    @param  whereContainer    - first range
    @param  whatContainer     - second range
    @retval                   - true if found
**/
template<class where_container_t, class what_container_t>
constexpr bool contains_any(const where_container_t& whereContainer, const what_container_t& whatContainer)
{
    return contains_any(whereContainer.begin(), whereContainer.end(), whatContainer.begin(), whatContainer.end());
}

} // namespace qx
