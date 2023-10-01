/**

    @file      ref.h
    @author    Khrapov
    @date      23.09.2023
    @copyright © Nick Khrapov, 2023. All right reserved.

**/
#pragma once

namespace qx
{

/**
    @brief   Get a reference to default construct a reference
    @details This function is useful when you cannot initialise a reference when creating an object,
             but once it is initialised you can guarantee the validity of the reference
    @tparam  T - reference type
    @retval    - stub reference. do not try to use it as it is invalid
**/
template<class T>
inline T& ref()
{
    static char temp;
    return reinterpret_cast<T&>(temp);
}

} // namespace qx
