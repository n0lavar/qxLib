/**

    @file      remove.h
    @brief     Contains std::remove extensions
    @details   ~
    @author    Khrapov
    @date      6.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <utility>

namespace qx
{

/**
    @brief  std::remove_if with index instead of data reference
    @tparam FwdItType     - iterator type
    @tparam PredicateType - predicate type
    @param  itBegin       - the range of elements begin iterator
    @param  itEnd         - the range of elements end iterator
    @param  predicate     - unary predicate which returns ​true if the element should be removed
    @param  nStartIndex   - we can't find out the index of itBegin so you should specify it
    @retval               - past-the-end iterator for the new range of values
**/
template<class FwdItType, class PredicateType>
FwdItType remove_if_i(FwdItType itBegin, FwdItType itEnd, const PredicateType& predicate, size_t nStartIndex = 0)
{
    FwdItType itDest = itBegin;
    size_t    i      = nStartIndex;
    for (FwdItType it = itBegin; it != itEnd; ++it)
    {
        if (!predicate(i))
            *itDest++ = std::move(*it);

        ++i;
    }
    return itDest;
}

/**
    @brief  std::remove_if with index instead of data reference
    @tparam ContainerType - container type
    @tparam PredicateType - predicate type
    @param  container     - the range of elements
    @param  predicate     - unary predicate which returns ​true if the element should be removed
    @param  nStartIndex   - we can't find out the index of itBegin so you should specify it
    @retval               - past-the-end iterator for the new range of values
**/
template<class ContainerType, class PredicateType>
auto remove_if_i(ContainerType& container, const PredicateType& predicate, size_t nStartIndex = 0)
{
    return remove_if_i(container.begin(), container.end(), predicate, nStartIndex);
}

} // namespace qx
