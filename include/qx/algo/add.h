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
    @tparam ContainerType - container type
    @tparam ValueType     - value type
    @param  container     - container to add to
    @param  value         - value to check and add
    @retval               - true if value was added
**/
template<class ContainerType, class ValueType>
bool add_unique(ContainerType& container, const ValueType& value)
{
    if (!contains(container, value))
    {
        container.insert(container.end(), value);
        return true;
    }
    else
    {
        return false;
    }
}

/**
    @brief  Add an element to the container if all elements do not satisfy the predicate
    @tparam ContainerType - container type
    @tparam ValueType     - value type
    @tparam PredicateType - predicate type which can be called with (element, value) or (element) only
    @param  container     - container to add to
    @param  value         - value to check and add
    @param  predicate     - predicate object
    @retval               - true if value was added
**/
template<class ContainerType, class ValueType, class PredicateType>
bool add_unique_if(ContainerType& container, const ValueType& value, const PredicateType& predicate)
{
    for (const auto& element : container)
    {
        if constexpr (std::is_invocable_v<PredicateType, decltype(element), const ValueType&>)
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
    container.insert(container.end(), value);
    return true;
}

} // namespace qx
