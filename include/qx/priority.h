/**

    @file      priority.h
    @author    Khrapov
    @date      3.12.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

#include <qx/containers/flags.h>
#include <qx/hash.h>
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

    @class   time_ordered_priority_key
    @brief   A class that can be used as a key in ordered containers
             so that items are ordered in descending order of priority but ascending order of creation time.
    @author  Khrapov
    @date    10.08.2025

**/
class time_ordered_priority_key
{
    friend std::hash<time_ordered_priority_key>;

public:
    constexpr time_ordered_priority_key() noexcept = default;

    /**
        @brief time_ordered_priority_key object constructor
        @param ePriority - key priority
    **/
    time_ordered_priority_key(priority ePriority) noexcept;

    /**
        @brief  Get key priority
        @retval  - key priority
    **/
    priority get_priority() const noexcept;

    /**
        @brief Set key priority
        @param ePriority - key priority
    **/
    constexpr void set_priority(priority ePriority) noexcept;

    constexpr bool operator==(const time_ordered_priority_key&) const noexcept = default;
    constexpr auto operator<(const time_ordered_priority_key& other) const noexcept;

private:
    static inline std::atomic_size_t m_nIdCounter { 0 };
    priority                         m_ePriority = priority::normal;
    size_t                           m_nId       = 0;
};

inline time_ordered_priority_key::time_ordered_priority_key(priority ePriority) noexcept
    : m_ePriority(ePriority)
    , m_nId(++m_nIdCounter)
{
}

inline priority time_ordered_priority_key::get_priority() const noexcept
{
    return m_ePriority;
}

constexpr void time_ordered_priority_key::set_priority(priority ePriority) noexcept
{
    m_ePriority = ePriority;
}

constexpr auto time_ordered_priority_key::operator<(const time_ordered_priority_key& other) const noexcept
{
    if (m_ePriority != other.m_ePriority)
        return m_ePriority > other.m_ePriority;
    else
        return m_nId < other.m_nId;
}

} // namespace qx

constexpr auto operator<=>(qx::priority eLeft, qx::priority eRight)
{
    return static_cast<u8>(eLeft) <=> static_cast<u8>(eRight);
}

template<>
struct std::hash<qx::time_ordered_priority_key>
{
    constexpr size_t operator()(const qx::time_ordered_priority_key& timeOrderedPriorityKey) const noexcept
    {
        size_t nHash = 0;
        qx::hash_combine(nHash, timeOrderedPriorityKey.m_nId);
        qx::hash_combine(nHash, timeOrderedPriorityKey.m_ePriority);
        return nHash;
    }
};
