/**

    @file      add_unique.h
    @brief     Contains add unique algorithms
    @details   ~
    @author    Khrapov
    @date      14.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/algo/contains.h>

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

} // namespace qx
