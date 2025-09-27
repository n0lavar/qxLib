/**

    @file      coalesce.h
    @author    Khrapov
    @date      10.06.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/algo/predicates.h>
#include <qx/meta/type_traits.h>

#include <optional>
#include <type_traits>

namespace qx
{

/**
    @brief   Coalesce function, C# `a ?? b` analogue
    @details Different types version. The result will be cast to return_t.
    @tparam  return_t - type to cast the result to
    @tparam  args_t   - parameters types, can be different
    @param   args     - template parameter pack
    @retval           - the first valid object or the last one
**/
template<class return_t, class... args_t>
constexpr return_t coalesce(args_t&&... args);

/**
    @brief  Coalesce function, C# `a ?? b` analogue
    @tparam args_t - parameters types, must be the same
    @param  args   - template parameter pack
    @retval        - the first valid object or the last one
**/
template<class... args_t>
    requires(same_variadic_args_v<args_t...>)
constexpr auto coalesce(args_t&&... args);

} // namespace qx

#include <qx/coalesce.inl>
