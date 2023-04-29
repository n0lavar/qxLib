/**

    @file      add.h
    @brief     Contains add algorithms
    @details   ~
    @author    Khrapov
    @date      14.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/algo/contains.h>

#include <type_traits>

namespace qx
{

/**
    @brief  Add an element to the container if it doesn't already contain one 
    @tparam container_t - container type
    @tparam value_t     - value type
    @param  container   - container to add to
    @param  value       - value to check and add
    @retval             - true if value was added
**/
template<class container_t, class value_t>
bool add_unique(container_t& container, value_t&& value)
{
    if (!contains(container, value))
    {
        container.insert(container.end(), std::forward<value_t>(value));
        return true;
    }
    else
    {
        return false;
    }
}

/**
    @brief  Add an element to the container if all elements do not satisfy the predicate
    @tparam container_t - container type
    @tparam value_t     - value type
    @tparam predicate_t - predicate type which can be called with (element, value) or (element) only
    @param  container   - container to add to
    @param  value       - value to check and add
    @param  predicate   - predicate object
    @retval             - true if value was added
**/
template<class container_t, class value_t, class predicate_t>
bool add_unique_if(container_t& container, value_t&& value, const predicate_t& predicate)
{
    for (const auto& element : container)
    {
        if constexpr (std::is_invocable_v<predicate_t, decltype(element), const value_t&>)
        {
            if (predicate(element, value))
                return false;
        }
        else
        {
            if (predicate(element))
                return false;
        }
    }

    container.insert(container.end(), std::forward<value_t>(value));
    return true;
}

} // namespace qx
