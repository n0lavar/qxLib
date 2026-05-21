/**

    @file      assert_compare.h
    @author    Khrapov
    @date      19.05.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once

#include <qx/algo/predicates.h>
#include <qx/containers/string/format.h>
#include <qx/containers/string/string_literal.h>

#include <functional>
#include <type_traits>
#include <utility>

namespace qx
{

/**

    @class   assert_comparison
    @brief   Lightweight assertion comparison object that preserves compared operand values for diagnostics
    @tparam  left_t      - left operand type
    @tparam  right_t     - right operand type
    @tparam  operation_t - operation type, must be a specialization of std binary function
                           (e.g. std::equal_to<>, std::less<>, etc.)
    @author  Khrapov
    @date    19.05.2026

**/
template<class left_t, class right_t, class operation_t>
class assert_comparison
{
public:
    /**
        @brief Construct comparison object from two operands.
        @param left  - left operand
        @param right - right operand
    **/
    constexpr assert_comparison(left_t&& left, right_t&& right) noexcept(
        std::is_nothrow_constructible_v<left_t, left_t&&> && std::is_nothrow_constructible_v<right_t, right_t&&>);

    /**
        @brief  Evaluate comparison.
        @retval - comparison result
    **/
    constexpr bool result() const noexcept(noexcept(operation_t {}(left(), right())));

    /**
        @brief  Convert comparison object to bool.
        @retval - comparison result
    **/
    constexpr explicit operator bool() const noexcept(noexcept(result()));

    /**
        @brief  Get left operand.
        @retval - left operand
    **/
    constexpr const auto& left() const noexcept;

    /**
        @brief  Get right operand.
        @retval - right operand
    **/
    constexpr const auto& right() const noexcept;

    /**
        @brief  Create assertion condition text with operand values.
        @param  svCondition - original condition expression string
        @retval             - condition text for assertion diagnostics
    **/
    string make_assert_condition_string(string_view svCondition) const noexcept;

private:
    left_t  m_Left;
    right_t m_Right;
};

template<class left_t, class right_t, class operation_t>
struct predicates::validator<assert_comparison<left_t, right_t, operation_t>>
{
    static constexpr bool is_valid(const assert_comparison<left_t, right_t, operation_t>& value) noexcept(
        noexcept(value.result()));
};

/**
    @brief  Compare two values for equality and preserve values for assertion diagnostics.
    @param  left  - left operand
    @param  right - right operand
    @retval       - assertion comparison object
**/
template<class left_t, class right_t>
constexpr auto assert_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::equal_to<>>(std::forward<left_t>(left), std::forward<right_t>(right))));

/**
    @brief  Compare two values for inequality and preserve values for assertion diagnostics.
    @param  left  - left operand
    @param  right - right operand
    @retval       - assertion comparison object
**/
template<class left_t, class right_t>
constexpr auto assert_not_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::not_equal_to<>>(std::forward<left_t>(left), std::forward<right_t>(right))));

/**
    @brief  Compare whether left value is less than right value and preserve values for assertion diagnostics.
    @param  left  - left operand
    @param  right - right operand
    @retval       - assertion comparison object
**/
template<class left_t, class right_t>
constexpr auto assert_less(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::less<>>(std::forward<left_t>(left), std::forward<right_t>(right))));

/**
    @brief  Compare whether left value is less than or equal to right value and preserve values for assertion diagnostics.
    @param  left  - left operand
    @param  right - right operand
    @retval       - assertion comparison object
**/
template<class left_t, class right_t>
constexpr auto assert_less_equal(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::less_equal<>>(std::forward<left_t>(left), std::forward<right_t>(right))));

/**
    @brief  Compare whether left value is greater than right value and preserve values for assertion diagnostics.
    @param  left  - left operand
    @param  right - right operand
    @retval       - assertion comparison object
**/
template<class left_t, class right_t>
constexpr auto assert_greater(left_t&& left, right_t&& right) noexcept(noexcept(
    assert_comparison<left_t, right_t, std::greater<>>(std::forward<left_t>(left), std::forward<right_t>(right))));

/**
    @brief  Compare whether left value is greater than or equal to right value and preserve values for assertion diagnostics.
    @param  left  - left operand
    @param  right - right operand
    @retval       - assertion comparison object
**/
template<class left_t, class right_t>
constexpr auto assert_greater_equal(left_t&& left, right_t&& right) noexcept(
    noexcept(assert_comparison<left_t, right_t, std::greater_equal<>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

} // namespace qx

#include <qx/asserts/assert_compare.inl>
