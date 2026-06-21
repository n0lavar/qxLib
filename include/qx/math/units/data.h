/**

    @file      data.h
    @author    Khrapov
    @date      11.08.2025
    @copyright (c) Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/math/common.h>
#include <qx/math/units/base.h>

#include <algorithm>

namespace qx::units
{

enum class data
{
    // binary prefixes (not SI)
    bits      = 0,  // 2^0 bits (1 bit)
    nibbles   = 2,  // 2^1 bits (4 bits)
    bytes     = 3,  // 2^3 bits (8 bits)
    kibibytes = 13, // 2^13 bits (1024 bytes)
    mebibytes = 23, // 2^23 bits (1024 kibibytes)
    gibibytes = 33, // 2^33 bits (1024 mebibytes)
    tebibytes = 43, // 2^43 bits (1024 gibibytes)
    pebibytes = 53, // 2^53 bits (1024 tebibytes)

    _first_si,

    // multiplicative prefixes (SI)
    kilobytes = _first_si + 3,  // 10^3 bytes
    megabytes = _first_si + 6,  // 10^6 bytes (1000 kilobytes)
    gigabytes = _first_si + 9,  // 10^9 bytes (1000 megabytes)
    terabytes = _first_si + 12, // 10^12 bytes (1000 gigabytes)
    petabytes = _first_si + 15, // 10^15 bytes (1000 terabytes)
};

} // namespace qx::units

#include <qx/math/units/data.inl>
