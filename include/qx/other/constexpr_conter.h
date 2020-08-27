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

    template <class Dummy, int = (adl_flag(Dummy{}), 0) >
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
    template<bool B = Flag<Tag<T, N>>{}.Read(), int M = Checker<T, N, Step, B>{}.currentval() >
    static constexpr int currentval()
    {
        return M;
    }
};

template<typename T, int N, int Step>
struct Checker<T, N, Step, true>
{
    template<int M = CheckerWrapper<T, N + Step, Step>{}.currentval() >
    static constexpr int currentval() noexcept
    {
        return M;
    }
};

template<typename T, int N, bool B = Flag<Tag<T, N>>{}.ReadSet() >
struct Next
{
    static constexpr int value() noexcept
    {
        return N;
    }
};

}

//==============================================================================
//
//!\class             constexpr_counter<Tag, Start, Step>
//
//!\brief   constexpr counter. use unique tag for different instances
//!\details modyfied version of Anthony Williams constexpr counter
//          https://stackoverflow.com/a/58200261/8021662
//          \see exapmles in tests\test_constexpr_counter.cpp
//
//!\author  Khrapov
//!\date    25.08.2020
//
//==============================================================================
template <class Tag = void, int Start = 0, int Step = 1>
class constexpr_counter
{
public:
    template <int N = detail::CheckerWrapper<Tag, Start, Step>{}.currentval()>
    static constexpr int next()
    {
        return detail::Next<Tag, N>{}.value();
    }
};

}