/**

    @file      constexpr_sequence.h
    @author    Khrapov
    @date      25.08.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/macros/config.h>

// https://stackoverflow.com/questions/65566935/
// https://developercommunity.visualstudio.com/content/problem/1300886/possible-error-in-compiler-with-cpp20.html
#define QX_CONSTEXPR_SEQUENCE_SUPPORTED !QX_MSVC

#if QX_CONSTEXPR_SEQUENCE_SUPPORTED

    #include <qx/meta/constexpr_flag.h>

namespace qx
{

/**

    @class   constexpr_sequence
    @brief   Constexpr sequence. use unique tag for different instances
    @details Modified version of Anthony Williams constexpr counter
             https://stackoverflow.com/a/58200261/8021662
             \see examples in tests\test_constexpr_sequence.cpp
             \note that you can't vary other template parameters with same Tag
             prefer using "using my_sequence = qx::constexpr_sequence<...>"
    @tparam  tag_t - tag for unique instances
    @tparam  T     - value type
    @tparam  Start - start value
    @tparam  Func  - function that modifies value
    @author  Khrapov
    @date    25.08.2020

**/
template<class tag_t, class T, T Start, T Func(T)>
class constexpr_sequence
{
private:
    template<size_t nIndex>
    struct element
    {
        static constexpr T value() noexcept
        {
            T _value = Start;

            for (size_t i = 0; i < nIndex; ++i)
                _value = Func(_value);

            return _value;
        }
    };

    template<size_t nIndex>
    using element_flag = constexpr_flag<element<nIndex>>;

    template<size_t nCurrent, bool bWasSet /* = false */>
    struct checker_setter
    {
        static constexpr size_t index() noexcept
        {
            return nCurrent;
        }
    };

    template<size_t nCurrent>
    struct checker_wrapper
    {
        template<
            bool   bWasSet = element_flag<nCurrent> {}.test(),
            size_t nNext   = checker_setter<nCurrent, bWasSet> {}.index()>
        static constexpr size_t index() noexcept
        {
            return nNext;
        }
    };

    template<size_t nCurrent>
    struct checker_setter<nCurrent, /* bool bWasSet = */ true>
    {
        template<size_t nNext = checker_wrapper<nCurrent + 1> {}.index()>
        static constexpr size_t index() noexcept
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
    template<size_t nIndex = checker_wrapper<0> {}.index(), T _value = element<nIndex> {}.value()>
    static constexpr T value() noexcept
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
        size_t nIndex = checker_wrapper<0> {}.index(),
        T      _value = element<nIndex> {}.value(),
        bool   bStub  = element_flag<nIndex> {}.test_and_set()>
    static constexpr T next() noexcept
    {
        return Func(_value);
    }
};

namespace details
{

template<class T, T Term>
constexpr T increase(T val)
{
    return val + Term;
}

template<class T, T Multiplier>
constexpr T multiply(T val)
{
    return val * Multiplier;
}

} // namespace details

template<class tag_t = struct counter_tag, class T = int, T Start = 0, T Term = 1>
using constexpr_counter = constexpr_sequence<tag_t, T, Start, details::increase<T, Term>>;

template<class tag_t = struct multiplier_tag, class T = int, T Start = 1, T Multiplier = 2>
using constexpr_multiplier = constexpr_sequence<tag_t, T, Start, details::multiply<T, Multiplier>>;

} // namespace qx

#endif
