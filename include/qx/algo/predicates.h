/**

    @file      predicates.h
    @author    Khrapov
    @date      26.08.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#pragma once

namespace qx::predicates
{

template<class T>
struct validator
{
    static constexpr bool is_valid(const T& value) noexcept
    {
        return static_cast<bool>(value);
    }
};

template<class T>
constexpr bool is_valid(const T& value) noexcept
{
    return validator<T>::is_valid(value);
}

} // namespace qx::predicates
