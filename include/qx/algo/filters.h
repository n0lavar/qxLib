/**

    @file      filters.h
    @author    Khrapov
    @date      3.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

namespace qx::filters
{

constexpr auto always_true = [](const auto&...)
{
    return true;
};

} // namespace qx::filters
