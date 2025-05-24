/**

    @file      filters.h
    @author    Khrapov
    @date      3.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <functional>

namespace qx
{
template<class T>
using filter = std::function<bool(const T&)>;

namespace filters
{

constexpr auto always_true = [](const auto&...)
{
    return true;
};

} // namespace filters

} // namespace qx
