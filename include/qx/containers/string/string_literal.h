/**

    @file      string_literal.h
    @brief     Contains string_literal class
    @author    Khrapov
    @date      10.09.2021
    @copyright � Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <algorithm>
#include <string_view>

namespace qx
{

/**

    @struct  string_literal
    @brief   Literal wrapper for a constant expression string
    @details Uses implicit conversion to allow templates to *seemingly*
             accept constant strings like IsAnswer<"42">()
    @tparam  T - char type
    @tparam  N - char array length
    @author  Khrapov
    @date    10.09.2021

**/
template<typename T, size_t N>
struct string_literal
{
    constexpr string_literal(const T (&str)[N]) noexcept
    {
        std::copy_n(str, N, value);
    }

    static constexpr size_t size(void) noexcept
    {
        return N;
    }

    constexpr const T* data() const noexcept
    {
        return &value[0];
    }

    constexpr std::basic_string_view<T> view() const noexcept
    {
        return std::basic_string_view<T>(data());
    }

    T value[N];
};

} // namespace qx