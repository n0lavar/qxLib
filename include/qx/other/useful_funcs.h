//============================================================================
//
//!\file                        useful_funcs.h
//
//!\brief
//!\details     ~
//
//!\author      Khrapov
//!\date        1.11.2019
//!\copyright   (c) Nick Khrapov, 2019. All right reserved.
//
//============================================================================
#pragma once

#include <initializer_list>
#include <algorithm>

#include <qx/other/typedefs.h>

//============================================================================
//!\fn                          SAFE_DELETE<T>
//
//!\brief  safe pointer deleting
//!\param  ptr    - pointer to delete
//!\param  bArray - true if need to use delete[]
//!\author Khrapov
//!\date   17.06.2019
//============================================================================
template<typename T>
inline void SAFE_DELETE(T*& ptr, bool bArray = false)
{
    if (ptr)
    {
        if (!bArray)
            delete ptr;
        else
            delete[] ptr;

        ptr = nullptr;
    }
}

namespace qx
{

//============================================================================
//!\fn                         between<L, R, V>
//
//!\brief  Checks if value is between left and right
//!\param  left  - left value
//!\param  right - right value
//!\param  value - value
//!\retval       - true if so
//!\author Khrapov
//!\date   3.11.2019
//============================================================================
template<typename L, typename R, typename V>
inline bool between(L left, R right, V value)
{
    return (value - left) <= (right - left);
}

template<typename E>
inline bool between_enum(E left, E right, E value)
{
    i64 l = static_cast<i64>(left);
    i64 r = static_cast<i64>(right);
    i64 v = static_cast<i64>(value);
    return between(l, r, v);
}

//============================================================================
//!\fn                          step_to<V, T>
//
//!\brief  Do step to some value
//!\param  val - value
//!\param  to  - value to check
//!\author Khrapov
//!\date   3.11.2019
//============================================================================
template<typename V, typename T>
inline void step_to(V& val, const T& to)
{
    if (val < to)
        val++;
    else if (val > to)
        val--;
}

//============================================================================
//!\fn                                pi
//
//!\brief  Get pi
//!\author Khrapov
//!\date   16.11.2019
//============================================================================
template <typename T = float>
inline constexpr T pi()
{
    return static_cast<T>(3.14159265358979323846264338327950288);
}

}