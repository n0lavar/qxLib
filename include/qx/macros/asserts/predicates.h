/**

    @file      predicates.h
    @author    Khrapov
    @date      27.12.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

/**
    @brief Use this as a condition in any macro above to indicate that this part of your code must never be executed
**/
#define QX_NO_ENTRY !"No entry"

/**
    @brief Use this as a condition in any macro above to indicate that this part of your code is not ready yet
**/
#define QX_NOT_IMPLEMENTED !"Not implemented"

namespace qx::details
{

inline bool hit_once(bool& bHit)
{
    const bool bReturn = bHit;
    bHit               = true;
    return bReturn;
}

} // namespace qx::details

/**
    @def   QX_PREDICATE_HIT_ONCE
    @brief Predicate to add to a condition in any EXPECT macro. When added, a macro will only hit once.
    @note  It must be after the actual condition.
    @code
    QX_EXPECT((a > b || b == 0) || QX_PREDICATE_HIT_ONCE());
    @endcode
**/
#define QX_PREDICATE_HIT_ONCE()          \
    []()                                 \
    {                                    \
        static bool h = false;           \
        return qx::details::hit_once(h); \
    }()
