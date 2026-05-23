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

namespace details
{

/**

    @class   assert_comparison
    @brief   Lightweight assertion comparison object that preserves compared operand values for diagnostics
    @tparam  left_t         - left operand type
    @tparam  right_t        - right operand type
    @tparam  operation_t    - operation type, must be a specialization of std binary function
                              (e.g. std::equal_to<>, std::less<>, etc.)
    @tparam  bLeftIsLvalue  - whether the left operand was passed as an lvalue
    @tparam  bRightIsLvalue - whether the right operand was passed as an lvalue
    @author  Khrapov
    @date    19.05.2026

**/
template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
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

private:
    left_t  m_Left;
    right_t m_Right;
};

} // namespace details

template<class left_t, class right_t, class operation_t, bool bLeftIsLvalue, bool bRightIsLvalue>
struct predicates::validator<details::assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>>
{
    static constexpr bool
        is_valid(const details::assert_comparison<left_t, right_t, operation_t, bLeftIsLvalue, bRightIsLvalue>& value)
            noexcept(noexcept(value.result()));
};

/**
    @brief   Compare two values for equality and preserve values for assertion diagnostics.
    @details When used in macro assertions, this allows you to see both the names and values of variables
    @param   left  - left operand
    @param   right - right operand
    @retval        - assertion comparison object

    @code
    QX_EXPECT(qx::assert_eq(nValue, nOther)); // "nValue [41] == nOther [42]"
    @endcode 
**/
template<class left_t, class right_t>
constexpr auto assert_eq(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
        left_t,
        right_t,
        std::equal_to<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

/**
    @brief   Compare two values for inequality and preserve values for assertion diagnostics.
    @details When used in macro assertions, this allows you to see both the names and values of variables
    @param   left  - left operand
    @param   right - right operand
    @retval        - assertion comparison object

    @code
    QX_EXPECT(qx::assert_ne(nValue, nSame); // "nValue [41] != nSame [41]"
    @endcode 
**/
template<class left_t, class right_t>
constexpr auto assert_ne(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
        left_t,
        right_t,
        std::not_equal_to<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

/**
    @brief   Compare whether left value is less than right value and preserve values for assertion diagnostics.
    @details When used in macro assertions, this allows you to see both the names and values of variables
    @param   left  - left operand
    @param   right - right operand
    @retval        - assertion comparison object

    @code
    QX_EXPECT(qx::assert_lt(nOther, nValue)); // "nOther [42] < nValue [41]"
    @endcode 
**/
template<class left_t, class right_t>
constexpr auto assert_lt(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
        left_t,
        right_t,
        std::less<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

/**
    @brief   Compare whether left value is less than or equal to right value and preserve values for assertion diagnostics.
    @details When used in macro assertions, this allows you to see both the names and values of variables
    @param   left  - left operand
    @param   right - right operand
    @retval        - assertion comparison object

    @code
    QX_EXPECT(qx::assert_le(nOther, nValue)); // "nOther [42] <= nValue [41]"
    @endcode 
**/
template<class left_t, class right_t>
constexpr auto assert_le(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
        left_t,
        right_t,
        std::less_equal<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

/**
    @brief   Compare whether left value is greater than right value and preserve values for assertion diagnostics.
    @details When used in macro assertions, this allows you to see both the names and values of variables
    @param   left  - left operand
    @param   right - right operand
    @retval        - assertion comparison object

    @code
    QX_EXPECT(qx::assert_gt(nValue, nOther)); // "nValue [41] > nOther [42]"
    @endcode 
**/
template<class left_t, class right_t>
constexpr auto assert_gt(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
        left_t,
        right_t,
        std::greater<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

/**
    @brief   Compare whether left value is greater than or equal to right value and preserve values for assertion diagnostics.
    @details When used in macro assertions, this allows you to see both the names and values of variables
    @param   left  - left operand
    @param   right - right operand
    @retval        - assertion comparison object

    @code
    QX_EXPECT(qx::assert_ge(nValue, nOther)); // "nValue [41] >= nOther [42]"
    @endcode 
**/
template<class left_t, class right_t>
constexpr auto assert_ge(left_t&& left, right_t&& right) noexcept(
    noexcept(details::assert_comparison<
        left_t,
        right_t,
        std::greater_equal<>,
        std::is_lvalue_reference_v<left_t>,
        std::is_lvalue_reference_v<right_t>>(
        std::forward<left_t>(left),
        std::forward<right_t>(right))));

} // namespace qx

#include <qx/asserts/assert_compare.inl>
