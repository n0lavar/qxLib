/**

    @file      remove.h
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
    @tparam fwd_it_t    - iterator type
    @tparam predicate_t - predicate type
    @param  itBegin     - the range of elements begin iterator
    @param  itEnd       - the range of elements end iterator
    @param  predicate   - unary predicate which returns ​true if the element should be removed
    @param  nStartIndex - we can't find out the index of itBegin so you should specify it
    @retval             - past-the-end iterator for the new range of values
**/
template<class fwd_it_t, class predicate_t>
fwd_it_t remove_if_i(fwd_it_t itBegin, fwd_it_t itEnd, const predicate_t& predicate, size_t nStartIndex = 0)
{
    fwd_it_t itDest = itBegin;
    size_t   i      = nStartIndex;
    for (fwd_it_t it = itBegin; it != itEnd; ++it)
    {
        if (!predicate(i))
            *itDest++ = std::move(*it);

        ++i;
    }
    return itDest;
}

/**
    @brief  std::remove_if with index instead of data reference
    @tparam container_t - container type
    @tparam predicate_t - predicate type
    @param  container   - the range of elements
    @param  predicate   - unary predicate which returns ​true if the element should be removed
    @retval             - past-the-end iterator for the new range of values
**/
template<class container_t, class predicate_t>
auto remove_if_i(container_t& container, const predicate_t& predicate)
{
    return remove_if_i(container.begin(), container.end(), predicate, 0);
}

} // namespace qx
