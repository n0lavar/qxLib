/**

    @file      constexpr_flag.h
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
    @tparam  tag_t - tag for unique instances 
    @tparam  T     - value type 
    @tparam  Start - start value 
    @tparam  End   - end value
    @author  Khrapov
    @date    14.09.2020

**/
template<class tag_t, class T = bool, T Start = false, T End = true>
class constexpr_flag
{
private:
    struct dummy
    {
        friend constexpr void adl_flag(dummy) noexcept;
    };

    template<T>
    struct writer
    {
        friend constexpr void adl_flag(dummy) noexcept
        {
        }
    };

    template<class dummy_t, int = (adl_flag(dummy_t {}), 0)>
    static constexpr T check(int) noexcept
    {
        return End;
    }

    template<class dummy_t>
    static constexpr T check(short) noexcept
    {
        return Start;
    }

public:
    template<class dummy_t = dummy, T Value = check<dummy_t>(0)>
    static constexpr T test_and_set() noexcept
    {
        writer<Value && 0> tmp {};
        (void)tmp;
        return Value;
    }

    template<class dummy_t = dummy, T Value = check<dummy_t>(0)>
    static constexpr T test() noexcept
    {
        return Value;
    }
};

} // namespace qx
