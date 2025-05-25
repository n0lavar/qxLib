/**

    @file      string_literal.h
    @author    Khrapov
    @date      10.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_view.h>

#include <algorithm>

namespace qx
{

/**

    @struct  string_literal
    @brief   Literal wrapper for a constant expression string
    @details Uses implicit conversion to allow templates to *seemingly*
             accept constant strings like IsAnswer<"42">()
    @tparam  char_t - char type
    @tparam  N      - char array length
    @author  Khrapov
    @date    10.09.2021

**/
template<class char_t, size_t N>
struct string_literal
{
    constexpr string_literal(const char_t (&str)[N]) noexcept
    {
        std::copy_n(str, N, value);
    }

    static constexpr size_t size() noexcept
    {
        return N;
    }

    constexpr const char_t* data() const noexcept
    {
        return &value[0];
    }

    constexpr basic_string_view<char_t> view() const noexcept
    {
        return basic_string_view<char_t>(data());
    }

    char_t value[N];
};

} // namespace qx
