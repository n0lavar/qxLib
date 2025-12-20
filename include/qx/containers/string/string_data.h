/**

    @file      string_data.h
    @author    Khrapov
    @date      8.11.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/sbo/type_sbo.h>

namespace qx
{

template<class string_traits_t>
struct string_dynamic_sbo_traits
{
    using size_type = typename string_traits_t::size_type;
    static constexpr size_type nSBOSize =
        sizeof(typename string_traits_t::value_type) * string_traits_t::small_string_size();
    static constexpr bool bShrinkToFitWhenSmall = string_traits_t::shrink_to_fit_when_small();
};

/**

    @class   string_data
    @brief   Represents string data
    @details Implements small string optimization
    @tparam  string_traits_t - char traits. \see string_traits.h
    @author  Khrapov
    @date    8.11.2020

**/
template<class string_traits_t>
using string_data = bytes_sbo<string_dynamic_sbo_traits<string_traits_t>>;

} // namespace qx
