/**

    @file      data.h
    @author    Khrapov
    @date      11.08.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/math/units/base.h>

#include <qx/math/common.h>

#include <algorithm>

namespace qx::units
{

enum class data
{
    // binary prefixes

    bits      = 0,  // 2^0 bits (1 bit)
    nibbles   = 2,  // 2^1 bits (4 bits)
    bytes     = 3,  // 2^3 bits (8 bits)
    kibibytes = 13, // 2^13 bits (1024 bytes)
    mebibytes = 23, // 2^23 bits (1024 kibibytes)
    gibibytes = 33, // 2^33 bits (1024 mebibytes)
    tebibytes = 43, // 2^43 bits (1024 gibibytes)
    pebibytes = 53, // 2^53 bits (1024 tebibytes)

    _last_binary,

    // multiplicative prefixes

    kilobytes = _last_binary + 3,  // 10^3 bytes
    megabytes = _last_binary + 6,  // 10^6 bytes (1000 kilobytes)
    gigabytes = _last_binary + 9,  // 10^9 bytes (1000 megabytes)
    terabytes = _last_binary + 12, // 10^12 bytes (1000 gigabytes)
    petabytes = _last_binary + 15, // 10^15 bytes (1000 terabytes)

    _last_multiplicative
};

} // namespace qx::units

#include <qx/math/units/data.inl>
