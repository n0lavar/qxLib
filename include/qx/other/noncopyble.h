//==============================================================================
//
//!\file                       noncopyble.h
//
//!\brief       Contains noncopyble class
//!\details     ~
//
//!\author      Khrapov
//!\date        16.01.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//==============================================================================
#pragma once

#define QX_NONCOPYBLE(name)                         \
        name        (name&&) noexcept   = default;  \
name&   operator=   (name&&) noexcept   = default;  \
        name        (const name&)       = delete;   \
name&   operator=   (const name&)       = delete;
