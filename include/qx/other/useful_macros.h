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

#include <cstddef>

#include <qx/other/typedefs.h>
#include <qx/other/config.h>

/*
    Placeholder for disabled macros
    Has no effect and work correctly with "if else"
*/
#define EMPTY_MACRO ((void*)0)

//==============================================================================

/*
    The STRINGIFY() macro can be used to turn any text in your code into a string,
    but only the exact text between the parentheses
    There are no variable dereferencing or macro substitutions or any other sort of thing done.
*/
#define STRINGIFY(name)  # name

//==============================================================================

/*
    Fast C#-like getters and setters
*/

#define GETTER(type, name)                                          \
    const type & Get ## name (void) const { return m_ ## name; }

#define GETTER_REF(type, name)                                      \
    type & Get ## name (void) { return m_ ## name; }

#define SETTER(type, name)                                          \
    void Set ## name (const type & val) { m_ ## name = val; }

//==============================================================================

/*
    Do magic! Creates a unique name using the line number
*/
#define LINE_NAME(prefix) _JOIN(prefix, __LINE__)
#define _JOIN(symbol1, symbol2) _DO_JOIN(symbol1, symbol2)
#define _DO_JOIN(symbol1, symbol2) symbol1##symbol2

//==============================================================================

#ifdef QX_WIN
    #define PATH_SEPARATOR '\\'
#else
    #define PATH_SEPARATOR '/'
#endif

namespace qx::detail
{
    constexpr const char * past_last_slash(const char* str, const char* last_slash)
    {
        return *str == '\0'
                ? last_slash
                : *str == PATH_SEPARATOR
                    ? past_last_slash(str + 1, str + 1)
                    : past_last_slash(str + 1, last_slash);
    }

    constexpr const char* past_last_slash(const char* str)
    {
        return past_last_slash(str, str);
    }
}

/*
    Cuts full absolute path to the file name only
    ex: C:\folder1\foler2\file.cpp  =>  file.cpp
*/
#define __SHORT_FILE__ qx::detail::past_last_slash(__FILE__)

//==============================================================================

/*
    Let macro param containing commas work fine

    ex: #define FOO(type, name) type name
        FOO(SINGLE_ARGUMENT(std::map<int, int>), map_var);
*/
#define SINGLE_ARGUMENT(...) (__VA_ARGS__)

//==============================================================================

/*
    ASSERT and ASSERT_MSG macros
    use ENABLE_ASSERTS, ENABLE_DEBUG_BREAK, PROCESS_ASSERT macros to configure behavior
*/

#ifndef ENABLE_ASSERTS
    #define ENABLE_ASSERTS _DEBUG
#endif

#ifndef ENABLE_DEBUG_BREAK
    #define ENABLE_DEBUG_BREAK _DEBUG
#endif

#ifndef PROCESS_ASSERT
    #define PROCESS_ASSERT(statement) EMPTY_MACRO
#endif

#ifndef PROCESS_ASSERT_MSG
    #define PROCESS_ASSERT_MSG(statement, msg, ...) PROCESS_ASSERT(statement)
#endif

#if ENABLE_DEBUG_BREAK

    #if defined(_WIN32)
        #define DEBUG_BREAK __debugbreak()
    #elif defined(_LINUX)
        #define DEBUG_BREAK if (detect_debugger() == 1) raise(SIGTRAP)
    #elif defined(ANDROID)
        #define DEBUG_BREAK assert(0)
    #else
        #define DEBUG_BREAK EMPTY_MACRO
    #endif

#else

    #define DEBUG_BREAK EMPTY_MACRO

#endif


#if ENABLE_ASSERTS

    #define ASSERT(statement)                               \
    do {                                                    \
        if (!(statement))                                   \
        {                                                   \
            PROCESS_ASSERT(statement);                      \
            DEBUG_BREAK;                                    \
        }                                                   \
    } while (false)

    #define ASSERT_MSG(statement, msg, ...)                 \
    do {                                                    \
        if (!(statement))                                   \
        {                                                   \
            PROCESS_ASSERT_MSG(statement, msg, __VA_ARGS__);\
            DEBUG_BREAK;                                    \
        }                                                   \
    } while (false)

#else

    #define ASSERT(statement)                   EMPTY_MACRO
    #define ASSERT_MSG(statement, msg, ...)     EMPTY_MACRO

#endif

//==============================================================================

/*
    Short assert and if (no need to double condition)
    CHECK  is checking always and can be used with else
    DCHECK is primary for debug and checks that has to be disabled in release
*/

#ifndef ENABLE_DCHECK
    #define ENABLE_DCHECK _DEBUG
#endif

#define CHECK(condition)                                    \
ASSERT(condition);                                          \
if (condition)

#if (ENABLE_DCHECK)

    #define DCHECK(condition)                               \
    ASSERT(condition);                                      \
    if (!(condition))                                       \
    {                                                       \
    }                                                       \
    else

#else

    #define DCHECK(condition) EMPTY_MACRO;

#endif

//==============================================================================

/*
    Stub for not implemented yet code lines
*/

#define ASSERT_NOT_IMPL ASSERT_MSG(0, "Implementation isn't ready")

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
    template<auto A, auto B>
    struct StaticAssertEqueal
    {
        static_assert(A == B, "Values are not equal");
    };
}

/*
    Shows A and B in error msg
*/
#define QX_STATIC_ASSERT_EQ(a, b) qx::detail::StaticAssertEqueal<(a), (b)> LINE_NAME(static_assert_equal_);

//==============================================================================

namespace qx::detail
{
    template<auto L, auto V, auto R>
    struct StaticAssertBetween
    {
        static_assert(static_cast<size_t>(V - L) <= (R - L), "V is not between R and L");
    };
}

/*
    Shows L, V and R in error msg
*/
#define QX_STATIC_ASSERT_BETWEEN(L, V, R) qx::detail::StaticAssertBetween<(L), (V), (R)> LINE_NAME(static_assert_between_);

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
