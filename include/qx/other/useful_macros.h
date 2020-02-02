//============================================================================
//
//!\file                           useful.h
//
//!\brief       Useful functions and macros
//!\details     ~
//
//!\author      Khrapov
//!\date        17.06.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <cstddef>

#include <qx/other/typedefs.h>
#include <qx/other/asserter.h>

/*
    Placeholder for disabled macros
    Has no effect and work correctly with "if else"
*/
#define EMPTY_MACRO ((void*)0)

//============================================================================

/*
    The STRINGIFY() macro can be used to turn any text in your code into a string,
    but only the exact text between the parentheses
    There are no variable dereferencing or macro substitutions or any other sort of thing done.
*/
#define STRINGIFY(name)  # name

//============================================================================

/*
    SFINAE class member existance check
    ex: class Class1
        {
            void mem1() { }
        }
    
        DEFINE_HAS_MEMBER(mem1);
        constexpr bool b1 = HAS_MEMBER(Class1, mem1); // true
        constexpr bool b2 = HAS_MEMBER(Class1, mem2); // false
*/

#define DEFINE_HAS_MEMBER(member_name)                                         \
    template <typename T>                                                      \
    class has_member_##member_name                                             \
    {                                                                          \
        typedef char yes_type;                                                 \
        typedef long no_type;                                                  \
        template <typename U> static yes_type test(decltype(&U::member_name)); \
        template <typename U> static no_type  test(...);                       \
    public:                                                                    \
        static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes_type);  \
    }

#define HAS_MEMBER(class_, member_name)  has_member_##member_name<class_>::value

//============================================================================

/*
    Fast C#-like getters and setters
*/

#define GETTER(type, name)                                          \
    const type & Get ## name (void) const { return m_ ## name; }

#define GETTER_REF(type, name)                                      \
    type & Get ## name (void) { return m_ ## name; }

#define SETTER(type, name)                                          \
    void Set ## name (const type & val) { m_ ## name = val; }

//============================================================================

/*
    Do magic! Creates a unique name using the line number
*/
#define LINE_NAME(prefix) _JOIN(prefix, __LINE__)
#define _JOIN(symbol1, symbol2) _DO_JOIN(symbol1, symbol2)
#define _DO_JOIN(symbol1, symbol2) symbol1##symbol2

//============================================================================

/*
    Short assert and if (no need to double condition)
    CHECK  is checking always and can be used with else
    DCHECK is primary for debug and checks that has to be disabled in release
*/

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

//============================================================================

#ifdef _WIN64
    #define PATH_SEPARATOR '\\'
#else
    #define PATH_SEPARATOR '/'
#endif

namespace detail
{
    constexpr cstr past_last_slash(cstr str, cstr last_slash)
    {
        return *str == '\0'
                ? last_slash
                : *str == PATH_SEPARATOR
                    ? past_last_slash(str + 1, str + 1)
                    : past_last_slash(str + 1, last_slash);
    }

    constexpr cstr past_last_slash(cstr str)
    {
        return past_last_slash(str, str);
    }
}

/*
    Cuts full absolute path to the file name only
    ex: C:\folder1\foler2\file.cpp  =>  file.cpp
*/
#define __SHORT_FILE__ detail::past_last_slash(__FILE__)

//============================================================================

/*
    C-style array size
*/
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

//============================================================================

/*
    C-style array bounds check
*/
#define IN_BOUNDS_ARR(arr, ind) (((ind) >= 0) && ((ind) < ARRAY_SIZE(arr)))

//============================================================================

namespace detail
{
    template<typename ...Args>
    constexpr std::size_t va_count(Args&...) { return sizeof...(Args); }
}

/*
    Variadic argument count
*/
#define VA_COUNT(...) detail::va_count(__VA_ARGS__)

//============================================================================

/*
    Let macro param containing commas work fine

    ex: #define FOO(type, name) type name
        FOO(SINGLE_ARGUMENT(std::map<int, int>), map_var);
*/
#define SINGLE_ARGUMENT(...) __VA_ARGS__

//============================================================================
