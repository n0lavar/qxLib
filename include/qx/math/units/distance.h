/**

    @file      distance.h
    @author    Khrapov
    @date      24.09.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#pragma once

#include <qx/math/common.h>
#include <qx/math/units/base.h>

namespace qx::units
{

enum class distance
{
    // metric (SI)
    nanometers  = -9, // 10^-9 meters
    micrometers = -6, // 10^-6 meters
    millimeters = -3, // 10^-3 meters
    centimeters = -2, // 10^-2 meters
    decimeters  = -1, // 10^-1 meters
    meters      = 0,
    decameters  = 1,  // 10^1  meters
    hectometers = 2,  // 10^2  meters
    kilometers  = 3,  // 10^3  meters
    megameters  = 6,  // 10^6  meters
    gigameters  = 9,  // 10^9  meters
    terameters  = 12, // 10^12 meters
    petameters  = 15, // 10^15 meters

    _last_metric,

    // imperial
    mils,     // 0.0000254 meters,  0.001 inch
    inches,   // 0.0254    meters
    hands,    // 0.1016    meters,  4     inches
    links,    // 0.201168  meters,  7.92  inches
    feet,     // 0.3048    meters,  12    inches
    yards,    // 0.9144    meters,  3     feet
    rods,     // 5.0292    meters,  5.5   yards
    chains,   // 20.1168   meters,  4     rods
    furlongs, // 201.168   meters,  10    chains
    miles,    // 1609.344  meters,  8     furlongs
    leagues,  // 4828.032  meters,  3     miles

    // sea units
    fathoms,        // 1.8288 meters, 2 yards
    cables,         // 185.2  meters, ~100 fathoms
    nautical_miles, // 1852.0 meters, 10 cables

    // astronomical units
    astronomical_units, // 149597870700 meters
    light_years,        // 9460730472580800 meters
    parsecs,            // 30856775814913673 meters
};

} // namespace qx::units

#include <qx/math/units/distance.inl>
