/**

    @file      static_assert.h
    @brief     Static assert macros
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>
#include <qx/math/common.h>

#include <functional>

namespace qx::details
{

template<auto left, auto right, typename compare_t>
struct static_assert_two
{
    static_assert(compare_t()(left, right));
};

template<auto left, auto right>
struct static_assert_two<left, right, std::equal_to<>>
{
    static_assert(std::equal_to<>()(left, right), "!(left == right)");
};

template<auto left, auto right>
struct static_assert_two<left, right, std::not_equal_to<>>
{
    static_assert(std::not_equal_to<>()(left, right), "!(left != right)");
};

template<auto left, auto right>
struct static_assert_two<left, right, std::less<>>
{
    static_assert(std::less<>()(left, right), "!(left < right)");
};

template<auto left, auto right>
struct static_assert_two<left, right, std::less_equal<>>
{
    static_assert(std::less_equal<>()(left, right), "!(left <= right)");
};

template<auto left, auto right>
struct static_assert_two<left, right, std::greater<>>
{
    static_assert(std::greater<>()(left, right), "!(left > right)");
};

template<auto left, auto right>
struct static_assert_two<left, right, std::greater_equal<>>
{
    static_assert(std::greater_equal<>()(left, right), "!(left >= right)");
};

template<auto left, auto value, auto right>
struct static_assert_between
{
    static_assert(qx::between(left, value, right), "value is not between right and left");
};

} // namespace qx::details

/*
    Static assertions that shows left and right in error msg
*/
#define QX_STATIC_ASSERT_EQ(left, right) \
    constexpr qx::details::static_assert_two<(left), (right), std::equal_to<>> QX_LINE_NAME(_static_assert_eq_)

#define QX_STATIC_ASSERT_NE(left, right) \
    constexpr qx::details::static_assert_two<(left), (right), std::not_equal_to<>> QX_LINE_NAME(_static_assert_nq_)

#define QX_STATIC_ASSERT_LT(left, right) \
    constexpr qx::details::static_assert_two<(left), (right), std::less<>> QX_LINE_NAME(_static_assert_lt_)

#define QX_STATIC_ASSERT_LE(left, right) \
    constexpr qx::details::static_assert_two<(left), (right), std::less_equal<>> QX_LINE_NAME(_static_assert_le_)

#define QX_STATIC_ASSERT_GT(left, right) \
    constexpr qx::details::static_assert_two<(left), (right), std::greater<>> QX_LINE_NAME(_static_assert_gt_)

#define QX_STATIC_ASSERT_GE(left, right) \
    constexpr qx::details::static_assert_two<(left), (right), std::greater_equal<>> QX_LINE_NAME(_static_assert_ge_)

/**
    @def   QX_STATIC_ASSERT_BETWEEN
    @brief Shows left, value and right in error msg
    @param left  - left value
    @param value - value to check
    @param right - right value
**/
#define QX_STATIC_ASSERT_BETWEEN(left, value, right) \
    qx::details::static_assert_between<(left), (value), (right)> QX_LINE_NAME(static_assert_between_)

/**
    @brief This static assert will fail if block it placed in must not be instantiated

    @code
    template<class T>
    constexpr int GetValue()
    {
        if constexpr (std::is_same_v<T, bool>)
        {
            return 0;
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            return 0;
        }
        else
        {
            QX_STATIC_ASSERT_NO_INSTANTIATION("T must be bool or int");
            return 0;
        }
    }

    constexpr int val1 = GetValue<bool>();  // ok
    constexpr int val2 = GetValue<int>();   // ok
    constexpr int val3 = GetValue<long>();  // static_assert failure
    @endcode 
    
    @param Message - static_assert message
**/
#define QX_STATIC_ASSERT_NO_INSTANTIATION(Message) \
    []<bool flag = false>()                        \
    {                                              \
        static_assert(flag, Message);              \
    }()