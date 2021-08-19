/**

    @file      constexpr_sequence.h
    @brief     Contains qx::constexpr_sequence class
    @author    Khrapov
    @date      25.08.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/config.h>

// https://stackoverflow.com/questions/65566935/
// https://developercommunity.visualstudio.com/content/problem/1300886/possible-error-in-compiler-with-cpp20.html
#define QX_CONSTEXPR_SEQUENCE_SUPPORTED !QX_MSVC

#if QX_CONSTEXPR_SEQUENCE_SUPPORTED

    #include <qx/meta/constexpr_flag.h>

namespace qx
{

/**

    @class   qx::constexpr_sequence<Tag, T, Start, Func>

    @brief   Constexpr sequence. use unique tag for different instances
    @details Modified version of Anthony Williams constexpr counter
             https://stackoverflow.com/a/58200261/8021662
             \see examples in tests\test_constexpr_sequence.cpp
             \note that you can't vary other template parameters with same Tag
             prefer using "using my_sequence = qx::constexpr_sequence<...>"

    @tparam  Tag   - tag for unique instances
    @tparam  T     - value type
    @tparam  Start - start value
    @tparam  Func  - function that modifies value
    @author  Khrapov
    @date    25.08.2020

**/
template<class Tag, typename T, T Start, T Func(T)>
class constexpr_sequence
{
private:
    template<T nIndex>
    struct Element
    {
        static constexpr T value(void) noexcept
        {
            T _value = Start;

            for (std::size_t i = 0; i < nIndex; i++)
                _value = Func(_value);

            return _value;
        }
    };

    template<std::size_t nCurrent, bool bWasSet /* = false */>
    struct CheckerSetter
    {
        static constexpr std::size_t index(void) noexcept
        {
            return nCurrent;
        }
    };

    template<T nCurrent>
    struct CheckerWrapper
    {
        template<
            bool        bWasSet = constexpr_flag<Element<nCurrent>> {}.test(),
            std::size_t nNext   = CheckerSetter<nCurrent, bWasSet> {}.index()>
        static constexpr std::size_t index(void) noexcept
        {
            return nNext;
        }
    };

    template<std::size_t nCurrent>
    struct CheckerSetter<nCurrent, /* bool bWasSet = */ true>
    {
        template<std::size_t nNext = CheckerWrapper<nCurrent + 1> {}.index()>
        static constexpr std::size_t index(void) noexcept
        {
            return nNext;
        }
    };

public:
    /**
        @brief   Get current sequence value
        @details As function works through generating new template instance each time,
                 return value will be the same for each code line. That means in loops
                 you will get same value each time. Use macros like BOOST_PP_REPEAT
                 to simplify the code
        @tparam  nIndex - current sequence index
        @tparam  _value - current sequence value
        @retval         - current sequence value
    **/
    template<
        std::size_t nIndex = CheckerWrapper<0> {}.index(),
        T           _value = Element<nIndex> {}.value()>
    static constexpr T value(void) noexcept
    {
        return _value;
    }

    /**
        @brief   Change value by Func and return new value
        ¹details As function works through generating new template instance each time,
                 return value will be the same for one code line. That means in loops
                 you will get same value each time. Use macros like BOOST_PP_REPEAT
                 to simplify the code
        @tparam  nIndex - current sequence index
        @tparam  _value - current sequence value
        @tparam  bStub  - stub parameter
        @retval         - next sequence value
    **/
    template<
        std::size_t nIndex = CheckerWrapper<0> {}.index(),
        T           _value = Element<nIndex> {}.value(),
        bool        bStub  = constexpr_flag<Element<nIndex>> {}.test_and_set()>
    static constexpr T next(void) noexcept
    {
        return Func(_value);
    }
};

namespace detail
{

template<typename T, T INC>
constexpr T increase(T val)
{
    return val + INC;
}

template<typename T, T MULT>
constexpr T multiply(T val)
{
    return val * MULT;
}

} // namespace detail

template<
    typename Tag = struct CounterTag,
    typename T   = int,
    T Start      = 0,
    T Inc        = 1>
using constexpr_counter =
    constexpr_sequence<Tag, T, Start, detail::increase<T, Inc>>;

template<
    typename Tag = struct MultiplierTag,
    typename T   = int,
    T Start      = 1,
    T Mult       = 2>
using constexpr_multiplier =
    constexpr_sequence<Tag, T, Start, detail::multiply<T, Mult>>;

} // namespace qx

#endif
