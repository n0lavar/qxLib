/**

    @file      contains.h
    @brief     Contains "contains" functions (ba-dam-tss)
    @details   ~
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
    @tparam FwdItType - forward iterator type
    @tparam T         - value type
    @param  itBegin   - range begin iterator
    @param  itEnd     - range end iterator
    @param  value     - value to check
    @retval           - true if range contains value
**/
template<class FwdItType, class T>
bool contains(FwdItType itBegin, FwdItType itEnd, const T& value)
{
    return std::find(itBegin, itEnd, value) != itEnd;
}

/**
    @brief  Check if container contains value
    @tparam ContainerType - container type
    @tparam T             - value type
    @param  container     - container to search in
    @param  value         - value to check
    @retval               - true if container contains value
**/
template<class ContainerType, class T>
bool contains(ContainerType& container, const T& value)
{
    return contains(container.begin(), container.end(), value);
}

/**
    @brief  Check if at least one of range elements satisfies predicate
    @tparam FwdItType     - forward iterator type
    @tparam PredicateType - predicate type
    @param  itBegin       - range begin iterator
    @param  itEnd         - range end iterator
    @param  predicate     - predicate to check
    @retval               - true if at least one of range elements satisfies predicate
**/
template<class FwdItType, class PredicateType>
bool contains_if(FwdItType itBegin, FwdItType itEnd, const PredicateType& predicate)
{
    return std::find_if(itBegin, itEnd, predicate) != itEnd;
}

/**
    @brief  Check if at least one of container elements satisfies predicate
    @tparam ContainerType - container type
    @tparam PredicateType - predicate type
    @param  container     - container to search in
    @param  predicate     - predicate to check
    @retval               - true if at least one of container elements satisfies predicate
**/
template<class ContainerType, class PredicateType>
bool contains_if(ContainerType& container, const PredicateType& predicate)
{
    return contains_if(container.begin(), container.end(), predicate);
}

} // namespace qx
