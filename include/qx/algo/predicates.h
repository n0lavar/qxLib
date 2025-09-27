/**

    @file      predicates.h
    @author    Khrapov
    @date      26.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

namespace qx::predicates
{

constexpr auto is_true = []<class T>(const T& value)
{
    return static_cast<bool>(value);
};

} // namespace qx::predicates
