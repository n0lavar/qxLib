/**

    @file      constexpr_flag.h
    @brief     Contains qx::constexpr_flag class
    @author    Khrapov
    @date      16.09.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

namespace qx
{

/**

    @class   constexpr_flag
    @brief   Constexpr flag class
    @details Returns "Start" at the beginning(test), "Start" with test_and_set and "End" after
    @tparam  Tag   - tag for unique instances 
    @tparam  T     - value type 
    @tparam  Start - start value 
    @tparam  End   - end value
    @author  Khrapov
    @date    14.09.2020

**/
template<typename Tag, typename T = bool, T Start = false, T End = true>
class constexpr_flag
{
private:
    struct Dummy
    {
        friend constexpr void adl_flag(Dummy) noexcept;
    };

    template<T>
    struct Writer
    {
        friend constexpr void adl_flag(Dummy) noexcept
        {
        }
    };

    template<class Dummy, int = (adl_flag(Dummy {}), 0)>
    static constexpr T check(int) noexcept
    {
        return End;
    }

    template<class Dummy>
    static constexpr T check(short) noexcept
    {
        return Start;
    }

public:
    template<class Dummy = Dummy, T Value = check<Dummy>(0)>
    static constexpr T test_and_set() noexcept
    {
        Writer<Value && 0> tmp {};
        (void)tmp;
        return Value;
    }

    template<class Dummy = Dummy, T Value = check<Dummy>(0)>
    static constexpr T test() noexcept
    {
        return Value;
    }
};

} // namespace qx
