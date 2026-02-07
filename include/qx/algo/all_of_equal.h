/**

    @file      all_of_equal.h
    @author    Khrapov
    @date      7.02.2026
    @copyright © Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <algorithm>

namespace qx
{

/**
    @brief   Returns true if the predicate yields the same boolean value for all elements in the range [itBegin, itEnd).
             That is, either the predicate is true for every element or false for every element;
             otherwise returns false.
    @details This implements a logical biconditional (logical equivalence) over the range:
             predicate(x1) <-> predicate(x2) <-> ... <-> predicate(xn)
    @tparam  fwd_it_t    - forward iterator type
    @tparam  predicate_t - predicate type
    @param   itBegin     - range begin iterator
    @param   itEnd       - range end iterator
    @param   predicate   - predicate to check
    @retval              - true if the predicate yields the same boolean value for all elements in the range, otherwise false
**/
template<class fwd_it_t, class predicate_t>
bool all_of_equal(fwd_it_t itBegin, fwd_it_t itEnd, const predicate_t& predicate)
{
    if (itBegin == itEnd)
        return true;

    const bool bFirst = static_cast<bool>(std::invoke(predicate, *itBegin));
    return std::all_of(
        ++itBegin,
        itEnd,
        [bFirst, &predicate](const auto& x)
        {
            return static_cast<bool>(std::invoke(predicate, x)) == bFirst;
        });
}

/**
    @brief   Returns true if the predicate yields the same boolean value for all elements in the range [itBegin, itEnd).
             That is, either the predicate is true for every element or false for every element;
             otherwise returns false.
    @details This implements a logical biconditional (logical equivalence) over the range:
             predicate(x1) <-> predicate(x2) <-> ... <-> predicate(xn)
    @tparam  container_t - container type
    @tparam  predicate_t - predicate type
    @param   container   - input range
    @param   predicate   - predicate to check
    @retval              - true if the predicate yields the same boolean value for all elements in the range, otherwise false
**/
template<class container_t, class predicate_t>
bool all_of_equal(const container_t& container, const predicate_t& predicate)
{
    return all_of_equal(std::begin(container), std::end(container), predicate);
}

} // namespace qx
