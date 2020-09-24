//==============================================================================
//
//!\file                        constexpr_flag.h
//
//!\brief       Contains constexpr_flag class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.09.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

namespace qx
{

//==============================================================================
//
//!\class               qx::constexpr_flag<Tag, T, Start, End>
//
//!\brief   constexpr_flag class
//!\details Returns "Start" at the beginning(test), "Start" with test_and_set and "End" after
//
//!\author  Khrapov
//!\date    14.09.2020
//
//==============================================================================
template <typename Tag, typename T = bool, T Start = false, T End = true>
class constexpr_flag
{
private:

    struct Dummy
    {
        friend constexpr void adl_flag(Dummy) noexcept;
    };

    template <T>
    struct Writer
    {
        friend constexpr void adl_flag(Dummy) noexcept { }
    };

    template <class Dummy, int = (adl_flag(Dummy{}), 0)>
    static constexpr T check(int) noexcept
    {
        return End;
    }

    template <class Dummy>
    static constexpr T check(short) noexcept
    {
        return Start;
    }

public:

    template <class Dummy = Dummy, T Value = check<Dummy>(0)>
    static constexpr T test_and_set(void) noexcept
    {
        Writer<Value && 0> tmp{};
        (void)tmp;
        return Value;
    }

    template <class Dummy = Dummy, T Value = check<Dummy>(0)>
    static constexpr T test(void) noexcept
    {
        return Value;
    }
};

}
