//==============================================================================
//
//!\file                       constexpr_conter.h
//
//!\brief       Contains constexpr_counter class
//!\details     ~
//
//!\author      Khrapov
//!\date        25.08.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

namespace qx
{

namespace detail
{

template <typename T> class Flag
{
    struct Dummy
    {
        constexpr Dummy()
        {
        }
        friend constexpr void adl_flag(Dummy);
    };

    template <bool>
    struct Writer
    {
        friend constexpr void adl_flag(Dummy)
        {
        }
    };

    template <class Dummy, int = (adl_flag(Dummy{}), 0)>
    static constexpr bool Check(int)
    {
        return true;
    }

    template <class Dummy>
    static constexpr bool Check(short)
    {
        return false;
    }

public:

    template <class Dummy = Dummy, bool Value = Check<Dummy>(0)>
    static constexpr bool ReadSet()
    {
        Writer<Value && 0> tmp{};
        (void)tmp;
        return Value;
    }

    template <class Dummy = Dummy, bool Value = Check<Dummy>(0)>
    static constexpr int Read()
    {
        return Value;
    }
};

template <typename T, int I>
struct Tag
{
    constexpr int value() const noexcept
    {
        return I;
    }
};

template<typename T, int N, int Step, bool B>
struct Checker
{
    static constexpr int currentval() noexcept
    {
        return N;
    }
};

template<typename T, int N, int Step>
struct CheckerWrapper
{
    template<bool B = Flag<Tag<T, N>>{}.Read(), int M = Checker<T, N, Step, B>{}.currentval()>
    static constexpr int currentval()
    {
        return M;
    }
};

template<typename T, int N, int Step>
struct Checker<T, N, Step, true>
{
    template<int M = CheckerWrapper<T, N + Step, Step>{}.currentval()>
    static constexpr int currentval() noexcept
    {
        return M;
    }
};

}

//==============================================================================
//
//!\class        qx::constexpr_counter<CounterTag, Start, Step>
//
//!\brief   constexpr counter. use unique tag for different instances
//!\details modyfied version of Anthony Williams constexpr counter
//          https://stackoverflow.com/a/58200261/8021662
//          \see exapmles in tests\test_constexpr_counter.cpp
//          \note that you can't vary Start and Step values with same Tag
//          prefer using "using my_counter = qx::constexpr_counter<struct MyTag, Start, Step>
//
//!\author  Khrapov
//!\date    25.08.2020
//
//==============================================================================
template <class CounterTag = void, int Start = 0, int Step = 1>
class constexpr_counter
{
public:

//==============================================================================
//!\fn      qx::constexpr_counter<CounterTag, Start, Step>::value<N>
//
//!\brief  Get current counter value
//!\retval  - current counter value
//!\author Khrapov
//!\date   12.09.2020
//==============================================================================
template <int  N = detail::CheckerWrapper<CounterTag, Start, Step>{}.currentval()>
static constexpr int value(void) noexcept
{
    return N;
}

//==============================================================================
//!\fn     qx::constexpr_counter<CounterTag, Start, Step>::next<N, B>
//
//!\brief  Increase value by Step and return new value
//!\retval  - increased value
//!\author Khrapov
//!\date   12.09.2020
//==============================================================================
template <int  N = detail::CheckerWrapper<CounterTag, Start, Step>{}.currentval(),
          bool B = detail::Flag<detail::Tag<CounterTag, N>>{}.ReadSet()>
static constexpr int next(void) noexcept
{
    return N + Step;
}

};

}
