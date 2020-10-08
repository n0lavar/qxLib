//==============================================================================
//
//!\file                      useful_macros.h
//
//!\brief       Useful macros
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/typedefs.h>
#include <qx/other/useful_funcs.h>

/*
    Placeholder for disabled macros
    Has no effect and work correctly with "if else"
*/
#define QX_EMPTY_MACRO ((void*)0)

//==============================================================================

/*
    Macro can be used to turn any text in your code into a string,
    but only the exact text between the parentheses
    There are no variable dereferencing or macro substitutions or any other sort of thing done.
*/
#define QX_STRINGIFY(name)  # name

//==============================================================================

/*
    Fast C#-like getters and setters
*/

#define QX_GETTER(type, name)                                       \
    const type & Get ## name (void) const { return m_ ## name; }

#define QX_GETTER_REF(type, name)                                   \
    type & Get ## name (void) { return m_ ## name; }

#define QX_SETTER(type, name)                                       \
    void Set ## name (const type & val) { m_ ## name = val; }

//==============================================================================

/*
    Do magic! Creates a unique name using the line number
*/
#define QX_LINE_NAME(prefix) _QX_JOIN(prefix, __LINE__)
#define _QX_JOIN(symbol1, symbol2) _QX_DO_JOIN(symbol1, symbol2)
#define _QX_DO_JOIN(symbol1, symbol2) symbol1##symbol2

//==============================================================================

#if QX_WIN
    #define QX_PATH_SEPARATOR '\\'
#else
    #define QX_PATH_SEPARATOR '/'
#endif

namespace qx::detail
{
    constexpr const char * last_slash(const char* str)
    {
        const char * pszLastSlash = str;
        while (str && *str != '\0')
        {
            if (*str == QX_PATH_SEPARATOR)
                pszLastSlash = str;

            str++;
        }
        return pszLastSlash + 1;
    }
}

/*
    Cuts full absolute path to the file name only
    ex: C:\folder1\foler2\file.cpp  =>  file.cpp
*/
#define QX_SHORT_FILE qx::detail::last_slash(__FILE__)

//==============================================================================

/*
    Let macro param containing commas work fine

    ex: #define FOO(type, name) type name
        FOO(QX_SINGLE_ARGUMENT(std::map<int, int>), map_var);
*/
#define QX_SINGLE_ARGUMENT(...) (__VA_ARGS__)

//==============================================================================

/*
    QX_ASSERT and QX_ASSERT_MSG macros
    use QX_ENABLE_ASSERTS, QX_ENABLE_DEBUG_BREAK, QX_PROCESS_ASSERT macros to configure behavior
*/

#ifndef QX_ENABLE_ASSERTS
    #define QX_ENABLE_ASSERTS QX_DEBUG
#endif

#ifndef QX_ENABLE_DEBUG_BREAK
    #define QX_ENABLE_DEBUG_BREAK QX_DEBUG
#endif

#ifndef QX_PROCESS_ASSERT
    #define QX_PROCESS_ASSERT(statement) QX_EMPTY_MACRO
#endif

#ifndef QX_PROCESS_ASSERT_MSG
    #define QX_PROCESS_ASSERT_MSG(statement, msg, ...) QX_PROCESS_ASSERT(statement)
#endif

#if QX_ENABLE_DEBUG_BREAK

    #if QX_WIN
        #define QX_DEBUG_BREAK __debugbreak()
    #elif QX_LINUX
        #define QX_DEBUG_BREAK if (detect_debugger() == 1) raise(SIGTRAP)
    #elif defined(ANDROID)
        #define QX_DEBUG_BREAK assert(0)
    #else
        #define QX_DEBUG_BREAK QX_EMPTY_MACRO
    #endif

#else

    #define QX_DEBUG_BREAK QX_EMPTY_MACRO

#endif


#if QX_ENABLE_ASSERTS

    #define QX_ASSERT(statement)                                    \
    do {                                                            \
        if (!(statement))                                           \
        {                                                           \
            QX_PROCESS_ASSERT(statement);                           \
            QX_DEBUG_BREAK;                                         \
        }                                                           \
    } while (false)

    #define QX_ASSERT_MSG(statement, msg, ...)                      \
    do {                                                            \
        if (!(statement))                                           \
        {                                                           \
            QX_PROCESS_ASSERT_MSG(statement, msg, ## __VA_ARGS__);  \
            QX_DEBUG_BREAK;                                         \
        }                                                           \
    } while (false)

#else

    #define QX_ASSERT(statement)                QX_EMPTY_MACRO
    #define QX_ASSERT_MSG(statement, msg, ...)  QX_EMPTY_MACRO

#endif

//==============================================================================

/*
    Short assert and if (no need to double condition)
    QX_CHECK  is checking always and can be used with else
    QX_DCHECK is primary for debug and checks that has to be disabled in release
*/

#ifndef QX_ENABLE_DCHECK
    #define QX_ENABLE_DCHECK QX_DEBUG
#endif

#define QX_CHECK(condition)                                 \
            QX_ASSERT(condition);                           \
            if (condition)

#if (QX_ENABLE_DCHECK)

    #define QX_DCHECK(condition)                            \
    QX_ASSERT(condition);                                   \
    if (!(condition))                                       \
    {                                                       \
    }                                                       \
    else

#else

    #define QX_DCHECK(condition) QX_EMPTY_MACRO;

#endif

//==============================================================================

/*
    Stub for not implemented yet code lines
*/

#define QX_ASSERT_NOT_IMPL QX_ASSERT_MSG(0, "Implementation isn't ready")

//==============================================================================

/*
    Define class as non-copyble
*/
#define QX_NONCOPYBLE(name)                         \
        name        (name&&) noexcept   = default;  \
name&   operator=   (name&&) noexcept   = default;  \
        name        (const name&)       = delete;   \
name&   operator=   (const name&)       = delete;

//==============================================================================

namespace qx::detail
{
    template<auto A, auto B, typename Compare>
    struct StaticAssertTwo
    { static_assert(Compare()(A, B)); };

    template<auto A, auto B>
    struct StaticAssertTwo<A, B, std::equal_to<>>
    { static_assert(std::equal_to<>()(A, B), "!(A == B)"); };

    template<auto A, auto B>
    struct StaticAssertTwo<A, B, std::not_equal_to<>>
    { static_assert(std::not_equal_to<>()(A, B), "!(A != B)"); };

    template<auto A, auto B>
    struct StaticAssertTwo<A, B, std::less<>>
    { static_assert(std::less<>()(A, B), "!(A < B)"); };

    template<auto A, auto B>
    struct StaticAssertTwo<A, B, std::less_equal<>>
    { static_assert(std::less_equal<>()(A, B), "!(A <= B)"); };

    template<auto A, auto B>
    struct StaticAssertTwo<A, B, std::greater<>>
    { static_assert(std::greater<>()(A, B), "!(A > B)"); };

    template<auto A, auto B>
    struct StaticAssertTwo<A, B, std::greater_equal<>>
    { static_assert(std::greater_equal<>()(A, B), "!(A >= B)"); };
}

/*
    Static assertions that shows A and B in error msg
*/
#define QX_STATIC_ASSERT_EQ(a, b) constexpr qx::detail::StaticAssertTwo<(a), (b), std::equal_to<>>       QX_LINE_NAME(_static_assert_eq_)
#define QX_STATIC_ASSERT_NE(a, b) constexpr qx::detail::StaticAssertTwo<(a), (b), std::not_equal_to<>>   QX_LINE_NAME(_static_assert_nq_)
#define QX_STATIC_ASSERT_LT(a, b) constexpr qx::detail::StaticAssertTwo<(a), (b), std::less<>>           QX_LINE_NAME(_static_assert_lt_)
#define QX_STATIC_ASSERT_LE(a, b) constexpr qx::detail::StaticAssertTwo<(a), (b), std::less_equal<>>     QX_LINE_NAME(_static_assert_le_)
#define QX_STATIC_ASSERT_GT(a, b) constexpr qx::detail::StaticAssertTwo<(a), (b), std::greater<>>        QX_LINE_NAME(_static_assert_gt_)
#define QX_STATIC_ASSERT_GE(a, b) constexpr qx::detail::StaticAssertTwo<(a), (b), std::greater_equal<>>  QX_LINE_NAME(_static_assert_ge_)

//==============================================================================

/*
    Static string comparisons
*/
#define QX_STATIC_ASSERT_STR_EQ(a, b) static_assert(qx::meta::strcmp((a), (b)) == 0)
#define QX_STATIC_ASSERT_STR_NE(a, b) static_assert(qx::meta::strcmp((a), (b)) != 0)
#define QX_STATIC_ASSERT_STR_LT(a, b) static_assert(qx::meta::strcmp((a), (b)) <  0)
#define QX_STATIC_ASSERT_STR_LE(a, b) static_assert(qx::meta::strcmp((a), (b)) <= 0)
#define QX_STATIC_ASSERT_STR_GT(a, b) static_assert(qx::meta::strcmp((a), (b)) >  0)
#define QX_STATIC_ASSERT_STR_GE(a, b) static_assert(qx::meta::strcmp((a), (b)) >= 0)

//==============================================================================

namespace qx::detail
{
    template<auto L, auto V, auto R>
    struct StaticAssertBetween
    {
        static_assert(qx::between(L, V, R), "V is not between R and L");
    };
}

/*
    Shows L, V and R in error msg
*/
#define QX_STATIC_ASSERT_BETWEEN(L, V, R) qx::detail::StaticAssertBetween<(L), (V), (R)> QX_LINE_NAME(static_assert_between_)

//==============================================================================

namespace qx::detail
{
    template<typename value_type>
    constexpr const value_type* const ChooseStrPrefix(const char* const, const wchar_t* const);

    template<>
    constexpr const char* const ChooseStrPrefix<char>(const char* const c, const wchar_t* const)
    {
        return c;
    }

    template<>
    constexpr const wchar_t* const ChooseStrPrefix<wchar_t>(const char* const, const wchar_t* const w)
    {
        return w;
    }

    template<typename value_type>
    constexpr value_type ChooseCharPrefix(char, wchar_t);

    template<>
    constexpr char ChooseCharPrefix<char>(char c, wchar_t)
    {
        return c;
    }

    template<>
    constexpr wchar_t ChooseCharPrefix<wchar_t>(char, wchar_t w)
    {
        return w;
    }
}

#define _QX_TO_WSTRING(x) L##x
#define QX_TO_WSTRING(x) _QX_TO_WSTRING(x)

/*
    chose witch of prefixes add to string : L or none
*/
#define QX_STR_PREFIX(value_type, str) qx::detail::ChooseStrPrefix<value_type>(str, QX_TO_WSTRING(str))

/*
    chose witch of prefixes add to char : L or none
*/
#define QX_CHAR_PREFIX(value_type, ch) qx::detail::ChooseCharPrefix<value_type>(ch, QX_TO_WSTRING(ch))

//==============================================================================
