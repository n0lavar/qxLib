/**

    @file      equal.h
    @author    Khrapov
    @date      20.08.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @brief   Check if two ranges contains same values in a certain order, which may be shifted
    @details For { 0, 1, 2 } returns true for { 1, 2, 0 }, but false for { 1, 2 } and { 2, 1, 0 }
    @tparam  it_1_t      - first range iterator type
    @tparam  it_2_t      - second range iterator type
    @tparam  pred_t      - predicate type
    @param   range1Begin - first range begin iterator
    @param   range1End   - first range end iterator
    @param   range2Begin - second range begin iterator
    @param   range2End   - second range end iterator
    @param   pred        - predicate that compares values from left and right ranges
    @retval              - true if ranges are equal
**/
template<class it_1_t, class it_2_t, class pred_t>
inline bool equal_rotated(
    it_1_t        range1Begin,
    it_1_t        range1End,
    it_2_t        range2Begin,
    it_2_t        range2End,
    const pred_t& pred) noexcept;

/**
    @brief   Check if two ranges contains same values in a certain order, which may be shifted
    @details For { 0, 1, 2 } returns true for { 1, 2, 0 }, but false for { 1, 2 } and { 2, 1, 0 }
    @tparam  range_1_t - first range type
    @tparam  range_2_t - second range type
    @tparam  pred_t    - predicate type
    @param   range1    - first range 
    @param   range2    - second range
    @param   pred      - predicate that compares values from left and right ranges
    @retval            - true if ranges are equal
**/
template<class range_1_t, class range_2_t, class pred_t>
inline bool equal_rotated(const range_1_t& range1, const range_2_t& range2, const pred_t& pred) noexcept;

/**
    @brief   Check if two ranges contains same values in a certain order, which may be shifted
    @details For { 0, 1, 2 } returns true for { 1, 2, 0 }, but false for { 1, 2 } and { 2, 1, 0 }
    @tparam  it_1_t      - first range iterator type
    @tparam  it_2_t      - second range iterator type
    @param   range1Begin - first range begin iterator
    @param   range1End   - first range end iterator
    @param   range2Begin - second range begin iterator
    @param   range2End   - second range end iterator
    @retval              - true if ranges are equal
**/
template<class it_1_t, class it_2_t>
inline bool equal_rotated(it_1_t range1Begin, it_1_t range1End, it_2_t range2Begin, it_2_t range2End) noexcept;

/**
    @brief   Check if two ranges contains same values in a certain order, which may be shifted
    @details For { 0, 1, 2 } returns true for { 1, 2, 0 }, but false for { 1, 2 } and { 2, 1, 0 }
    @tparam  range_1_t - first range type
    @tparam  range_2_t - second range type
    @param   range1    - first range
    @param   range2    - second range
    @retval            - true if ranges are equal
**/
template<class range_1_t, class range_2_t>
inline bool equal_rotated(const range_1_t& range1, const range_2_t& range2) noexcept;

} // namespace qx

#include <qx/algo/equal.inl>
