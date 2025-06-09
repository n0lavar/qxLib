/**

    @file      priority.h
    @author    Khrapov
    @date      3.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/flags.h>
#include <qx/typedefs.h>

namespace qx
{

/**
    @enum  priority
    @brief User may use the predefined values or the custom ones, for ex. "normal - 1",
           this type is supposed to be compared relatively and not for equality
    @note  The base type of this enum is u8,
           and lowest will always be the lowest value and highest will be the highest.
           You should use std::greater<qx::priority> as a predicate in ordered containers to iterate them with decreasing priority.
**/
enum class priority : u8
{
    lowest    = 0,
    very_low  = 32,
    low       = 64,
    normal    = 128,
    high      = 160,
    very_high = 224,
    highest   = 255,
};

/**
    @struct time_ordered_priority_key
    @brief  A structure that can be used as a key in ordered containers
            so that items are ordered in descending order of priority but ascending order of creation time.
**/
struct time_ordered_priority_key
{
    priority ePriority = priority::normal;
    size_t   nId       = ++nIdCounter;

    constexpr bool operator==(const time_ordered_priority_key&) const noexcept = default;
    constexpr auto operator<(const time_ordered_priority_key& other) const noexcept
    {
        if (ePriority != other.ePriority)
            return ePriority > other.ePriority;
        else
            return nId < other.nId;
    }

private:
    static inline std::atomic_size_t nIdCounter { 0 };
};

} // namespace qx

constexpr auto operator<=>(qx::priority eLeft, qx::priority eRight)
{
    return static_cast<u8>(eLeft) <=> static_cast<u8>(eRight);
}
