/**

    @file      useful_macros.h
    @brief     Useful macros
    @author    Khrapov
    @date      17.06.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/useful_funcs.h>

/**
    @def     QX_EMPTY_MACRO
    @brief   Placeholder for disabled macros
    @details Has no effect and work correctly with "if else"
**/
#define QX_EMPTY_MACRO ((void*)0)

/**
    @def   QX_STRINGIFY
    @brief Macro can be used to turn any text in your code into a string,
           but only the exact text between the parentheses
           There are no variable dereferencing or macro substitutions or any other sort of thing done.
    @param name - name to convert to the string
**/
#define QX_STRINGIFY(name) #name

/**
    @def   QX_GETTER
    @brief Fast C#-like getter
    @param type - value type
    @param name - value name
**/
#define QX_GETTER(type, name)     \
    const type& Get##name() const \
    {                             \
        return m_##name;          \
    }

/**
    @def   QX_GETTER_REF
    @brief Fast C#-like ref getter
    @param type - value type
    @param name - value name
**/
#define QX_GETTER_REF(type, name) \
    type& Get##name()             \
    {                             \
        return m_##name;          \
    }

/**
    @def   QX_SETTER
    @brief Fast C#-like setter
    @param type - value type
    @param name - value name
**/
#define QX_SETTER(type, name)       \
    void Set##name(const type& val) \
    {                               \
        m_##name = val;             \
    }

/**
    @def   QX_PROPERTY
    @brief A set of data member, getter and setter
    @param type - data type
    @param name - data name
    @param ...  - data default value
**/
#define QX_PROPERTY(type, name, ...) \
public:                              \
    QX_GETTER(type, name);           \
    QX_SETTER(type, name);           \
                                     \
private:                             \
    type m_##name = type(__VA_ARGS__);

/**
    @def   QX_LINE_NAME
    @brief Do magic! Creates a unique name using the line number
    @param prefix - name prefix
**/
#define QX_LINE_NAME(prefix)          _QX_JOIN(prefix, __LINE__)
#define _QX_JOIN(symbol1, symbol2)    _QX_DO_JOIN(symbol1, symbol2)
#define _QX_DO_JOIN(symbol1, symbol2) symbol1##symbol2


#if QX_WIN
#define QX_PATH_SEPARATOR '\\'
#else
#define QX_PATH_SEPARATOR '/'
#endif

namespace qx::detail
{

constexpr const char* last_slash(const char* str)
{
    const char* pszLastSlash = str;
    while (str && *str != '\0')
    {
        if (*str == QX_PATH_SEPARATOR)
            pszLastSlash = str;

        str++;
    }
    return pszLastSlash + 1;
}

} // namespace qx::detail

/**
    @def   QX_SHORT_FILE
    @brief Cuts full absolute path to the file name only
           ex: "C:\folder1\foler2\file.h"  =>  "file.h"
**/
#define QX_SHORT_FILE qx::detail::last_slash(__FILE__)

/**
    @def   QX_SINGLE_ARGUMENT
    @brief Let macro param containing commas work fine
           "#define FOO(type, name) type name"
           FOO(QX_SINGLE_ARGUMENT(std::map<int, int>), map_var);
    @param ... - param containing commas
**/
#define QX_SINGLE_ARGUMENT(...) __VA_ARGS__

/**
    @def   QX_COPYABLE
    @brief Define class as default copyable
    @param ... - class name
**/
#define QX_COPYABLE(...)                       \
    __VA_ARGS__(const __VA_ARGS__&) = default; \
    __VA_ARGS__& operator=(const __VA_ARGS__&) = default;

/**
    @def   QX_MOVABLE
    @brief Define class as default movable
    @param ... - class name
**/
#define QX_MOVABLE(...)                            \
    __VA_ARGS__(__VA_ARGS__&&) noexcept = default; \
    __VA_ARGS__& operator=(__VA_ARGS__&&) noexcept = default;

/**
    @def   QX_COPYMOVABLE
    @brief Define class as default copyable and movable
    @param ... - class name
**/
#define QX_COPYMOVABLE(...)  \
    QX_COPYABLE(__VA_ARGS__) \
    QX_MOVABLE(__VA_ARGS__)

/**
    @def   QX_NONCOPYABLE
    @brief Define class as non copyable
    @param ... - class name
**/
#define QX_NONCOPYABLE(...)                   \
    __VA_ARGS__(const __VA_ARGS__&) = delete; \
    __VA_ARGS__& operator=(const __VA_ARGS__&) = delete;

/**
    @def   QX_NONMOVABLE
    @brief Define class as non movable
    @param ... - class name
**/
#define QX_NONMOVABLE(...)                        \
    __VA_ARGS__(__VA_ARGS__&&) noexcept = delete; \
    __VA_ARGS__& operator=(__VA_ARGS__&&) noexcept = delete;

/**
    @def   QX_NONCOPYMOVABLE
    @brief Define class as non copyable and non movable
    @param ... - class name
**/
#define QX_NONCOPYMOVABLE(...)  \
    QX_NONCOPYABLE(__VA_ARGS__) \
    QX_NONMOVABLE(__VA_ARGS__)


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

} // namespace qx::detail

/*
    Static assertions that shows A and B in error msg
*/
#define QX_STATIC_ASSERT_EQ(a, b)                                    \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::equal_to<>> \
        QX_LINE_NAME(_static_assert_eq_)

#define QX_STATIC_ASSERT_NE(a, b)                                        \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::not_equal_to<>> \
        QX_LINE_NAME(_static_assert_nq_)

#define QX_STATIC_ASSERT_LT(a, b)                                              \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::less<>> QX_LINE_NAME( \
        _static_assert_lt_)

#define QX_STATIC_ASSERT_LE(a, b)                                      \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::less_equal<>> \
        QX_LINE_NAME(_static_assert_le_)

#define QX_STATIC_ASSERT_GT(a, b)                                   \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::greater<>> \
        QX_LINE_NAME(_static_assert_gt_)

#define QX_STATIC_ASSERT_GE(a, b)                                         \
    constexpr qx::detail::StaticAssertTwo<(a), (b), std::greater_equal<>> \
        QX_LINE_NAME(_static_assert_ge_)

namespace qx::detail
{

template<auto L, auto V, auto R>
struct StaticAssertBetween
{
    static_assert(qx::between(L, V, R), "V is not between R and L");
};

} // namespace qx::detail

/**
    @def   QX_STATIC_ASSERT_BETWEEN
    @brief Shows L, V and R in error msg
    @param L - left value
    @param V - value to check
    @param R - right value
**/
#define QX_STATIC_ASSERT_BETWEEN(L, V, R)                        \
    qx::detail::StaticAssertBetween<(L), (V), (R)> QX_LINE_NAME( \
        static_assert_between_)
