//==============================================================================
//
//!\file                     constexpr_sequence.h
//
//!\brief       Contains constexpr_sequence class
//!\details     ~
//
//!\author      Khrapov
//!\date        25.08.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/other/constexpr_flag.h>
#include <qx/other/constexpr_funcs.h>
#include <qx/other/type_traits.h>

namespace qx
{

//==============================================================================
//
//!\class         qx::constexpr_sequence<Tag, T, Start, Func>
//
//!\brief   constexpr sequence. use unique tag for different instances
//!\details modyfied version of Anthony Williams constexpr counter
//          https://stackoverflow.com/a/58200261/8021662
//          \see exapmles in tests\test_constexpr_sequence.cpp
//          \note that you can't vary other template parameters with same Tag
//          Func is function that modifies value
//          prefer using "using my_sequence = qx::constexpr_sequence<...>"
//
//!\author  Khrapov
//!\date    25.08.2020
//
//==============================================================================
template <class Tag, typename T, T Start, T Func(T)>
class constexpr_sequence
{

template <T N>
struct StepTag;

template<T NextValue, bool Equal /* = false */>
struct CheckerEqual
{
    template<T SequenceVal = CheckerWrapper<NextValue>{}.value()>
    static constexpr T value(void) noexcept
    {
        return SequenceVal;
    }
};

template<T NextValue>
struct CheckerEqual<NextValue, /* bool Equal = */ true>
{
    static constexpr T value(void) noexcept
    {
        return NextValue;
    }
};

template<T CurrentValue, bool WasSetted /* = false */>
struct CheckerSetter
{
    static constexpr T value(void) noexcept
    {
        return CurrentValue;
    }
};

template<T CurrentValue>
struct CheckerSetter<CurrentValue, /* bool WasSetted = */ true>
{
    template<T NextValue   = Func(CurrentValue),
             T SequenceVal = CheckerEqual<NextValue, CurrentValue == NextValue>{}.value()>
    static constexpr T value(void) noexcept
    {
        return SequenceVal;
    }
};

template<T N>
struct CheckerWrapper
{
    template<bool WasSetted     = constexpr_flag<StepTag<N>>{}.test(),
             T    SequenceVal   = CheckerSetter<N, WasSetted>{}.value()>
    static constexpr T value(void) noexcept
    {
        return SequenceVal;
    }
};

public:

//==============================================================================
//!\fn       qx::constexpr_sequence<Tag, T, Start, Func>::value<N>
//
//!\brief   Get current sequence value
//!\details As function works through generating new template instance each time,
//          return value will be the same for each code line. That means in loops
//          you will get same value each time. Use macros like BOOST_PP_REPEAT
//          to simplify the code
//!\retval  - current sequence value
//!\author  Khrapov
//!\date   12.09.2020
//==============================================================================
template <T N = CheckerWrapper<Start>{}.value()>
static constexpr T value(void) noexcept
{
    return N;
}

//==============================================================================
//!\fn      qx::constexpr_sequence<Tag, T, Start, Func>::next<N, B>
//
//!\brief   Change value by Func and return new value
//!\details As function works through generating new template instance each time,
//          return value will be the same for one code line. That means in loops
//          you will get same value each time. Use macros like BOOST_PP_REPEAT
//          to simplify the code
//!\retval  - new value
//!\author  Khrapov
//!\date    12.09.2020
//==============================================================================
template <T    N    = CheckerWrapper<Start>{}.value(),
          bool Stub = constexpr_flag<StepTag<N>>{}.test_and_set()>
static constexpr T next(void) noexcept
{
    return Func(N);
}

};

template<typename Tag = struct CounterTag, typename T = int, T Start = 0, T Inc = 1>
using constexpr_counter = constexpr_sequence<Tag, T, Start, increase<T, Inc>>;

template<typename Tag = struct MultiplierTag, typename T = int, T Start = 1, T Mult = 2>
using constexpr_multiplier = constexpr_sequence<Tag, T, Start, multiply<T, Mult>>;

}
