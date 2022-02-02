/**

    @file      pvs_config.h
    @brief     File contains PVS-Studio configuration comments
    @details   Include this file in your PCH
    @author    Khrapov
    @date      2.02.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

// Implicit assignment type conversion to memsize type
// too pedantic warning
//-V::101

// Call of function with variable number of arguments. N argument has memsize type
// assume we use 64bit only
//-V::111

// Dangerous magic number N used
// too pedantic warning
//-V::112

// Implicit type conversion from memsize to double type or vice versa
// too pedantic warning
//-V::113

// Memsize type is used in the struct/class
// assume we use 64bit only
//-V::122

// Be advised that the size of the type 'long' varies between LLP64/LP64 data models
// assume we use 64bit only
//-V::126

// Explicit conversion from 32-bit integer type to memsize type
// too pedantic warning
//-V::201

// Explicit conversion from memsize type to 32-bit integer type
// too pedantic warning
//-V::202

// Explicit type conversion from memsize to double type or vice versa
// too pedantic warning
//-V::203

// The switch statement does not cover all values
// valid in most cases
//-V::719
