/**

    @file      pvs_config.h
    @brief     File contains PVS-Studio configuration comments
    @details   Include this file in your PCH
    @author    Khrapov
    @date      2.02.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

// Call of function with variable number of arguments. N argument has memsize type
// assume we use 64bit only
//-V::111

// Memsize type is used in the struct/class
// assume we use 64bit only
//-V::122

// Be advised that the size of the type 'long' varies between LLP64/LP64 data models
// assume we use 64bit only
//-V::126

// Explicit type conversion from memsize to double type or vice versa
// we assume that we do not use such large values
//-V::203
