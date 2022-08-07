/**

    @file      static_assert.h
    @brief     
    @details   ~
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

#include <qx/macros/common.h>
#include <qx/math/common.h>

#include <functional>

namespace qx::detail
{

template<auto A, auto B, typename Compare>
struct StaticAssertTwo
{
    static_assert(Compare()(A, B));
};

template<auto A, auto B>
struct StaticAssertTwo<A, B, std::equal_to<>>
{
    static_assert(std::equal_to<>()(A, B), "!(A == B)");
};

template<auto A, auto B>
struct StaticAssertTwo<A, B, std::not_equal_to<>>
{
    static_assert(std::not_equal_to<>()(A, B), "!(A != B)");
};

template<auto A, auto B>
struct StaticAssertTwo<A, B, std::less<>>
{
    static_assert(std::less<>()(A, B), "!(A < B)");
};

template<auto A, auto B>
struct StaticAssertTwo<A, B, std::less_equal<>>
{
    static_assert(std::less_equal<>()(A, B), "!(A <= B)");
};

template<auto A, auto B>
struct StaticAssertTwo<A, B, std::greater<>>
{
    static_assert(std::greater<>()(A, B), "!(A > B)");
};

template<auto A, auto B>
struct StaticAssertTwo<A, B, std::greater_equal<>>
{
    static_assert(std::greater_equal<>()(A, B), "!(A >= B)");
};

template<auto L, auto V, auto R>
struct StaticAssertBetween
{
    static_assert(qx::between(L, V, R), "V is not between R and L");
};

} // namespace qx::detail

/*
    Static assertions that shows A and B in error msg
*/
#define QX_STATIC_ASSERT_EQ(a, b) \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::equal_to<>> QX_LINE_NAME(_static_assert_eq_)

#define QX_STATIC_ASSERT_NE(a, b) \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::not_equal_to<>> QX_LINE_NAME(_static_assert_nq_)

#define QX_STATIC_ASSERT_LT(a, b) \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::less<>> QX_LINE_NAME(_static_assert_lt_)

#define QX_STATIC_ASSERT_LE(a, b) \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::less_equal<>> QX_LINE_NAME(_static_assert_le_)

#define QX_STATIC_ASSERT_GT(a, b) \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::greater<>> QX_LINE_NAME(_static_assert_gt_)

#define QX_STATIC_ASSERT_GE(a, b) \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::greater_equal<>> QX_LINE_NAME(_static_assert_ge_)

/**
    @def   QX_STATIC_ASSERT_BETWEEN
    @brief Shows L, V and R in error msg
    @param L - left value
    @param V - value to check
    @param R - right value
**/
#define QX_STATIC_ASSERT_BETWEEN(L, V, R) \
    qx::detail::StaticAssertBetween<(L), (V), (R)> QX_LINE_NAME(static_assert_between_)

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
    }                                              \
    ()