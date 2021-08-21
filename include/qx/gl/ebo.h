/**

    @file      ebo.h
    @brief     Contains qx::base_ebo class
    @author    Khrapov
    @date      19.01.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/gl/buffer_base.h>

namespace qx
{

/**

    @class   qx::base_ebo
    @brief   Base EBO class
    @details ~

    @author  Khrapov
    @date    10.07.2020

**/
class base_ebo : public buffer_base
{
protected:
    QX_DECL_BUFFER_BASE
};

using ebo = base_ebo;

} // namespace qx

#include <qx/gl/ebo.inl>
